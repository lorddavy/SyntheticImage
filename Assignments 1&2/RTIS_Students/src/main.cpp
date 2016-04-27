#include <iostream>
#include <stdlib.h> /* srand, rand */
#include <vector>
#include <algorithm>

#include "core/film.h"
#include "core/matrix4x4.h"
#include "core/ray.h"
#include "core/utils.h"
#include "shapes/sphere.h"
#include "cameras/ortographic.h"
#include "cameras/perspective.h"

void transformationsExercise()
{
    /* *************** */
    /* TRANSFORMATIONS */
    /* *************** */
    std::string separator     = "\n----------------------------------------------\n";
    std::string separatorStar = "\n**********************************************\n";

    std::cout << separatorStar << "Construct and visualize transforms" << separatorStar << std::endl;

    // Identity Matrix
    Matrix4x4 idMat; // By default, a matrix4x4 is initialized with the identity matrix
    std::cout << "The content of matrix idMat is: \n" << std::endl;
    std::cout << idMat << separator << std::endl;

    // Translation Matrix
    double deltaX, deltaY, deltaZ;
    deltaX = 1; deltaY = -2; deltaZ = 3;
    Vector3D delta(deltaX, deltaY, deltaZ);
    Matrix4x4 translationMat = Matrix4x4::translate(delta);
    std::cout << "The content of matrix translationMat is: \n" << std::endl;
    std::cout << translationMat << separator << std::endl;

    // Scale Matrix
	double sX, sY, sZ;
	sX = 2; sY = 1; sZ = -1;
	Vector3D s(sX, sY, sZ);
	Matrix4x4 scaleMat = Matrix4x4::scale(s);
    std::cout << "The content of matrix scaleMatrix is: \n" << std::endl;
    std::cout << scaleMat << separator << std::endl;

    // Rotate around X Matrix
    double angleInDegrees = 60;
    double thetaInRadians = Utils::degreesToRadians(angleInDegrees);
	Vector3D r(1, 0, 0);
	Matrix4x4 rotateXMatrix = Matrix4x4::rotate(thetaInRadians, r);
    std::cout << "The content of matrix rotateXMatrix is: \n" << std::endl;
    std::cout << rotateXMatrix << separator << std::endl;

    // Rotate around an arbitrary axis Matrix
	angleInDegrees = 30;
	thetaInRadians = Utils::degreesToRadians(angleInDegrees);
	r = (1, 1, 1);
	Matrix4x4 rotateArtitraryAxisMatrix = Matrix4x4::rotate(thetaInRadians, r);
    std::cout << "The content of matrix rotateArtitraryAxisMatrix is: \n" << std::endl;
    std::cout << rotateArtitraryAxisMatrix << separator << std::endl;

    // Transposed and Inversion
    std::cout << separatorStar << "Inverting and Transposing a Matrix" << separatorStar << std::endl;
    Matrix4x4 translationMatTransposed;
    translationMat.transpose(translationMatTransposed);
    std::cout << "The transpose of matrix \n\n" << translationMat << "\n is \n\n"
              << translationMatTransposed << separator << std::endl;

    Matrix4x4 inverseTranslationMat;
	translationMat.inverse(inverseTranslationMat);
    std::cout << "The inverse of matrix \n\n" << translationMat << "\n is \n\n" << inverseTranslationMat << std::endl;
    std::cout << "And their multiplication should thus give the identity matrix:\n\n";
    
	std::cout << translationMat.operator*(inverseTranslationMat) << separator << std::endl;

    // Combine here some transforms, and visualize the result
    std::cout << separatorStar << "Combine transforms and visualize the result" << separatorStar << std::endl;

    Matrix4x4 scaleTranslate = (scaleMat.operator*(translationMat));
    std::cout << "The content of matrix scaleTranslate is: \n" << std::endl;
    std::cout << scaleTranslate << separator << std::endl;

    Matrix4x4 translateScale = (translationMat.operator*(scaleMat));
    std::cout << "The content of matrix translateScale is: \n" << std::endl;
    std::cout << translateScale << separator << std::endl;
}

void normalTransformExercise()
{
    std::string separator = "\n----------------------------------------------\n";

    // NOTE: points, vectors and normals are represented, in this framework, using
    //  the Vector3D class. It is up to the programmer to take care of whether the
    //  Vector3D is representing a point, a vector or a normal. For example, when
    //  applying a transform using a Matrix4x4, the programmer must choose which
    //  "applyTransform" method of the namespace Matrix4x4 should be used.

    Vector3D v(1, 1, 0);
    Vector3D n(-1.0/sqrt(2), 1.0/sqrt(2), 0);
    Matrix4x4 S = Matrix4x4::scale(Vector3D(2, 1, 1));

    std::cout << "Vector v = " << v << "\n" << std::endl;
    std::cout << "Normal n = " << n << "\n" << std::endl;
    std::cout << "Scale Matrix: \n" << std::endl;
    std::cout << S << std::endl;

    Vector3D vTransformed = S.transformVector(v);
    std::cout << "Vector v\' = " << vTransformed << "\n" << std::endl;

	Vector3D nTransformed = S.transformVector(n);
	std::cout << "Vector n\' = " << nTransformed << "\n" << std::endl;
	std::cout << "dot(n\', v\') = " << dot(nTransformed, vTransformed) << "\n" << std::endl;

	Matrix4x4 sTransposed;
	Matrix4x4 sTransposedInversed;
	S.transpose(sTransposed);
	sTransposed.inverse(sTransposedInversed);
	
	nTransformed = sTransposedInversed.transformVector(n);
	std::cout << "Vector n\' = " << nTransformed << "\n" << std::endl;
	std::cout << "dot(n\', v\') = " << dot(nTransformed, vTransformed) << "\n" << std::endl;
}

void paintingAnImageExercise()
{
    // Define the film (i.e., image) resolution
    size_t resX, resY;
    resX = 512;
    resY = 512;
    Film film(resX, resY);
	Vector3D v;

	for (int i = 0; i < resY; i++)
	{
		for (int j = 0; j < resX; j++)
		{
			v.x = (i + 0.5) / resX;
			v.y = (j + 0.5) / resY;
			v.z = 0;
			film.setPixelValue(i, j, v);
		}
	}

    // Save the final result to file
    film.save();
}

void filteringAnImageExercise()
{
	// Create two instances of the film class with the same resolution
	int resX, resY;
	resX = 512;
	resY = 512;
	Film f1(resX, resY);
	Film f2(resX, resY);

	Film* original = &f1;
	Film* result = &f2; 
	// Create the original image
	//  Draw a circle centered at centerX, centerY (in pixels, image space)
	//   and with ray r (also in pixels)
	int centerX = resX / 2;
	int centerY = resY / 2;
	int r = std::min(centerX, centerY) / 2;
	for (int lin = 0; lin < resX; lin++)
	{
		for (int col = 0; col < resY; col++)
		{
			// Use the equation of the sphere to determine the pixel color
			if ((lin - centerX)*(lin - centerX) + (col - centerY)*(col - centerY) < r*r)
				f1.setPixelValue(col, lin, Vector3D(1, 1, 0));
		}
	}

	// Filter-related variables
	int filterSize = 9;
	int margin = (filterSize - 1) / 2;
	int numIterations = 100;
	Vector3D color;

	// Implement here your image filtering algorithm
	for (int it = 0; it < numIterations; it++)
	{
		for (int lin = (0 + margin); lin < (resX - margin); lin++)
		{
			for (int col = (0 + margin); col < (resY - margin); col++)
			{
				// Use the filtering to determine the pixel color
				for (int i = -margin; i <= margin; i++)
				{
					for (int j = -margin; j <= margin; j++)
					{
						color += original->getPixelValue(col + j, lin + i);
					}
				}

				color = color / (filterSize*filterSize);
				result->setPixelValue(col, lin, color);
				color = (0, 0, 0);
			}
		}
		original = result;
	}
	// DO NOT FORGET TO SAVE YOUR IMAGE!
	result->save();
}

void completeSphereClassExercise()
{
    // Make your intersection tests here

	Vector3D p(0, 0, 3);
	Matrix4x4 objectToWorld = Matrix4x4::translate(p);
	Sphere s(1, objectToWorld);
	Ray r1(Vector3D(0, 0, 0), Vector3D(0, 0, 1));
	Ray r2(Vector3D(0, 0, 0), Vector3D(0, 1, 0));
	std::string text = "";

	std::cout << "\n" << s << "\n" << std::endl;
	if (s.rayIntersectP(r1))
		text = "True";
	else
		text = "False";

	std::cout << "Testing intersection of Ray r = (0, 0, 0) + (0, 0, 1)t with the sphere:" << std::endl;
	std::cout << "\n" << text << "\n" << std::endl;

	if (s.rayIntersectP(r2))
		text = "True";
	else
		text = "False";

	std::cout << "Testing intersection of Ray r = (0, 0, 0) + (0, 1, 0)t with the sphere:" << std::endl;
	std::cout << "\n" << text << "\n" << std::endl;
}

void eqSolverExercise()
{
    EqSolver solver;
    rootValues roots;

    double A, B, C;

	A = 5;
	B = 6;
	//B = 2;
	C = 1;

    bool hasRoots = solver.rootQuadEq(A, B, C, roots);

    if(!hasRoots)
    {
        std::cout << "Equation has no real roots!" << std::endl;
    }
    else
    {
        // SHOW THE SOLUTIONS OF THE EQUATION	
		std::string text = "";
		double root;
		std::cout << "The number of roots of the equation is: " <<  roots.nValues << std::endl;
		std::cout << "\nThe  roots of the equation are: \n" << text << std::endl;
		for (int i = 0; i < roots.nValues; i++)
		{
			std::cout << roots.values[i] << std::endl;			
		}
    }
}

void raytrace()
{
    // Define the film (i.e., image) resolution
    size_t resX, resY;
    resX = 512;
    resY = 512;
    Film film1(resX, resY);
	Film film2(resX, resY);

	Vector3D p(0, 0, 3);
	Matrix4x4 objectToWorld = Matrix4x4::translate(p);
	Sphere s(1, objectToWorld);
	Ray r1;
	Ray r2;

    /* ******************* */
    /* Orthographic Camera */
    /* ******************* */
    Matrix4x4 cameraToWorld; // By default, this gives an ID transform
                             // meaning that the camera space = world space
    OrtographicCamera camOrtho(cameraToWorld, film1);

	for (float i = 0; i < resY; i++)
	{
		for (float j = 0; j < resX; j++)
		{
			r1 = camOrtho.generateRay(i/(float)resY, j/(float)resX);
			if (s.rayIntersectP(r1))
			{
				film1.setPixelValue(i, j, Vector3D(1, 0, 0));
			}
			else {
				film1.setPixelValue(i, j, Vector3D(0, 0, 0));
			}
			
		}
	}

    /* ******************* */
    /* Perspective Camera */
    /* ******************* */
    double fovRadians = Utils::degreesToRadians(60);
    PerspectiveCamera camPersp(cameraToWorld, fovRadians, film2);

	for (float i = 0; i < resY; i++)
	{
		for (float j = 0; j < resX; j++)
		{
			r2 = camPersp.generateRay(i/(float)resY, j/(float)resX);
			if (s.rayIntersectP(r2))
			{
				film2.setPixelValue(i, j, Vector3D(1, 0, 0));
			}
			else {
				film2.setPixelValue(i, j, Vector3D(0, 0, 0));
			}

		}
	}

    // Save the final result to file
    film1.save();
	film2.save();
}

int main()
{
    std::string separator = "\n----------------------------------------------\n";

    std::cout << separator << "RTIS - Ray Tracer for \"Imatge Sintetica\"" << separator << std::endl;

    // ASSIGNMENT 1
    //transformationsExercise();
    //normalTransformExercise();
    //paintingAnImageExercise();
	//filteringAnImageExercise();

    // ASSIGNMENT 2
    eqSolverExercise();
    completeSphereClassExercise();
    raytrace();

    std::cout << "\n\n" << std::endl;
    return 0;
}
