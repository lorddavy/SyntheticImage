#include "matrix4x4.h"

Matrix4x4::Matrix4x4()
{
    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++ )
        {
            if(lin == col)
            {
                data[lin][col] = 1;
            } else
            {
                data[lin][col] = 0;
            }
        }
    }
}

Matrix4x4::Matrix4x4(double data_[4][4])
{
    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++ )
        {
            data[lin][col] = data_[lin][col];
        }
    }
}

Matrix4x4::Matrix4x4( double a00, double a01, double a02, double a03,
           double a10, double a11, double a12, double a13,
           double a20, double a21, double a22, double a23,
           double a30, double a31, double a32, double a33)
{
    data[0][0] = a00; data[0][1] = a01; data[0][2] = a02; data[0][3] = a03;
    data[1][0] = a10; data[1][1] = a11; data[1][2] = a12; data[1][3] = a13;
    data[2][0] = a20; data[2][1] = a21; data[2][2] = a22; data[2][3] = a23;
    data[3][0] = a30; data[3][1] = a31; data[3][2] = a32; data[3][3] = a33;
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4 &m) const
{
    Matrix4x4 sum;

    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++)
        {
            sum.data[lin][col] = data[lin][col] + m.data[lin][col];
        }
    }

    return sum;
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4 &m) const
{
    Matrix4x4 sum;

    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++)
        {
            sum.data[lin][col] = data[lin][col] - m.data[lin][col];
        }
    }

    return sum;
}

// Product between two matrices 4x4
// res(lin, col) = inner product of this.data(lin,:)
//                  with m.data(:,col)
// Given the current matrix m1 and a second matrix m2, returns a matrix
// res which, applied to an object (e.g., a point p) is equal to m1(m2(p))
Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &m) const
{
    Matrix4x4 res;

    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++)
        {
            res.data[lin][col] = data[lin][0] * m.data[0][col] +
                                 data[lin][1] * m.data[1][col] +
                                 data[lin][2] * m.data[2][col] +
                                 data[lin][3] * m.data[3][col];
        }
    }
    return res;
}

Matrix4x4 Matrix4x4::operator*(const double a) const
{
    Matrix4x4 res;

    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++)
        {
            res.data[lin][col] = data[lin][col]*a;
        }
    }
    return res;
}

// CHANGE THE TEXT BELOW
// This operator assumes that Vector3D are implicitly represented
// through homogeneous coordinates [vx, vy, vz, 0]
Vector3D Matrix4x4::transformVector(const Vector3D &v) const
{
    double xTransformed, yTransformed, zTransformed;

    xTransformed = data[0][0] * v.x +
                   data[0][1] * v.y +
                   data[0][2] * v.z;

    yTransformed = data[1][0] * v.x +
                   data[1][1] * v.y +
                   data[1][2] * v.z;

    zTransformed = data[2][0] * v.x +
                   data[2][1] * v.y +
                   data[2][2] * v.z;

    return Vector3D(xTransformed, yTransformed, zTransformed);
}

// This operator assumes that Point3D are implicitly represented
// through homogeneous coordinates [px, py, pz, 1]
Vector3D Matrix4x4::transformPoint(const Vector3D &p) const
{
    double xTransformed, yTransformed,
           zTransformed, wTransformed;

    xTransformed = data[0][0] * p.x + data[0][1] * p.y +
                   data[0][2] * p.z + data[0][3];

    yTransformed = data[1][0] * p.x + data[1][1] * p.y +
                   data[1][2] * p.z + data[1][3];

    zTransformed = data[2][0] * p.x + data[2][1] * p.y +
                   data[2][2] * p.z + data[2][3];

    wTransformed = data[3][0] * p.x + data[3][1] * p.y +
                   data[3][2] * p.z + data[3][3];

    if (wTransformed == 1.0)
    {
        return Vector3D(xTransformed, yTransformed, zTransformed);
    } else
    {
        if (wTransformed == 0.0)
            std::cout << "Problem! wTransformed = 0 in Matrix4x4::operator*(const Point3D &p)" << std::endl;
        return Vector3D(xTransformed, yTransformed, zTransformed) / wTransformed;
    }
}

Ray Matrix4x4::transformRay(const Ray &r) const
{
    Ray transformedRay = r;
    Vector3D transformedOrigin = transformPoint(r.o);
    Vector3D transformedDir    = transformVector(r.d);

    transformedRay.o = transformedOrigin;
    transformedRay.d = transformedDir;

    return transformedRay;
}

//Normal Matrix4x4::operator*(const Normal &n) const
//{
//    double xTransformed, yTransformed, zTransformed;

//    xTransformed = data[0][0] * n.x +
//                   data[0][1] * n.y +
//                   data[0][2] * n.z;

//    yTransformed = data[1][0] * n.x +
//                   data[1][1] * n.y +
//                   data[1][2] * n.z;

//    zTransformed = data[2][0] * n.x +
//                   data[2][1] * n.y +
//                   data[2][2] * n.z;

//    return Normal(xTransformed, yTransformed, zTransformed);
//}

std::string Matrix4x4::toString() const
{
    std::stringstream s;

    auto oldPrecision = s.precision(3);
    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++)
        {
            s << data[lin][col] << "\t";
        }
        s << std::endl;
    }
    s.precision(oldPrecision);
    return s.str();
}

// Compute the inverse of a square matrix using the Gauss-Jordan algorithm
// To find the inverse of matrix A, using Gauss-Jordan elimination, we must
// find a sequence of elementary row operations that reduces A to the identity
// and then perform the same operations on In to obtain A-1.
// The "Elementary Row Operations" are simple things like adding rows, multiplying and swapping
// Strongly inspired in the pbrt and mitsuba's implementations of the method
//  Check http://matrix.reshish.com/inverCalculation.php
//   for a visual example
bool Matrix4x4::inverse(Matrix4x4 &target) const
{
    int indxc[4], indxr[4];
    int ipiv[4] = { 0, 0, 0, 0 };
    //double minv[4][4];
    memcpy(target.data, data, 4*4*sizeof(double));
    for (int i = 0; i < 4; i++) {
        int irow = -1, icol = -1;
        double big = 0.;
        // Choose pivot
        for (int j = 0; j < 4; j++) {
            if (ipiv[j] != 1) {
                for (int k = 0; k < 4; k++) {
                    if (ipiv[k] == 0) {
                        if (std::abs(target.data[j][k]) >= big) {
                            big = std::abs(target.data[j][k]);
                            irow = j;
                            icol = k;
                        }
                    }
                    else if (ipiv[k] > 1) {
                        std::cout << "Error: Singular matrix in MatrixInvert" << std::endl;
                        return false;
                    }
                }
            }
        }
        ++ipiv[icol];
        // Swap rows _irow_ and _icol_ for pivot
        if (irow != icol) {
            for (int k = 0; k < 4; ++k)
                std::swap(target.data[irow][k], target.data[icol][k]);
        }
        indxr[i] = irow;
        indxc[i] = icol;
        if (target.data[icol][icol] == 0.) {
            std::cout << "Error: Singular matrix in MatrixInvert" << std::endl;
            return false;
        }

        // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
        double pivinv = 1.0 / target.data[icol][icol];
        target.data[icol][icol] = 1.0;
        for (int j = 0; j < 4; j++)
            target.data[icol][j] *= pivinv;

        // Subtract this row from others to zero out their columns
        for (int j = 0; j < 4; j++) {
            if (j != icol) {
                double save = target.data[j][icol];
                target.data[j][icol] = 0;
                for (int k = 0; k < 4; k++)
                    target.data[j][k] -= target.data[icol][k]*save;
            }
        }
    }
    // Swap columns to reflect permutation
    for (int j = 3; j >= 0; j--) {
        if (indxr[j] != indxc[j]) {
            for (int k = 0; k < 4; k++)
                std::swap(target.data[k][indxr[j]], target.data[k][indxc[j]]);
        }
    }
    return true;
}


void Matrix4x4::setToZeros()
{
    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++ )
        {
            data[lin][col] = 0;
        }
    }
}

void Matrix4x4::transpose(Matrix4x4 &target) const
{
    for(size_t lin=0; lin<4; lin++)
    {
        for(size_t col=0; col<4; col++)
        {
            target.data[lin][col] = data[col][lin];
        }
    }
}

// static method implementation
Matrix4x4 Matrix4x4::translate(const Vector3D &delta)
{
    Matrix4x4 m(1, 0, 0, delta.x,
                0, 1, 0, delta.y,
                0, 0, 1, delta.z,
                0, 0, 0, 1);

    return m;
}

// static method implementation
Matrix4x4 Matrix4x4::scale(const Vector3D &scalingVector)
{
    Matrix4x4 m(scalingVector.x, 0, 0, 0,
                0, scalingVector.y, 0, 0,
                0, 0, scalingVector.z, 0,
                0, 0, 0, 1);
    return m;
}

// static method implementation
Matrix4x4 Matrix4x4::rotate(const double angleInRad, const Vector3D &axis)
{
    Vector3D a = axis.normalized();
    double s = std::sin(angleInRad);
    double c = std::cos(angleInRad);
    double m[4][4];
    m[0][0] = a.x * a.x + (1.0 - a.x * a.x) * c;
    m[0][1] = a.x * a.y * (1.0 - c) - a.z * s;
    m[0][2] = a.x * a.z * (1.0 - c) + a.y * s;
    m[0][3] = 0;
    m[1][0] = a.x * a.y * (1.0 - c) + a.z * s;
    m[1][1] = a.y * a.y + (1.0 - a.y * a.y) * c;
    m[1][2] = a.y * a.z * (1.0 - c) - a.x * s;
    m[1][3] = 0;
    m[2][0] = a.x * a.z * (1.0 - c) - a.y * s;
    m[2][1] = a.y * a.z * (1.0 - c) + a.x * s;
    m[2][2] = a.z * a.z + (1.0 - a.z * a.z) * c;
    m[2][3] = 0;
    m[3][0] = 0;
    m[3][1] = 0;
    m[3][2] = 0;
    m[3][3] = 1;
    Matrix4x4 mat(m);

    return mat;
}

ostream& operator<<(ostream &out, const Matrix4x4 &m)
{

    out << m.toString();
    return out;
}
