#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100 // Maximum number of contacts allowed

// Structure to hold details of a single contact
typedef struct
{
    char name[50];  // Contact's name
    char phone[20]; // Contact's phone number
    char email[50]; // Contact's email address
} Contact;

// Structure to manage the address book
typedef struct
{
    Contact contacts[100]; // Array of contacts
    int contactCount;      // Current number of contacts
} AddressBook;

void createContact(AddressBook *addressBook);      // Creates a new contact
int searchContact(AddressBook *addressBook);       // Searches for a contact
void editContact(AddressBook *addressBook);        // Edits an existing contact
void deleteContact(AddressBook *addressBook);      // Deletes a contact
void listContacts(AddressBook *addressBook);       // Lists all contacts
void initialize(AddressBook *addressBook);         // Initializes the address book
void saveContactsToFile(AddressBook *AddressBook); // Saves contacts to file

// Validation function prototypes
int validate_name(char new_name[]);                             // Validates the name input
int validate_phone(char new_phone[], AddressBook *addressBook); // Validates the phone number
int validate_email(char new_email[], AddressBook *addressBook); // Validates the email address

#endif
