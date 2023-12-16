#include<iostream>
#include<memory>
#include<stdlib.h>
using namespace std;

class Foo {
        int x;

    public:
        explicit Foo(int x): x{x}  {}
        int getX() { return x; }
    ~Foo() { cout << "Foo Destructor called" << endl; }
};

int main() {

    foo *f

    std::unique_ptr<Foo> p(new Foo(10)); // ways of creating Unique Pointer

    std::unique_ptr<Foo> p2 = make_unique<Foo>(20); // other way of creating

    std::unique_ptr<Foo> p3 = std::move(p1); // move content of p1 to p3 AND P1 BECOMES A null pointer
    cout << p->getX() << endl;

    Foo* p = p3.get (); // will give the object new Foo(10) 

    Foo* p4 = p3.release();

    p2.reset(p4) ; // changing managed object

    return 0;
}