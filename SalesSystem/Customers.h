#ifndef _CUSTOMERS_H
#define _CUSTOMERS_H
#include<iostream>
using namespace std;

#include<string>
#include<vector>
#include"Customer.h"
#include"Person.h"
#include"Company.h"
#include"Stock.h"
#include"Transaction.h"
#include"Product.h"

class Customers
{
private:
    Customer** customersList;
    int countCustomers;
    int customersListSiz;
    Customer* custmrPntr;

    Stock* stockOfProducts;

    Transaction* transactionList;
    int trnscLstSiz;
    int trnscCount;

    Order* ordersList;
    int ordrsCount;
    int ordrsLstSiz;

    Product*productsList;
    int productsCount;
    int productsListSiz;

    void writeApplicationData();
    void readApplicationData();

public:
    Customers();
    ~Customers();
    template<class t>
    void incAnyList(t*& defArray, int& siz);

    void printCustomers()const;
    void AddCustomer();
    void UpdateCustomer();
    void DeleteCustomer();

    void addTransaction();
    void printTransactions();

    void addOrder();
    void updateOrder(bool choos);
    void payOrder();
    void printOrders();

    void addProductToStock();
    void addProduct();
    void updateProduct();
    void deleteProduct(bool stat=1);
    void PrintProducts(bool stat=1);
};
#endif

