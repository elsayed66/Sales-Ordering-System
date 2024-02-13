#include "Payment.h"
#include<ctime>
Payment::Payment()
{
    // set time of payment as constructing object
    paid_date.tTime = time(NULL);
    paid_date.tdate = ctime(&paid_date.tTime);
}

void Payment::inputData()
{
    cout << "Please Enter Payment Amount : ";
    cin >> amount;
}
