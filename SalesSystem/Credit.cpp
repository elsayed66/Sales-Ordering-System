#include "Credit.h"
#include<ctime>

Credit::Credit()
{
    expireDate.tTime = time(0);
    expireDate.tTimePoint = localtime(&expireDate.tTime);
}

void Credit::inputData()
{
    Payment::inputData();
    cin.ignore();
    cout << "Please Enter Card Number : ";
    getline(cin, nubmer);
    cout << "Please Enter Card type : ";
    getline(cin, type);
    // Take a valid expiration Date
    int expMonth, expYear;
    cout << "Please Enter card Expiration Date\n"
         <<"Enter Expiration Month :";
    while (true)
    {
        cin >> expMonth;
        if (expMonth >= 1 && expMonth <= 12)
            break;
        else
            cout << "\aPlease Enter a valid Month ";
    }
    cout << "Enter Expiration year as follow :- 2030 :";
    while (true)
    {
        cin >> expYear;
        if (expYear >= expireDate.tTimePoint->tm_year)
            break;
        else
            cout << "\aPlease Enter a valid Date ";
    }
    expireDate.expTime = to_string(expMonth) +'/' +to_string(expYear);


}
