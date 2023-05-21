# include <iostream>
#include <string>
#include "stddef.h"
#include "stdio.h"
#include "stdlib.h"
#include <string.h>

using namespace std;

class Coffee {
    protected:
    char _type[20];

    public :

    Coffee()
    {
        cout << "Coffee class Constructor Called"<< endl;

    }

    char *getType()
    {
        return _type;
    }

};

class Espresso: public Coffee
{
    public:
    Espresso() : Coffee()
    {
        strcpy(_type, "Espresso");
        cout<< endl << "Making a Cup of Espresso" << endl;
        cout<< "Grind and brew one scoop of Espresso Beans" << endl;
        cout<< "Pour in a cup of hot water" << endl;
    }
};

class Cappuchino : public 
Coffee
{
    public:
    Cappuchino() : Coffee()
    {
        strcpy(_type, "Cappuchino");
        cout<< endl << " Making a cup of Cappuchino" << endl;
        cout<< endl << " Heat and foam Milk " << endl;
    }
};