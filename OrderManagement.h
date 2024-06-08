#ifndef ORDERMANAGEMENT_H
#define ORDERMANAGEMENT_H
#include <iostream>
#include <fstream>
#include "product.h"
#include "productOnSale.h"
#include <ctime>

using namespace std;

class OrderManagement {
private:
    int cartId;
    float disPrice, totalPrice;
    products* item;
    productsOnSale* disItem;

public:
    static int id;


    OrderManagement() {
        cartId = 0;
        disPrice = 0;
        item = nullptr;
        disItem = nullptr;
    }
    OrderManagement(int cartId, int disPrice, products* products, productsOnSale* productsOnSale) {
        this->cartId = cartId;
        this->disPrice = disPrice;
        this->item = products;
        this->disItem = productsOnSale;
    }
    OrderManagement(OrderManagement& obj) {
        this->cartId = obj.cartId;
        this->disPrice = obj.disPrice;
        this->item = obj.item;
        this->disItem = obj.disItem;
    }

    ~OrderManagement() {
        delete item;
    }

    void setTotalPrice(float totalPrice) {
        this->totalPrice = totalPrice;
    }

    float getTotalPrice() {
        return totalPrice;
    }

    void setDisPrice(float disPrice) {
        this->disPrice = disPrice;
    }

    float getDisPrice() {
        return disPrice;
    }
    void setCartId(int cid) {
        this->cartId = cid;
    }
    int getCartId() {
        return cartId;
    }

    string tostring() {
        generateId();
        return  "Product Id: " + to_string(item->getProductId()) + " - " + "Cart ID :" + to_string(cartId) + " - " + " Name: " + item->getName() + " - " + to_string(item->getPrice()) + " - " + " Inventory: " + to_string(item->getInventory()) + " - " + "Discount: " + to_string(disItem->getdisPercentage()) + " - " + "Discounted price :" + to_string(getDisPrice()) + "-" + "\n";
    }

    void generateId() {
        srand(time(nullptr));
        int randomId = rand() % 9999 + 1000;
        cartId = randomId;
    }



    void addItem() {
        int counter = 0;

        ifstream fin;
        fin.open("products.txt");
        if (!fin.is_open())
        {
            cout << "Error opening products file." << endl;
            return;
        }

        string line;
        while (getline(fin, line))
        {
            counter++;

        }
        fin.close();

        OrderManagement* productList = new OrderManagement[counter];

        fstream fiin;
        fiin.open("products.txt");
        if (!fiin.is_open())
        {
            cout << "Error opening products file." << endl;
            return;
        }

        ofstream fout;
        fout.open("Cart Management.txt", ios::app);
        if (!fout.is_open()) {
            cout << "Error Opening cart file\n";
        }

        int tempid, tempinventory, tempdiscount, tempdisprice;
        string tempname, temporary;
        float tempprice;
        char temp;
        bool found = false;

        int i = 0;
        cout << id;

        while (i < counter)
        {
            getline(fiin, temporary, ':');
            fiin >> tempid >> temp;
            getline(fiin, temporary, ':');
            getline(fiin, tempname, '-');
            fiin >> tempprice >> temp;
            getline(fiin, temporary, ':');
            fiin >> tempinventory >> temp;
            getline(fiin, temporary, ':');
            fiin >> tempdiscount >> temp;



            productList[i].item = new products();
            productList[i].disItem = new productsOnSale();

            productList[i].item->setProductId(tempid);
            productList[i].item->setName(tempname);
            productList[i].item->setPrice(tempprice);
            productList[i].item->setInventory(tempinventory);
            productList[i].disItem->setDisPercentage(tempdiscount);


            if (productList[i].item->getProductId() == id) {
                found = true;
                cout << "Product found!\n";

                fout << productList[i].tostring();

                cout << "Product added Successfully to cart!" << endl;
            }
            i++;
        }
        if (found == false) {
            cout << "Product not found in database! Unable to add to cart! \n";
        }

        // Deallocate memory
        delete[] productList;
        fout.close();
        fin.close();
    }


    void removeItem() {
        int counter = 0;

        ifstream fin;
        fin.open("Cart Management.txt");
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

        OrderManagement* productList = new OrderManagement[counter];

        fin.open("Cart Management.txt");
        if (!fin.is_open())
        {
            cout << "Error opening file." << endl;
            return;
        }

        ofstream fout;
        fout.open("Updatedcart.txt", ios::app);

        int delId;
        delId = id;
        // cout << "Enter ID of the product you want to delete: ";
        // cin >> delId;

        int tempid, tempinventory, tempdiscount, tempcid, tempdisprice;
        string tempname, temporary;
        float tempprice;
        char temp;
        bool found = false;

        int i = 0;
        while (i < counter) {
            getline(fin, temporary, ':');
            fin >> tempid >> temp;
            getline(fin, temporary, ':');
            fin >> tempcid >> temp;
            getline(fin, temporary, ':');
            getline(fin, tempname, '-');
            fin >> tempprice >> temp;
            getline(fin, temporary, ':');
            fin >> tempinventory >> temp;
            getline(fin, temporary, ':');
            fin >> tempinventory >> temp;
            getline(fin, temporary, ':');
            fin >> tempdisprice >> temp;

            productList[i].item = new products();
            productList[i].disItem = new productsOnSale();

            productList[i].item->setProductId(tempid);
            productList[i].cartId;
            productList[i].item->setName(tempname);
            productList[i].item->setPrice(tempprice);
            productList[i].item->setInventory(tempinventory);
            productList[i].disItem->setDisPercentage(tempdiscount);
            productList[i].disPrice;

            if (productList[i].item->getProductId() == delId) {
                found = true;
                cout << "Product Removed!\n";
            }
            else {
                fout << productList[i].tostring();
                cout << productList[i].tostring();
            }
            i++;
        }
        if (found == false) {
            cout << "Data not found in database! Unable to delete!\n";
        }
        delete[] productList;
        fout.close();
        fin.close();
        remove("Cart Management.txt");
        rename("Updatedcart.txt", "Cart Management.txt");
    }


    void viewItems() {
        try
        {
            fstream fin;
            fin.open("Cart Management.txt", ios::in);
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


    void clearCart() {
        ofstream fout;
        fout.open("Cart Management.txt", ios::out | ios::trunc);
        fout.close();
        cout << "Cart cleared successfully!" << endl;
    }

    void applyDiscount() {
        {
            int counter = 0;

            ifstream fin;
            fin.open("Cart Management.txt");
            if (!fin.is_open())
            {
                cout << "Error opening filecart file 1." << endl;
                return;
            }

            string line;
            while (getline(fin, line))
            {
                counter++;
            }
            fin.close();

            OrderManagement* productList = new OrderManagement[counter];

            fin.open("Cart Management.txt");
            if (!fin.is_open())
            {
                cout << "Error opening file cart file2." << endl;
                return;
            }

            ofstream fout;
            fout.open("UpdatedCart.txt", ios::app);
            if (!fin.is_open()) {
                cout << "Error opening file updatedcart file2." << endl;
                return;
            }


            int disId;
            disId = id;
            // cout << "Enter ID of the product you want to edit: ";
            // cin >> editId;

            int tempid, tempinventory, tempcid, tempdisprice;
            string tempname, temporary;
            float tempdiscount, tempprice, dP = 0;
            char temp;
            bool found = false;

            int i = 0;
            while (i < counter)
            {
                getline(fin, temporary, ':');
                fin >> tempid >> temp;
                getline(fin, temporary, ':');
                fin >> tempcid >> temp;
                getline(fin, temporary, ':');
                getline(fin, tempname, '-');
                fin >> tempprice >> temp;
                getline(fin, temporary, ':');
                fin >> tempinventory >> temp;
                getline(fin, temporary, ':');
                fin >> tempdiscount >> temp;
                getline(fin, temporary, ':');
                fin >> tempdisprice >> temp;

                productList[i].item = new products();
                productList[i].disItem = new productsOnSale();

                productList[i].item->setProductId(tempid);
                productList[i].cartId;
                productList[i].item->setName(tempname);
                productList[i].item->setPrice(tempprice);
                productList[i].item->setInventory(tempinventory);
                productList[i].disItem->setDisPercentage(tempdiscount);
                productList[i].disPrice;


                if (tempdiscount != 0) {
                    found = true;
                    cout << "Calculating Discounted Price!\n";

                    dP = tempdiscount / 100;
                    dP = (tempprice * (1 - (dP)));
                    productList[i].setDisPrice(dP);
                    fout << productList[i].tostring();

                    cout << "Data Updated Successfully!" << endl;
                }
                else if (tempdiscount == 0) {
                    productList[i].setDisPrice(tempprice);
                    fout << productList[i].tostring();

                }
                i++;
            }
            if (found == false) {
                cout << "No product applicable for discount! Unable to calculate discounted price! \n";
            }

            // Deallocate memory
            delete[] productList;
            fout.close();
            fin.close();
            remove("Cart Management.txt");
            rename("UpdatedCart.txt", "Cart Management.txt");
        }

    }

    void calculateTotalPrice() {
        
            int counter = 0;

            ifstream fin;
            fin.open("Cart Management.txt");
            if (!fin.is_open())
            {
                cout << "Error opening filecart file 1." << endl;
                return;
            }

            string line;
            while (getline(fin, line))
            {
                counter++;
            }
            fin.close();

            OrderManagement productList; 

            fin.open("Cart Management.txt");
            if (!fin.is_open())
            {
                cout << "Error opening file cart file2." << endl;
                return;
            }



            int disId;
            disId = id;

            int tempid, tempinventory, tempcid;
            string tempname, temporary;
            float tempdiscount, tempprice, tempdisprice, tP=0;
            char temp;
            bool found = false;

            int i = 0;
            while (i < counter)
            {
                getline(fin, temporary, ':');
                fin >> tempid >> temp;
                getline(fin, temporary, ':');
                fin >> tempcid >> temp;
                getline(fin, temporary, ':');
                getline(fin, tempname, '-');
                fin >> tempprice >> temp;
                getline(fin, temporary, ':');
                fin >> tempinventory >> temp;
                getline(fin, temporary, ':');
                fin >> tempdiscount >> temp;
                getline(fin, temporary, ':');
                fin >> tempdisprice >> temp;

                if(tempcid==id){

                found = true;
                
                tP += tempdisprice;


                productList.setTotalPrice(tP);
                
                }
                i++;
                
            }
            cout << "Total Bill Calculated Sucessfully!" << endl;
            cout<<"Your Total Bill is: "<<productList.getTotalPrice()<<endl;
            


            // Deallocate memory
            //delete[] productList;

            fin.close();
            //remove("Cart Management.txt");
            //rename("UpdatedCart.txt", "Cart Management.txt");
        }
    
};

#endif



