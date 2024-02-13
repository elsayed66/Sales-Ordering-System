#ifndef _ORDERITEM_H
#define _ORDERITEM_H
#include<iostream>
using namespace std;
#include "Stock.h"

class OrderItem
{
private :
    int id;
    bool paidBool;
    Product *prdct;
    int quantity;
    double sale_Price;
    double tot_Price;

public:
    OrderItem();
    OrderItem(OrderItem&);


    void setProduct(Product * prdct);
    void setQuantity(int quantity){this->quantity = quantity;}
    void setId(int id){this->id = id;}
    double getTotPrice(){calcTotPrice(); return tot_Price;    }

    void UpdateQuantity(int new_quantity);
    void calcTotPrice(){tot_Price = quantity * sale_Price;}
    void fillNewQuantity();
    void checkQuantity();
    void paid();

    void readDataFile(ifstream& ifStrm,Product**prdctsList,int prdctsListSiz);
    friend ofstream& operator <<(ofstream& ofStrm,OrderItem& ordrItm);
    friend ostream& operator<<(ostream& ostrm, OrderItem& ordrItm);


    /*
    operator++
    operator--
    operator+=
    operator-=
    */
};
#endif
