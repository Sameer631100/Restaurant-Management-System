#include <bits/stdc++.h>
using namespace std ;

class Table
{

private:
    map<int, int> tableCount = {
        {2, 4},     // {Type of seater, No. of tables}
        {4, 6},
        {6, 2}};

public:
    unordered_map<int, pair<bool, int>> tableStatus = {
        {21, {true, 0}},
        {22, {true, 0}},
        {23, {true, 0}},
        {24, {true, 0}},
        {41, {true, 0}},
        {42, {true, 0}},
        {43, {true, 0}},
        {44, {true, 0}},
        {45, {true, 0}},
        {46, {true, 0}},
        {61, {true, 0}},
        {62, {true, 0}},
    };
    queue<int> waiting2;
    queue<int> waiting4;
    queue<int> waiting6;

    void allocation()
    {
        int people, tableId = 0;
        cout << "Enter number of people: ";
        cin >> people;
        if (people > 6)
        {
            cout << "Sorry we don't have that capacity." << endl;
            system("pause");
            return;
        }
        for (auto it : tableCount)
        {
            if (it.first >= people && it.second > 0)
            {
                tableId = it.first * 10 + it.second;
                tableCount[it.first]--;
                tableStatus[tableId].first = false;
                tableStatus[tableId].second = people;
                break;
            }

            else if (it.first >= people)
            {
                break;
            }
        }
        if (tableId != 0)
        {
            cout << "You have been allocated table id: " << tableId << endl;
        }
        else
        {
            int custId;
            cout << "Tables are full, you are in queue!" << endl;
            cout << "Enter your ID: ";
            cin >> custId;

            if (people <= 2)
                waiting2.push(custId);
            else if (people <= 4)
                waiting4.push(custId);
            else if (people <= 6)
                waiting6.push(custId);
            cout << "Thankyou,  just wait for a while!" << endl;
        }
        system("pause");
        return;
    }
    bool isValid(int tno)
    {
        if (tableStatus.find(tno) == tableStatus.end())
            return false;
        else if (tableStatus[tno].first == true)
            return false;
        return true;
    }
};

class Order : public Table
{
public:
    unordered_map<int, unordered_map<int, int>> viewBill;

    map<int, pair<string, int>> menu
    {
        {1, {"Thali       ", 70}},
        {2, {"French Fries",40}},
        {3, {"Pizza       ", 90}},
        {4, {"Sandwich    ", 45}},
        {5, {"Burger      ", 55}},
        {6, {"Spring Rolls", 40}},
        {7, {"Dosa Sambar ", 80}},
        {8, {"Idli Sambar ", 60}},
        {9, {"Momos       ", 40}},
        {10, {"Soup       ", 50}},
        {11, {"Tea        ", 30}},
        {12, {"Coffee     ", 35}}    
    };

    void orderFood()
    {
        int tableId;
        cout << "Enter table id: ";
        cin >> tableId;
        if (!isValid(tableId))
        {
            cout << "INVALID" << endl;
            system("pause");
            return;
        }
        cout << endl << "-----------MENU-----------" << endl;
        cout << "S.No\tItem\t\tPrice" << endl;
        for (auto it : menu)
        {
            cout << it.first << ".\t" << it.second.first << "\t" << it.second.second << endl;
        }
        int orderNo;
        cout << endl<< "Enter the numbers you want to order one by one." << endl
             << "When you finish, enter any character: " << endl;
        while (1)
        {
            cin >> orderNo;
            if (cin.fail() || orderNo > 12 || orderNo < 1)
                break;
            viewBill[tableId][orderNo]++;
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Your order has been placed successfully...!" << endl;
        system("pause");
        return;
    }
};

class Bill : public Order
{
public:
    void printBill(int tno)
    {
        int i = 1, total = 0;
        cout << "\nS.No\tItem\t\tCount\tPrice\n";
        for (auto it : viewBill[tno])
        {
            cout << i << ".\t" << menu[it.first].first << "\t" << it.second << "\t" << menu[it.first].second * it.second << endl;
            total += menu[it.first].second * it.second;
            i++;
        }
        cout << endl
             << "\t\tTotal:\t" << total << endl;
    }
    void billing()
    {
        int tno, total = 0;
        cout << "Enter table number: ";
        cin >> tno;
        if (!isValid(tno))
        {
            cout << "INVALID" << endl;
            system("pause");
            return;
        }
        cout << endl << "--------------------BILL--------------------" ;

        printBill(tno);

        cout << "Continue after payment." << endl;
        system("pause");
        cout << endl;
        cout << "    Thankyou! Visit again...!" << endl;
        system("pause");
        viewBill[tno].clear();
        allocateQueue(tno);
        return;
    }

private:
    void allocateQueue(int tno)
    {
        if (waiting2.size() > 0 || waiting4.size() > 0 || waiting6.size() > 0)
        {
            int custId;
            if (tno / 10 <= 2)
            {
                custId = waiting2.front();
                waiting2.pop();
            }
            else if (tno / 10 <= 4)
            {
                custId = waiting4.front();
                waiting4.pop();
            }
            else if (tno / 10 <= 6)
            {
                custId = waiting6.front();
                waiting6.pop();
            }
            cout << "Seats are available" << endl
                 << "Table no " << tno << " is allotted for " << custId << endl;
            int peopleCount;
            cout << "Enter number of people: ";
            cin >> peopleCount;
            tableStatus[tno].second = peopleCount;
            system("pause");
        }
        else
        {
            tableStatus[tno].first = true;
            tableStatus[tno].second = 0;
        }
    }
};

class Overview : public Bill
{
public:
    void detailedOverview()
    {
        string pass ;
        cout<< "Enter password: " ;
        cin>> pass ;
        
        if (pass == "15631")
        {
            cout << endl << "#################  MANAGER VIEW  #################" << endl ;
            cout << "Number of groups in queue (2-seater): " << waiting2.size() << endl
                 << "Number of groups in queue (4-seater): " << waiting4.size() << endl
                 << "Number of groups in queue (6-seater): " << waiting6.size() << endl;
            system("pause");
            
            cout << endl<< "\t---------Table Status---------" << endl;
            cout << "Available tables are: ";
            for (auto it : tableStatus)
            {
                if (it.second.first == true)
                {
                    cout << it.first << " ";
                }
            }
            cout << endl;
            system("pause");
            
            for (auto it : tableStatus)
            {
                if (it.second.first == false)
                {
                    cout << endl<< "Table " << it.first << " is allotted, " << it.second.second << " people occupied the table, order details: " << endl;
                    printBill(it.first);
                }
            }
            
        }
        
        else
        {
            cout<< "Your Password is incorrect !" ;
        }
        system("pause");
    }
};

int main()
{
    Overview obj;
    while (1)
    {
        int option;
        cout<< endl << endl ;
        cout << "******************************************************************************************" << endl ;
        cout << "                              !!!  URBAN SPICE RESTAURANT  !!!                            " << endl;
        cout << "******************************************************************************************" << endl << endl;
        cout << "1. Table Allocation" << endl
             << "2. Order Food" << endl
             << "3. View Bill" << endl
             << "4. Manager View" << endl
             << "5. Exit" << endl << endl 
             << "Enter your choice: ";
        cin >> option;
        switch (option)
        {
            case 1:
                obj.allocation();
                break;
                
            case 2:
                obj.orderFood();
                break;

            case 3:
                obj.billing();
                break;

            case 4:
                obj.detailedOverview();
                break;

            case 5:
                exit(0);
                break;

            default:
                cout << "Invalid" << endl;
        }
    }
    return 0;
}
