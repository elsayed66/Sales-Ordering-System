// OOP3.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <iostream>         // cin, cout
#include <cstdlib>          // cls
#include <windows.h>        // Sleep
#include <cstring>          // string, to_string
#include <bits/stdc++.h>    // stringstream
#include <windows.h>        // SetConsoleTextAttribute
#include<conio.h>
using namespace std;
HANDLE cout_handle = GetStdHandle(STD_OUTPUT_HANDLE);
/*
    My Exceptions list
      -1 -> Empty Function's implementation

*/
#include"Customers.h"
Customers ProgObj;

// template Functions
void intro();
void MainScreen();
void handle_dataEntry();
void handle_salesProcess();
void handle_print();
void handle2_customers();
void handle2_stocK();
void handle2_updateOrder();


int main()
{
    MainScreen();
    return 0;
}




// Functions Implementation

/** ASSISTANT INLINE FUNCTIONS **/
inline void wait_or_clear( float sec, bool clear_screen = false)
{
    Sleep(sec*1000);
    if (clear_screen) system("cls");
}

inline void printline(string msg, bool end_line = true, int color_code=15)
{
    SetConsoleTextAttribute(cout_handle, color_code);
    cout <<  msg << (end_line?"\n":"\t");
}
inline void print_try_again(){
    printline("\n\n\n\aInvalid Choice Try Again!!!!!!!!",1,4);
    wait_or_clear(3, 1);
}

/** MAIN PRINT MENU FUNCTION **/
int get_menu_choise(string menu, int level = 0)
{
    stringstream X(menu);
    string line, padding;
    int i = 1;
    for(int p=0; p<level+1; ++p)
        padding +="\t";

    while (getline(X, line, ','))
    if(level==0)
        printline(padding + '['+to_string(i++) +']'+ ". " + line,1,level+11);
        else if(level==1)
        printline(padding + '('+to_string(i++) +')'+ ". " + line,1,level+11);
        else if(level==2)
        printline(padding + '{'+to_string(i++) +'}'+ ". " + line,1,level+11);

    printline(level?padding+"<0>. RETURN BACK":padding+"<0>. EXIT APP",1,5);
    int c;
    printline("ENTER YOUR CHOICE :",false,2);
    cin >> c;
    return c;
}

void intro(){
// Intro Screen for the Application

    printline ("\n\n\n\n\n\n\n\n\n\n\n");
    printline ("\t\t\t\t     ==============================",1,9);
    printline("\t\t\t\t\t  SALES ORDER SYSTEM",1,10);
    printline("\t\t\t\t     ==============================",1,9);
    Sleep(2500);
    system("cls");
}

void outro(){
    wait_or_clear(0,1);
	printline( "\n\n\n\t\t\t*** Programmed by : Elsayed Ahmed Elsayed :) ***\n\n\n\n\n\n" ,1,112);
    wait_or_clear(2.5);
}

void MainScreen()
{
    // Application main Screen

    intro();
    int decs = -1;
    while (decs)
    {

        printline("\t\t\t Main Menu",1,10);
        printline("\t\t\t-----------");
        printline("\n\n\n");
        decs = get_menu_choise("DATA ENTRY,SALES PROCESS,PRINTS",0);
        switch (decs)
        {
        case 1:
            handle_dataEntry();
            break;
        case 2:
            handle_salesProcess();
            break;
        case 3:
            handle_print();
            break;
        case 0 :
            outro();
            break;
        default:
            print_try_again();
            wait_or_clear(3,true);
        }
    }


}

void handle_dataEntry()
{
    int decs = 1;
    while (decs)
    {
        system("cls");
        printline("\t\t\t Data Entry Menu",1,6);
        printline("\t\t\t-----------------",1,1);
        printline("\n\n");
        decs = get_menu_choise("Customers Data,Products Data,",1);
        switch (decs)
        {
        case 1:
            handle2_customers();
            break;
        case 2:
            handle2_stocK();
            break;
        case 0:
            wait_or_clear(0,1);
            return;
        default:
            print_try_again();
        }
    }
}

void handle_salesProcess()
{
    int decs = 1;
    while (decs)
    {
        system("cls");
        printline("\t\t\t Sales Process Menu",1,6);
        printline("\t\t\t--------------------",1,1);
        printline("\n\n");
        decs = get_menu_choise("Add Transaction,Add Order,Update Order,Pay Order",1);
        switch (decs)
        {
        case 1:
            ProgObj.addTransaction();
            wait_or_clear(3);
            break;
        case 2:
            ProgObj.addOrder();
            wait_or_clear(3);
            break;
        case 3:
            handle2_updateOrder();
            break;
        case 4:
            ProgObj.payOrder();
             wait_or_clear(3);
            break;
        case 0:
            wait_or_clear(0,1);
            return;
        default:
            print_try_again();
        }
    }
}

void handle_print()
{
    int decs = 1;
    while (decs)
    {
        system("cls");
        printline("\t\t\t Printing Menu",1,6);
        printline("\t\t\t--------------------",1,1);
        printline("\n\n");
        decs = get_menu_choise("Customers,Products Data,Stock Data,Orders Data,Transactions Data",1);
        switch (decs)
        {
        case 1:
            ProgObj.printCustomers();
            printline("Press Any Key to Proceed : ", false);
            _getch();
            break;
        case 2:
            ProgObj.PrintProducts();
            printline("Press Any Key to Proceed : ", false,13);
            _getch();
            break;
        case 3:
            ProgObj.PrintProducts(0);
            printline("Press Any Key to Proceed : ", false,13);
            _getch();
            break;
        case 4:
            ProgObj.printOrders();
            printline("Press Any Key to Proceed : ", false,13);
            _getch();
            break;
        case 5:
            ProgObj.printTransactions();
            printline("Press Any Key to Proceed : ", false,13);
            _getch();
            break;
        case 0:
            wait_or_clear(0,1);
            return;
        default:
            print_try_again();
        }
    }
}

void handle2_customers()
{
    int decs = 1;
    while (decs)
    {
        system("cls");
        printline("\t\t\t Customers Menu",1,9);
        printline("\t\t\t---------------",1,11);
        printline("\n\n");
        decs = get_menu_choise("Add Customer,Update Customer,Delete Customer",2);
        switch (decs)
        {
        case 1:
            ProgObj.AddCustomer();
             wait_or_clear(3);
            break;
        case 2:
            system("cls");
            ProgObj.UpdateCustomer();
             wait_or_clear(3);
            break;
        case 3:
            ProgObj.DeleteCustomer();
            wait_or_clear(3);
            break;
        case 0:
            wait_or_clear(0,1);
            return;
        default:
            print_try_again();
        }
    }

}

void handle2_stocK()
{
    int decs = 1;
    while (decs)
    {
        system("cls");
        printline("\t\t\t  Products Menu",1,9);
        printline("\t\t\t---------------",1,11);
        printline("\n\n");
        decs = get_menu_choise("Add new Product,Update Product,Delete Product,Add Product To Stock,Remove Product From Stock",2);
        switch (decs)
        {
        case 1:
            ProgObj.addProduct();
            wait_or_clear(3);
            break;
        case 2:
            ProgObj.updateProduct();
            wait_or_clear(3);
            break;
        case 3:
            ProgObj.deleteProduct();
            wait_or_clear(3);
            break;
        case 4:
            ProgObj.addProductToStock();
            wait_or_clear(3);
            break;
        case 5:
            ProgObj.deleteProduct(0);
            wait_or_clear(3);
            break;
        case 0:
            wait_or_clear(0,1);
            return;
        default:
            print_try_again();
        }
    }
}

void handle2_updateOrder()
{
    int decs = 1;
    while (decs)
    {
        system("cls");
        printline("\t\t\t Update Order",1,9);
        printline("\t\t\t---------------",1,11);
        printline("\n\n");
        decs = get_menu_choise("Order Item Quantity,Order Statues",2);
        cin.ignore();
        switch (decs)
        {
        case 1:
            ProgObj.updateOrder(1);
            wait_or_clear(3);
            break;
        case 2:
            ProgObj.updateOrder(0);
            wait_or_clear(3);
            break;
        case 0:
            wait_or_clear(0,1);
            return;
        default:
            print_try_again();
        }
    }
}
