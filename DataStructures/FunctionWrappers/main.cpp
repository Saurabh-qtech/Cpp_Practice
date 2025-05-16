// introduce universal function wrappers (std::function) in C++11

// import library
#include <iostream>
#include <functional>

// scalar i/p and scalar return type
template <typename T>
using FunctionType = std::function <T (const T&)>;

// print value
template <typename T>
void print(const FunctionType<T>& f, T t ){
    std::cout << f(t) << std::endl;
}

// calculate square - free function
double square (const double& d){
    return d*d;
}

// calculate cube - function object
class Cube {
    public:
    double operator() (const double& d){
        return d*d*d;
    }
};

int main(){

    // create instance of function wrapper
    FunctionType<double> f1;
    // assign function wrapper to square
    f1 = square;
    // print f1(5)
    std::cout << "sqaured using free function : ";
    print(f1, 5.0);

    // create instance of function wrapper
    FunctionType<double> f2 ;
    // create instance of functor
    Cube c;
    // assign function wrapper to cube
    f2 = c;
    // print f2(5)
    std::cout << "cube using functor : ";
    print(f2, 5.0);

    // create instance of function wrapper
    FunctionType<double> f3;
    // assign function wrapper to forth power
    f3 = [] (const double& d) -> double {return d*d*d*d;};
    // print f#(5)
    std::cout << "forth power using lambda function : ";
    print(f3, 5.0);

    return 0;
    
}