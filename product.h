#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include <fstream>
#include<string>
#include <cstring>
using namespace std;

class products
{
private:
    int productID;
    string name;
    float price;
    int inventory;


public:
    static int statId;

    products()
    {
        productID = 0000;
        name = "Default";
        price = 0.0;
        inventory = 00;
    }
    products(int productID, string name, float price, int inventory, int statId)
    {
        this->productID = productID;
        this->name = name;
        this->price = price;
        this->inventory = inventory;
    }
    products(products& obj)
    {
        this->productID = obj.productID;
        this->name = obj.name;
        this->price = obj.price;
        this->inventory = obj.inventory;
    }
    ~products()
    {

    }
    void setProductId(int productID)
    {
        this->productID = productID;
    }
    void setName(string name)
    {
        this->name = name;
    }
    void setPrice(float price)
    {
        this->price = price;
    }
    void setInventory(int inventory)
    {
        this->inventory = inventory;
    }
    int getProductId()
    {
        return productID;
    }
    string getName()
    {
        return name;
    }
    float getPrice()
    {
        return price;
    }
    int getInventory()
    {
        return inventory;
    }

    virtual string tostring()
    {
        return  "Product Id: " + to_string(productID) + " - " + " Name: " + name + " - " + to_string(price) + " - " + " Inventory: " + to_string(inventory) + " - " + "\n";
    }
    virtual void addProduct()
    {
        cout << "Add Products to the System\n";
        cout << "Enter Product ID: \n";
        cin >> productID;
        cout << "Enter Name: \n";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Product Price: \n";
        cin >> price;
        cout << "Enter Product Inventory: \n";
        cin >> inventory;
        storetofile();
    }
    virtual void storetofile()
    {
        try
        {
            fstream fout;
            fout.open("products.txt", ios::app);
            fout << tostring();
            fout.close();
        }
        catch (const runtime_error& error)
        {
            cout << error.what() << endl;
        }
    }
    static void viewProductsFromFile()
    {
        try
        {
            fstream fin;
            fin.open("products.txt", ios::in);
            if(!fin.is_open()){
                cout<<"Error Opening Products file!\n";
            }
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

    virtual void searchProduct()

    {
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

        products* productList = new products[counter];

        fin.open("products.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        int searchId;
        searchId = statId;
        // cout << "Enter ID of the product you want to edit: ";
        // cin >> searchId;

        int tempid, tempinventory;
        string tempname, temporary;
        float tempprice;
        char temp;

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
            getline(fin, temporary, '-');

            productList[i].setProductId(tempid);
            productList[i].setName(tempname);
            productList[i].setPrice(tempprice);
            productList[i].setInventory(tempinventory);

            if (productList[i].getProductId() == searchId) {
                cout << "\nData found!\n\n";
                cout << "Product ID: " << productList[i].getProductId() << endl;
                cout << "Product Name: " << productList[i].getName() << endl;
                cout << "Product Price: " << productList[i].getPrice() << endl;
                cout << "Product Inventory: " << productList[i].getInventory() << endl;

            }
            else {}
            i++;
        }
        fin.close();
        delete[] productList;
    }


    static void viewProducts()
    {
        try
        {
            fstream fin;
            fin.open("products.txt", ios::in);
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

    virtual void editProduct()
    {
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

        products* productList = new products[counter];

        fin.open("products.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        ofstream fout;
        fout.open("UpdatedProducts.txt", ios::app);

        int editId;
        editId = statId;
        // cout << "Enter ID of the product you want to edit: ";
        // cin >> editId;

        int tempid, tempinventory;
        string tempname, temporary;
        float tempprice;
        char temp;

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
            getline(fin, temporary, '-');

            productList[i].setProductId(tempid);
            productList[i].setName(tempname);
            productList[i].setPrice(tempprice);
            productList[i].setInventory(tempinventory);

            if (productList[i].getProductId() == editId) {
                cout << "Data found!\n";
                cout << "Enter new name of the product: ";
                cin.ignore();
                getline(cin, tempname);
                productList[i].setName(tempname);

                cout << "Enter new price of the product: ";
                cin >> tempprice;
                productList[i].setPrice(tempprice);

                cout << "Enter new inventory of the product: ";
                cin >> tempinventory;
                productList[i].setInventory(tempinventory);

                fout << productList[i].tostring();

                cout << "Data Updated Successfully!" << endl;
            }
            else {
                fout << productList[i].tostring();
            }
            i++;
        }

        // Deallocate memory
        delete[] productList;
        fout.close();
        fin.close();
        remove("products.txt");
        rename("UpdatedProducts.txt", "products.txt");
    }

    virtual void deleteProduct() {
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

        products* productList = new products[counter];

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
        float tempprice;
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
            getline(fin, temporary, '-');

            productList[i].setProductId(tempid);
            productList[i].setName(tempname);
            productList[i].setPrice(tempprice);
            productList[i].setInventory(tempinventory);

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
