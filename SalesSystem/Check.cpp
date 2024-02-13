#include "Check.h"

void Check::inputData()
{
    Payment::inputData();
    cout << "Please enter Check Name : ";
    getline(cin, name);
    cout << "Please Enter Bank Id : ";
    getline(cin, Bank_id);
}
