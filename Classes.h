class Animal
{
    private:
        int age;

    public:
        Animal(int age) : age{age} {}

        int getAge() {return age;}
};

class Dog : public Animal
{
    public:
        Dog(int age) : Animal(age) {}
};