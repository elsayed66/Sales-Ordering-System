#ifndef _CREDIT_H
#define _CREDIT_H
#include<iostream>
using namespace std;

#include<string>
#include"Payment.h"
struct expTime
{
    time_t tTime;
    tm* tTimePoint;
    string expTime;
};

class Credit:public Payment
{
private:
    string nubmer;
    expTime expireDate;
    string type;
public:
    Credit();
    void inputData();
};
#endif
