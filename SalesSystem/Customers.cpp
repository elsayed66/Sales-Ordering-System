#include "Customers.h"
#include<fstream>

template<class t>
void incrsPointerLstSiz(t**& defArr, int& siz);

void Customers::writeApplicationData()
{
    {
        ofstream fOut;
        fOut.open("ProductsData.txt");
        // using operator overloading to write data on specific file
        for (auto i = 0; i < productsCount; ++i)
        {
            fOut << productsList[i];
            // to write on new line
            if(i != productsCount -1 )
                fOut<<'\n';
        }
        fOut.close();
    }


    {
        // write customers data

        ofstream fOut;

        fOut.open("CustomersData.txt");
        for (auto i = 0; i < countCustomers; ++i)
        {
            fOut << (*customersList[i]);
            if(i != countCustomers -1 )
                fOut<<'\n';
        }
        fOut.close();
    }

    {
        // write stock data
        ofstream fOut;

        fOut.open("StockData.txt");
        stockOfProducts->writeDataFile(fOut);
        fOut.close();
    }

    {
        // write Orders data
        ofstream fOut;

        fOut.open("OrdersData.txt");
        for (int i = 0; i < ordrsCount; ++i)
        {
            fOut <<ordersList[i];
            if(i != ordrsCount -1 )
                fOut<<'\n';
        }
        fOut.close();
    }

    {
        // write Transactions data
        ofstream fOut;

        fOut.open("TransactionsData.txt");
        for (int i = 0; i < trnscCount; ++i)
        {
            fOut <<transactionList[i];
            if(i != trnscCount -1 )
                fOut<<'\n';
        }
        fOut.close();
    }


}

void Customers::readApplicationData()
{
    {
        // read data of products
        ifstream fIn;
        fIn.open("ProductsData.txt");
        if (!fIn)
        {
            cout << "Error Opening File ";
            return;
        }

        while (!fIn.eof())
        {
            productsList[productsCount].setId(productsCount + 1);

            fIn >> productsList[productsCount];
            ++productsCount;

            if (productsCount >= productsListSiz)
                incAnyList(productsList, productsListSiz);
        }

        fIn.close();
    }

    {
        // read data of Customers
        ifstream fIn;
        fIn.open("CustomersData.txt");
        if (!fIn)
        {
            cout << "Error Opening File ";
            return;
        }

        Customer* custPoint;
        short typ = 0;
        // type -> 1 for Person , 2 for Company
        while (!fIn.eof())
        {
            fIn>>typ;
            if(typ==1)
            {
                custPoint = new Person;
            }
            else if(typ == 2)
            {
                custPoint = new Company;
            }
            else continue;

            customersList[countCustomers] = custPoint;
            customersList[countCustomers]->setId(countCustomers + 1);

            fIn >> (*customersList[countCustomers]);
            ++countCustomers;

            if (countCustomers >= customersListSiz)
                incrsPointerLstSiz(customersList, customersListSiz);
        }

        fIn.close();
    }

    {
        // read data of Stock
        ifstream fIn;
        fIn.open("StockData.txt");
        if (!fIn)
        {
            cout << "Error Opening File ";
            return;
        }

        stockOfProducts->readDataFile(fIn,productsList,productsCount);
        fIn.close();
    }

    {
        // read data of Orders
        ifstream fIn;
        fIn.open("OrdersData.txt");
        if (!fIn)
        {
            cout << "Error Opening File ";
            return;
        }

        while(!fIn.eof())
        {
            ordersList[ordrsCount].readOrdersFile(fIn,customersList,countCustomers,stockOfProducts->GetProductsList(),stockOfProducts->GetProductsCount());
            ordersList[ordrsCount].setId(ordrsCount+1);
            ++ordrsCount;
            if(ordrsCount>= ordrsLstSiz-1)
                incAnyList(ordersList,ordrsLstSiz);
        }

        fIn.close();
    }

    {
        // read Data of Transactions
        ifstream fIn;
        fIn.open("TransactionsData.txt");
        if (!fIn)
        {
            cout << "Error Opening File ";
            return;
        }

        while(!fIn.eof())
        {
            transactionList[trnscCount].readFileData(fIn,customersList,countCustomers,ordersList,ordrsCount);
            transactionList[trnscCount].setId(trnscCount+1);
            ++trnscCount;
            if(trnscCount>=trnscLstSiz-1)
                incAnyList(transactionList,trnscLstSiz);
        }

        fIn.close();
    }



}

Customers::Customers()
{
    // initialization of customers list
    custmrPntr = nullptr;
    customersListSiz = 10;
    countCustomers = 0;
    customersList = new Customer*[customersListSiz];

    // initialization of transaction list
    trnscLstSiz = 10;
    trnscCount = 0;
    transactionList = new Transaction[trnscLstSiz];

    stockOfProducts = new Stock;

    ordrsCount = 0;
    ordrsLstSiz = 10;
    ordersList = new Order[ordrsLstSiz];

    productsListSiz = 10;
    productsCount = 0;
    productsList = new Product[productsListSiz];

    readApplicationData();

}

Customers::~Customers()
{
    // writing data on files upon closing the program
    writeApplicationData();




    // delete memeory occupied dynamically by customers list
    for (size_t i = 0; i < countCustomers; i++)
    {
        delete customersList[i];
    }
    delete []customersList;

    delete stockOfProducts;

    delete[]ordersList;

    delete[]productsList;
}

template<class t>
void incrsPointerLstSiz(t**& defArr, int& siz)
{
    int incVal = 5;
    // increase size of array using temporary pointer
    t** tempPointer = new t*[siz+ incVal];
    copy(defArr, defArr + siz, tempPointer);

    delete[]defArr;
    defArr = tempPointer;
    siz += incVal;
}

void Customers::printCustomers()const
{
    for (auto i = 0; i < countCustomers; ++i)
        cout<<(* customersList[i] )<< endl;
}
void Customers::AddCustomer()
{
    short cstmrTyp = 0;
    cout << "Please Choose Type of Customer" << endl;
    cout << "[1] Person \t \t [2] Company" << endl;

    //Loop check for the validay of the input taken from user
    while (true)
    {
        cin >> cstmrTyp;
        if (cstmrTyp >= 1 && cstmrTyp <= 2)
            break;
        else
            cout << "\aPlease Enter a valid number (1 or 2)"<<endl;
    }
    cin.ignore();
    if (cstmrTyp == 1)
    {
        custmrPntr = new Person;
        //custmrPntr->fillData();
        cin>>(*custmrPntr);
    }
    else
    {
        custmrPntr = new Company;
        cin >> (*custmrPntr);
    }
    // inserting the added element into array of pointers and give it an id
    customersList[countCustomers] = custmrPntr;
    customersList[countCustomers]->setId(countCustomers+1);
    ++countCustomers;

    // check if the array need to be resized to take new elements
    if(countCustomers>=customersListSiz-1)
        incrsPointerLstSiz(customersList,customersListSiz);

    cout << "A new customer is Added Successfully \n"
         << "--------------------------------------" << endl;
}

void Customers::UpdateCustomer()
{
    // Updating Customers Menu
    short custId;
    cout << "\t\t\tUpdating Customers Menu\n"
         << "\t\t\t------------------------\n\n\n" << endl;

    cout << "Please Enter Customer Id : ";
    while (true)
    {
        cin >> custId;
        if (countCustomers != 0 && custId >= 1 && custId <= countCustomers)
            break;
        else
            cout << "\aPlease Enter a valid id !! :";
    }
    cin.ignore();
    customersList[custId - 1]->Update();
    cout << "Customer Updated Successfully" << endl;
}

void Customers::DeleteCustomer()
{
    // fuction delete a customer based on an index taken from user
    short deltIndx = -1;
    cout << "Please Enter Customer Id to Delete : ";
    // loop check for the validaty of id
    while (deltIndx != 0)
    {
        cin >> deltIndx;
        if (countCustomers != 0 && deltIndx >= 1 && deltIndx <= countCustomers)
        {
            // this id is valid
            if (countCustomers == 1)
            {
                // if there is an only one element in the list
                delete customersList[deltIndx-1];
                --countCustomers;

            }
            else
            {
                // delete selected element and chnge the value of its pointer to the last element of the list
                delete customersList[deltIndx - 1];
                customersList[deltIndx - 1] = customersList[countCustomers-1];
                customersList[deltIndx - 1]->setId(deltIndx);
                --countCustomers;
            }
            cout << "\t\t\tCustomer Deleted Successfully\n"
                 << "\t\t\t------------------------------" << endl;
            break;
        }
        else
        {
            // is not valid id
            if (countCustomers == 0)
            {
                cout << "\aThere are no Customers in the system!!!"<<endl;
                break;
            }
            else
            {
                cout << "Plese Enter a valid Id [1-" << countCustomers << "] or press 0 to exit." << endl;
            }
        }

    }
    cin.ignore();

}

void Customers::addTransaction()
{
    //Print();
    printCustomers();
    short custId = -1;
    cout << endl;
    cout << "Please Enter Customer Id : ";
    // check for validaty of id
    while (true)
    {
        cin >> custId;
        if (countCustomers != 0 && custId>=1 && custId<= countCustomers || custId ==0)
        {
            // this is a valid id
            break;
        }
        else
        {
            // not a valid id
            cout << "Please Enter a valid Id (1 - " << countCustomers << ") or 0 to exit: ";
        }
    }
    // if the user refuse to enter id
    if (custId == 0)
    {
        cout << "Adding Transaction Failed\n";
        return;
    }

    transactionList[trnscCount].setCustomer(customersList[custId - 1]);
    transactionList[trnscCount].setId(trnscCount+1);

    transactionList[trnscCount].addOrders(ordersList,ordrsCount);


    ++trnscCount;
    // check if the array is occupied or not
    if (trnscCount >= trnscLstSiz - 1)
        incAnyList(transactionList,trnscLstSiz);

    cout << "\t\t\t  A New Transaction is Added Successfully\n"
         << "\t\t\t---------------------------------------------" << endl;
}

void Customers::addOrder()
{
    //printing all customers;
    printCustomers();
    short custId = -1;
    cout << endl;
    cout << "Please Enter Customer Id to buy Order : ";
    // check for validaty of id
    while (true)
    {
        cin >> custId;
        if (countCustomers != 0 && custId >= 1 && custId <= countCustomers || custId == 0)
        {
            // this is a valid id
            break;
        }
        else
        {
            // not a valid id
            cout << "Please Enter a valid Id (1 - " << countCustomers << ") or 0 to exit: ";
        }
    }
    // if the user refuse to set id
    if (custId == 0)
    {
        cout << "\aAdding Order Failed\n";
        return;
    }

    ordersList[ordrsCount].setCustomer(customersList[custId - 1]);
    ordersList[ordrsCount].setId(ordrsCount+1);
    ordersList[ordrsCount].CreateOrder(stockOfProducts);

    // increase Count of orders and check if array need to be resized
    ++ordrsCount;
    if (ordrsCount >= ordrsLstSiz-1)
        incAnyList(ordersList, ordrsLstSiz);

    cout<<"\t\t\t\aOrder is Added Successfully : )\n";
}


template<class t>
void Customers::incAnyList(t* &defultArray, int& siz)
{
    // Increasing size of array using a temporary pointer as a place holder
    t* tempPoint= new t[siz + 10];
    copy(defultArray, defultArray + siz, tempPoint);

    delete[]defultArray;
    defultArray = tempPoint;
    siz += 10;
}

void Customers::updateOrder(bool choos)
{
    // choos boolean used for determine what is needed to be updated
    cout << "\t\t\tList Of Orders \n";
    cout << "\t\t\t-----------------\n\n";
    for (auto i = 0; i < ordrsCount; i++)
    {
        cout << ordersList[i];
    }
    cout << endl;
    int ordrId;
    cout << "Please Enter Oder Id : ";
    while (true)
    {
        cin >> ordrId;
        if ( ordrId >= 1 && ordrId <= ordrsCount )
            break;
        else
            cout << "\a Please Enter a valid Id : ";
    }
    cin.ignore();

    if (choos)
    {
        // update order quantity
        cout << "Chosen Order Data : \n" << ordersList[ordrId - 1]<<endl;
        ordersList[ordrId - 1].updateItemsQuantity();
        cout << " Item's Quantity Updated Successfully\n"
             << "---------------------------------------\n";
    }
    else
    {
        // update order Status
        cout << "Chosen Order Data : \n" << ordersList[ordrId - 1] << endl;
        int ordStat = -1;
        cout << "Order Statues" << endl;
        cout << "(1) New \t (2) Hold \t (3) Paid \t (4) Canceled" << endl;

        cout << "Please Choose the Order Statues : ";
        // check for the validaty of input
        while (true)
        {
            cin >> ordStat;
            if (ordStat >= 1 && ordStat <= 4)
                break;
            else
            {
                cout << "\aPlease Enter a valid Number (1 - 4) : ";
            }
        }
        cin.ignore();
        ordersList[ordrId - 1].changeOrderStatus(ordStat - 1);
        cout << " Order Statues Updated Successfully\n"
             << "-----------------------------------\n";
    }

}

void Customers::addProductToStock()
{
    cout << "Products Data:" << endl;
    for (auto i = 0; i < productsCount; i++)
    {
        cout << productsList[i]<<endl;
    }
    int prdctId;
    cout << "Please Enter Product Id to add to stock : ";
    while (true)
    {
        cin >> prdctId;
        if (prdctId >= 1 && prdctId <= productsCount)
            break;
        else
            cout << "\aPlease Enter a valid product id :. ";
    }
    stockOfProducts->AddProductToStock(productsList + (prdctId - 1));
}

void Customers::addProduct()
{
    //stockOfProducts->AddProductToStock();
    cout << "Adding Product : : " << endl;
    cin >> productsList[productsCount];
    productsList[productsCount].setId(productsCount + 1);
    ++productsCount;
    if (productsCount >= productsListSiz)
        incAnyList(productsList, productsListSiz);

    cout << "Product Added Successfully::)" << endl;
}

void Customers::updateProduct()
{
    // Updating Products Menu
    short custId;
    cout << "\t\t\t Updating Products Menu\n"
         << "\t\t\t-------------------------\n\n\n" << endl;

    cout << "Please Enter product Id : ";
    while (true)
    {
        cin >> custId;
        if (productsCount != 0 && custId >= 1 && custId <= productsCount)
            break;
        else
            cout << "\aPlease Enter a valid id !! :";
    }
    cin.ignore();
    productsList[custId - 1].Update();
    cout << "Product Updated Successfully" << endl;
}

void Customers::deleteProduct(bool stat)
{

    if (!stat)
    {
        // function: remove element only from stock
        short deltIndx = -1;
        cout << "Please Enter product Id to remove from Stock : ";
        while (true)
        {
            cin >> deltIndx;
            if (deltIndx >= 1 && deltIndx <= productsCount)
                break;
            else
                cout << "\aPlease Enter a valid Id :";
        }
        if (stockOfProducts->DeleteProduct(deltIndx))
        {
            cout << "Product removed Successfully";
        }
        else
        {
            cout << "Chosen Object is Already out of stock";
        }

    }
    else
    {
        // Function : Delete element from products list and remove it from stock
        short deltIndx = -1;
        cout << "Please Enter product Id to Delete : ";
        // loop check for the validaty of id
        while (deltIndx != 0)
        {
            cin >> deltIndx;
            if (productsCount != 0 && deltIndx >= 1 && deltIndx <= productsCount)
            {
                // this id is valid
                if (productsCount == 1)
                {
                    // if there is an only one element in the list
                    stockOfProducts->DeleteProduct(deltIndx);
                    --productsCount;
                }
                else
                {
                    // using = overloading to exchange data inside deleted index with last element then decrease count
                    stockOfProducts->DeleteProduct(deltIndx);
                    productsList[deltIndx - 1] = productsList[productsCount - 1];
                    --productsCount;
                }
                cout << "\t\t\tProduct Deleted Successfully\n"
                     << "\t\t\t------------------------------" << endl;
                break;
            }
            else
            {
                // is not valid id
                if (productsCount == 0)
                {
                    cout << "\aThere are no products in the system!!!" << endl;
                    break;
                }
                else
                {
                    cout << "Plese Enter a valid Id [1-" << productsCount << "] or press 0 to exit." << endl;
                }
            }

        }
    }
    cin.ignore();
}

void Customers::payOrder()
{
    cout << "\t\t\t   Payment Menu : ";
    cout << "\n\t\t\t-----------------" << endl;
    cout << "\n\n\n";
    int ordrId;
    cout << "Please Enter Id of an Order to buy : ";
    // Check the validaty of id
    bool exitBool = false;
    while (true)
    {
        cin >> ordrId;
        if (ordrId >= 1 && ordrId <= ordrsCount)
            break;
        else if (ordrId == 0)
        {
            exitBool = true;
            break;
        }
        else
        {
            cout << "Please Enter a valid Id or 0 to exit : ";
        }
    }
    if (exitBool) return;

    // this is a valid id ->
    cout << "Order Data ::\n";
    cout << "-------------- ::\n";
    cout << (ordersList[ordrId - 1]);

    ordersList[ordrId - 1].pay();
}


void Customers::PrintProducts(bool stat)
{
    if(stat)
    {
        // print all products
        for (auto i = 0; i < productsCount; i++)
        {
            cout << productsList[i]<<endl;
        }
    }
    else
    {
        // print products in stock
        cout << *stockOfProducts << endl;
    }
}

void Customers::printTransactions()
{
    for (auto i = 0; i < trnscCount; i++)
    {
        cout << transactionList[i] << endl;
    }
}

void Customers::printOrders()
{
    for (auto i = 0; i < ordrsCount; i++)
    {
        cout << ordersList[i] << endl;
        cout<<"=================================="<<endl;
    }
}
