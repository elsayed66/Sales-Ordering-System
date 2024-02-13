#include "Company.h"

string Company::Print() const
{
    return Customer::Print()+"Company Name: " + company_name + " \t" +"Location : " + location + " \t";
}

void Company::fillData()
{
    Customer::fillData();
    cout << "Please Enter Company Name : ";
    getline(cin, company_name);
    cout << "Please Enter Location : ";
    getline(cin, location);
}

void Company::Update()
{
    // function update data of a Company

    short updTyp = -1;
    cout << Print() << endl;
    cout << "----------------------------------------------------------" << endl;
    cout << "(1) Change Phone \n"
         << "(2) Change Company Name \n"
         << "(3) Change Location \n"
         << "(0) Exit this menu\n";
    cout << "Please Choose A number to proceed : ";
    cin >> updTyp;
    cin.ignore();
    switch (updTyp)
    {
    case 0:
        break;
    case 1:
        cout << "Please Enter New Phone : ";
        getline(cin, phone);
        Update();
        break;
    case 2:
        cout << "Please Enter New Name : ";
        getline(cin, company_name);
        Update();
        break;
    case 3:
        cout << "Please Enter New Location : ";
        getline(cin, location);
        Update();
        break;
    default:
        cout << "\a Please Enter a valid Number(0-3)" << endl;
        Update();
    }


}


void Company::readDataFile(ifstream& inStrm)
{

    // inStrm>> id;
    getline(inStrm,phone,'^');
    getline(inStrm,company_name,'^');
    getline(inStrm,location);
    // check if space is read by getline
    if(phone[0] == ' ')
    {
        phone.erase(0,1);
    }

};
void Company::writeDataFile(ofstream& ofStrm)
{
    ofStrm<<2<<' ';
    //ofStrm<<id<<' ';
    ofStrm<<phone<<'^';
    ofStrm<<company_name <<'^';
    ofStrm<<location;
};

