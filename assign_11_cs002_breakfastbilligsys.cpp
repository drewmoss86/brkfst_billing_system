/**********************************************************
*AUTHOR    		 : Andrew Moss
*Assignment #11  : Breakfast Billing System
*CLASS     		 : CS 002
*SECTION		 : MTWR: 7:30a – 12:30p
*Due Date  		 : 2/8/17
**********************************************************/
#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <fstream>
#include <iomanip>
#include <cstdlib>
/**********************************************************
* BREAKFAST BILLING SYSTEM
* ________________________________________________________
* Program Description: This program helps a local restaurant
*   automate its breakfast billing system. The program should
*   do the following:
*	1) Show the customer the different breakfast items offered
*		by the restaurant.
*	2) Allow the customer to select more than one item from the
*		menu as well as multiple items of a particular type.
*	3) Calculate and print the bill.
*
* ________________________________________________________
* OUTPUT:
*   tax              : product of total before tax and tax percentage
*   totalBill        : product of to cost of each item and quantity ordered
*   afterTaxTotal    : sum of cost of all items and the tax amount
*   m.menuItem       : stored items on menu
*   m.menuPrice      : stored price for each item on menu
*
*
*************************************************************/
using namespace std;

//Struct for menu items
struct MenuItemType
{
    string menuItem;
    double menuPrice;
};

//Function prototype
vector<MenuItemType> getData(ifstream&, vector<MenuItemType>&);
void showMenu (vector<MenuItemType>&);
void printCheck (vector<MenuItemType>&, vector<int>, vector<int>);

int main()
{
    //Constants
    vector<MenuItemType> menuList;      //Vector holds menu items and price
    vector<int> allItems;               //INPUT: Vector holds item numbers input
                                        //by user
    vector<int> allOrderAmt;            //INPUT: Vector holds order amts input
                                        //by user
    string filename;                    //INPUT: String for filename
    int itemNum;                        //INPUT: Integer for item menu selection
    int ordAmt;                         //INPUT: Integer for amt per item
    bool condition = true;              //Boolean

    //INPUT: User inputs file name
    cout << "Enter filename: " << endl;
    getline(cin, filename);

    //Open file
    ifstream inFile;
    inFile.open(filename.c_str());

    //Call function to store input file data for item names and prices
    getData(inFile, menuList);


    //Loop to display menu items for user to order
    while (condition)
    {

         //Function that displays the menu
         showMenu(menuList);


         //INPUT: User selects item number based on menu
         cout << "Enter the item number: " << endl;
         cin >> itemNum;

         if(itemNum == 0)
         {
             condition = false;
             break;
         }

         allItems.push_back(itemNum);


         //INPUT: User selects quantity of each item to order
         cout << "How many would you like to order? " << endl;
         cin >> ordAmt;
         cout << endl;

         allOrderAmt.push_back(ordAmt);



    }
         //Function to print check to display items ordered, tax and total
         //amt due
         printCheck (menuList, allItems, allOrderAmt);

    return 0;
}

/***********************************************************
* FUNCTIONS
* _________________________________________________________
* getData
*  This function loads the data from a file (“menu.txt”)
*   into the vector menuList.
*
* showMenu
*  This function shows the different items offered by the
*   restaurant and tells the user how to select the items.
*
* printCheck
*  This function calculates and prints the check.
*
 ************************************************************/
vector<MenuItemType> getData(ifstream& inFile, vector<MenuItemType>& m)
{
    string itemOptionsAndItemPrices;        //String of initial values from file
    string itemOptions;                     //String of item names
    string stringItemPrices;                //String of item prices
    char cstringItemPrices[100];            //Cstring converted from string of
                                            //item prices
    double numItemPrices = 0;               //Double converted from cstring of
                                            //item prices


    int count = 0;                          //Counter for while loop


    //Loop to parse out initial string from file and initialize the two parts
    //of the menu list vector
    while (getline(inFile, itemOptionsAndItemPrices))
    {
        stringItemPrices =
        itemOptionsAndItemPrices.substr(itemOptionsAndItemPrices.find("$") + 1,
        string::npos);

        itemOptions =
        itemOptionsAndItemPrices.erase(itemOptionsAndItemPrices.find("$"),
        stringItemPrices.length() + 1);

        strcpy(cstringItemPrices, stringItemPrices.c_str());
        numItemPrices = atof(cstringItemPrices);

        m.push_back(MenuItemType());
        m[count].menuItem = itemOptions;

        m.push_back(MenuItemType());
        m[count].menuPrice = numItemPrices;

        count++;
    }
    return m;
}

void showMenu (vector<MenuItemType>& m)
{

    //OUTPUT: Restaurant greeting title above menu
    cout << endl << "Welcome to Johnny's Restaurant" << endl << endl;


    //OUTPUT: Menu title
    cout << setw(17) << right << "Menu" << endl << endl;


    //OUTPUT: Displays menu items
    for(int i = 0; i < m.size()/2; i++)
    {
        cout << (i + 1) << ". " << setw(20) << left << m[i].menuItem;
        cout << fixed << setprecision(2) << "\t$" << setw(5) << right
             << m[i].menuPrice << left << endl;

    }

    cout << "\nEnter 0 when you finish your order." << endl << endl;


}

void printCheck (vector<MenuItemType>& m, vector<int> item, vector<int> amt)
{
    string measuringStick (29, '-');      //String to create line for receipt
    vector<double> totalBill;             //Vector to store total price of each
                                          //item ordered
    double beforeTaxTotal = 0;            //CALC OUT: Double representing total
                                          //before tax
    double afterTaxTotal = 0;             //CALC OUT: Double representing total
                                          //after tax
    double tax = 0;                       //CALC OUT: Double value representing
                                          //tax amt

    //OUTPUT: Restaurant greeting title above receipt
    cout << endl << "\nWelcome to Johnny's Restaurant" << endl << endl;


    //OUTPUT: Sale title
    cout << setw(17) << right << "SALE" << endl << endl;


    //PROCESSING: Calculating total of each item and quantity ordered
    for(unsigned int i = 0; i < item.size(); i++)
    {
       totalBill.push_back(m[item[i]-1].menuPrice * amt[i]);
    }

    //OUTPUT: List of amount ordered, item, quantity and cost
    for(unsigned int i = 0; i < item.size(); i++)
    {
        cout << amt[i] << " " << setw(21) << left <<  m[item[i]-1].menuItem
             << fixed << setprecision(2) << "$" << setw(5) << right
             << totalBill[i] << left << endl;


        //PROCESSING: Before tax total
        beforeTaxTotal += totalBill[i];
    }

    //PROCESSING: Calculating tax
    tax = beforeTaxTotal * 0.05;


    //OUTPUT: Calculated tax amount
    cout << setw(23) << left << "Tax" << fixed << setprecision(2)
         << "$"  << setw(5) << right << tax << left << endl;


    //PROCESSING: Calculating after tax total
    afterTaxTotal = beforeTaxTotal + tax;


    //OUTPUT: A series of '-' representing a line and the total amount due
    cout << measuringStick << endl << setw(23) << left << "Amount Due "
         << fixed << setprecision(2) << "$" << setw(5) << right << afterTaxTotal
         << endl << endl;

}
