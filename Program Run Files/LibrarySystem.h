#ifndef LIBRARYSYSTEM_H
#define LIBRARYSYSTEM_H

/*
    LibrarySystem.h
    Author: Saeed Nawaz SN1153@live.mdx.ac.uk
    Created: 24/12/2023
    Updated: 11/01/2024
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <ctime>

//Creating a structure to group and store book data
struct Book {
    int id;
    std::string name;
    int pageCount;
    std::string authorFirstName;
    std::string authorLastName;
    std::string bookType;
    int borrowedByMemberId;
    time_t dueDate;
};

//Creating a structure to group and store member data
struct Member {
    int id;
    std::string name;
};

//Defining the Person class
class Person {
protected:
    int id;
    std::string name;
    std::string address;
    std::string email;

public:
    Person(int id, const std::string& name, const std::string& 
    address, const std::string& email)
        : id(id), name(name), address(address), email(email) {}

    virtual ~Person() {}

    int getId() const {
        return id;
    }

    std::string getName() const {
        return name;
    }

    std::string getAddress() const {
        return address;
    }

    std::string getEmail() const {
        return email;
    }
};

//Defining the librarian class as a nested class inside the Person class
class Librarian : public Person {
public:
    Librarian(int id, const std::string& name, const std::string
    & address, const std::string& email, int salary)
        : Person(id, name, address, email), salary(salary) {}

    //Member function declarations
    void addMember(std::vector<Member>& members);
    void issueBook(int memberId, int bookId, std::vector<Member>
    & members, std::vector<Book>& books);
    void returnBook(int memberId, int bookId, std::vector<Member>
    & members, std::vector<Book>& books);
    void displayBorrowedBooks(int memberId, const std::vector<Book>
    & books);
    void listAllMembers(const std::vector<Member>& members) const;

private:
    int salary;
};

//Declaring non member functions
std::vector<Book> getBook(const std::string& filename);
int getValidIntInput();
std::string getValidStringInput();
std::string getValidMemberName();

#endif