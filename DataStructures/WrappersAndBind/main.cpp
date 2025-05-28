// Modify function args using std::bind, so that the new function conforms to std::function<T (const T&)>

// This way we can modify the function that we have created to fit signature need for a new problem


// include headers
#include <iostream>
#include <functional>

// some class C
class C
{ // Function object with extra member functions
    private:
        double _data;
    public:
        C(double data) : _data(data) {}         // constructor

        double operator () (double factor)      // functor
        {
            return _data + factor;
        }
        double translate (double factor)
        {
            return _data + factor;
        }
        double translate2 (double factor1, double factor2)
        {
            return _data + factor1 + factor2;
        }
        static double Square(double x)      // static member function
        {
            return x*x;
        }
};

// function wrapper
template <typename T>
using FunctionType = std::function<T (const T& )> ;

int main() {

    // a. bind the function wrapper to C's static member funciton
    FunctionType<double> f1 = C::Square;

    // object of class C
    C c_obj(5);

    // b. bind the funciton wrapper to C's member function
    FunctionType<double> f2 = std::bind(c_obj, std::placeholders::_1);

    FunctionType<double> f3 = std::bind(&C::translate, &c_obj, std::placeholders::_1);

    FunctionType<double> f4 = std::bind(&C::translate2, &c_obj, 2, std::placeholders::_1);


    // c.Test
    std::cout << f1(3) << std::endl;
    std::cout << f2(3) << std::endl; 
    std::cout << f3(4) << std::endl; 
    std::cout << f4(4) << std::endl; 
    

    return 0;

}






