#include <stdlib.h>
#include <iostream>
#include <sstream>
#include<windows.h>
#include "mysql_connection.h"
#include <cppconn/driver.h>         //cppconn api libararies
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <cppconn/resultset.h>

using namespace std;
using namespace sql;
const string server = "localhost";
const string username = "root";
const string password = "2211";
const string database = "mydb";

class Student { //Manages student data (ID)
private:
    string Id;
public:
    Student() : Id("") {}

    void setId(string id) {
        Id = id;
    }

    string getId() {
        return Id;
    }
};

class Library {     //
private:
    string Name;
    int Quantity;
public:
    Library() : Name(""), Quantity(0) {}

    void setName(string name) {
        Name = name;
    }

    void setQuantity(int quantity) {
        Quantity = quantity;
    }

    int getQuantity() {
        return Quantity;
    }

    string getName() {
        return Name;
    }
};

void admin(Connection* conn, Library& l, Student& s) {
    bool closed = false;
    while (!closed) {
        int choice;
        cout << "1. Add Book." << endl;
        cout << "2. Add Student." << endl;
        cout << "0. Exit." << endl;
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            system("cls");
            string name;
            int quantity;

            cout << "Book Name: ";
            cin >> name;
            l.setName(name);

            cout << "Enter Quantity: ";
            cin >> quantity;
            l.setQuantity(quantity);

            try {
               PreparedStatement* pstmt;
                pstmt = conn->prepareStatement("INSERT INTO lib (Name, Quantity) VALUES (?, ?)");
                pstmt->setString(1, l.getName());
                pstmt->setInt(2, l.getQuantity());
                pstmt->execute();
                delete pstmt;
                cout << "Book Inserted Successfully" << endl;
            }
            catch (SQLException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 2) {
            system("cls");
            string id;
            cout << "Enter Student ID: ";
            cin >> id;
            s.setId(id);

            try {
               PreparedStatement* pstmt;
                pstmt = conn->prepareStatement("INSERT INTO student (Id) VALUES (?)");
                pstmt->setString(1, s.getId());
                pstmt->execute();
                delete pstmt;
                cout << "Student Inserted Successfully" << endl;
            }
            catch (SQLException& e) {
                cout << "Error: " << e.what() << endl;
            }
        }
        else if (choice == 0) {
            closed = true;
            cout << "System is closing" << endl;
        }
    }
    Sleep(3000);
}

void display(Connection* conn) {
    system("cls");
    cout << "Available Books" << endl;
    cout << "***************" << endl;

    try {
        Statement* stmt;
        ResultSet* res;

        stmt = conn->createStatement();
        res = stmt->executeQuery("SELECT * FROM lib");

        while (res->next()) {
            cout << " " << res->getString("Name") << " " << res->getInt("Quantity") << endl;
        }

        delete res;
        delete stmt;
    }
    catch (SQLException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int book(Connection* conn, string Bname) {
    try {
        PreparedStatement* pstmt;
        ResultSet* res;

        pstmt = conn->prepareStatement("SELECT Quantity FROM lib WHERE Name = ?");
        pstmt->setString(1, Bname);
        res = pstmt->executeQuery();

        if (res->next()) {
            int quantity = res->getInt("Quantity");
            delete res;
            delete pstmt;
            return quantity;
        }
        else {
            cout << "Book Not Found." << endl;
            delete res;
            delete pstmt;
            return 0;
        }
    }
    catch (SQLException& e) {
        cout << "Error: " << e.what() << endl;
        return 0;
    }
}

void user(Connection* conn, Library& l, Student& s) {
    system("cls");
    display(conn);
    string Sid;
    cout << "Enter Your ID: ";
    cin >> Sid;

    try {
        PreparedStatement* pstmt;
        ResultSet* res;

        pstmt = conn->prepareStatement("SELECT * FROM student WHERE Id = ?");
        pstmt->setString(1, Sid);
        res = pstmt->executeQuery();

        if (res->next()) {
            cout << "Student ID Found." << endl;
            string Bname;
            cout << "Enter Book Name: ";
            cin >> Bname;

            int bookQuantity = book(conn, Bname);

            if (bookQuantity > 0) {
                bookQuantity -= 1;
                pstmt = conn->prepareStatement("UPDATE lib SET Quantity = ? WHERE Name = ?");
                pstmt->setInt(1, bookQuantity);
                pstmt->setString(2, Bname);
                pstmt->execute();
                delete pstmt;

                cout << "Book is available. Borrowing Book...." << endl;
            }
            else {
                cout << "Book is not Available." << endl;
            }
        }
        else {
            cout << "This Student is Not Registered." << endl;
        }

        delete res;
        delete pstmt;
    }
    catch (SQLException& e) {
        cout << "Error: " << e.what() << endl;
    }
}

int main() {
    Student s;
    Library l;

    Driver* driver;
    Connection* conn;

    try {
        driver = get_driver_instance();
        conn = driver->connect(server, username, password);
        conn->setSchema(database);
        cout << "Logged In!" << endl;
    }
    catch (SQLException& e) {
        cout << "Could not connect to server. Error message: " << e.what() << endl;
        system("pause");
        exit(1);
    }

    Sleep(3000);
    bool exit = false;
    while (!exit) {
        system("cls");
        int val;
        cout << "Welcome To Library Management System" << endl;
        cout << "************************************" << endl;
        cout << "1. Administration." << endl;
        cout << "2. User." << endl;
        cout << "0. Exit." << endl;
        cout << "Enter Choice: ";
        cin >> val;

        if (val == 1) {
            system("cls");
            admin(conn, l, s);
        }
        else if (val == 2) {
            user(conn, l, s);
            Sleep(5000);
        }
        else if (val == 0) {
            exit = true;
            cout << "Good Luck!" << endl;
            Sleep(3000);
        }
    }
    delete conn;
    return 0;
}
