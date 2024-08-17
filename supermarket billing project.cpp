#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Shopping {
private:
    int pcode;
    float price;
    float discount;
    string pname;

public:
    void menu();
    void administrator();
    void buyer();
    void add();
    void edit();
    void list();
    void remove();
    void receipt();
};

void Shopping::menu() {
    int choice;
    string email;
    string password;

    do {
        cout << "\t\t\t\t__________________________________\n";
        cout << "\t\t\t\t                                  \n";
        cout << "\t\t\t\t       Supermarket Main Menu      \n";
        cout << "\t\t\t\t                                  \n";
        cout << "\t\t\t\t__________________________________\n";

        cout << "\t\t\t\t|  1)Administrator   |\n";
        cout << "\t\t\t\t|  2)Buyer           |\n";
        cout << "\t\t\t\t|  3)Exit            |\n";
        cout << "\n\t\t\t  Please select!  ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "\t\t\t  Please login!  \n";
                cout << "\t\t\t  Enter Email:    \n";
                cin >> email;
                cout << "\t\t\t  Password:       \n";
                cin >> password;
                if (email == "tanaypandey205@gmail.com" && password == "tanay@123") {
                    administrator();
                } else {
                    cout << "Invalid email/password\n";
                }
                break;
            case 2:
                buyer();
                break;
            case 3:
                exit(0);
            default:
                cout << "Please select a valid option\n";
        }
    } while (true);
}

void Shopping::administrator() {
    int choice;

    do {
        cout << "\n\n\n\t\t\t  Administrator Menu";
        cout << "\n\t\t\t____1) Add the product____";
        cout << "\n\t\t\t____2) Modify the product____";
        cout << "\n\t\t\t____3) Delete the product____";
        cout << "\n\t\t\t____4) Back to main menu____";

        cout << "\n\n\t Please enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                add();
                break;
            case 2:
                edit();
                break;
            case 3:
                remove();
                break;
            case 4:
                return;
            default:
                cout << "Invalid choice\n";
        }
    } while (true);
}

void Shopping::buyer() {
    int choice;

    do {
        cout << "\t\t\t  Buyer\n";
        cout << "\t\t\t______________\n";
        cout << "\n\t\t\t1) Buy Product\n";
        cout << "\n\t\t\t2) Go Back\n";

        cout << "\n\n\t Please enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                receipt();
                break;
            case 2:
                return;
            default:
                cout << "Invalid choice\n";
        }
    } while (true);
}

void Shopping::add() {
    fstream data;
    int c;
    float p, d;
    string n;
    int token = 0;

    cout << "\n\n\t\t\t Add new product";
    cout << "\n\n\t Product code: ";
    cin >> pcode;
    cout << "\n\n\t Name of the product: ";
    cin >> pname;
    cout << "\n\n\t Price of the product: ";
    cin >> price;
    cout << "\n\n\t Discount on product: ";
    cin >> discount;

    data.open("database.txt", ios::in);
    if (!data) {
        data.open("database.txt", ios::app | ios::out);
        data << pcode << " " << pname << " " << price << " " << discount << "\n";
        data.close();
    } else {
        data >> c >> n >> p >> d;
        while (!data.eof()) {
            if (c == pcode) token++;
            data >> c >> n >> p >> d;
        }
        data.close();

        if (token == 1) {
            cout << "\n\n\t Product code already exists. Try again!";
        } else {
            data.open("database.txt", ios::app | ios::out);
            data << pcode << " " << pname << " " << price << " " << discount << "\n";
            data.close();
            cout << "\n\n\t\t Record inserted!";
        }
    }
}

void Shopping::edit() {
    fstream data, data1;
    int pkey;
    int token = 0;
    int c;
    float p, d;
    string n;

    cout << "\n\t\t\t Modify the record";
    cout << "\n\t\t\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nFile doesn't exist\n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> discount;
        while (!data.eof()) {
            if (pkey == pcode) {
                cout << "\n\t\t Product new code: ";
                cin >> c;
                cout << "\n\t\t Name of the product: ";
                cin >> n;
                cout << "\n\t\t Price: ";
                cin >> p;
                cout << "\n\t\t Discount: ";
                cin >> d;
                data1 << c << " " << n << " " << p << " " << d << "\n";
                cout << "\n\n\t\t Record edited\n";
                token++;
            } else {
                data1 << pcode << " " << pname << " " << price << " " << discount << "\n";
            }
            data >> pcode >> pname >> price >> discount;
        }
        data.close();
        data1.close();
        
        rename("database1.txt", "database.txt");
        if (token == 0) cout << "\n\nRecord not found!\n";
    }
}

void Shopping::remove()
 {
    fstream data, data1;
    int pkey;
    int token = 0;

    cout << "\n\n\t Delete product";
    cout << "\n\n\t Product code: ";
    cin >> pkey;

    data.open("database.txt", ios::in);
    if (!data) {
        cout << "File doesn't exist\n";
    } else {
        data1.open("database1.txt", ios::app | ios::out);
        data >> pcode >> pname >> price >> discount;
        while (!data.eof()) {
            if (pcode == pkey) {
                cout << "\n\n\t Product deleted successfully\n";
                token++;
            } else {
                data1 << pcode << " " << pname << " " << price << " " << discount << "\n";
            }
            data >> pcode >> pname >> price >> discount;
        }
        data.close();
        data1.close();
    
        rename("database1.txt", "database.txt");
        if (token == 0)
		 cout << "\n\nRecord not found!\n";
    }
}

void Shopping::list() {
    fstream data;
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\nFile doesn't exist\n";
        return;
    }

    cout << "\n\n__________________________________________________\n";
    cout << "ProNo\t\tName\t\tPrice\n";
    cout << "__________________________________________________\n";
    data >> pcode >> pname >> price >> discount;
    while (!data.eof()) {
        cout << pcode << "\t\t" << pname << "\t\t" << price << "\n";
        data >> pcode >> pname >> price >> discount;
    }
    data.close();
}

void Shopping::receipt() {
    fstream data;
    int arrc[100], arrq[100];
    char choice;
    int c = 0;
    float amount = 0, dis = 0, total = 0;

    cout << "\n\n\t\t\t\t RECEIPT";
    data.open("database.txt", ios::in);
    if (!data) {
        cout << "\n\n Empty database\n";
        return;
    }
    data.close();
    list();
    cout << "\t\t\t\t__________________________________\n";
    cout << "\t\t\t\t       Please place the order     \n";
    cout << "\t\t\t\t__________________________________\n";

    do {
        cout << "\n\nEnter Product code: ";
        cin >> arrc[c];
        cout << "\n\nEnter the product quantity: ";
        cin >> arrq[c];
        for (int i = 0; i < c; i++) {
            if (arrc[c] == arrc[i]) {
                cout << "\n\n Duplicate product code. Please try again!";
                goto skip;
            }
        }
        c++;
        skip:
        cout << "\n\n Do you want to buy another product? If yes, then press y else no: ";
        cin >> choice;
    } while (choice == 'y');

    cout << "\n\n\t\t\t______ RECEIPT____ \n";
    cout << "\nProduct No\tProduct Name\tProduct Quantity\tPrice\tAmount\tAmount with Discount\n";
    for (int i = 0; i < c; i++) {
        data.open("database.txt", ios::in);
        data >> pcode >> pname >> price >> discount;
        while (!data.eof()) {
            if (pcode == arrc[i]) {
                amount = price * arrq[i];
                dis = amount - (amount * discount / 100);
                total += dis;
                cout << pcode << "\t\t" << pname << "\t\t" << arrq[i] << "\t\t" << price << "\t" << amount << "\t\t" << dis << "\n";
            }
            data >> pcode >> pname >> price >> discount;
        }
        data.close();
    }
    cout << "\n\n_____________________\n";
    cout << "\n Total Amount: " << total << "\n";
}

int main() {
    Shopping s;
    s.menu();
    return 0;
}

