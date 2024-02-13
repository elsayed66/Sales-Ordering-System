#include "Stock.h"


ostream& operator<<(ostream& ostrm, Stock& stock)
{
    cout << "\n\n\t\t\t List of Products :: " << endl;
    for (int i = 0; i < stock.stk_countProducts; ++i)
    {
        ostrm << (*stock.stk_productsList[i]) << endl;
    }
    return ostrm;
    // TODO: insert return statement here
}


Stock::Stock()
{
    stk_countProducts = 0;
    stk_productsArrSiz = 10;
    stk_productsList = new Product*[stk_productsArrSiz];
}

Stock::~Stock()
{
    // delete allocated memory for array of pointers
    delete[]stk_productsList;
}

void Stock::AddProductToStock(Product* prdctPoint)
{

    // attach new product to list using operator overloading
    stk_productsList[stk_countProducts] = prdctPoint;
    ++stk_countProducts;
    // check if the array is occupied or not
    if (stk_countProducts >= stk_productsArrSiz - 1)
        incrsPointerLstSiz(stk_productsList,stk_productsArrSiz);
    cout << "A new Product Added Successfully\n";
}


void Stock::updateProduct()
{
    // Updating Products Menu
    short custId;
    cout << "\t\t\t Updating Products Menu\n"
         <<  "\t\t\t-------------------------\n\n\n" << endl;

    cout << "Please Enter product Id : ";
    while (true)
    {
        cin >> custId;
        if (stk_countProducts != 0 && custId >= 1 && custId <= stk_countProducts)
            break;
        else
            cout << "\aPlease Enter a valid id !! :";
    }
    cin.ignore();
    stk_productsList[custId - 1]->Update();
    cout << "Product Updated Successfully" << endl;
}

bool Stock::DeleteProduct(int id)
{
    // removing specific product from array of stock
    for (auto i = 0; i < stk_countProducts; i++)
    {
        if(stk_productsList[i]->getId() == id)
        {
            if (stk_countProducts == 1)
            {
                // if only one cell of list is occupied
                stk_productsList[i] = nullptr;
            }
            else
            {
                // if more than cell is occupied
                stk_productsList[i] = stk_productsList[stk_countProducts-1];
                stk_productsList[stk_countProducts-1] = nullptr;
            }
            --stk_countProducts;
            return true;
        }
        if (i == stk_countProducts-1)
        {
            // product Not found
            return false;
        }

    }
}
Product* Stock::getProductById(int id)
{

    for(int i = 0; i<stk_countProducts ; ++i)
    {
        if(stk_productsList[i]->getId() == id)
            return stk_productsList[i];
    }

    return nullptr;
}

template<class t>
void Stock::incrsPointerLstSiz(t**& defArr, int& siz)
{
    int incVal = 5;
    // increase size of array using temporary pointer
    t** tempPointer = new t*[siz+ incVal];
    copy(defArr, defArr + siz, tempPointer);

    delete[]defArr;
    defArr = tempPointer;
    siz += incVal;
}
void Stock::readDataFile(ifstream& ifStrm,Product* prdctList, int prdctsCount)
{
    // read Product Number and search for it in array to get product address
    string number;
    getline(ifStrm,number);
    for(int i=0; i<prdctsCount; ++i)
    {
        if(prdctList[i].getNumber()== number )
        {
            stk_productsList[stk_countProducts] = (prdctList+i);
            ++stk_countProducts;

            if(stk_countProducts >= stk_productsArrSiz-1)
                incrsPointerLstSiz(stk_productsList,stk_productsArrSiz);
            break;
        }
    }

};

void Stock::writeDataFile(ofstream& ofStrm)
{
// write data of
    for(int i =0 ; i<stk_countProducts; ++i)
    {
        ofStrm<<stk_productsList[i]->getNumber();
        if(i != stk_countProducts-1)
            cout<<'\n';
    }

};

