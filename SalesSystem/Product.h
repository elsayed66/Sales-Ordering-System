#ifndef _PRODUCT_H
#define _PRODUCT_H
#include<iostream>
using namespace std;
#include<string>
#include<fstream>

class Product
{
private:
    int id;
    string number;
    string name;
    double price;
    int quantity;

public:
    Product();
    void Update();
    void setId(int id){this->id = id;}
    string getNumber(){return number;}
    double getPrice(){return price;}
    int getId(){return id;}
    int getQuantity(){return quantity;}

    void operator = (Product& prdct);
    Product& operator -=(int i){quantity -= i; return *this;}
    friend ostream& operator <<(ostream& ostrm, Product& prdct);
    friend istream& operator >>(istream& istrm, Product& prdct);
    friend ofstream& operator <<(ofstream& ofstrm, Product& prdct);
    friend ifstream& operator >>(ifstream& ifstrm, Product& prdct);
};
#endif

