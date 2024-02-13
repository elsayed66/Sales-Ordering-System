#ifndef _PERSON_H
#define _PERSON_H
#include<iostream>
using namespace std;

#include<string>
#include"Customer.h"

class Person:public Customer
{
private:
    string billing_address;
    string fullName;
public:
    string Print()const;
    void fillData();
    void Update();
    void readDataFile(ifstream& inStrm);
    void writeDataFile(ofstream& inStrm);

};
#endif

