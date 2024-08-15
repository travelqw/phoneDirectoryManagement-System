#include <iostream>
#include <regex>
#include <cctype>
#include <string>
using namespace std;

struct Contact
{
    string empName, empPhoneNumber;
    Contact *next;
};
Contact *head = nullptr; // initially-empty

string trim(const string &str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    size_t last = str.find_last_not_of(" \t\n\r");
    if (first == string::npos || last == string::npos)
        return ""; // If the string contains only whitespace characters
    return str.substr(first, last - first + 1);
}

bool validatePhoneNumber(const string &phoneNumber)
{
    regex pattern(R"(^(\+92|92|0)?3[0-9]{2}[0-9]{7}$)");
    return regex_match(phoneNumber, pattern);
}

void addContact()
{
    string name, phoneNum;
    cout << "Enter employee's name: ";
    getline(cin, name);
    name = trim(name);

    while (name.empty())
    {
        cout << "Invalid Input! Emloyee's name cannot be empty or contain only spaces...\nKindly re-enter: ";
        getline(cin, name);
        name = trim(name);
    }

    cout << "Enter employee's phone number in one of the following three formats:\n";
    cout << "1. +923000000000\n2. 923000000000\n3. 03000000000\n";
    cout << "Enter employee's phone number: ";
    cin >> phoneNum;
    cin.ignore();

    while (true)
    {
        if (!validatePhoneNumber(phoneNum))
        {
            cout << "Invalid phone number! Kindly re-enter a valid phone number in one of the following three formats:\n";
            cout << "1. +923000000000\n2. 923000000000\n3. 03000000000\n";
            cout << "Please re-enter employee's phone number: ";
            cin >> phoneNum;
            cin.ignore();
            continue;
        }

        bool found = false;
        Contact *current = head;
        while (current != nullptr)
        {
            if (current->empPhoneNumber == phoneNum)
            {
                found = true;
                break;
            }
            current = current->next;
        }

        if (found)
        {
            cout << "This phone number '" << phoneNum << "' is already added in the phone directory. Employee's contact numbers should be distinct. Kindly re-enter employee's phone number in one of the following three formats:\n";
            cout << "1. +923000000000\n2. 923000000000\n3. 03000000000\n";
            cout << "Please re-enter employee's phone number: ";
            cin >> phoneNum;
            cin.ignore();
        }
        else
            break; // Valid and unique phone number found, exit loop
    }

    Contact *temp = new Contact(); // Creating a new contact
    temp->empName = name;
    temp->empPhoneNumber = phoneNum;
    temp->next = nullptr;

    if (head == nullptr)
        head = temp;
    else
    {
        Contact *current = head;
        while (current->next != nullptr)
            current = current->next;
        current->next = temp;
    }

    cout << "Contact of employee: '" << name << "' with phone number: '" << phoneNum << "', added to the phone directory.\n\n";
}

Contact *searchContact()
{
    if (head == nullptr)
    {
        cout << "No contacts in the directory. The phone directory is empty.\n";
        return nullptr;
    }
    string contact;
    cout << "Enter employee contact to find contact details: "; // as contact is always distinct and name can be same
    cin >> contact;
    cin.ignore(); // input buffer
    bool found = false;

    Contact *current = head;
    while (current != nullptr)
    {
        if (current->empPhoneNumber == contact)
        {
            found = true;
            cout << "Employee found!\n";
            cout << "o) Employee name: " << current->empName << endl;
            cout << "   Employee Contact: " << current->empPhoneNumber << endl;
            cout << endl;
            return current;
        }
        current = current->next;
    }

    if (!found)
    {
        cout << contact << " not found in the employee phone directory.\n";
        return nullptr;
    }
}

void displayAllContacts()
{
    if (head == nullptr)
    {
        cout << "No contacts in the directory. The phone directory is empty.\n";
        return;
    }
    Contact *current = head;
    cout << "Employee List:\n";
    while (current != nullptr)
    {
        cout << "o) Employee name: " << current->empName << endl;
        cout << "   Employee Contact: " << current->empPhoneNumber << endl;
        cout << endl;
        current = current->next;
    }
}

void updateContact() // update by searching
{
    Contact *contactToUpdate = searchContact();
    if (contactToUpdate != nullptr)
    {
        char choice = '\0';
        cout << "What do you want to update:\no) Employee's Name or\no) Employee's Contact\nPress 'n' for name and 'c' for contact: ";
        cin >> choice;
        cin.ignore(); // input buffer

        string newInfo = "";
        switch (tolower(choice))
        {
        case 'n':
            cout << "Enter new name: ";
            getline(cin, newInfo);
            newInfo = trim(newInfo);

            while (newInfo.empty())
            {
                cout << "Invalid Input! Emloyee's name cannot be empty or contain only spaces...\nKindly re-enter: ";
                getline(cin, newInfo);
                newInfo = trim(newInfo);
            }

            contactToUpdate->empName = newInfo;
            cout << "Employee's name updated suceesfully";
            break;
        case 'c':
            cout << "Enter employee's new phone number in one of the following three formats:\n";
            cout << "1. +923000000000\n2. 923000000000\n3. 03000000000\n";
            cout << "Enter employee's phone number: ";
            cin >> newInfo;
            cin.ignore();

            while (!validatePhoneNumber(newInfo))
            {
                cout << "Invalid phone number! Kindly re-enter a valid phone number in one of the following three formats:\n";
                cout << "1. +923000000000\n2. 923000000000\n3. 03000000000\n";
                cout << "Please re-enter employee's phone number: ";
                cin >> newInfo;
                cin.ignore();
            }

            contactToUpdate->empPhoneNumber = newInfo;
            cout << "Employee's contact Updated Suceesfully";
            break;

        default:
            cout << "Invalid character entered.";
            break;
        }
        cout << endl;
    }
}

void deleteContact() // delete by searching
{
    Contact *contactToDelete = searchContact(); // Search for the contact to delete
    if (contactToDelete != nullptr)
    {
        if (contactToDelete == head)
        {
            head = head->next;
            delete contactToDelete;
            cout << "Contact Deleted Successfully.\n";
            return;
        }

        Contact *prev = head; // previous node of contactToDelete
        while (prev->next != contactToDelete)
            prev = prev->next;
        prev->next = contactToDelete->next;
        delete contactToDelete;
        cout << "Contact Deleted Successfully.\n";
    }
}

void deleteAllContacts()
{
    if (head == nullptr)
    {
        cout << "Contacts directory is already empty.\n";
        return;
    }
    Contact *current = head;
    while (current != nullptr)
    {
        Contact *next = current->next;
        delete current; // dellocating memeory, not actually deleting the value in it
        current = next;
    }
    head = nullptr;
    cout << "All ccontacts deleted.\n";
}

int main()
{ // contact management system
    cout << "\t\t\tPhone Directory Management System\n";
    int choice;
    do
    {
        cout << "You can do the following operations:\n";
        cout << "1. Add Contact\n2. Delete Contact\n3. Search Contact\n4. Display All Contacts\n5. Update Contact Information\n6. Delete/Clean Entire Directory\n7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Input buffer

        switch (choice)
        {
        case 1:
            addContact();
            break;
        case 2:
            deleteContact();
            break;
        case 3:
            searchContact();
            break;
        case 4:
            displayAllContacts();
            break;
        case 5:
            updateContact();
            break;
        case 6:
            deleteAllContacts();
            break;
        case 7:
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 7);

    exit(0); // 7 is pressed

    return 0;
}