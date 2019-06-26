#include <string>

using namespace std;

class Animal
{
    private:
        int age;

    public:
        Animal(int age) : age{age} {}

        int getAge() {return age;}
        virtual string type() {return "Animal";}

        void print1(Animal * a) {cout << a->type() << endl;}
};

class Dog : public Animal
{
    public:
        Dog(int age) : Animal(age) {}
        virtual string type() {return "Dog";}

        void print() {print1(this);}
};      

