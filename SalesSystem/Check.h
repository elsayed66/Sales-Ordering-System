#include"Payment.h"
#ifndef _CHECK_H
#define _CHECK_H
#include <iostream>
using namespace std;

#include<string>

class Check:public Payment
{
    string name;
    string Bank_id;
public:
    void inputData();
};
#endif
