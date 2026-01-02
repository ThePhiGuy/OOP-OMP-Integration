#ifndef OOINT_HPP
#include <iostream>
#include <vector>
#include <random>
#include <math.h>
#include <omp.h>
#include <immintrin.h>

using namespace std;

struct Term {
    char type;
    double value;
    double exp;
};

class Equation {
    public:
        Equation();
        Equation(const vector<double> &eq, char variable = 'x'); // standard constructor of equation with a vector representation of an equation.
        Equation(const double* equation, int size, char variable = 'x'); // C Type Constructor with an array of doubles and the size of the array.
        Equation(const vector<double> &eq, const vector<char> &types, const vector<double> &exps, char variable = 'x'); // constructor supporting variance in type of each parameter.
        Equation(const vector<double> &eq, const vector<double> &exp, char variable = 'x'); // constructor supporting different exp in equations.

        vector<Term> getEquation() const;
        char getVariable() const;

        void setVariable(char newVar);

        

        double integrate(double a, double b, long trials) const;
        double integrate(double a, double b, long trials, double* error) const;
        double integrateByTolerance(double a, double b, double error) const;

    private:
        vector<Term> myEquation;
        char var;

        void buildEquation(const vector<char> &types, const vector<double> &values, const vector<double> &exponentials);
        double getArea(double a, double b, long trials) const;
};

ostream& operator<<(ostream& lhs, Equation eq);
#endif