// This file has functions to save and load contacts from a file
#ifndef FILE_H
#define FILE_H

#include "contact.h"  // Include the contact structure

// This function saves all contacts to a CSV file
void saveContactsToFile(AddressBook *addressBook);
// This function loads contacts from the CSV file
void loadContactsFromFile(AddressBook *addressBook);

#endif
