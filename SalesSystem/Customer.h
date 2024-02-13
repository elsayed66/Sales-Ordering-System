#ifndef _CUSTOMER_H
#define _CUSTOMER_H
#include <iostream>
using namespace std;

#include<string>
#include<fstream>

class Customer
{
protected:
    int id;
    string phone;

public:
    Customer();
    virtual ~Customer() {};
    string getPhone()
    {
        return phone;
    }
    void setId(int id)
    {
        this->id = id;
    }

    virtual void fillData();
    virtual string Print()const;
    virtual void Update()=0;

    friend 	ostream& operator <<(ostream& outStrm, Customer& cust);
    friend istream& operator >>(istream& inStrm, Customer& cust);

    virtual void readDataFile(ifstream& inStrm) = 0;
    virtual void writeDataFile(ofstream& inStrm) = 0;
    friend 	ofstream& operator <<(ofstream& outStrm, Customer& cust);
    friend ifstream& operator >>(ifstream& inStrm, Customer& cust);

};
#endif
