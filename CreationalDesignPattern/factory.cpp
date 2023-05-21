#include <iostream>
#include <string>
using namespace std;

class Shape
{
    public:
    virtual string getName() = 0;

};

class Triangle : public Shape{
    public:
    string getName() { return "Traingle";}
};

class Square: public Shape {
    public:
    string getName() { return "Square";}
};
class Circle: public Shape {
    public:
    string getName() { return "Circle";}
};

 enum Type{ TRAINGLE , SQUARE , CIRCLE } ;

 class ShapeFactory
 {
    public:
    Shape* getShape(Type type)      // Factory Method
    {
        switch(type)
        {
            case TRAINGLE:
            return new Triangle();

            case SQUARE:
            return new Square();

            case CIRCLE:    
            return new Circle();    

            default:
            return NULL;
        }
        // return nullptr; 
    }
 };

 int main()
 {
    ShapeFactory shapeFactory;
    Shape* shape = shapeFactory.getShape(TRAINGLE);

    delete shape;
    return 0;
 }
