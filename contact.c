#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include <ctype.h>

// Function prototypes for searching contacts
int searchbyname(AddressBook *addressBook);
int searchbyphone(AddressBook *addressBook);
int searchbyemail(AddressBook *addressBook);

// Function prototypes for entering contact details
void enter_name(char new_name[], AddressBook *addressBook);
void enter_phone(char new_phone[], AddressBook *addressBook);
void enter_email(char new_email[], AddressBook *addressBook);


//||||||||||||||||||||||||||||||||||||||| Initialize function |||||||||||||||||||||||||||||||||||||||//

void initialize(AddressBook *addressBook) // Function to initialize address book
{
	loadContactsFromFile(addressBook); // Load existing contacts from file
}


//||||||||||||||||||||||||||||||||||||||| Create Contact Function (➕) |||||||||||||||||||||||||||||||||||||||//

void createContact(AddressBook *addressBook) // Function to create new contact
{
	if (addressBook->contactCount >= MAX_CONTACTS) // Check if address book is full
	{
		printf("Address book is full!\n"); // Show error message
		return;							   // Exit the function
	}

	int choice; // Variable to hold user choice
	printf("\n1. Enter the details\n2. Go to main menu\n\nEnter your choice: ");
	scanf("%d", &choice); // Read the choice from user

	if (choice == 1)
	{
		char new_name[50], new_phone[20], new_email[50]; // Temporary variables for new contact details

		enter_name(new_name, addressBook);	 // Call function to get name
		enter_phone(new_phone, addressBook); // Call function to get phone
		enter_email(new_email, addressBook); // Call function to get email

		strcpy(addressBook->contacts[addressBook->contactCount].name, new_name);   // Copy name to contact
		strcpy(addressBook->contacts[addressBook->contactCount].phone, new_phone); // Copy phone to contact
		strcpy(addressBook->contacts[addressBook->contactCount].email, new_email); // Copy email to contact

		addressBook->contactCount++; // Increase the number of contacts
	}
}
//||||||||||||||||||||||||||||||||||||||| enter name function |||||||||||||||||||||||||||||||||||||||//

void enter_name(char new_name[], AddressBook *addressBook __attribute__((unused))) // Function to enter name
{
	int valid = 0; // Flag for validation

	while (!valid)
	{
		printf("\nEnter Name (only alphabets): "); // Prompt
		getchar();								   // Clear buffer
		scanf("%[^\n]", new_name);				   // Read name

		valid = validate_name(new_name); // Validate name

		if (!valid)
		{
			printf("Name should contain only alphabets, please try again\n"); // Error message
		}
	}
}

//||||||||||||||||||||||||||||||||||||||| Enter phone fucntion |||||||||||||||||||||||||||||||||||||||//

void enter_phone(char new_phone[], AddressBook *addressBook) // Function to enter phone
{
	printf("\nEnter Phone Number (must contain 10 digits): "); // Print prompt
	scanf("%s", new_phone);									   // Read phone
	// calling the validate_phone fucntion
	int ret = validate_phone(new_phone, addressBook); // Validate phone
	if (ret)										  // If valid
	{
		return; // Return
	}
	else // Else invalid
	{
		printf("Invalid phone number. Please try again\n");
		enter_phone(new_phone, addressBook); // Call again
	}
}

//||||||||||||||||||||||||||||||||||||||| Enter email function |||||||||||||||||||||||||||||||||||||||//

void enter_email(char new_email[], AddressBook *addressBook) // Function to enter email
{
	printf("\nEnter Email id: "); // Print prompt
	scanf("%s", new_email);		  // Read email
	// calling the validate_email function
	int ret = validate_email(new_email, addressBook); // Validate email

	if (ret == 1)
	{
		printf("Validation SuccessFull!\n"); // Print success

		printf("\nPlease save the contact by entering 6.\n");
		return; // Return
	}
	else if (ret == 2) // If duplicate
	{
		// This case is for duplicate emails
		enter_email(new_email, addressBook); // Call again
	}
	else // Else invalid
	{
		printf("Invalid email id. Sample email id: abc@gmail.com\nPlease try again\n"); // Print error
		enter_email(new_email, addressBook);											// Call again
	}
}

//||||||||||||||||||||||||||||||||||||||| Search Contact Function (🔎) |||||||||||||||||||||||||||||||||||||||//

int searchContact(AddressBook *addressBook) // Function to search contact
{
	int searchChoice; // Declare choice
	int validChoice = 0;

	while (!validChoice)
	{
		printf("\nSearch Menu:\n");
		printf("1. Search by Name\n");
		printf("2. Search by Phone Number\n");
		printf("3. Search by Email ID\n");
		printf("4. Go to main menu\n");
		printf("\nEnter the choice: ");
		scanf("%d", &searchChoice);

		if (searchChoice >= 1 && searchChoice <= 4)
		{
			validChoice = 1;	  // Exit the loop
			switch (searchChoice) // Switch
			{
			case 1:
				return searchbyname(addressBook); // Call search by name
			case 2:
				return searchbyphone(addressBook); // Call search by phone
			case 3:
				return searchbyemail(addressBook); // Call search by email
			case 4:
				return 0; // No search performed
			}
		}
		else
		{
			printf("Invalid choice. Please try again.\n");
		}
	}
	return 0; // Return 0
}

//||||||||||||||||||||||||||||||||||||||| Search by name function |||||||||||||||||||||||||||||||||||||||//

int searchbyname(AddressBook *addressBook) // Function to search by name
{
	char name[50];							// Declare name
	printf("\nEnter the Name to search: "); // Print prompt
	getchar();								// Clear input buffer
	scanf("%[^\n]", name);					// Read name

	int found = 0; // Flag for match
	int foundCount = 0; // Count of found contacts

	for (int i = 0; i < addressBook->contactCount; i++) // Loop through contacts
	{
		if (strcasecmp(name, addressBook->contacts[i].name) == 0) // If match
		{
			if (foundCount == 0) // Print header only for first match
			{
				// Print header with title and emojis
				printf("\n╔════════════════════════════════════════════════════════════════════════════════════════╗\n");
				printf("║                                 🔎   SEARCHED CONTACT   🔎                             ║\n");
				printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n");

				// Print table header with double line borders and emojis
				printf("╔═════════╦═══════════════════════════╦═══════════════════╦══════════════════════════════╗\n");
				printf("║ 🔢 S.No ║ 👤 Name                   ║ ☎️  Phone          ║ 📧  Email                    ║\n");
				printf("╠═════════╬═══════════════════════════╬═══════════════════╬══════════════════════════════╣\n");
			}

			printf("║ %-7d ║ %-25s ║ %-17s ║ %-28s ║\n",
				   i,
				   addressBook->contacts[i].name,
				   addressBook->contacts[i].phone,
				   addressBook->contacts[i].email);
			// Add empty row between data rows if more found
			if (++foundCount > 1)
			{
				printf("║         ║                           ║                   ║                              ║\n");
			}

			found = 1; // Set found flag
		}
	}

	if (found)
	{
		// Print table bottom border
		printf("╚═════════╩═══════════════════════════╩═══════════════════╩══════════════════════════════╝\n");
		printf("\nContact Found!\n");
		return 1; // Return 1 if found
	}
	else
	{
		printf("Contact Not found!\n");
		return 0; // Return 0 if not found
	}
}

//||||||||||||||||||||||||||||||||||||||| Search by phone number function |||||||||||||||||||||||||||||||||||||||//

int searchbyphone(AddressBook *addressBook) // Function to search by phone
{
	char phone[20]; // Declare phone
	printf("\nEnter the Phone number to search: ");
	scanf("%s", phone); // Read phone

	int found = 0; // Flag for match
	int foundCount = 0; // Count of found contacts

	for (int i = 0; i < addressBook->contactCount; i++) // Loop through contacts
	{
		if (strcmp(phone, addressBook->contacts[i].phone) == 0) // If match
		{
			if (foundCount == 0) // Print header only for first match
			{
				// Print header with title and emojis
				printf("\n╔════════════════════════════════════════════════════════════════════════════════════════╗\n");
				printf("║                                 🔎   SEARCHED CONTACT   🔎                             ║\n");
				printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n");

				// Print table header with double line borders and emojis
				printf("╔═════════╦═══════════════════════════╦═══════════════════╦══════════════════════════════╗\n");
				printf("║ 🔢 S.No ║ 👤 Name                   ║ ☎️  Phone          ║ 📧  Email                    ║\n");
				printf("╠═════════╬═══════════════════════════╬═══════════════════╬══════════════════════════════╣\n");
			}

			printf("║ %-7d ║ %-25s ║ %-17s ║ %-28s ║\n",
				   i,
				   addressBook->contacts[i].name,
				   addressBook->contacts[i].phone,
				   addressBook->contacts[i].email);
			// Add empty row between data rows if more found
			if (++foundCount > 1)
			{
				printf("║         ║                           ║                   ║                              ║\n");
			}

			found = 1; // Set found flag
		}
	}

	if (found)
	{
		// Print table bottom border
		printf("╚═════════╩═══════════════════════════╩═══════════════════╩══════════════════════════════╝\n");
		printf("\nContact Found!\n");
		return 1; // Return 1 if found
	}
	else
	{
		printf("Contact Not found!\n");
		return 0; // Return 0 if not found
	}
}

//||||||||||||||||||||||||||||||||||||||| Search by Email ID function |||||||||||||||||||||||||||||||||||||||//

int searchbyemail(AddressBook *addressBook) // Function to search by email
{
	char email[50]; // Declare email
	printf("\nEnter the Email Id to search: ");
	scanf(" %s", email); // Read email

	int found = 0; // Flag for match
	int foundCount = 0; // Count of found contacts

	for (int i = 0; i < addressBook->contactCount; i++) // Loop through contacts
	{
		if (strcasecmp(email, addressBook->contacts[i].email) == 0) // If match (case-insensitive)
		{
			if (foundCount == 0) // Print header only for first match
			{
				// Print header with title and emojis
				printf("\n╔════════════════════════════════════════════════════════════════════════════════════════╗\n");
				printf("║                                 🔎   SEARCHED CONTACT   🔎                             ║\n");
				printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n");

				// Print table header with double line borders and emojis
				printf("╔═════════╦═══════════════════════════╦═══════════════════╦══════════════════════════════╗\n");
				printf("║ 🔢 S.No ║ 👤 Name                   ║ ☎️  Phone          ║ 📧  Email                    ║\n");
				printf("╠═════════╬═══════════════════════════╬═══════════════════╬══════════════════════════════╣\n");
			}

			printf("║ %-7d ║ %-25s ║ %-17s ║ %-28s ║\n",
				   i,
				   addressBook->contacts[i].name,
				   addressBook->contacts[i].phone,
				   addressBook->contacts[i].email);
			// Add empty row between data rows if more found
			if (++foundCount > 1)
			{
				printf("║         ║                           ║                   ║                              ║\n");
			}

			found = 1; // Set found flag
		}
	}

	if (found)
	{
		// Print table bottom border
		printf("╚═════════╩═══════════════════════════╩═══════════════════╩══════════════════════════════╝\n");
		printf("\nContact Found!\n");
		return 1; // Return 1 if found
	}
	else
	{
		printf("Contact Not found!\n");
		return 0; // Return 0 if not found
	}
}


//||||||||||||||||||||||||||||||||||||||| Edit Contact function (✏️) |||||||||||||||||||||||||||||||||||||||//

void editContact(AddressBook *addressBook) // Function to edit contact
{
	int index;														// Declare index
	printf("Please select an option to search for the contact.\n"); // Print prompt
	int ret = searchContact(addressBook);							// Call search
	if (ret)														// If found
	{
		printf("Enter the Index number of the contact you want to edit: "); // Ask index
		scanf("%d", &index);												// Read index

		if (index < 0 || index >= addressBook->contactCount) // Check valid index
		{
			printf("Invalid Index number. Please try again.\n"); // Print error
			return;												 // Return
		}

	editmenu:
		printf("What you want to Edit?\n1. Name\n2. Phone Number\n3. Email Id\n4. Search again\n5. Exit\n"); // Print edit menu
		printf("\nEnter your choice: ");																		 // Prompt for choice
		int editoption;																						 // Declare option
		scanf("%d", &editoption);																			 // Read option

		if (editoption >= 1 && editoption <= 5) // If valid
		{
			switch (editoption) // Switch
			{
			case 1:
			{
				char new_name[50];
				int valid = 0;

				while (!valid)
				{
					printf("Enter new name: ");
					getchar(); // Clear buffer
					scanf("%[^\n]", new_name);

					valid = validate_name(new_name);
					if (!valid)
						printf("Name should contain only alphabets, please try again\n");
				}

				strcpy(addressBook->contacts[index].name, new_name);
				printf("Contact Updated Successfully!\n");
				break;
			}
			case 2:
			{
				char new_phone[20]; // Declare phone
				int ret;			// Declare ret

				do
				{
					printf("Enter new phone number: ");			  // Print prompt
					scanf("%s", new_phone);						  // Read phone
					ret = validate_phone(new_phone, addressBook); // Validate
					if (!ret)									  // If invalid
					{
						printf("Invalid phone number. Please try again\n"); // Print error
					}
				} while (!ret); // While invalid

				strcpy(addressBook->contacts[index].phone, new_phone); // Copy phone
				printf("Contact Updated Successfully!\n");			   // Print success
				break;												   // Break
			}

			case 3:
			{
				char new_email[50]; // Declare email
				int ret;			// Declare ret

				do
				{
					printf("Enter new email id: ");				  // Print prompt
					scanf("%s", new_email);						  // Read email
					ret = validate_email(new_email, addressBook); // Validate

					if (ret == 0) // If invalid
					{
						printf("Invalid email id. Sample email id: abc@gmail.com\nPlease try again\n"); // Print error
					}
					else if (ret == 2) // If duplicate
					{
						printf("Email already exists! Please enter a different email id.\n"); // Print duplicate
						ret = 0;															  // Treat as invalid to loop
					}
				} while (!ret); // While invalid

				strcpy(addressBook->contacts[index].email, new_email); // Copy email
				printf("Contact Updated Successfully!\n");			   // Print success
				break;												   // Break
			}

			case 4:
				editContact(addressBook); // Call edit again
				return;					  // Return after recursion

			case 5:
				return; // Return
			}
			// Print header for edited contact
			printf("\n╔════════════════════════════════════════════════════════════════════════════════════════╗\n");
			printf("║                                ✏️   EDITED CONTACT   ✏️                                  ║\n");
			printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n");

			// Print table header
			printf("╔═════════╦═══════════════════════════╦═══════════════════╦══════════════════════════════╗\n");
			printf("║ 🔢 S.No ║ 👤 Name                   ║ ☎️  Phone          ║ 📧  Email                    ║\n");
			printf("╠═════════╬═══════════════════════════╬═══════════════════╬══════════════════════════════╣\n");

			// Print the edited contact row
			printf("║ %-7d ║ %-25s ║ %-17s ║ %-28s ║\n",
				   index,
				   addressBook->contacts[index].name,
				   addressBook->contacts[index].phone,
				   addressBook->contacts[index].email);

			// Print table bottom border
			printf("╚═════════╩═══════════════════════════╩═══════════════════╩══════════════════════════════╝\n");

			printf("\nPlease save the changes by entering 6.\n"); // Print save
		}
		else // Else invalid
		{
			printf("Invalid input! Please try again.\n"); // Print error
			goto editmenu;								  // Go to menu
		}
	}
	else // Else not found
	{
		return; // Return
	}
}

//||||||||||||||||||||||||||||||||||||||| Delete Contact Function (🗑️) |||||||||||||||||||||||||||||||||||||||//


void deleteContact(AddressBook *addressBook) // Function to delete contact
{
	int index;															   // Declare index
	printf("Please select an option to search and delete the contact.\n"); // Prompt
	int ret = searchContact(addressBook);								   // Call search

	if (ret) // If found
	{
		printf("\nEnter the Index number of contact which you want to delete: "); // Ask index
		scanf("%d", &index);													  // Read index

		if (index < 0 || index >= addressBook->contactCount) // Check validity
		{
			printf("Invalid Index number. Please try again.\n");
			return;
		}

		for (int i = index; i < addressBook->contactCount - 1; i++) // Shift contacts
		{
			addressBook->contacts[i] = addressBook->contacts[i + 1];
		}

		addressBook->contactCount--; // Decrease count
		printf("Contact deleted successfully!\n");
		printf("\nPlease save the changes by entering 6.\n");
	}
}

//||||||||||||||||||||||||||||||||||||||| List Contacts (📋) |||||||||||||||||||||||||||||||||||||||//

// This function shows a menu to list contacts in different ways
void listContacts(AddressBook *addressBook) // Function to list contacts
{
	int sortChoice;
	printf("\nList Menu:\n"); // Print list menu header
	printf("1. List by Name\n");
	printf("2. List by Phone Number\n");
	printf("3. List by Email ID\n");
	printf("4. List all Contacts\n");
	printf("5. To go to Main menu\n");
	printf("\nEnter your choice: ");

	scanf("%d", &sortChoice);				// Read the choice from user
	if (sortChoice >= 1 && sortChoice <= 5) // Check if choice is valid
	{
		switch (sortChoice) // Start switch based on choice
		{
		case 1:
			// Sort contacts by name using bubble sort
			for (int i = 0; i < addressBook->contactCount; i++) // Outer loop for sorting
			{
				for (int j = 0; j < addressBook->contactCount - i - 1; j++) // Inner loop for sorting
				{
					if (strcmp(addressBook->contacts[j].name, addressBook->contacts[j + 1].name) > 0) // Check if names are out of order
					{
						Contact temp = addressBook->contacts[j];				 // Swap contacts
						addressBook->contacts[j] = addressBook->contacts[j + 1]; // Swap first contact
						addressBook->contacts[j + 1] = temp;					 // Swap second contact
					}
				}
			}
			goto printlist; // Jump to print the list
			break;			// End case 1

		case 2:
			// Sort contacts by phone number
			for (int i = 0; i < addressBook->contactCount; i++) // Outer loop
			{
				for (int j = 0; j < addressBook->contactCount - i - 1; j++) // Inner loop
				{
					if (strcmp(addressBook->contacts[j].phone, addressBook->contacts[j + 1].phone) > 0) // Compare phones
					{
						Contact temp = addressBook->contacts[j];				 // Temp for swap
						addressBook->contacts[j] = addressBook->contacts[j + 1]; // Swap
						addressBook->contacts[j + 1] = temp;					 // Complete swap
					}
				}
			}
			goto printlist; // Go to print
			break;

		case 3:
			// Sort contacts by email
			for (int i = 0; i < addressBook->contactCount; i++) // Outer loop
			{
				for (int j = 0; j < addressBook->contactCount - i - 1; j++) // Inner loop
				{
					if (strcmp(addressBook->contacts[j].email, addressBook->contacts[j + 1].email) > 0) // Compare emails
					{
						Contact temp = addressBook->contacts[j];				 // Temp
						addressBook->contacts[j] = addressBook->contacts[j + 1]; // Swap
						addressBook->contacts[j + 1] = temp;					 // Complete
					}
				}
			}

			goto printlist; // Go to print
			break;

		case 4:
		printlist:
			// Print header with title and emojis
			printf("\n╔════════════════════════════════════════════════════════════════════════════════════════╗\n");
			printf("║                          📞   A D D R E S S   B O O K   C O N T A C T S   📞           ║\n");
			printf("╚════════════════════════════════════════════════════════════════════════════════════════╝\n");

			// Print table header with double line borders and emojis
			printf("╔═════════╦═══════════════════════════╦═══════════════════╦══════════════════════════════╗\n");
			printf("║ 🔢 S.No ║ 👤 Name                   ║ ☎️  Phone          ║ 📧  Email                    ║\n");
			printf("╠═════════╬═══════════════════════════╬═══════════════════╬══════════════════════════════╣\n");

			// Loop through contacts and print each row
			for (int i = 0; i < addressBook->contactCount; i++)
			{
				printf("║ %-7d ║ %-25s ║ %-17s ║ %-28s ║\n",
					   i + 1,
					   addressBook->contacts[i].name,
					   addressBook->contacts[i].phone,
					   addressBook->contacts[i].email);
				// Add empty row between data rows
				if (i < addressBook->contactCount - 1)
				{
					printf("║         ║                           ║                   ║                              ║\n");
				}
			}

			// Print table bottom border
			printf("╚═════════╩═══════════════════════════╩═══════════════════╩══════════════════════════════╝\n");

			break;

		case 5:
			return; // Go back to main menu
		}
	}
	else // Else for invalid choice
	{
		printf("Invalid choice. Please try again.\n"); // If choice is wrong, ask again
		listContacts(addressBook);					   // Recursive call
	}
}


//|||||||||||||||||||||||||||||||||||||||  Save and Exit function (🚪) |||||||||||||||||||||||||||||||||||||||//

void saveAndExit(AddressBook *addressBook) // Function to save and exit
{
	saveContactsToFile(addressBook); // Save all contacts to file
}
