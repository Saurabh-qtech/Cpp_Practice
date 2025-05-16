// partial function evaluation using std::bind
// reduce function with a given arity to lower arity

// import library
#include <iostream>
#include <functional>

// free function - to add three numbers
double freeFunction3 (double x, double y, double z){
    return x + y + z;
}

// arity 3 function - using std::bind and auto keyword for type of arity_3
auto arity_3 = std::bind (freeFunction3, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3);

// arity 2 function - using std::bind
std::function<double (double, double)> arity_2 = std::bind(freeFunction3, std::placeholders::_1, 2.0 , std::placeholders::_2);

// arity 1 function - using custom function bind1st3rd (pre C++11)
std::function<double (double)> bind1st3rd (std::function<double (double, double, double)> f, double d1, double d3) {      // first: create function bind1st3rd
    return [=] (double d2) -> double {
        return f(d1, d2, d3);
    };
};
auto arity_1 = bind1st3rd(freeFunction3, 1, 3);  // second: intialize arity_1

// arity 0 function - using std::bind
auto arity_0 = std::bind(freeFunction3, 7, 8, 9);




int main(){

    // print o/p using arity functions v/s freeFunction3

    std::cout << "Comparing output form arity functions vs direct i/p to freeFunction3 : " << std::endl;
    std::cout << "Arity 3 : " << arity_3(1,2,3) << "\tFreeFunction3 : " << freeFunction3(1,2,3) << std::endl;
    std::cout << "Arity 2 : " << arity_2(7,7) << "\tFreeFunction3 : " << freeFunction3(7,2,7) << std::endl;
    std::cout << "Arity 1 : " << arity_1(5) << "\tFreeFunction3 : " << freeFunction3(1,5,3) << std::endl;
    std::cout << "Arity 0 : " << arity_0() << "\tFreeFunction3 : " << freeFunction3(7,8,9) << std::endl;

    return 0;

}
