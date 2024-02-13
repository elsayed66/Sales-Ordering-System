#include "OrderItem.h"

OrderItem::OrderItem()
{
    prdct = nullptr;
    paidBool = false;
}

OrderItem::OrderItem(OrderItem& obj)
{
    this->prdct = obj.prdct;
    this->quantity = obj.quantity;
    this->sale_Price = obj.sale_Price;
    this->tot_Price = obj.tot_Price;
}

void OrderItem::UpdateQuantity(int new_quantity)
{
    // change qunatity after checking the quantity of product found
    if(new_quantity >= 0 && new_quantity<= prdct->getQuantity())
        quantity = new_quantity;
    else
    {
        quantity = prdct->getQuantity();
    }
    calcTotPrice();
}

void OrderItem::setProduct(Product * prdct)
{
    this->prdct = prdct;
    sale_Price = prdct->getPrice();
}

void OrderItem::fillNewQuantity()
{
    int newQuantity;
    cout << "Please Enter New Quantity(0 - " << prdct->getQuantity() << ") : ";
    while (true)
    {
        cin >> newQuantity;
        if (newQuantity >= 0 && newQuantity <= prdct->getQuantity())
            break;
        else
            cout<<"Please Enter a valid Quantity (0 - " << prdct->getQuantity() << ") : ";
    }
    quantity = newQuantity;
}

void OrderItem::checkQuantity()
{
    // function check if the quantity can be payed or not
    // if not it will change quantity to maximum quantity allowed
    if(quantity > prdct->getQuantity())
    {
        quantity = prdct->getQuantity();
    }
}

void OrderItem::paid()
{
    (*prdct) -= quantity;
    paidBool = true;
}

ostream& operator<<(ostream& ostrm, OrderItem& ordrItm)
{
    ostrm<<'\n';
    ostrm<<"Product Data : \n";
    ostrm << (*ordrItm.prdct)<<endl;
    ostrm << "Ordered Quantity : " << ordrItm.quantity<<endl;
    ostrm << "Total Order Item Price : " << ordrItm.getTotPrice() << endl;
    ostrm << "\t\t\t-------------------------------------" << endl;

    return ostrm;
}

ofstream& operator <<(ofstream& ofStrm,OrderItem& ordrItm)
{
    ofStrm<<ordrItm.paidBool<<' ';
    ofStrm<<ordrItm.quantity<<' ';
    ofStrm<<ordrItm.sale_Price<<' ';
    ofStrm<<ordrItm.prdct->getNumber();
}

void OrderItem::readDataFile(ifstream& ifStrm,Product**prdctsList,int prdctsListSiz)
{
    string prdctNum;
    ifStrm>>paidBool;
    ifStrm>>quantity;
    ifStrm>>sale_Price;
    ifStrm>>prdctNum;

    // get address of product to set id inside order item
    for(int i=0; i< prdctsListSiz; ++i)
    {
        if(prdctsList[i]->getNumber() == prdctNum)
        {
            prdct = prdctsList[i];
            break;
        }
    }
    this->calcTotPrice();
}



