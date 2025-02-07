#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
using namespace std;

const int NumOfUser = 5;
const int NumOfItem = 10;

bool ErrorsOfNumbers(string input)
{
    if (input.empty())
    {
        cout << "Error!\n"
             << "Field must not be empty!\n";
        return false;
    }
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] < '0' || input[i] > '9' || input[i] != '.')
        {
            cout << "Error!!!\n"
                 << "The input you provided is invalid.\n"
                 << "Please enter a number.\n";
            return false;
        }
    }
    double num = stod(input);
    if (num <= 0)
    {
        cout << "Error!!!\n"
             << "Please enter a positive number.\n";
        return false;
    }
    return true;
}

struct Wallet
{
    double initial_balance = 5.5;
    double current_balance = 5.5;
    bool increase_balance(string a)
    {
        if (ErrorsOfNumbers(a))
        {
            double num = stod(a);
            this->current_balance += num;
            cout << "Your wallet has been recharged ! \n";
            return true;
        }
        else
        {
            return false;
        }
    }
    bool decrease_balance(string a)
    {
        if (ErrorsOfNumbers(a))
        {
            double num = stod(a);
            if ((current_balance -= num) >= initial_balance)
            {
                this->current_balance -= num;
                cout << "Your wallet has decreased ! \n";
                return true;
            }
            else
            {
                cout << "Not enough balance ! \n"
                     << "You can't make this purchase.\n";
                     return
            }
        }
        else
        {
            return false;
        }
    }
};

struct User
{
    string username;
    string password;
    bool isAdmin;
    Wallet wallet;
};

struct Item
{
    string name;
    double price;
    int count;
};

User users[NumOfUser] = {
    {"Ali", "aa123mn1", 0, 5.5}, {"Kiana", "asdfgdhj", 0, 5.5}, {"Sina", "liuuyer12", 0, 5.5}, {"Zahra", "1234ddddd", 1, 0}, {"Ailar", "lklklkqqq12", 1, 0}};

Item items[NumOfItem] = {
    {"apple", 4, 12}, {"pear", 7.2, 10}, {"greengage", 5, 12}};

void UsersSaveToFile()
{
    ofstream file("users.txt");

    for (int i = 0; i < NumOfUser; i++)
    {
        file << users[i].username << " " << users[i].password << " " << users[i].isAdmin << " " << users[i].wallet.current_balance << '\n';
    }
    file.close();
}

void ReadUsersOfFile()
{
    ifstream file("users.txt");
    for (int i = 0; i < NumOfUser; i++)
    {
        file >> users[i].username >> users[i].password >> users[i].isAdmin >> users[i].wallet.current_balance;
    }
    file.close();
}

void ProductSaveToFile()
{
    ofstream file("products.txt");
    if (!file)
    {
        cout << "Error opening pruducts.txt for writing !!!\n";
        return;
    }

    for (int i = 0; i < NumOfItem; i++)
    {
        file << items[i].name << " " << items[i].price << " " << items[i].count << '\n';
    }
    file.close();
}

void ReadProductsOfFile()
{
    ifstream file("products.txt");
    for (int i = 0; i < NumOfItem; i++)
    {
        file >> items[i].name >> items[i].price >> items[i].count;
    }
    file.close();
}

user *login()
{
    string username, password;
    cout << "Please enter your username : \n";
    cin >> username;
    if (username.empty())
    {
        cout << "Error!\n"
             << "Field must not be empty!\n";
        return nullptr;
    }

    for (int i = 0; i < NumOfUser; i++)
    {
        if (username == users[i].username)
        {
            cout << "Please enter your password : \n";
            cin >> password;
            if (password == users[i].password)
            {
                cout << "User login successful ! \n";
                return &users[i];
            }
        }
    }
    cout << "Incorrect username or password ! \n"
         << "Please try again.\n";
}

/*struct User_Commands
{
    void showItem(string item)
    {
    }
};*/

int main()
{
    ReadUsersOfFile();
    ReadProductsOfFile();

    cout << setw(40) << "******************************\n";
    cout << setw(40) << "*    WELCOME TO OUR WMS !    *\n";
    cout << setw(40) << "******************************\n";

    user *User = nullptr;
    while (User == nullptr)
    {
        User = login();
    }
}
