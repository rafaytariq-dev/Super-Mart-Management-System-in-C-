#ifndef CUSTOMER_H
#define CUSTOMER_H
#include "Person.h"
#include"OrderManagement.h"
#include<iostream>
#include <string>
using namespace std;


class Customer : public Person
{
private:
   
    OrderManagement *cart;
public:
    // Default Constructor
    Customer(){

    } 

    // Parameterized Constructor
    Customer(int id, string name, string phone, OrderManagement* cart)
        : Person(id, name, phone), cart(cart){}


    // Getter function for cart
    OrderManagement* getCart() const {
        return cart;
    }

    // Setter function for cart
    void setCart(OrderManagement* cart) {
        this->cart = cart;
    }




    // Overridden function to convert Customer object to string
    virtual string tostring() override {
        return "Customer ID: " + to_string(getid()) + " - Name: " + getname() + " - Phone Number: " + getphone() + " - "+ "\n";
    }

virtual void addPerson() override {
        id = generateID();
        cout << "\nEnter the following information...\n";
        cout<<id<<" is your id\n";
        cout << "Enter Your Name: ";
        cin.ignore();
        getline(cin, name);

        cout << "Enter Your Phone Number (exactly 11 digits): ";
        //cin >> phoneNo;
        while (true)
            {
                getline(cin, phoneNo);
                if (phoneNo.length() != 11) 
                { // Check if the phone number is the correct length
                    cout << "Invalid phone number format. Please try again: ";
                    continue;
                }
                break; // Valid phone number, exit loop
            }

        
        storetofile();
    }

    
virtual void storetofile() override
    {
        try
        {
            fstream fout;
            fout.open("Customer.txt", ios::app);
            fout << tostring();
            fout.close();
        }
        catch (const runtime_error& error)
        {
            cout << error.what() << endl;
        }
    }

virtual void SearchPerson() override {
    int counter = 0;

    ifstream fin;
    fin.open("Customer.txt");
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }

    string line;
    while (getline(fin, line)) {
        counter++;
    }
    fin.close();

    Customer* CustomerList;
    CustomerList = new Customer[counter];

    fin.open("Customer.txt");
    if (!fin.is_open()) {
        cout << "Error opening file." << endl;
        return;
    }


    int tempid;
    string tempname, temporary;
    string TempPhone;
    char temp;
    bool found = false;

    int i = 0;
    while (i < counter) {
        getline(fin, temporary, ':');
        fin >> tempid >> temp;
        getline(fin, temporary, ':');
        getline(fin, tempname, '-');
        getline(fin, temporary, ':');
        fin >> TempPhone >> temp;

        CustomerList[i].setid(tempid);
        CustomerList[i].setname(tempname);
        CustomerList[i].setphone(TempPhone);

        if (CustomerList[i].getid() == sid) { // Change sid to searchId
            found = true;
            cout << "Data found!\n";
            cout << "ID: " << CustomerList[i].getid() << endl;
            cout << "Name: " << CustomerList[i].getname() << endl;
            cout << "Phone Number: " << CustomerList[i].getphone() << endl;
        }
        i++;
    }
    if (!found) {
        cout << "Person not found in database! Unable to search!\n";
    }
    fin.close();
    delete[] CustomerList;
}

virtual void editPerson()override
    {
        int counter = 0;

        ifstream fin;
        fin.open("Customer.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(fin, line))
        {
            counter++;
        }
        fin.close();

        
        Customer *CustomerList = new Customer[counter];

        fin.open("Customer.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        ofstream fout;
        fout.open("UpdatedPersonData.txt", ios::app);

        int tempid;
        string tempname, temporary;
        string TempPhone;
        char temp;
        bool found=false;

        int i = 0;
        while (i < counter)
        {
            getline(fin, temporary, ':');
            fin >> tempid >> temp;
            getline(fin, temporary, ':');
            getline(fin, tempname, '-');
            getline(fin, temporary, ':');
            fin >> TempPhone >> temp;

          

            CustomerList[i].setid(tempid);
            CustomerList[i].setname(tempname);
            CustomerList[i].setphone(TempPhone);
 
            if (CustomerList[i].getid() == sid) {
                found=true;
                cout << "Data found!\n";
                cout << "Enter new name of the Person: ";
                cin.ignore();
                getline(cin, tempname);
                CustomerList[i].setname(tempname);
                cout << "Enter new phone of the person: ";
                cin >> TempPhone;
                CustomerList[i].setphone(TempPhone);

                fout << CustomerList[i].tostring();

                cout << "Data Updated Successfully!" << endl;
            }
            else {
                fout << CustomerList[i].tostring();
            }
            i++;
        }
        if(found==false){
            cout<<"Person not found in database! Unable to edit!\n";
        }

        // Deallocate memory
        delete[] CustomerList;
        fout.close();
        fin.close();
        remove("Customer.txt");
        rename("UpdatedPersonData.txt", "Customer.txt");
    }

virtual void deletePerson()override{
        int counter = 0;

        ifstream fin;
        fin.open("Customer.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        string line;
        while (getline(fin, line))
        {
            counter++;
        }
        fin.close();

        Customer* CustomerList;
        CustomerList = new Customer[counter];

        fin.open("Customer.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        ofstream fout;
        fout.open("UpdatedPersonData.txt", ios::app);

        //int delId;
        //cout << "Enter ID of the Person you want to delete: ";
        //cin >> delId;

        int tempid, temployaltyp;
        string tempname, temporary;
        string TempPhone;
        char temp;
        bool found=false;

        int i = 0;
            while(i<counter){
                getline(fin, temporary, ':');
                fin >> tempid >> temp;
                getline(fin, temporary, ':');
                getline(fin, tempname, '-');
                getline(fin, temporary, ':');
                fin >> TempPhone >> temp;

                

                CustomerList[i].setid(tempid);
                CustomerList[i].setname(tempname);
                CustomerList[i].setphone(TempPhone);

        
                if (CustomerList[i].getid() == sid) 
                {
                    found=true;
                    cout << "Data Deleted!\n";
                }
                else 
                {
                    fout << CustomerList[i].tostring();
                }
                i++;
            }
            if(found==false){
                cout<<"Person not found in database! Unable to delete!\n";
            }
        delete[] CustomerList;
        fout.close();
        fin.close();
        remove("Customer.txt");
        rename("UpdatedPersonData.txt", "Customer.txt");
    }

virtual void viewFromFile()override
    {
        try
        {
            fstream fin;
            fin.open("Customer.txt", ios::in);
            string line;
            while (getline(fin, line))
            {
                cout << line << endl;
            }
        }
        catch (const runtime_error& error)
        {
            cout << error.what() << endl;
        }
    }
    


    int generateID()override{
        // Seed the random number generator with current time
        srand(static_cast<unsigned int>(time(nullptr)));

        // Generate a random number between 10 and 99 (inclusive) for the ID
        return rand() % 991 + 100; // Generates a random number in range [10, 999]
    }
};
#endif