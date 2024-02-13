#ifndef _CASH_H
#define _CASH_H

#include"Payment.h"

class Cash:public Payment
{
private:
    double cashValue;
public:
    void inputData();
};
#endif
