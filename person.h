#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <ctime>
using namespace std;

class Person
{
protected:
    int id;
    string name;
    string phoneNo;

public:
   //declaring a static variable
   static int sid;
   // Default Constructor
    Person() : id(1), name("CUSTOMER"), phoneNo("0000") {}
   
   //Parameterized Constructor
    Person(int id, string name, string phone) {
        this->id=id;
        this->name=name;
        this->phoneNo=phone;
    }
   // Copy Constructor
    Person(Person& temp)
    {
        this->id=temp.id;
        this->name=temp.name;
        this->phoneNo=temp.phoneNo;
    }
    // Destructor
    ~Person() {}

    // Getter functions
    int getid() const {
        return id;
    }

    string getname() const {
        return name;
    }

    string getphone() const {
        return phoneNo;
    }

    // Setter functions
    void setid(int id) {
        this->id = id;
    }

    void setname(const string& name) {
        this->name = name;
    }

    void setphone(const string& phone) {
        this->phoneNo = phone;
    }

    virtual string tostring()=0;
    virtual void addPerson()=0;
    virtual int generateID() = 0;

    virtual void storetofile()=0;

    virtual void viewFromFile()=0;

    virtual void SearchPerson()=0;

    virtual void editPerson()=0;


    virtual void deletePerson()=0;
        
    
};  