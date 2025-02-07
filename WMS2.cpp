#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <cctype>
using namespace std;

const int NumOfUser = 3;
const int NumOfAdmin = 2;
int itemCount = 10;

bool Isempty(string input)
{
    if (input.empty())
    {
        cout << "Error!\n"
             << "Field must not be empty!\n";
        return false;
    }
    else
    {
        return true;
    }
}

bool ErrorsOfNumbers(string input) // shows errors for invalid numeric inputs.
{
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
    bool increase_balance(double a)
    {
        if (Isempty(to_string(a)))
        {
            return false;
        }
        if (ErrorsOfNumbers(to_string(a)))
        {
            this->current_balance += a;
            cout << "Your wallet has been recharged ! \n";
            return true;
        }
        else
        {
            return false;
        }
    }
    bool decrease_balance(double a)
    {
        if (Isempty(to_string(a)))
        {
            return false;
        }
        if (ErrorsOfNumbers(to_string(a)))
        {
            double CheckBalance = current_balance -= a;
            if (CheckBalance >= initial_balance)
            {
                this->current_balance -= a;
                cout << "Your wallet has decreased ! \n";
                return true;
            }
            else
            {
                cout << "Not enough balance ! \n"
                     << "You can't make this purchase.\n";
                return false;
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
    Wallet wallet;
};

struct Admin
{
    string username;
    string password;
};

struct Item
{
    string name;
    double price;
    int count;
};

User users[NumOfUser] = {
    {"Ali", "aa123mn1", 5.5}, {"Kiana", "asdfgdhj", 5.5}, {"Sina", "liuuyer12", 5.5}};

Admin admins[NumOfAdmin] = {
    {"Zahra", "1234ddddd"}, {"Ailar", "lklklkqqq12"}};

Item *items = new Item[10]{
    {"pear", 10, 7}, {"greengage", 8.5, 5}, {"apple", 2.5, 8}, {"kiwi", 9, 11}, {"apricot", 6, 4}, {"grapefruit", 11.5, 3}, {"pineapple", 10.5, 12}, {"tomato", 4.5, 2}, {"banana", 13.4, 8}, {"strawberry", 15, 3}};

void resizeArray(int newSize, int previousSize)
{
    if (newSize > previousSize)
    {
        Item *newitems = new Item[newSize];
        for (int i = 0; i < previousSize; i++)
        {
            newitems[i] = items[i];
        }
        delete[] items;
        items = newitems;
    }
    else
    {
        Item *newitems = new Item[newSize];
        for (int i = 0; i < newSize; i++)
        {
            newitems[i] = items[i];
        }
        delete[] items;
        items = newitems;
    }
}

void UsersSaveToFile()
{
    ofstream file("users.txt");
    if (!file)
    {
        cout << "Error opening file (users.txt) for writing!\n";
        return;
    }
    for (int i = 0; i < NumOfUser; i++)
    {
        file << users[i].username << " " << users[i].password << " " << users[i].wallet.current_balance << '\n';
    }
    for (int i = 0; i < NumOfAdmin; i++)
    {
        file << admins[i].username << " " << admins[i].password << '\n';
    }
    file.close();
}

void ReadUsersOfFile()
{
    ifstream file("users.txt");
    if (!file)
    {
        cout << "Error : opening file (users.txt) for reading !\n";
        return;
    }
    for (int i = 0; i < NumOfUser; i++)
    {
        file >> users[i].username >> users[i].password >> users[i].wallet.current_balance;
    }
    for (int i = 0; i < NumOfAdmin; i++)
    {
        file >> admins[i].username >> admins[i].password;
    }
    file.close();
}

void ProductSaveToFile()
{
    ofstream file("products.txt");
    if (!file)
    {
        cout << "Error opening file (pruducts.txt) for writing !\n";
        return;
    }
    int NumOfProducts = itemCount;
    file << NumOfProducts << '\n'; // save the numbers of products at first in file.

    for (int i = 0; i < NumOfProducts; i++)
    {
        file << items[i].name << " " << items[i].price << " " << items[i].count << '\n';
    }
    file.close();
}

void ReadProductsOfFile()
{
    ifstream file("products.txt");
    if (!file)
    {
        cout << "Error opening file (products.txt) for reading !\n";
        return;
    }
    file >> itemCount;
    resizeArray(itemCount, 10);
    for (int i = 0; i < itemCount; i++)
    {
        file >> items[i].name >> items[i].price >> items[i].count;
    }
    file.close();
}

bool FileExists(const string &filename)
{
    ifstream file(filename);
    return file.is_open();
}

void *login(int *check)
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
                *check = 2;
                cout << "User login successful ! \n";
                return &users[i];
            }
        }
    }
    for (int i = 0; i < NumOfAdmin; i++)
    {
        if (username == admins[i].username)
        {
            cout << "Please enter your password : \n";
            cin >> password;
            if (password == admins[i].password)
            {
                *check = 1;
                cout << "Login as admin successful ! \n";
                return &admins[i];
            }
        }
    }
    cout << "Incorrect username or password ! \n"
         << "Please try again.\n";
    return nullptr;
}

void toLower(string *str)
{
    for (int i = 0; i < str->size(); i++)
    {
        (*str)[i] = tolower((*str)[i]);
    }
}

void boundary()
{
    cout << setw(40) << "------------------------------------------\n";
}

Item *find(string prefix)
{
    for (int i = 0; i < itemCount; i++)
    {
        if (prefix == items[i].name)
        {
            return &items[i];
        }
    }
    cout << "Item not found!\n";
    return nullptr;
}

void show(string prefix)
{
    boundary();
    if (prefix == "item")
    {
        for (int i = 0; i < itemCount; i++)
        {
            cout << "Item " << i + 1 << " :\t" << items[i].name << '\n';
        }
    }
    else
    {
        Item *ans = find(prefix);
        if (ans != nullptr)
        {
            cout << "Item : " << ans->name << '\t' << "The price :" << ans->price << "$\n";
        }
    }
    boundary();
}

void buy(string prefix, User *user)
{
    Item *ans = nullptr;
    if (prefix == "item")
    {
        string item;
        cout << "Whitch item do you want to buy ?\n";
        show(prefix);
        cout << "Choose an item from the list.\n# ";
        cin >> item;
        toLower(&item);
        ans = find(item);
    }
    else
    {
        ans = find(prefix);
    }
    boundary();
    if (ans != nullptr)
    {
        if ((ans->count) > 0)
        {
            if (user->wallet.decrease_balance(ans->price))
            {
                ans->count--;
                cout << "Your purchase was successful.\n";
                cout << "You bought 1 kg of " << ans->name << ".";
            }
        }
        else
        {
            cout << "Sorry , We don't have enough items in stock.\n";
        }
    }
    boundary();
}

void help(string prefix)
{
    boundary();
    if (prefix == "command")
    {
        cout << "Here is the list of commands : \n";
        cout << "show ITEM\t" << "buy ITEM\t" << "balance\t" << "help COMMAND\n";
    }
    else if (prefix == "show")
    {
        cout << "***** show COMMAND *****\n";
        cout << "With this command , you can view a list of items in the WMS.\n";
        cout << "If you enter the name of an item , like : show apple \n"
             << " detailed information about that item include its name and price will be displayed.\n";
        cout << "To use it , enter the command name.\n";
    }
    else if (prefix == "buy")
    {
        cout << "***** buy COMMAND *****\n";
        cout << "With this command , you can buy the you want.\n";
        cout << "If you enter the name of an item , like : buy apple \n"
             << "you can buy 1 kg of that item.\n ";
        cout << "To use it , enter the command name.\n";
    }
    else if (prefix == "balance")
    {
        cout << "***** balance COMMAND *****\n";
        cout << "With this command , you can see your current wallet balance.\n";
        cout << "To use it , enter the command name.\n";
    }
    else if (prefix == string::npos)
    {
        cout << "***** help COMMAND *****\n";
        cout << "With this command , you can see a list of all commands.\n";
        cout << "if you enter the name of an item , like : help shown\n " << "the system will give you details on how tp use it.\n";
        cout << "To use it , enter the command name.\n";
    }
    boundary();
}

void userCommand(string command, User *user)
{
    int index_space = command.find(' ');
    string baseWord = command.substr(0, index_space);
    string prefix = "";
    if (index_space != string::npos)
    {
        prefix = command.substr(index_space + 1);
        if (baseWord == "show")
        {
            show(prefix);
        }
        else if (baseWord == "buy")
        {
            buy(prefix, user);
        }
        else if (baseWord == "balance")
        {
            boundary();
            cout << "Your current balance is : " << user->wallet.current_balance << " $\n";
            boundary();
        }
        else if (baseWord == "help")
        {
            help(prefix);
        }
    }
    else
    {
        cout << "Command not found. You can use the 'help' command to find the correct one.\n";
    }
}

int main()
{
    if (!FileExists("users.txt"))
    {
        UsersSaveToFile();
    }
    if (!FileExists("products.txt"))
    {
        ProductSaveToFile();
    }
    ReadUsersOfFile();
    ReadProductsOfFile();

    cout << setw(40) << "******************************\n";
    cout << setw(40) << "*    WELCOME TO OUR WMS !    *\n";
    cout << setw(40) << "******************************\n";

    void *loggedUser = nullptr;
    int check = 0;
    Admin *admin = nullptr;
    User *user = nullptr;
    while (loggedUser == nullptr)
    {
        loggedUser = login(&check);
    }
    if (check == 1) // when the user is admin.
    {
        admin = static_cast<Admin *>(loggedUser);
        cout << "Welcome , Admin " << admin->username << "." << '\n';
    }
    else if (check == 2)
    { // when the user is regular.
        user = static_cast<User *>(loggedUser);
        cout << "Welcome , User " << user->username << "." << '\n';
    }

    bool continuee = true;
    string input;
    string command;
    if (check == 2) // when the user is regular.
    {
        cin.ignore();
        while (continuee)
        {
            cout << "Enter your command :\n"
                 << "# ";
            getline(cin, command);
            toLower(&command);
            userCommand(command, user);
            UsersSaveToFile();
            ProductSaveToFile();
            cout << "Do you still want to continue ? \n"
                 << "IF you don't want to continue , enter 0 .\n";
            getline(cin, input);
            if (input == "0")
            {
                continuee = false;
            }
        }
    }
}