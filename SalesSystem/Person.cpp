#include "Person.h"

string Person::Print() const
{
    return Customer::Print() +"Name : " + fullName + " \t" + "Billing Address : " + billing_address + " \t";
}

void Person::fillData()
{
    Customer::fillData();
    cout << "Please Enter billing Address : ";
    getline(cin, billing_address);
    cout << "Please Enter Full Name : ";
    getline(cin, fullName);
}

void Person::Update()
{
    // function update data of a person customer

    short updTyp = -1;
    cout << Print() << endl;
    cout << "----------------------------------------------------------"<<endl;
    cout << "(1) Change Phone \n"
         << "(2) Change Name \n"
         << "(3) Change Location \n"
         << "(0) Exit this menu\n";
    cout << "Please Choose A number to proceed : ";
    cin >> updTyp;
    cin.ignore();
    switch (updTyp)
    {
    case 0 :
        break;
    case 1:
        cout << "Please Enter New Phone : ";
        getline(cin, phone);
        Update();
        break;
    case 2:
        cout << "Please Enter New Full Name : ";
        getline(cin, fullName);
        Update();
        break;
    case 3:
        cout << "Please Enter New Billing Address : ";
        getline(cin, billing_address);
        Update();
        break;
    default:
        cout << "\a Please Enter a valid Number(0-3)" << endl;
        Update();
    }

}


void Person::readDataFile(ifstream& inStrm)
{

    //inStrm>>id;
    getline(inStrm,phone,'^');
    getline(inStrm,fullName,'^');
    getline(inStrm,billing_address);
    // check if space is read by getline
    if(phone[0] == ' ')
    {
        phone.erase(0,1);
    }

};
void Person::writeDataFile(ofstream& ofStrm)
{
    ofStrm<<1<<' ';
    //ofStrm<<id<<' ';
    ofStrm<<phone<<'^';
    ofStrm<<fullName<<'^';
    ofStrm<<billing_address;
};
