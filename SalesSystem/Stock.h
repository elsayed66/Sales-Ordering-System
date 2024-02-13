#ifndef _STOCK_H
#define _STOCK_H
#include<iostream>
using namespace std;
#include<string>
#include<vector>
#include "Product.h"
class Stock
{
private:
    int stk_countProducts;
    Product **stk_productsList;
    int stk_productsArrSiz;


public:
    Stock();
    ~Stock();

    Product** GetProductsList()
    {
        return stk_productsList;
    }
    Product* getProductById(int id);
    int GetProductsCount()
    {
        return stk_countProducts;
    }
    int GetQuantity(int product_id)
    {
        return stk_productsList[product_id - 1]->getQuantity();
    }

    void AddProductToStock(Product*prdctsList);
    void updateProduct();
    bool DeleteProduct(int id);
    void readDataFile(ifstream& ifStrm,Product* prdcstList, int prdctsCount);
    void writeDataFile(ofstream& ofStrm);

    template<class t>
    void incrsPointerLstSiz(t**& defArr,int& incVal);

    friend ostream& operator <<(ostream& ostrm, Stock& prdcstockt);
};
#endif

