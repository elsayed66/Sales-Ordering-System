#include "Order.h"
#include<cstring>
// memory takin size = 97.65635 kilo Byte
bool Order::numberFreqArr[100000] = {false};



Order::Order()
{
    itemsCount = 0;
    totalPrice = 0;
    // Take unchosen random number then mark its place as taken
    do
    {
        number = rand() % 100000 + 1;
    }
    while (numberFreqArr[number-1]==true);
    numberFreqArr[number - 1] = 1;

    cstmr = nullptr;

    itemsCount = 0;
    itemsLstSiz = 10;
    orderItemsLIst= new OrderItem[itemsLstSiz];
}

void Order::CreateOrder(Stock* stock)
{
    date.tTime = time(NULL);
    date.tdate = ctime(&date.tTime);

    addItems(stock);
    calcTotalValue();
}


void Order::updateItemsQuantity()
{
    int itemId;
    cout << "Enter Item Id :";
    while (true)
    {
        cin >> itemId;
        if (itemId >= 1 && itemId <= itemsCount)
            break;
        else
            cout << "\aPlease Enter a valid Item Id: ";
    }
    // take the new quantity from user
    orderItemsLIst[itemId-1].fillNewQuantity();
}

Order::~Order()
{
    delete[]orderItemsLIst;
    // mark the taken number as not occupied
    numberFreqArr[number - 1] = 0;
}

Order::Order(Order& ordr2)
{
    this->id = ordr2.id;
    this->number = ordr2.number;
    this->date.tTime = ordr2.date.tTime;
    this->date.tdate = ordr2.date.tdate;
    this->cstmr = ordr2.cstmr;
    this->totalPrice = ordr2.totalPrice;
    this->stat = ordr2.stat;
    this->orderItemsLIst = ordr2.orderItemsLIst;
    this->itemsCount = ordr2.itemsCount;
    this->itemsLstSiz = ordr2.itemsLstSiz;

}

void Order::pay()
{
    if(stat == PAID)
    {
        cout<<"This order is already paid"<<endl;
        return;
    }
    int paytype;
    cout << "Please Choose payment Type \n"
         << "[1] Credit \t [2] Cash \t [3] Check\n";
    while (true)
    {
        cin >> paytype;
        if (paytype >= 1 && paytype <= 3)
            break;
        else
            cout << "\aPlease Enter a valid Choice :";
    }
    Payment* paymntPntr = nullptr;
    bool doneProcess = true;
    switch (paytype)
    {
    case 1:
        paymntPntr = new Credit;
        paymntPntr->inputData();
        break;
    case 2:
        paymntPntr = new Cash;
        paymntPntr->inputData();
        break;
    case 3:
        paymntPntr = new Check;
        paymntPntr->inputData();
        break;

    default:
        doneProcess = false;
        cout << "\a Process Terminated Bec. Not valid Choice \n";
        break;
    }
    if (!doneProcess) return;

    // check for quantity of given order items in stock
    for(int i=0; i<itemsCount; ++i)
    {
        orderItemsLIst[i].checkQuantity();
    }

    PaidValue = paymntPntr->getAmount();
    if (PaidValue >= getOrdrPrice())
    {
        cout << "Order is totally paied successefully :)"<<endl;
        stat = OrderStatus::PAID;

        for(int i=0; i<itemsCount; ++i)
        {
            orderItemsLIst[i].paid();
        }

    }
    else
    {
        cout << "Order is being Hold because there is no enough money :(" << endl;
        stat = OrderStatus::HOLD;
    }
    cout << "Total Amount of Order value : " << totalPrice << endl;
    cout << "Total amount payed is : " << PaidValue << endl;

    cout << "Thank You For using our Payment Service\n";


}

void Order::calcTotalValue()
{
    totalPrice = 0;
    for (auto i = 0; i < itemsCount; i++)
    {
        totalPrice += orderItemsLIst[i].getTotPrice();
    }
}

void Order::addItems(Stock* stock)
{
    cout << ( * stock);
    int itemsNum;
    cout << "Please Enter Number of Items to add : ";
    cin >> itemsNum;

    while (itemsNum--)
    {
        // take id of product to add to order
        int prdctId;
        cout << "Please Enter Product Id to add : ";
        while (true)
        {
            // check for the validaty of the product
            cin >> prdctId;
            if (stock->getProductById(prdctId) != nullptr)
                break;
            else
            {
                cout << "\aPlease Enter a valid product id :";
            }
        }
        orderItemsLIst[itemsCount].setProduct(stock->getProductById(prdctId));

        int quantity;
        cout << "Please Enter Product Quantity to be bought : ";
        cin >> quantity;
        orderItemsLIst[itemsCount].setQuantity(quantity);

        // increase count of items and check if array need to be resized
        ++itemsCount;
        if (itemsCount >= itemsLstSiz)
            incAnyListSiz(orderItemsLIst, itemsLstSiz);
    }
}



void Order::changeOrderStatus(int status)
{
    // change order statues
    switch (status)
    {
    case 0:
        stat = OrderStatus::NEW;
        break;
    case 1:
        stat = OrderStatus::HOLD;
        break;
    case 2:
        stat = OrderStatus::PAID;
        break;
    case 3:
        stat = OrderStatus::CANCELED;
        break;
    default:
        break;
    }

}
string Order::getOrderStatus()
{

    switch (stat)
    {
    case NEW:
        return "NEW";
        break;
    case HOLD:
        return "HOLD";
        break;
    case PAID:
        return "PAID";
        break;
    case CANCELED:
        return "CANCELED";
        break;
    default:
        break;
    }
}




template<class t>
inline void Order::incAnyListSiz(t*& arrOfObjcts, int& siz)
{
    t* tempArr = new t[siz + 5];
    copy(arrOfObjcts, arrOfObjcts + siz, tempArr);
    delete[]arrOfObjcts;
    arrOfObjcts = tempArr;
    siz += 5;
}
ostream& operator<<(ostream& ostrm, Order& ordr)
{
    ostrm << "Order Id -> " << ordr.id << " \t" << "Order Number : " << ordr.number << " \t" << "Order Statues : " << ordr.getOrderStatus() << endl;
    ostrm << "Order Date : \t" << ordr.date.tdate << endl;
    ostrm << "Number Of Items : " << ordr.itemsCount << endl;
    ostrm << "Items Data : \n";
    ostrm << "--------------" << endl;
    // loop print all order items using << operator
    for (size_t i = 0; i < ordr.itemsCount; i++)
    {
        cout << ordr.orderItemsLIst[i];
    }
    ostrm << "\n\n Total Order Value : " << ordr.getOrdrPrice() << endl;
    return ostrm;
}

istream& operator>>(istream& istrm, Order& ordr)
{
    return istrm;
    // TODO: insert return statement here
}

ofstream& operator<<(ofstream& ofstrm, Order& ordr)
{
    ofstrm<<ordr.stat<<' ';
    ofstrm<<ordr.PaidValue<<' ';
    ofstrm<<ordr.number<<' ';
    ofstrm<<ordr.date.tdate<<'^';
    // print key for customer to search for after program work
    ofstrm<<ordr.cstmr->getPhone()<<'^';

    // write order items data on file
    ofstrm<<ordr.itemsCount<<'\n';
    for(auto i = 0; i<ordr.itemsCount; ++i)
    {
        ofstrm<<ordr.orderItemsLIst[i];
        if(i!=ordr.itemsCount-1)
            ofstrm<<'\n';
    }
}
void Order::readOrdersFile(ifstream& ifStrm,Customer** customersList,int cstmrLstSiz,Product** prdctsList,int prdctsListSiz)
{
    char* tempCharPoint;
    string custPhone,dateStr;
    int OrderNum,n_ItemsCount,stats;

    ifStrm>>stats;
    ifStrm>>PaidValue;
    ifStrm>>OrderNum;
    getline(ifStrm,dateStr,'^');
    getline(ifStrm,custPhone,'^');
    ifStrm>>n_ItemsCount;

    // taking data of each orderItem
    for(int i =0; i<(int)n_ItemsCount; ++i)
    {
        orderItemsLIst[i].readDataFile(ifStrm,prdctsList,prdctsListSiz);
        orderItemsLIst[i].setId(itemsCount+1);
        ++itemsCount;
        if(itemsCount>= itemsLstSiz-1)
            incAnyListSiz(orderItemsLIst,itemsLstSiz);
    }
    this->changeOrderStatus(stats);
    this->setNumber(OrderNum);
    // set date
    tempCharPoint =new char[dateStr.length()+1];
    strcpy(tempCharPoint,dateStr.c_str());
    date.tdate = (tempCharPoint);

    //delete [] tempCharPoint;

    // search for customer to save its address
    for(int i =0; i<cstmrLstSiz; ++i)
    {
        if(customersList[i]->getPhone()==custPhone)
        {
            cstmr = customersList[i];
            break;
        }
    }

}





