#include "tester.h"

Tester::Tester()
{

}

void Tester::testMatrixClass()
{
    std::cout << "Matrix Class Tester\n" << std::endl;
    Matrix4x4 m(1, 1, 2, 3,
                4, 5, 6, 5,
                4, 6, 4, 6,
                1, 8, 3, 6);
    std::cout << "Matrix4x4 m:\n" << m << std::endl;
    std::cout << "m * 2: \n" << m*2 << std::endl;


    Matrix4x4 mInv;
    m.inverse(mInv);
    std::cout << "Inverse of m:\n" << mInv << std::endl;
    std::cout << "inv(m) * m: \n" << mInv*m << std::endl;

    Matrix4x4 mPrime;
    mInv.inverse(mPrime);
    std::cout << "Inverse of the inverse of m (i.e., m):\n" << mPrime << std::endl;

    Matrix4x4 mTranspose;
    mPrime.transpose(mTranspose);
    std::cout << "Transpose of m:\n" << mTranspose << std::endl;

    std::cout << "m + (m)^T:\n" << m + mTranspose << std::endl;
    std::cout << "m :\n"        << m << std::endl;
    std::cout << "m - (m)^T:\n" << m - mTranspose << std::endl;

    std::cout << "Matrix Vector Operations:\n" << std::endl;
    Vector3D v(1, -2, 3);
    std::cout << "Vector3D v = " << v << "\n" << std::endl;
    Matrix4x4 id;
    std::cout << "id matrix:\n" << id << std::endl;
    std::cout << "id.transformVector(v) = " <<
                 id.transformVector(v) << std::endl;
    std::cout << "id.transformPoint(v) = " <<
                 id.transformPoint(v) << "\n" << std::endl;

    Matrix4x4 id2 = id * 2;
    std::cout << "id2 = id * 2:\n" << id2 << std::endl;

    std::cout << "id2.transformVector(v) = " <<
                 id2.transformVector(v) << std::endl;
    std::cout << "id2.transformPoint(v) = " <<
                 id2.transformPoint(v) << "\n" << std::endl;

    std::cout << "Testing transformations:\n" << std::endl;
    Vector3D delta(4, 7, -5);
    Matrix4x4 t = Matrix4x4::translate(delta);
    std::cout << "Create a translation matrix t from vector delta = "
              << delta << ":\n" << t << std::endl;
    std::cout << "Result of translating the vector delta by delta: "
              << t.transformVector(delta) << std::endl;
    std::cout << "Result of translating the point delta by delta: "
              << t.transformPoint(delta) << std::endl;

    Vector3D scalingVector(2, 2, -2);
    Matrix4x4 s = Matrix4x4::scale(scalingVector);
    std::cout << "\nCreate a scale matrix s from vector scalingVector = "
              << scalingVector << ":\n" << s << std::endl;
    std::cout << "Result of scaling the vector scalingVector by scalingVector: "
              << s.transformVector(scalingVector) << std::endl;
    std::cout << "Result of translating the point scalingVector by scalingVector: "
              << s.transformPoint(scalingVector) << std::endl;

    std::cout << "\nTransformation matrix resulting from translating and then scaling (s*t):\n"
              << s*t << std::endl;
    std::cout << "(s*t).transformVector(Vector3D(1,1,1)) = " << (s*t).transformVector(Vector3D(1,1,1)) << std::endl;
    std::cout << "(s*t).transformPoint(Vector3D(1,1,1)) = " << (s*t).transformPoint(Vector3D(1,1,1)) << std::endl;

    std::cout << "\nTransformation matrix resulting from scaling and then translating (t*s):\n"
              << t*s << std::endl;
    std::cout << "(t*s).transformVector(Vector3D(1,1,1)) = " << (t*s).transformVector(Vector3D(1,1,1)) << std::endl;
    std::cout << "(t*s).transformPoint(Vector3D(1,1,1)) = " << (t*s).transformPoint(Vector3D(1,1,1)) << std::endl;


    Vector3D axis(0, 1, 0);
    double angle = 45.0 * 3.14159 / 180.0;
    Matrix4x4 r = Matrix4x4::rotate(angle, axis);
    std::cout << "\nCreate a rotation matrix r of " << angle << " rads around "
              << axis << ":\n" << r << std::endl;

}
