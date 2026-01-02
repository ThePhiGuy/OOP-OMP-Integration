#include "ooint.h"

void test1();
void test2();

int main() {
    vector<double> times;
    times.push_back(omp_get_wtime());
    // test1();
    test2();
    cout << "\nFinal Time : " << omp_get_wtime() - times[0] << endl;
    cout << "Threads: " << omp_get_max_threads() << endl;
    return 0;
}

void test1() {
    vector<double> test1;
    test1.push_back(1);
    test1.push_back(0);
    test1.push_back(0);
    Equation eq2(test1);    
    double* error = (double*)calloc(9, sizeof(double));

    cout << eq2;
    for (int i = 0; i < 9; i++) {
        cout <<  "\n" << pow(10, i) << "\t" << eq2.integrate(0, 2, pow(10, i), &error[i]) << "\t Error : " << error[i]; 
    }
}

void test2() {
    vector<double> test2;
    test2.push_back(1);
    test2.push_back(-2);
    test2.push_back(3);
    vector<char> types;
    types.push_back('p');
    types.push_back('s');
    types.push_back('c');
    vector<double> exps;
    exps.push_back(4.2);
    exps.push_back(1.11);
    exps.push_back(-41);

    Equation eq2(test2, types, exps);

    cout << eq2 << "\n";

    cout << eq2.integrate(0.0, 1.0, 100000000);

}