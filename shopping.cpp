#include <iomanip>
#include<iostream>
#include<string>
#include <sstream>
#include<sqlite3.h>
#include<windows.h>
#include"trees.h"
#include"animation.h"
#include"stackme.h"
#include <chrono>
#include <ctime>
using namespace std;

int search(int);
int display();
string check(int);       //   for checking quantity

int createDB(const char* s);
int createTable(const char* s);
int displayCustomers();
int callback(void* NotUsed, int argc, char** argv, char** azColName);

////////////////////////////////////////////////////////////////////
class node : public bucket,public TrieNode {
    int ID;
    string proName;
    double prePrice;
    int quantity;
    node* next;
public:
    node()
    {
        ID = 0;
        proName = "";
        prePrice = 0.00;
        quantity = 0;
        next = NULL;
    }
    node(int i, string s, double p, int q, node* n)
    {
        ID = i;
        proName = s;
        prePrice = p;
        quantity = q;
        next = n;
    }
    void setID(int i)
    {
        ID = i;
    }
    void setproName(string s)
    {
        proName = s;
    }
    void setprePrice(double p)
    {
        prePrice = p;
    }
    void setquantity(int q)
    {
        quantity = q;
    }
    void setnext(node* n)
    {
        next = n;
    }
    int getID()
    {
        return ID;
    }
    string getproName()
    {
        return proName;
    }
    int getprePrice()
    {
        return prePrice;
    }
    int getquantity()
    {
        return quantity;
    }
    node* getnext()
    {
        return next;
    }
};

class SLL :public TrieNodeList, public BUC {
    node* head;
    node* p;
    node* current;
    node* previous;
    int n;
    int *arry = new int(n);
    TrieNode *arr = new TrieNode[n];
    TrieNode *currentp;
public:
    SLL()
    {
        head = NULL;
        p = NULL;
        current = NULL;
        previous = NULL;
    }
    void beg(const char* s)
    {
        system("cls");

        sqlite3* DB;
        char* messageError;

        int id, quant;
        string name;
        double pre;
        node* t = new node();
        p = head;
        cout << "\t\t\tEnter product ID:-";
        cin >> id;
        t->setID(id);
        cout << "\t\t\tEnter product Name:-";
        cin >> name;
        t->setproName(name);
        cout << "\t\t\tEnter product price:-";
        cin >> pre;
        t->setprePrice(pre);
        cout << "\t\t\tEnter product quantity--:-";
        cin >> quant;
        t->setquantity(quant);
        cout << "Record insert" << endl;
        string sql("INSERT INTO GRADES (PID, PNAME, Price, Quantity) VALUES('" + to_string(id) + "','" + name + "','" + to_string(pre) + "', '" + to_string(quant) + "');");

        int exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in insertData function." << endl;
            sqlite3_free(messageError);
        }
        else
            cout << "Records inserted Successfully!" << endl;
        if (head == NULL)
        {
            t->setnext(head);
            head = t;
        }
        else
        {
            while (p->getnext() != NULL)
            {
                p = p->getnext();
            }
            p->setnext(t);
            t->setnext(NULL);
        }

        cout << "\n\n\t\t\t\tThis product is Inserted!\n\n\n";
    }
    int search(int id)
    {
        int count = 1;
        while (p != NULL)
        {
            if (p->getID() == id)
            {
                break;
            }
            else
            {
                count++;
                p = p->getnext();
            }
        }
        return count;
    }
    void delPro()
    {

        display();

        int id;
        current = head;
        previous = head;
        cout << "\n\nEnter ID to delete that product:\n\n";
        cin >> id;

        sqlite3* DB;
        char* messageError;
        string sql = "DELETE FROM GRADES WHERE PID = " + to_string(id);

        int exit = sqlite3_open("STUDENTS.db", &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in deleteData function." << endl;
            sqlite3_free(messageError);
        }
        else
            cout << "Records deleted Successfully!" << endl;


        int count = display();


    }
    void modify()
    {
        int id;
        double pre;
        string pName;
        int nid;
        int nq;
        if (head == NULL)
        {
            system("cls");
            cout << "List is empty" << endl;
        }
        else
        {
            displayLinked();
            cout << "\n\nEnter ID to modify product Name and its price:\n";
            cin >> id;
            current = head;
            int pos = 0;
            int count = displayLinked();
            pos = search(id);
            if (pos <= count)
            {
                while (current->getID() != id)
                {
                    current = current->getnext();
                }
                cout << "\nOld ID : " << current->getID() << endl;
                cout << "\nOld Name : " << current->getproName() << endl;
                cout << "\nOld Price : " << current->getprePrice() << endl;
                cout << "\nOld Quantity : " << current->getquantity() << endl;
                cout << endl << endl;
                cout << "Enter new ID:";
                cin >> nid;
                current->setID(nid);
                cout << "Enter new Name:";
                cin >> pName;
                current->setproName(pName);
                cout << "Enter new Price:";
                cin >> pre;
                current->setprePrice(pre);
                cout << "Enter new Quantity:";
                cin >> nq;
                current->setquantity(nq);
            }
            else
            {
                cout << id << " is <<<Not found>>\n\n";
            }
        }
    }
    int display()
    {
        system("cls");



        int c = 0;
        p = head;
        cout << "Existing products are:\n";
        cout << "ID\t\tProduct Name\t\tPrice\t\tQuantity\n";
        cout << "=================================================================|\n";




        sqlite3* DB;
        char* messageError;

        string sql = "SELECT PID,PNAME,Price,Quantity FROM GRADES;";

        int exit = sqlite3_open("STUDENTS.db", &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
        exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in selectData function." << endl;
            sqlite3_free(messageError);
        }
        else
            cout << "Records selected Successfully!" << endl;
        cout << "\nTotal products in our store is : " << c << "\n\n\n";
        return c;
    }
    string check(int quant)
    {
        int a = quant;
        stringstream ss;
        ss << a;
        string quantity = ss.str();
        if (quant <= 0)
        {
            return "out of stock!";
        }
        else
        {
            return quantity;
        }
    }
    void buy()
    {


        system("cls");
        displayLinked();
		string products[20];
		int pay = 0,no,c = 0,price,i = 1;
        if(head == NULL)
        {
	    cout<<"\n<<<<There is no items to buy>>>>\n\n";
        }
	    else
        {
		cout<< "How many items you wanna to buy!\n";
		cin >> no;
        int count = displayLinked();
        int quant;
		while (i <= no)
        {
            current = head;
             a:
            cout<< "Enter id of item that you want to buy: ";
            int id, pos = 0;
            cin>> id;
            if(id == -1)
            {
                system("cls");
                return;
            }
	        pos = search(id);
	        if(pos <= count)
            {
		      while(current->getID() != id)
              {
			   current=current->getnext();
		      }

	           if(current->getquantity() < quant)
               {
               cout<<"\n\n\t\t\t----The Quantity You Entered is not available---"<<endl;
               cout<<"\n\t\t\t-----(Press -1 for Back to Main Menu)------"<<endl;
               goto a;
           }
           products[c]=current->getproName();
		   c++;

	       i++;
	     }
	    else
        {
            cout<<"\n<<<<<<<<<This item is not available in our store at this time>>>>\n\n";
	    }
}
currentp = root;
cout << "How many customer want to buy the product: ";
cin >> n;
for(int i = 0; i < n; i++)
{
    currentp = pCrawl->getnode();
}
        string customer[n];
        for(int i = 0; i < n; i++)
        {
        cout<<"\n\t\t Enter customer Name: ";
        cin >> customer[i];
        insert(&arr[i],customer[i]);
        cout<<"How many quantities you want:";
	           cin>>quant;
        pay = pay + (current->getprePrice() * quant);
	       current->setquantity(current->getquantity() - quant);
        }
     insert_into_DB(customer,n);
	    system("cls");
        cout<<"\n\n\n\n\t\t\tYou have bought : ";
        for(int i = 0;i < no; i++)
       {
        cout<<products[i]<<",";
       }
        price = pay * (0.90);
	    cout<<"\n\nOriginal price : "<< pay;
        cout<<"\n with 10% discount: "<< price <<"\nThank you! for the shopping\n\n";
        }
    }

    void insert_into_DB(string customer[],int n){
     sqlite3* DB;
        char* messageError;

         time_t now = time(0);

   // convert now to string form
   char* dt = ctime(&now);

   for(int i=0;i<n;i++){
     string sql("INSERT INTO Customer1 (NAME,Date) VALUES('" + customer[i] + "','" + dt + "');");
      int exit = sqlite3_open("STUDENTS.db", &DB);
     exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
            if (exit != SQLITE_OK) {
                cerr << "Error in insertData function." << endl;
                sqlite3_free(messageError);
            }
            else
                cout << "Records inserted Successfully!" << endl;
        }
   }


    void administator()
    {
        system("cls");
        const char* dir = R"(D:\sqllite\Demo\Project3\STUDENTS.db)";

        int ch;
        do
        {
            cout << "\t\t============================================" << endl;
            cout << "\t\t|          Administator Portal              |" << endl;
            cout << "\t\t============================================" << endl;
            cout << "\t\t     Enter 1 for ADD a new product    " << endl;
            cout << "\t\t     Enter 2 to display all products   " << endl;
            cout << "\t\t     Enter 3 for MODIFY Existing product" << endl;
            cout << "\t\t     Enter 4 for Delete a particular product item" << endl;
            cout << "\t\t     Enter 5 for Customers List " << endl;
            cout << "\t\t     Enter 6 for Schedule" << endl;



            cout << "\t\t     Enter 0 for Main Menu" << endl;

            cout << "\nEnter Your choice >>>";   cin >> ch;
            switch (ch) {
            case 1:
                beg(dir);
                break;
            case 2:
                system("cls");
                display();
                break;
            case 3:
                modify();
                system("cls");
                break;
            case 4:
                delPro();
                cout << "\n-------Product is Deleted-------\n";
                break;
            case 5:
                {
               system("cls");
                int choice1;
                string sea;
                do{
                    cout << "1-Display Customers From Database" << endl;
                    cout << "2-Search Customers From Trees" << endl;
                    cout << "3-Back to main Menu" << endl;
                    cout << "Enter Your Choice :";
                    cin >> choice1;
                    cout << "\n";

                    switch(choice1)
                    {
                    case 1:
                        system("cls");
                        cout << "|============CUSTOMERS NAMES LIST==============|" << endl;

                        displayCustomers();
                        break;
                    case 2:
                        int comp;

                        system("cls");
                        cout << "|============CUSTOMERS NAMES LIST==============|" << endl;
                        cout << "Enter the alphabet to search the customers: ";
                        cin >> sea;
                        for (int i = 0; i < n; i++)
                        {
                            comp = printAutoSuggestions(&arr[i], sea);
                        }

                        if (comp == -1)
                        {
                            cout << "No other strings found with this prefix\n";
                        }
                        else if (comp == 0)
                        {
                            cout << "No string found with this prefix\n";
                        }
                        break;

                    }
                }while (choice1 !=3);
                }
                break;
                    case 6:
                        {
                        displaySchedule();
                        }
                        break;

            }
        } while (ch != 0);
    }

    void displaySchedule(){
    system("cls");



        int c = 0;
        p = head;
        cout << "Schedule:\n";
        cout << "|==================================================================================================|\n";
        cout<<"Week"<<setw(22)<<"Morning"<<setw(22)<<"Break"<<setw(22)<<"Evening"<<endl;



        sqlite3* DB;
        char* messageError;

        string sql = "SELECT * FROM Schedule4;";
        int exit = sqlite3_open("STUDENTS.db", &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
        exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in selectData function." << endl;
            sqlite3_free(messageError);
        }
        else{
            cout << "|==================================================================================================|\n";
            cout << "Records selected Successfully!" << endl;
        }


    }
    int displayLinked()
    {
        system("cls");



        int c = 0;
        p = head;
        cout << "Existing products are:\n";
        cout << "ID\t\tProduct Name\t\tPrice\t\tQuantity\n";
        cout << "=================================================================|\n";
        while (p != NULL)
        {
            cout << p->getID() << "\t\t" << p->getproName() << "\t\t\t" << p->getprePrice() << "\t\t\t" << check(p->getquantity()) << "\n";
            p = p->getnext();
            c = c + 1;
        }



        cout << "\nTotal products in our store is : " << c << "\n\n\n";
        return c;
    }
};
int main()
{

     system("cls");
    const char* dir = R"(D:\sqllite\Demo\Project3\STUDENTS.db)";
    createDB(dir);
    createTable(dir);


    SLL s1;
    for (int i = 0;i <= 51; i++)
    {
        s1.push(i);
    }
    system("color F1");
    gotoxy(17, 5);
    cout << "--------------------------------------------------" << endl;
    gotoxy(17, 7);
    cout << "||            Shopping Club System                ||" << endl;
    gotoxy(17, 9);
    cout << "--------------------------------------------------" << endl;
    gotoxy(17, 11);
    cout << "|Subject Teacher ->> Sir Sagheer <<-- |\n" << endl;
    gotoxy(17, 13);
    cout << ">>>----Project Implemented By-----<<<" << endl;
    gotoxy(22, 15);
    cout << "Muhammad Awab Ahmad (210943)" << endl;
    gotoxy(22, 16);
    cout << "Muhammad Taha Shayan  (210940)" << endl;
    gotoxy(22, 17);
    cout << "Wajahat Ali Khan   (211015)" << endl << endl;
    system("pause");
    system("cls");
    system("color Fc");
    int ch = 0;
    while (ch != 3)
    {    system("cls");
        cout << "\n\t\t|--------<Main Menu>-----------|";
        cout << "\n\n";
        cout << "\t\t 1)Administator of Market\n";
        cout << "\t\t 2)Customer               \n";
        cout << "\t\t 3)Exit                    \n";

        cout << "\nEnter Your choice >>>";cin >> ch;
        switch (ch) {
        case 1:
            s1.administator();
            break;
        case 2:
            cout << endl << endl;
            s1.bpop();
            system("pause");
            s1.buy();
            break;
        case 3:
            cout << "\n\n\t\t\t\t\tThank You\t\t\t\t";
            break;
        }
    }
    return 0;
}

 int createDB(const char* s)
{
    sqlite3* DB;

    int exit = 0;
    exit = sqlite3_open(s, &DB);

    sqlite3_close(DB);

    return 0;
}
int createTable(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql = "CREATE TABLE IF NOT EXISTS GRADES("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
        "PID        TEXT NOT NULL , "
        "PNAME      TEXT NOT NULL, "
        "Price      TEXT NOT NULL, "
        "Quantity   TEXT NOT NULL );";





    try
    {
        int exit = 0;
        exit = sqlite3_open(s, &DB);
        /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
        exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            cerr << "Error in createTable function." << endl;
            sqlite3_free(messageError);
        }
        else
            cout << " " << endl;
        sqlite3_close(DB);
    }
    catch (const exception& e)
    {
        cerr << e.what();
    }

    return 0;
}

int insertData(const char* s)
{
    sqlite3* DB;
    char* messageError;

    string sql("INSERT INTO GRADES (PID, PNAME, Price, Quantiry) VALUES('Alice', 'Chapa', 35, 'Tampa', 'A');");

    int exit = sqlite3_open(s, &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here */
    exit = sqlite3_exec(DB, sql.c_str(), NULL, 0, &messageError);
    if (exit != SQLITE_OK) {
        cerr << "Error in insertData function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records inserted Successfully!" << endl;

    return 0;
}



int callback(void* NotUsed, int argc, char** argv, char** azColName)
{


    for (int i = 0; i < argc; i++) {

        cout << argv[i] << "\t\t";

    }
    cout << endl;
    return 0;
}


 int displayCustomers() {
    sqlite3* DB;
    char* messageError;

    string sql = "SELECT NAME,Date FROM Customer1;";

    int exit = sqlite3_open("STUDENTS.db", &DB);
    /* An open database, SQL to be evaluated, Callback function, 1st argument to callback, Error msg written here*/
    exit = sqlite3_exec(DB, sql.c_str(), callback, NULL, &messageError);

    if (exit != SQLITE_OK) {
        cerr << "Error in selectData function." << endl;
        sqlite3_free(messageError);
    }
    else
        cout << "Records selected Successfully!" << endl;
    return 0;
}
