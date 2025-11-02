#include <stdio.h>
#include <stdlib.h>
#include "file.h"

//||||||||||||||||||||||||||||||||||||||| Save Contacts To File |||||||||||||||||||||||||||||||||||||||//

// This function saves all contacts to a CSV file
void saveContactsToFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.csv", "w"); // Open the file for writing
    if (fptr == NULL)                        // If file can't be opened, show error
    {
        printf("Could not open 'contacts.csv' file for writing!\n");
        return;
    }

    fprintf(fptr, "%d\n", addressBook->contactCount); // Write the number of contacts first

    // Loop through each contact and write their details
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        fprintf(fptr, "%s,%s,%s\n", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); // Write name, phone, email separated by commas
    }
    fclose(fptr); // Close the file

    return; // End the function
}

//||||||||||||||||||||||||||||||||||||||| Loads Contacts From The CSV File |||||||||||||||||||||||||||||||||||||||//

// This function loads contacts from the CSV file
void loadContactsFromFile(AddressBook *addressBook)
{
    FILE *fptr = fopen("contacts.csv", "r"); // Open the file for reading
    if (fptr == NULL)                        // If file can't be opened, show error
    {
        printf("Could not open 'contacts.csv' file for reading!\n");
        return;
    }

    fscanf(fptr, "%d\n", &addressBook->contactCount); // Read the number of contacts from the first line

    if (addressBook->contactCount > 0) // If there are contacts
    {
        // Loop to read each contact's details
        for (int i = 0; i < addressBook->contactCount; i++)
        {
            fscanf(fptr, " %[^,],%[^,],%[^\r\n]", addressBook->contacts[i].name, addressBook->contacts[i].phone, addressBook->contacts[i].email); // Read name, phone, email
        }
        fclose(fptr);                                // Close the file
        printf("\nContacts loaded successfully!\n"); // Show success message
    }
    else
    {
        printf("\nContact book is empty!\n"); // If no contacts, show message
        return;
    }
}
