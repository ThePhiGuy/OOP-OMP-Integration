#include "ooint.h"

ostream& operator<<(ostream& lhs, Equation eq) {
    vector<Term> terms = eq.getEquation();
    char variable = eq.getVariable();

    for (int i = 0; i < terms.size(); i++) {
        if (terms[i].type == 'p') {
            if(terms[i].value > 0) {
                lhs << "+" << terms[i].value << variable << "^" << terms[i].exp;
            } else if (terms[i].value < 0){
                lhs << abs(terms[i].value) << variable << "^" << terms[i].exp;
            } else {
                continue;
            }
        } else if (terms[i].type == 's') {
            if(terms[i].exp > 0) {
                lhs << "+" << terms[i].exp << "sin(" << terms[i].value << "*" << variable << ")";
            } else if (terms[i].value < 0){
                lhs << abs(terms[i].exp) << "sin(" << terms[i].value << "*" << variable << ")";
            } else {
                continue;
            }
        } else if (terms[i].type == 'c') {
            if(terms[i].exp > 0) {
                lhs << "+" << terms[i].exp << "cos(" << terms[i].value << "*" << variable << ")";
            } else if (terms[i].exp < 0){
                lhs << terms[i].exp << "cos(" << terms[i].value << "*" << variable << ")";
            } else {
                continue;
            }
        } else if (terms[i].type == 't') {
            if(terms[i].exp > 0) {
                lhs << "+" << terms[i].exp << "tan(" << terms[i].value << "*" << variable << ")";
            } else if (terms[i].exp < 0){
                lhs << terms[i].exp << "tan(" << terms[i].value << "*" << variable << ")";
            } else {
                continue;
            }
        }
    }

    return lhs;
}

vector<Term> Equation::getEquation() const {
    return myEquation;
}

char Equation::getVariable() const {
    return var;
}

void Equation::setVariable(char newVar) {
    var = newVar;
    return;
}
Equation::Equation() {
    var = 'x';
    return;
}

Equation::Equation(const vector<double> &eq, char variable) {
    var = variable;
    vector<double> exp;
    for(int i = eq.size()-1; i>= 0; i--) {
        exp.push_back(i);
    }
    vector<char> types(eq.size(), 'p');
    buildEquation(types, eq, exp);
    return;
}

Equation::Equation(const double* equation, int size, char variable) {
    var = variable;
    vector<double> eq;
    for (int i = 0; i < size; i++) {
        eq.push_back(equation[i]);
    }
    vector<double> exp;
    for(int i = eq.size()-1; i>= 0; i--) {
        exp.push_back(i);
    }
    vector<char> types(exp.size(), 'p');
    buildEquation(types, eq, exp);
}

Equation::Equation(const vector<double> &eq, const vector<char> &types, const vector<double> &exp, char variable) {
    var = variable;
    if (eq.size() != exp.size()) {
        throw invalid_argument("The equation must have identical exp to terms.");
    } else if (eq.size() != types.size()) {
        throw invalid_argument ("there must be an equal number of types compared to terms.");
    }
    buildEquation(types, eq, exp);
}

Equation::Equation(const vector<double> &eq, const vector<double> &exp, char variable) {
    var = variable;
    if (eq.size() != exp.size()) {
        throw invalid_argument("The equation must have identical exp to terms.");
    }
    vector<char> types(exp.size(), 'p');
    buildEquation(types, eq, exp);
}

void Equation::buildEquation(const vector<char> &types, const vector<double> &values, const vector<double> &exponentials) {
    myEquation.clear();
    for (int i = 0; i < types.size(); i++) {
        Term newTerm;
        newTerm.exp = exponentials[i];
        newTerm.type = types[i];
        newTerm.value = values[i];
        myEquation.push_back(newTerm);
    }
    return;
}

double Equation::integrate(double a, double b, long trials) const {
    double area = getArea(a, b, trials);
    double result = 0;
    #pragma omp parallel 
    {
        int thread = omp_get_thread_num();

        seed_seq seed{12345, thread};
        mt19937 rng(seed);

        uniform_real_distribution<double> distribution(a, b);

        #pragma omp for reduction(+:result)
        for(long i = 0; i < trials; i++) {
            double val = distribution(rng);

            double eval = 0.0;
            for (int x = 0; x < myEquation.size(); x++) {
                if (myEquation[x].type == 'p') { // polynomial type, standard.
                    eval += myEquation[x].value * pow(val, myEquation[x].exp);
                }
                if (myEquation[x].type == 's') { // sin transcendental exp * cos(val * x)
                    eval += myEquation[x].exp * sin(val * myEquation[x].value);
                }
                if (myEquation[x].type == 'c') { // cos transcendental exp * cos(val * x)
                    eval += myEquation[x].exp * cos(val * myEquation[x].value);
                }
                if (myEquation[x].type == 't') { // tan transcendental exp * tan(val * x)
                    eval += myEquation[x].exp * tan(val * myEquation[x].value);
                }
            }
            result += eval * area;
        }
    }
    return result;  
}

double Equation::integrate(double a, double b, long trials, double* error) const {
    *error = 1.0 / sqrt(trials);
    return integrate(a, b, trials);
}

double Equation::integrateByTolerance(double a, double b, double error) const {
    if (fabs(error) != error) {
        throw invalid_argument("You cannot have a negative error value!");
    }
    long trials = (long)pow((1.0 / error), 2) + 1;
    cout << trials;
    return integrate(a, b, trials);
}

double Equation::getArea(double a, double b, long trials) const {
    return (b - a) / trials;
}   