#include <cmath>
#include <iostream>

#include "eqsolver.h"

EqSolver::EqSolver()
{

}

// Compute the root of a linear equation of type: c1*x + c0 = 0
// (useful for solving intersections of rays with planes, i.e., polygons)
bool EqSolver::rootLinEq(double c1, double c0, rootValues &res)
{
    if (c1 == 0) {
        /* [VERIFY]
         *  case c1 == 0 && c0 == 0
         */
        res.nValues = 0; // No Roots
        return false;
    } else
    {
        // Single solution (Polynomial of degree 1)
        res.nValues   = 1;
        /* [VERIFY]
         *  case c0 >> c1 -> overflow + div by 0
         */
        res.values[0] = -c0/c1;
        return true;
    }
}

// Compute the roots of a quadratic equation of type: c2*x^2 + c1*x + c0 = 0
// (useful for solving intersections of rays with spheres)
bool EqSolver::rootQuadEq(double c2, double c1, double c0, rootValues &res)
{
    if(c2 == 0)
    {
        // This is a linear equation!
        return rootLinEq(c1, c0, res);
    } else
    {
        // Compute the discriminant "d"
        double d = c1*c1 - 4*c2*c0;

        // Get the roots based on the discriminant
        if(d < 0)
        {
            // There are no real roots (only complex!)
            res.nValues = 0;
            return false;
        } else if (d > 0)
        {
            // There are two real roots...
            res.nValues = 2;
            // ... with values:
            res.values[0] = ( -c1 + std::sqrt(d) ) / (2*c2);
            res.values[1] = ( -c1 - std::sqrt(d) ) / (2*c2);
            if(res.values[0] > res.values[1])
            {
                double aux = res.values[0];
                res.values[0] = res.values[1];
                res.values[1] = aux;
            }

        } else
        {
            // There is a single real root
            res.nValues = 1;
            // ... with value:
            res.values[0] = -c1 / (2*c2);
            res.values[1] = -c1 / (2*c2);
        }
        return true;
    }
}

void EqSolver::testerRootLinearEq(double c1, double c0) {

    std::cout << std::endl << "Computing the roots of:" << std::endl;
    std::cout << c1 << "*x + " << c0 << " = 0" << std::endl;

    rootValues roots;
    rootLinEq(c1, c0, roots);

    if(roots.nValues > 0u)
    {
        std::cout << "Result: x = " << roots.values[0] << std::endl;
    } else
    {
        std::cout << "Result: none or infininte solutions!" << std::endl;
    }

}


void EqSolver::testerRootQuadEq(double c2, double c1, double c0) {

    std::cout << std::endl << "Computing the roots of:" << std::endl;
    std::cout << c2 << "*x^2 + " << c1 << "*x + " << c0 << " = 0" << std::endl;

    rootValues roots;
    rootQuadEq(c2, c1, c0, roots);

    if(roots.nValues == 0u)
    {
        std::cout << "Result: no real roots" << std::endl;
    } else if(roots.nValues == 1u)
    {
        std::cout << "Result: single real root with value x = " << roots.values[0] << std::endl;
    } else
    {
        std::cout << "Result: two real roots with value x1 = " << roots.values[0] << " and x2 = " << roots.values[1] << std::endl;
    }
}
