#ifndef EQSOLVER_H
#define EQSOLVER_H

// Auxiliar structure for storing the roots of polynomials up
// to a degree 2
struct rootValues
{
    unsigned int nValues;
    double values[2];
};


class EqSolver
{
public:
    EqSolver();

    bool rootLinEq(double c1, double c0, rootValues &res);
    bool rootQuadEq(double c2, double c1, double c0, rootValues &res);

    void testerRootLinearEq(double c1, double c0);
    void testerRootQuadEq(double c2, double c1, double c0);
};

#endif // EQSOLVER_H
