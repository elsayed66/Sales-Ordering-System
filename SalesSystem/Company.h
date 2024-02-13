#ifndef _COMPANY_H
#define _COMPANY_H

#include<iostream>
using namespace std;
#include<string>
#include"Customer.h"

class Company:public Customer
{
private:
    string location;
    string company_name;
public:
    string Print() const;
    void fillData();
    void Update();
    void readDataFile(ifstream& inStrm);
    void writeDataFile(ofstream& inStrm);
};
#endif

