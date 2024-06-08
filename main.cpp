#include<iostream>
#include "product.h"
#include "productOnSale.h"
#include "OrderManagement.h"
#include "customer.h"


using namespace std;

void productManagement();
void cartManagement();
void customerManagement();


//Customer c;

int products::statId=0;
int OrderManagement::id=0;
int Person::sid=0;

products p1;
productsOnSale p2;

OrderManagement Order;

string LoginID;
int password;

int main() {

    bool found=false;
    do{
        cout<<"*************** WELCOME TO SUPER MART MANAGEMENT SYSTEM ***************\n";
        cout<<"Enter your Login ID\n";
        cin>>LoginID;
        cout<<"Enter Password to access System\n";
        cin>>password;  
        if(LoginID == "mart" && password == 1234 ) {
            found=true;
            cout<<"1. Product Management\n";
            cout<<"2. Cart Management\n";
            cout<<"3. Customer Management\n";
            int n;
            std::cin>>n;
            switch (n){
                case 1:
                productManagement();
                break; 
                case 2:
                cout<<"Enter Id of the customer whose cart you want to manage: \n";
                cin>>Person::sid;
                cartManagement();
                break;
                case 3:
                customerManagement();
                break;
            }
        }   
        else if(LoginID != "mart" || password != 1234) {
            cout<<"Incorrect User Id or Password! Try Again\n";
        }
    }
    while(!found);
    return 0;
}

void customerManagement(){
    Person* person = new Customer;
    Customer c1;
    Customer *c; // Create an array of Customer objects
    int choice;
    do {
        cout << "\n*Customer Management System*\n";
        cout << "1. Add Customer\n";
        cout << "2. Edit Customer\n";
        cout << "3. Search Customer\n";
        cout << "4. Delete Customer\n";
        cout << "5. View All Customers\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:

            { int n;
                 cout << "Enter the number of customers you want to add: ";
                cin >> n;
                cin.ignore();
                c = new Customer[n]; // Create an array of Person objects
                for (int i = 0; i < n; i++) {
                    c[i].addPerson();
                }
            delete[] c; // Release the memory allocated for the Person objects
                break;
            }
            case 2:
            { 
                cout << "Enter the Person ID you want to edit\n";
                cin >> Person::sid;
                person->editPerson();
                break;
            }
            case 3: {
                cout << "Enter the ID of the customer to search: ";
                cin >> Person::sid;
                person->SearchPerson(); // Search for a customer
                
                break;
            }
            case 4: {
                cout << "Enter the ID of the customer to delete: ";
                cin >> Person::sid;
                person->deletePerson(); // Delete a customer
                
                break;
            }
            case 5: {
                cout << "\nList of Customers:\n";
                person->viewFromFile(); // View all customers
                
                break;
            }
            case 6: {
                cout<<"Exiting System\n";
                break;
            }

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 6);
}




void cartManagement() {
    Customer * newCustomer= new Customer;
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


    int tempid, temployalty;
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


        if (CustomerList[i].getid() == Person::sid) {
        found=true;

        while (true) {
        cout << "Options:" << endl;
        cout << "1. Add product to cart" << endl;
        cout << "2. Remove product from cart" << endl;
        cout << "3. View cart items" << endl;
        cout << "4. Apply discounts" << endl;
        cout << "5. Clear Cart" << endl;
        cout << "6. Calculate Total Bill"<<endl;
        cout << "7. Exit" << endl;

        int option;
        std::cin >> option;

        switch (option) {
            case 1: {
                int productId;
                cout << "Enter product ID to add to cart: ";
                cin >> OrderManagement::id;
                CustomerList[i].getCart()->addItem();
                break;
            }
            case 2: {
                cout << "Enter product ID to remove from cart: ";
                cin >> OrderManagement::id;
                CustomerList[i].getCart()->removeItem();
                break;
            }
            case 3:
                CustomerList[i].getCart()->viewItems();
                break;
            case 4:
                CustomerList[i].getCart()->applyDiscount();
                break;
            case 5:
                CustomerList[i].getCart()->clearCart();
                break;
            case 6:
                cout << "Enter Cart ID to calculate total price: ";
                cin >> OrderManagement::id;
                CustomerList[i].getCart()->calculateTotalPrice();
                break;
            case 7:
                cout<<"Exiting System\n";
                exit(0);
                break;
            default:
                cout << "Invalid option" << endl;
        }
    }
        }
        i++;
    }
    if (!found) {
        cout << "Person not found in database! Unable to search!\n";
    }
    fin.close();
    delete[] CustomerList;

}



void productManagement(){
    int a;

    do {
        cout << "*Product Management System";
        cout << "\n1. Add data\n";
        cout << "2. Edit Data\n";
        cout << "3. search Data\n";
        cout << "4. delete products\n";
        cout << "5. View Products\n";
        cout<<"6. Add Discount\n";
        cout<<"7. Edit Discount\n";
        cout<<"8. Exit Product Management\n";
        cin >> a;
        switch (a) {
        case 1:
            p1.addProduct();
            break;

        case 2:
            cout << "\n Enter the ID of the product\n";
            cin >> products::statId;
            p1.editProduct();
            break;

        case 3:
            cout << "\n Enter the ID of the product\n";
            cin >> products::statId;
            p1.searchProduct();
            break;

        case 4:
            cout << "\n Enter the ID of the product\n";
            cin >> products::statId;
            p1.deleteProduct();
            break;

        case 5:
            p1.viewProductsFromFile();
            break;
        
        case 6: 
            float dis;
            cout<<"Enter the Id of product that you want to add discount too\n";
            cin>>products::statId;
            p2.addDiscount();
            break;

        case 7: 
            float disc;
            cout<<"Enter the Id of product that you want to add discount too\n";
            cin>>products::statId;
            p2.editDiscount();
            break;
        
        case 8:
            cout<<"Exiting System\n";
            break;
        default:
            cout << "Invalid option" << endl;
        }
    }
    while (a != 8); 
}


