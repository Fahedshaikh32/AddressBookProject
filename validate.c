#include <stdio.h>
#include <string.h>
#include "contact.h"
#include <ctype.h>

//||||||||||||||||||||||||||||||||||||||| Validate Name Function |||||||||||||||||||||||||||||||||||||||//
// Validate that name contains only letters and spaces
int validate_name(char new_name[])
{
    for (int i = 0; new_name[i] != '\0'; i++)
    {
        if (!((new_name[i] >= 'A' && new_name[i] <= 'Z') || (new_name[i] >= 'a' && new_name[i] <= 'z') || new_name[i] == ' '))
        {
            return 0; // Invalid character found
        }
    }
    return 1; // Valid name
}

//||||||||||||||||||||||||||||||||||||||| Validate Phone Function |||||||||||||||||||||||||||||||||||||||//
// Validate phone: must be 10 digits and not duplicate
int validate_phone(char new_phone[], AddressBook *addressBook)
{
    if (strlen(new_phone) != 10)
    {
        return 0; // Must be exactly 10 digits
    }
    for (int i = 0; new_phone[i] != '\0'; i++)
    {
        if (!isdigit((unsigned char)new_phone[i]))
            return 0; // Non-digit found
    }

    // Check duplicates
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcmp(new_phone, addressBook->contacts[i].phone) == 0)
        {
            printf("Phone number already exists.\n");
            return 0; // Duplicate found
        }
    }
    return 1; // Valid phone
}

//||||||||||||||||||||||||||||||||||||||| Validate Emai; Function |||||||||||||||||||||||||||||||||||||||//
// Validate email: must have '@' and '.' after '@', and not duplicate
int validate_email(char new_email[], AddressBook *addressBook)
{
    // Check duplicates first
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasecmp(new_email, addressBook->contacts[i].email) == 0)
        {
            printf("Email already exists! Please enter a different email id.\n");
            return 2; // Duplicate
        }
    }

    int at_count = 0;
    char *at_pos = NULL;

    for (int i = 0; new_email[i] != '\0'; i++)
    {
        char ch = new_email[i];

        // Only allow letters, digits, ., _, -, @
        if (!(isalnum(ch) || ch == '.' || ch == '_' || ch == '-' || ch == '@'))
        {
            return 0; // Invalid character found
        }

        if (ch == '@')
        {
            at_count++;
            at_pos = &new_email[i]; // remember position of @
        }
    }

    if (at_count != 1)
        return 0; // Must have exactly one '@'

    // There must be a dot after '@'
    char *dot_pos = strchr(at_pos, '.');
    
    if (dot_pos == NULL || *(dot_pos + 1) == '\0')
        return 0;

    return 1; // Valid email
}
