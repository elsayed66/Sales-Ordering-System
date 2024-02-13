#ifndef _TRANSACTION_H
#define _TRANSACTION_H

#include<vector>
#include"Order.h"
#include"Order.h"
#include"Customer.h"

#include"Payment.h"
#include"Credit.h"
#include"Cash.h"
#include"Check.h"

class Transaction
{
private:
    int id;
    Time Transaction_date;
    Customer* cstmr;
    double totalTransValue;
    double paidValue;

    // list of pointers to orders to take order data only once
    Order** ordersList;
    int ordrscount;
    int ordrsLstSiz;
public:
    Transaction();
    ~Transaction();
    void setCustomer(Customer* cstmr){this->cstmr = cstmr;}
    void setId(int id){this->id = id;}
    Order& GetOrder(int order_id);
    void addOrders(Order*ordersArr,int len);

    void readFileData(ifstream& ifStrm,Customer** cstmrsLst,int cstmrsLstSiz,Order* ordersArr,int len);
    friend ofstream& operator <<(ofstream& ostrm, Transaction& trnsctn);
    friend ostream& operator <<(ostream& ofSrm, Transaction& trnsctn);

};
#endif
