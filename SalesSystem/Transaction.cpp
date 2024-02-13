#include "Transaction.h"
#include<cstring>

template<class t>
void incrsPointerLstSiz(t**& defArr, int& siz);

Transaction::Transaction()
{
    // set the data during constructing Transcation
    Transaction_date.tTime = time(NULL);
    Transaction_date.tdate = ctime(&Transaction_date.tTime);
    paidValue = 0;

    ordrsLstSiz = 10;
    ordrscount = 0;
    ordersList = new Order * [ordrsLstSiz];

    totalTransValue = 0;
}

Transaction::~Transaction()
{
    // Deleting occupied Memory
}

Order& Transaction::GetOrder(int order_id = 0)
{
    return *ordersList[id];
}

void Transaction::addOrders(Order* ordersArr,int len)
{

    // each time putting element starts to keep aware of any change done to orders
    ordrscount = 0;

    for (auto i = 0; i < len; ++i)
    {
        if (ordersArr[i].getCustomer() == cstmr)
        {
            ordersList[ordrscount] = (ordersArr + i);
            ++ordrscount;
            // check if the array need to be resized
            if (ordrscount >= ordrsLstSiz)
                incrsPointerLstSiz(ordersList, ordrsLstSiz);
        }
    }
}



ostream& operator<<(ostream& ostrm, Transaction& trnsctn)
{
    ostrm<<endl;
    ostrm<<"Transaction id ->{"<<trnsctn.id<<"} \n";
    ostrm << "Transaction Date : \n\t\t\t"<< trnsctn.Transaction_date.tdate << endl;
    ostrm << "Customer Data : " << endl;
    ostrm << "-----------------\n";
    ostrm << *trnsctn.cstmr << endl;
    ostrm << "Orders Data : " << endl;
    ostrm << "-----------------\n";
    trnsctn.totalTransValue = 0;
    for (auto i = 0; i < trnsctn.ordrscount; i++)
    {
        ostrm << (*trnsctn.ordersList[i]);
        trnsctn.totalTransValue += trnsctn.ordersList[i]->getOrdrPrice();
    }
    ostrm<<"----------------------------------------------\n";
    ostrm << "\n\nTotal Transaction Value : " << trnsctn.totalTransValue;
    ostrm<<"\n\t\t\t======================================\n";

    return ostrm;
}

ofstream& operator <<(ofstream& ofStrm, Transaction& trnsctn)
{
    ofStrm<<trnsctn.Transaction_date.tdate<<'^';
    ofStrm<<trnsctn.totalTransValue<<' ';
    ofStrm<<trnsctn.cstmr->getPhone();

};

void Transaction::readFileData(ifstream& ifStrm,Customer** cstmrsLst,int cstmrsLstSiz,Order* ordersArr,int len)
{
    string dateVal,custPhone;
    char* tempCharPoint;

    getline(ifStrm,dateVal,'^');
    ifStrm>>totalTransValue;
    getline(ifStrm,custPhone);

    //delete a space which is been taken by getline
    if(custPhone[0]==' ')
    {
        custPhone.erase(0,1);
    }
    // find customer and put its address inside the transaction
    for(int i =0; i<cstmrsLstSiz; ++i)
    {
        if(cstmrsLst[i]->getPhone() == custPhone)
        {
            this->cstmr = cstmrsLst[i];
            break;
        }
    }
    addOrders(ordersArr,len);

    // convert string type into array of characters
    tempCharPoint =new char[dateVal.length()+1];
    strcpy(tempCharPoint,dateVal.c_str());
    Transaction_date.tdate = (tempCharPoint);
};




template<class t>
void incrsPointerLstSiz(t**& defArr, int& siz)
{
    int incVal = 5;
    // increase size of array using temporary pointer
    t** tempPointer = new t*[siz+ incVal];
    copy(defArr, defArr + siz, tempPointer);

    delete[]defArr;
    defArr = tempPointer;
    siz += incVal;
}
