#include "LibrarySystem.h"

/*
    Main.cpp
    Author: Saeed Nawaz SN1153@live.mdx.ac.uk
    Created: 24/12/2023
    Updated: 11/01/2024
*/

int main(int argc, char* argv[]) {
    //If file is not found, return help message and end the program
    if (argc != 2) {
        std::cerr << "\nUsage: " << argv[0] << " <csv_filename>" << std::endl;
        return 1;
    }

    const std::string filename = argv[1];
    std::vector<Book> books = getBook(filename);
    std::vector<Member> members;

    Librarian librarian(1, "LibrarianName", "LibrarianAddress", 
    "librarian@email.com", 50000);

    //Begin main program inside while loop whilst choice is not 0

    int choice;
    do {
        std::cout << "\nMenu:" << std::endl;
        std::cout << "1 - Borrow Book from Library" << std::endl;
        std::cout << "2 - Currently Borrowed Books by Member" << std::endl;
        std::cout << "3 - Return Book by Member" << std::endl;
        std::cout << "4 - Add New Member" << std::endl;
        std::cout << "5 - List All Currently Registered Members" << std::endl;
        std::cout << "0 - Exit" << std::endl;
        std::cout << "\nEnter your choice: ";
        choice = getValidIntInput();

        //Case switch used to get the validated user input and process accordingly

        switch (choice) {
        case 1: {
            int memberId;
            std::cout << "\nEnter the Member ID: ";
            memberId = getValidIntInput();

            int bookId;
            std::cout << "\nEnter the Book ID to issue: ";
            bookId = getValidIntInput();

            librarian.issueBook(memberId, bookId, members, books);
            break;
        }
        case 2: {
            int memberId;
            std::cout << "\nEnter the Member ID: ";
            memberId = getValidIntInput();
            
            librarian.displayBorrowedBooks(memberId, books);
            break;
        }
        case 3: {
            int memberId;
            std::cout << "\nEnter the Member ID: ";
            memberId = getValidIntInput();

            int bookId;
            std::cout << "\nEnter the Book ID to return: ";
            bookId = getValidIntInput();

            librarian.returnBook(memberId, bookId, members, books);
            break;
        }
        case 4: {
            librarian.addMember(members);
            break;
        }
        case 5: {
            librarian.listAllMembers(members);
            break;
        }
        case 0:
            std::cout << "\nExiting the program." << std::endl;
            break;
        default:
            std::cout << "\nInvalid choice. Please try again." << std::endl;
        }
    } while (choice != 0);

    return 0;
}
