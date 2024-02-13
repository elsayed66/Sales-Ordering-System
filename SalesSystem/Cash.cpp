#include "Cash.h"

void Cash::inputData()
{
    Payment::inputData();
    cout << "Please Enter Cash Value : ";
    cin >> cashValue;
}
