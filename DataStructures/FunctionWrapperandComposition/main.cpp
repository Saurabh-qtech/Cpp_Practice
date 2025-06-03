// modify a class heirarchy using polymorphism to a single class with function wrapper

// include header files
#include <iostream>


template<typename T>
using voidFunctionType = std::function<void (T)>;

// next gen design pattern
template <typename T>
class Shape
{
    private:
        voidFunctionType<T> _func;
    public:
        Shape (const voidFunctionType<T>& function) : _func(function) {
        }

        void rotate(double d) {  _func(d) ; }
        
        void switchFunction(const voidFunctionType<T>& function)
        { _func = function; }
};

int main(){

    // lambda functions
    auto triangle = [] (double d) {std::cout << "Roatate Triangle by " << d << " degrees" << std::endl;};
    auto square = [] (double d) {std::cout << "Rotate Square by " << d << " degrees" << std::endl;};
    auto circle = [] (double d) {std::cout << "Rotate Circle by " << d << " degrees" << std::endl;};

    // instantiate Shape
    Shape<double> s1 (triangle);
    s1.rotate(5.0) ; /// rotate triancgle

    s1.switchFunction(square) ; // switch to square

    s1.rotate(6.0) ; // rotate swqaure

    s1.switchFunction(circle) ; // switch to square

    s1.rotate(9.0) ; // rotate swqaure

    return 0;
}

