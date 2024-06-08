#ifndef PRODUCTONSALE_H
#define PRODUCTONSALE_H
#include <iostream>
#include <fstream>
#include<string>
#include <cstring>
#include "product.h"
using namespace std;

class productsOnSale : public products {

private:
    float discountPercentage ;
public:

    productsOnSale() : products(), discountPercentage(0.0) {}

    productsOnSale(int productID, string name, float price, int inventory, int statId, float discountPercentage) : products(productID, name, price, inventory, statId), discountPercentage(discountPercentage) {}

    productsOnSale(productsOnSale& obj) : products(obj), discountPercentage(obj.discountPercentage) {}

    
    float getdisPercentage() {
        return discountPercentage;
    }
    void setDisPercentage(float percentage) {
        this->discountPercentage = percentage;
    }
    string tostring()override {
        return  "Product Id: " + to_string(getProductId()) + " - " + " Name: " + getName() + " - " + to_string(getPrice()) + " - " + " Inventory: " + to_string(getInventory()) + " - " + "Discount: " + to_string(getdisPercentage()) + " -" + "\n";
    }


void addDiscount() {
        int counter = 0;

        ifstream fin;
        fin.open("Products.txt");
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

        productsOnSale* productList = new productsOnSale[counter];

        fin.open("Products.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        ofstream fout;
        fout.open("UpdatedProducts.txt", ios::app);
        if (!fout.is_open())
        {
            cout << "Error opening new updated products file." << endl;
            return;
        }

        int disId;
        disId = statId;
 

        int tempid, tempinventory;
        string tempname, temporary;
        float tempprice, disc;
        char temp;
        bool found = false;

        int i = 0;
        while (i < counter) {
            getline(fin, temporary, ':');
            fin >> tempid >> temp;
            getline(fin, temporary, ':');
            getline(fin, tempname, '-');
            fin >> tempprice >> temp;
            getline(fin, temporary, ':');
            fin >> tempinventory >> temp;
            getline(fin, temporary, ':');
            fin >> disc >> temp;

            productList[i].setProductId(tempid);
            productList[i].setName(tempname);
            productList[i].setPrice(tempprice);
            productList[i].setInventory(tempinventory);
            productList[i].setDisPercentage(disc);

            if (productList[i].getProductId() == disId) {
                found = true;
                cout << "Enter the percentage of the discount to be given: ";
                cin >> productList[i].discountPercentage;
                fout << productList[i].tostring();
                //cout << productList[i].tostring();
                cout << "Discount Added Successfully\n";
            }
            else {
                fout << productList[i].tostring();

                //cout << productList[i].tostring();
            }
            i++;
        }
        if (found == false) {
            cout << "Data not found in database! Unable to add discount!\n";
        }
        delete[] productList;
        fout.close();
        fin.close();
        remove("Products.txt");
        rename("UpdatedProducts.txt", "Products.txt");
    }

void editDiscount(){
    {
        int counter = 0;

        ifstream fin;
        fin.open("Products.txt");
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

        productsOnSale* productList = new productsOnSale[counter];

        fin.open("Products.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        ofstream fout;
        fout.open("UpdatedProducts.txt", ios::app);

        int disId;
        disId = statId;
        // cout << "Enter ID of the product you want to edit: ";
        // cin >> editId;

        int tempid, tempinventory, tempdiscount;
        string tempname, temporary;
        float tempprice;
        char temp;
        bool found=false;

        int i = 0;
        while (i < counter)
        {
            getline(fin, temporary, ':');
            fin >> tempid >> temp;
            getline(fin, temporary, ':');
            getline(fin, tempname, '-');
            fin >> tempprice >> temp;
            getline(fin, temporary, ':');
            fin >> tempinventory >> temp;
            getline(fin, temporary, ':');
            fin >> tempdiscount >> temp;

            productList[i].setProductId(tempid);
            productList[i].setName(tempname);
            productList[i].setPrice(tempprice);
            productList[i].setInventory(tempinventory);

            if (productList[i].getProductId() == disId) {
                found=true;
                cout << "Data found!\n";
                cout << "Enter new discount on the product: ";
                cin>>productList[i].discountPercentage;

                fout << productList[i].tostring();

                cout << "Data Updated Successfully!" << endl;
            }
            else {
                fout << productList[i].tostring();
            }
            i++;
        }
            if (found==false){
                cout<<"Product not found in database! Unable to edit! \n";
            }

        // Deallocate memory
        delete[] productList;
        fout.close();
        fin.close();
        remove("Products.txt");
        rename("UpdatedProducts.txt", "Products.txt");
    }

}

    void deleteProduct()override {
        int counter = 0;

        ifstream fin;
        fin.open("products.txt");
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

        productsOnSale* productList = new productsOnSale[counter];

        fin.open("products.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        ofstream fout;
        fout.open("UpdatedProducts.txt", ios::app);

        int delId;
        delId = statId;
        // cout << "Enter ID of the product you want to delete: ";
        // cin >> delId;

        int tempid, tempinventory;
        string tempname, temporary;
        float tempprice, tempdiscount;
        char temp;

        int i = 0;
        while (i < counter) {
            getline(fin, temporary, ':');
            fin >> tempid >> temp;
            getline(fin, temporary, ':');
            getline(fin, tempname, '-');
            fin >> tempprice >> temp;
            getline(fin, temporary, ':');
            fin >> tempinventory >> temp;
            getline(fin, temporary, ':');
            fin >> tempdiscount >> temp;

            productList[i].setProductId(tempid);
            productList[i].setName(tempname);
            productList[i].setPrice(tempprice);
            productList[i].setInventory(tempinventory);
            productList[i].setDisPercentage(tempdiscount);
            if (productList[i].getProductId() == delId) {
                cout << "Data Deleted!\n";
            }
            else {
                fout << productList[i].tostring();
            }
            i++;
        }
        delete[] productList;
        fout.close();
        fin.close();
        remove("products.txt");
        rename("UpdatedProducts.txt", "products.txt");
    }

};
#endif