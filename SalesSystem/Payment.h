#ifndef _PAYMENT_H
#define _PAYMENT_H
#include<iostream>
using namespace std;

struct Time
{
    time_t tTime;
    char* tdate;
};

class Payment
{
private:
    Time paid_date;
    double amount;

public:
    Payment();
    virtual ~Payment() {};
    virtual void inputData();
    double getAmount()
    {
        return amount;
    }
};
#endif
