#include "Product.h"

ostream& operator<<(ostream& ostrm, Product& prdct)
{
    //ostrm <<"[id] \tName \t Price \t Number \t Type";
    ostrm <<"id -> " << prdct.id << " \t" <<"Product Name : "  << prdct.name << " \t" << "Product Serial : " << prdct.number<<" \t" << "Price : " << prdct.price << " \t" << "Qantity : " << prdct.quantity << endl;
    return ostrm;
}

istream& operator>>(istream& istrm, Product& prdct)
{
    cout << "Please Enter Product Name : ";
    getline(istrm, prdct.name);
    cout << "Please Enter Product Serial : ";
    getline(istrm, prdct.number);
    cout << "Please Enter Product Price : ";
    istrm >> prdct.price;
    cout << "Please Enter Product Quantity : ";
    istrm >> prdct.quantity;
    cin.ignore();
    return istrm;
    // TODO: insert return statement here
}

ofstream& operator<<(ofstream& ofstrm, Product& prdct)
{
    // '^' -> is a signal to the end of a string to be used during reading data
    ofstrm << prdct.price<<' ';
    ofstrm << prdct.quantity<<' ';
    ofstrm << prdct.name<<'^';
    ofstrm << prdct.number;
    return ofstrm;
}

ifstream& operator>>(ifstream& ifstrm, Product& prdct)
{
    ifstrm >> prdct.price;
    ifstrm >> prdct.quantity;
    getline(ifstrm, prdct.name,'^');
    getline(ifstrm, prdct.number);
    // delete space read by first getline statement
    if(prdct.name[0] == ' ')
    {
        prdct.name.erase(0,1);
    }

    return ifstrm;
}

Product::Product()
{

}

void Product::Update()
{

    // function update data of a Product

    short updTyp = -1;
    cout << (*this);
    cout << "----------------------------------------------------------" << endl;
    cout << "(1) Change Product Name \n"
         << "(2) Change Price \n"
         << "(3) Change Number \n"
         << "(4) Change Product type \n"
         << "(0) Exit this menu\n";
    cout << "Please Choose A number to proceed : ";
    cin >> updTyp;
    cin.ignore();
    switch (updTyp)
    {
    case 0:
        break;
    case 1:
        cout << "Please Enter New Product Name : ";
        getline(cin, name);
        Update();
        break;
    case 2:
        cout << "Please Enter New Price : ";
        cin>>price;
        cin.ignore();
        Update();
        break;
    case 3:
        cout << "Please Enter New Number : ";
        getline(cin, number);
        Update();
        break;
    case 4:
        cout << "Please Enter New Quantity : ";
        cin>>quantity;
        cin.ignore();
        Update();
        break;
    default:
        cout << "\a Please Enter a valid Number(0-3)" << endl;
        Update();
    }


}

void Product::operator=(Product& prdct)
{
    // assigning values of two objects
    id = prdct.id;
    number = prdct.number;
    name = prdct.name;
    price = prdct.price;
    quantity = prdct.quantity;

}
