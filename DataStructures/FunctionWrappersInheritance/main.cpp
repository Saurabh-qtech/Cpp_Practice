// Modify a class heirarchy using polymorphism to a class heirarchy that uses a function wrapper

// import header files
#include <iostream>
#include <functional>

// function wrapper
using  VoidFunctionType = std::function<void (double)>;

// some class Shape
class Shape {

    protected:
        VoidFunctionType f ;
    
    public :
        void rotate (double d){
            f(d);  // call member variable f
        }

        // constructor
        Shape(const VoidFunctionType&) ;


};

// constructor definitions
Shape::Shape(const VoidFunctionType& f_) : f(f_) { }  // shape class

// some class Circle
class Circle : public Shape {

    public:

        // constructor
        Circle (const VoidFunctionType&);

        void rotate (double d) {
            std::cout << "Circle rotate" << std::endl;
        }

};

// constructor definitions
Circle::Circle(const VoidFunctionType& f_) : Shape(f_) { } // circle class

// some class Triangle
class Triangle : public Shape {

    public:

        // constructor
        Triangle (const VoidFunctionType&);

        void rotate (double d) {
            std::cout << "Triangle rotate" << std::endl;
        }

};

// constructor definitions
Triangle::Triangle(const VoidFunctionType& f_) : Shape(f_) { } // triangle class


// target method
void rotate_target (double d){
    std::cout << "Circle rotate via Shape protectd function wrapper " << "\n";
}

int main (){

    // dynamically allocate memory
    Shape* s1 = new Triangle([] (double d) -> void {std::cout << "Triangle  rotate via Shape protectd function wrapper " << std::endl;});
    Shape* s2 = new Circle(rotate_target);

    // call the functions used to initialize : VoidFunctionType f
    s1->rotate(5);
    s2->rotate(7);

    // we successfully replce virtual/override in the base/derived classes using protected wrapper function 
    // the rotate in the derived classes (triangle and circle) are not invoked


    // free memory
    delete s1;
    delete s2;

    return 0;
}
