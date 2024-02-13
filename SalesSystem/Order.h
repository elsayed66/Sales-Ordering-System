#ifndef _ORDER_H
#define _ORDER_H

#include<iostream>
#include<string>
using namespace std;
#include<ctime>
#include"OrderItem.h"
#include"Stock.h"
#include"Customer.h"
#include"Payment.h"
#include"Credit.h"
#include"Cash.h"
#include"Check.h"

enum OrderStatus
{
    NEW = 0, HOLD, PAID, CANCELED
};

class Order
{
private:
    static bool numberFreqArr[100000];
    int id;
    int number;
    Time date;
    double totalPrice;
    double PaidValue;
    OrderStatus stat;

    Customer* cstmr;

    OrderItem* orderItemsLIst;
    int itemsCount;
    int itemsLstSiz;

    template<class t>
    void incAnyListSiz(t*& arrOfObjcts, int& siz);
public:
    Order();
    Order(Order& ordr2);
    ~Order();
    void CreateOrder(Stock* stock);
    void changeOrderStatus(int status);
    void addItems(Stock* stock);
    void updateItemsQuantity();
    void calcTotalValue();
    void pay();

    Customer* getCustomer()
    {
        return cstmr;
    }
    string getOrderStatus();
    double getOrdrPrice()
    {
        calcTotalValue();
        return totalPrice;
    }

    void setCustomer(Customer* cstmr)
    {
        this->cstmr = cstmr;
    }
    void setId(int id)
    {
        this->id = id;
    }
    void setNumber(int number)
    {
        if(number>=1 && number<= 100000)
        {
            this->numberFreqArr[this->number-1] = false;
            this->number = number;
            this->numberFreqArr[number -1] = true;
        }
    }

    void readOrdersFile(ifstream& ifStrm,Customer** customersList,int cstmrLstSiz,Product** prdctsList,int prdctsListSiz);

    friend ostream& operator<<(ostream& ostrm, Order& ordr);
    friend istream& operator>>(istream& istrm, Order& ordr);

    friend ofstream& operator<<(ofstream& ofStrm, Order& ordr);


};
#endif
