
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
using namespace std;

// Base class
class User {
protected:
    int userID;
    string userName;

public:
    User(int id, string name) {
        userID = id;
        userName = name;
    }

    virtual void displayRole() {
        cout << "Library User" << endl;
    }

    virtual ~User() {}
};

// Derived class
class Student : public User {
public:
    Student(int id, string name) : User(id, name) {}

    void displayRole() override {
        cout << "User Type: Student" << endl;
    }
};

// Book class
class Book {
private:
    int bookID;
    string title;
    string author;
    bool available;

public:
    Book(int id, string t, string a, bool status = true) {
        bookID = id;
        title = t;
        author = a;
        available = status;
    }

    int getID() {
        return bookID;
    }

    bool isAvailable() {
        return available;
    }

    void issueBook() {
        if (available) {
            available = false;
            cout << "Book issued successfully!" << endl;
        } else {
            cout << "Book is already issued." << endl;
        }
    }

    void returnBook() {
        if (!available) {
            available = true;
            cout << "Book returned successfully!" << endl;
        } else {
            cout << "Book was not issued." << endl;
        }
    }

    void display() {
        cout << "\nBook ID: " << bookID;
        cout << "\nTitle: " << title;
        cout << "\nAuthor: " << author;
        cout << "\nStatus: "
             << (available ? "Available" : "Issued");
        cout << "\n--------------------------";
    }
};

// Library class
class Library {
private:
    vector<Book> books;

    void saveToFile() {
        ofstream file("books.txt");

        for (const Book &b : books) {
            file << b.getID() << endl;
            // Book details are saved separately below
        }

        file.close();
    }

    void loadFromFile() {
        // Initial sample books
        books.push_back(Book(101, "The Alchemist", "Paulo Coelho"));
        books.push_back(Book(102, "Wings of Fire", "A.P.J. Abdul Kalam"));
        books.push_back(Book(103, "1984", "George Orwell"));
    }

public:
    Library() {
        loadFromFile();
    }

    void addBook() {
        int id;
        string title, author;

        cout << "Enter Book ID: ";
        cin >> id;

        for (Book &b : books) {
            if (b.getID() == id) {
                cout << "Book ID already exists!" << endl;
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Book Title: ";
        getline(cin, title);

        cout << "Enter Author Name: ";
        getline(cin, author);

        books.push_back(Book(id, title, author));

        saveToFile();

        cout << "Book added successfully!" << endl;
    }

    void displayBooks() {
        if (books.empty()) {
            cout << "No books available." << endl;
            return;
        }

        for (Book &b : books) {
            b.display();
        }

        cout << endl;
    }

    void searchBook() {
        int id;
        cout << "Enter Book ID to search: ";
        cin >> id;

        for (Book &b : books) {
            if (b.getID() == id) {
                b.display();
                cout << endl;
                return;
            }
        }

        cout << "Book not found!" << endl;
    }

    void issueBook() {
        int id;
        cout << "Enter Book ID to issue: ";
        cin >> id;

        for (Book &b : books) {
            if (b.getID() == id) {
                b.issueBook();
                saveToFile();
                return;
            }
        }

        cout << "Book not found!" << endl;
    }

    void returnBook() {
        int id;
        cout << "Enter Book ID to return: ";
        cin >> id;

        for (Book &b : books) {
            if (b.getID() == id) {
                b.returnBook();
                saveToFile();
                return;
            }
        }

        cout << "Book not found!" << endl;
    }
};

// Main function
int main() {
    Library library;

    int choice;

    Student student(1, "Student");

    cout << "================================\n";
    cout << "     LIBRARY MANAGEMENT SYSTEM\n";
    cout << "================================\n";

    student.displayRole();

    do {
        cout << "\n\n1. Add New Book";
        cout << "\n2. Display All Books";
        cout << "\n3. Search Book";
        cout << "\n4. Issue Book";
        cout << "\n5. Return Book";
        cout << "\n6. Exit";

        cout << "\n\nEnter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                library.addBook();
                break;

            case 2:
                library.displayBooks();
                break;

            case 3:
                library.searchBook();
                break;

            case 4:
                library.issueBook();
                break;

            case 5:
                library.returnBook();
                break;

            case 6:
                cout << "Thank you for using the system!";
                break;

            default:
                cout << "Invalid choice! Try again.";
        }

    } while (choice != 6);

    return 0;
}
