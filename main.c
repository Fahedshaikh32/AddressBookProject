
#include <stdio.h>
#include "file.h"

int main()
{
    int choice; // This variable stores the user's menu choice (a number from 1 to 7)

    AddressBook addressBook; // This is the main structure that holds all contacts

    initialize(&addressBook); // Load existing contacts from the file when the program starts

    // This loop shows the menu and keeps running until the user chooses to exit
    do
    {
        // Print the menu options for the user
        printf("\nAddress Book Menu:\n");
        printf("\n1. Create contact ➕\n");
        printf("\n2. Search contact 🔎\n");
        printf("\n3. Edit contact ✏️\n");
        printf("\n4. Delete contact 🗑️\n");
        printf("\n5. List all contacts 📋\n");
        printf("\n6. Save contacts 💾\n");
        printf("\n7. Exit 🚪\n");
        printf("\nEnter your choice: "); // Ask user to pick a number
        scanf("%d", &choice);          // Read the user's choice

        // Based on the choice, call the right function
        switch (choice)
        {
        case 1:
            createContact(&addressBook); // Add a new contact
            break;
        case 2:
            searchContact(&addressBook); // Find a contact
            break;
        case 3:
            editContact(&addressBook); // Change a contact's info
            break;
        case 4:
            deleteContact(&addressBook); // Remove a contact
            break;
        case 5:
            listContacts(&addressBook); // Show all contacts
            break;
        case 6:
            printf("\nSaving contacts...\n");   // Show a message while saving
            saveContactsToFile(&addressBook); // Save to file
            break;
        case 7:
            printf("\nExiting...\n"); // Show exit message
            break;
        default:
            printf("\nInvalid choice. Please try again.\n"); // If choice is wrong, ask again
        }
    } while (choice != 7); // Keep looping until user chooses 7 (exit)

    return 0; // End the program successfully
}
