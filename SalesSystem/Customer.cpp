#include "Customer.h"


Customer::Customer()
{
}
ostream& operator<<(ostream& outStrm, Customer& cust)
{
    outStrm<<cust.Print();
    return outStrm;
}

istream& operator>>(istream& inStrm, Customer& cust)
{
    cust.fillData();
    return inStrm;
}

string Customer::Print()const
{
    // function return data of each customer as string
    return "id ->[" + to_string(id) + ']' + " \t" "Phone : "+ phone + " \t";
}



void Customer::fillData()
{
    // function fill data by taking inputs from user
    cout << "Please Enter Customer Phone : ";
    getline(cin, phone);
}

ofstream& operator <<(ofstream& oFStrm, Customer& cust)
{
    cust.writeDataFile(oFStrm);
    return oFStrm;
};
ifstream& operator >>(ifstream& iFStrm, Customer& cust)
{
    cust.readDataFile(iFStrm);
    return iFStrm;
};
