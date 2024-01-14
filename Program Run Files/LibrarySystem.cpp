#include "LibrarySystem.h"

/*
    Main.cpp
    Author: Saeed Nawaz SN1153@live.mdx.ac.uk
    Created: 24/12/2023
    Updated: 11/01/2024
*/


/*
    Function to add a new member to the run data
    @param Member stores the data for the members in the run data
*/
void Librarian::addMember(std::vector<Member>& members) {
    std::string memberName;
    std::cout << "\nEnter the name of the new member: ";
    std::getline(std::cin, memberName);

    Member newMember = { static_cast<int>(members.size()) + 1, memberName };
    members.push_back(newMember);

    std::cout << "\nNew member added with ID " << newMember.id << ".\n";
    std::cout << "Member Name: " << newMember.name << std::endl;
}

/*
    Function to issue/allow a member to borrow a book from the .csv data file
    @param memberId the member identified by id number to borrow the book
    @param bookId the book id number input that the member is to borrow
    @param Member to be able to update that the member has borrowed a specific book
    @param Book to be able to update that the book borrowed has now been issued
*/
void Librarian::issueBook(int memberId, int bookId, std::vector<Member>
& members, std::vector<Book>& books) {
    auto memberIt = std::find_if(members.begin(), members.end(),
        [memberId](const Member& member) {
            return member.id == memberId;
        });

    //Check if member is found
    if (memberIt == members.end()) {
        std::cout << "\nMember with ID " << memberId
            << " does not exist. Cannot issue a book." << std::endl;
        return;
    }

    //Find the book with the given bookId and return whether or not it is available
    auto bookIt = std::find_if(books.begin(), books.end(),
        [bookId](const Book& book) {
            return book.id == bookId && book.borrowedByMemberId == 0;
        });

    //If the book is available, issue to member
    if (bookIt != books.end()) {
        bookIt->borrowedByMemberId = memberId;
        bookIt->dueDate = std::time(nullptr) + 3 * 24 * 60 * 60;

        std::cout << "\nBook with ID " << bookId << " issued to Member ID " 
        << memberId << ".\n";
        std::cout << "Due Date: " << std::ctime(&bookIt->dueDate);
    }
    else {
        std::cout << "\nBook with ID " << bookId 
        << " not available for borrowing or already borrowed.\n";
    }
}

/*
    Function to return/allow a member to return a book from the .csv data file and calculate
        a fine if the book returned was overdue based on the rate of £1/day book was overdue
    @param memberId the member identified by id number to return the book
    @param bookId the book id number input that the member is to return
    @param Member to be able to update that the member has returned a specific book
    @param Book to be able to update that the book issued previously has now been returned
*/
void Librarian::returnBook(int memberId, int bookId, std::vector<Member>
& members, std::vector<Book>& books) {
    auto memberIt = std::find_if(members.begin(), members.end(),
        [memberId](const Member& member) {
            return member.id == memberId;
        });

    //Check if member is found
    if (memberIt == members.end()) {
        std::cout << "\nMember with ID " << memberId
            << " does not exist. Cannot return a book." << std::endl;
        return;
    }

    //Search for the borrowed book's due date
    auto bookIt = std::find_if(books.begin(), books.end(),
        [bookId, memberId](const Book& book) {
            return book.id == bookId && book.borrowedByMemberId == memberId;
        });

    //If book is found
    if (bookIt != books.end()) {
        time_t returnTime = std::time(nullptr);
        double fineRate = 1.0;

        //Check if book is overdue and apply fine if required
        if (returnTime > bookIt->dueDate) {
            double overdueDays = difftime(returnTime, bookIt->dueDate) 
            / (60 * 60 * 24);
            double fine = fineRate * overdueDays;

            std::cout << "\nBook returned is overdue. The fine to be paid is: £"
                << std::fixed << std::setprecision(2) << fine << ".\n";
        }
        else {
            std::cout << "\nBook returned on-time.\n";
        }

        bookIt->borrowedByMemberId = 0;
        bookIt->dueDate = 0;

        std::cout << "Book with ID " << bookId << " returned by Member ID " 
        << memberId << ".\n";
    }
    else {
        std::cout << "\nBook with ID " << bookId
            << " not found or not borrowed by Member ID " << memberId << ".\n";
    }
}

/*
    Function to display the books and their information that have been borrowed by a certain member
    @param memberId get the information from the member via their identification
    @param Book to check each book id and get the information of the borrowed book
*/
void Librarian::displayBorrowedBooks(int memberId, const std::vector<Book>
& books) {
    std::cout << "\nBorrowed Books by Member ID " << memberId << ":\n" << std::endl;
    bool memberHasBorrowedBooks = false;

    for (const auto& book : books) {
        if (book.borrowedByMemberId == memberId) {
            std::cout << "Book ID: " << book.id << std::endl;
            std::cout << "Book Name: " << book.name << std::endl;
            std::cout << "Author: " << book.authorFirstName + " " 
            + book.authorLastName << std::endl;
            std::cout << "Book Type: " << book.bookType << std::endl;
            std::cout << "Page Count: " << book.pageCount << std::endl;
            std::cout << "Due Date: " << std::ctime(&book.dueDate) 
            << std::endl;
            std::cout << std::endl;
            memberHasBorrowedBooks = true;
        }
    }

    if (!memberHasBorrowedBooks) {
        std::cout << "No books currently borrowed by Member ID " 
        << memberId << ".\n";
    }
}

/*
    Function to allow the user/staff to see a list of registered members with their name and id
    @param Member reference the member data and output that information for each members
*/
void Librarian::listAllMembers(const std::vector<Member>& members) const {
    std::cout << "\nList of Currently Registered Members:\n" << std::endl;

    if (members.empty()) {
        std::cout << "No members currently registered.\n";
    } else {
        for (const auto& member : members) {
            std::cout << "Member ID: " << member.id << std::endl;
            std::cout << "Member Name: " << member.name << std::endl;
            std::cout << std::endl;
        }
    }
}

/*
    Function to read the .csv data file and store data inside a vector of the Book structures
    @param filename to reference the file from the directory that the program is also located in
*/
std::vector<Book> getBook(const std::string& filename) {
    std::ifstream file(filename);
    std::vector<Book> books;

    //If file is accessible, read data according to format
    if (file.is_open()) {
        std::string line;
        std::getline(file, line);

        while (std::getline(file, line)) {
            Book book;
            char comma;

            std::istringstream iss(line);

            iss >> book.id >> comma;
            std::getline(iss, book.name, ',');
            iss >> book.pageCount >> comma;
            std::getline(iss, book.authorFirstName, ',');
            std::getline(iss, book.authorLastName, ',');
            std::getline(iss, book.bookType);

            book.borrowedByMemberId = 0;
            book.dueDate = 0;

            books.push_back(book);
        }

        file.close();
    }
    else {
        std::cerr << "\nError opening file: " << filename << std::endl;
        exit(0);
    }

    return books;
}

/*
    Function to get and validate user input when the expected input is an integar
*/
int getValidIntInput() {
    int input;
    while (!(std::cin >> input)) {
        std::cerr << "\nError: Invalid input. Please enter a valid integer.\n";
        std::cin.clear();
        while (std::cin.get() != '\n');
    }
    std::cin.ignore();
    return input;
}

/*
    Function to get and validate user input when the expected input is a string
*/
std::string getValidStringInput() {
    std::string input;
    std::cin.ignore();
    std::getline(std::cin, input);
    return input;
}

/*
    Function to get the name of a new member to register that user with the run data
*/
std::string getValidMemberName() {
    std::string input;
    std::cout << "\nEnter the name of the new member: ";
    input = getValidStringInput();
    return input;
}
