#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void formatName(char *name)
{
    int flag = 0;

    for (int i = 0; name[i] != '\0'; i++)
    {
        if (name[i] == ' ' )
        {
            flag = 1;
        }
        else if (flag)
        {
            if (name[i] >= 'a' && name[i] <= 'z')
            {
                name[i] = name[i] - 'a' + 'A';
            }
            flag = 0;
        }
        if ((name[0] >= 'A' && name[0] <= 'Z') == 0) 
        {
            name[0] = name[0] + ' ';
        }
        else
        {
            if (name[i] >= 'A' && name[i] <= 'Z')
            {
                name[i] = name[i] - 'A' + 'a';
            }
        }
    }
}

int Name(char *name)
{
    for (int i = 0; name[i] != '\0'; i++)
    {
        if ((name[i] >= 'A' && name[i] <= 'Z' || name[i] >= 'a' && name[i] <= 'z' || name[i] == ' ') == 0)
        {
            return 0;
        }
    }
    return 1;
}

int Phone(AddressBook *addressBook, char *phone)
{
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcmp(addressBook->contacts[i].phone, phone) == 0)
        {
            return 0;
        }
    }

    int len = strlen(phone);
    if (len != 10)
    {
        return 0;
    }

    if(phone[0] == '0')
    {
        return 0;
    }

    for (int i = 0; i < len; i++)
    {
        if ((phone[i] >= '0' && phone[i] <= '9') == 0)
        {
            return 0;
        }
    }
    return 1;
}

int Email(AddressBook *addressBook, char *email)
{
    for(int i = 0; i != '\0'; i++)
    {
        if((email[i] >= 'a' && email[i] <= 'z') == 0)
        {
            return 0;
        }   
    }
    if((email[0] >= 'a' && email[0] <= 'z') == 0)
    {
        return 0;
    }
    if (strchr(email, '@') == NULL)
    {
        return 0;
    }
    if (strstr(email, ".com") == NULL)
    {
        return 0;
    }
    if(strcmp(email + strlen(email) - 4, ".com"))
    {
        return 0;
    }
    if ((strstr(email, ".com")) - (strchr(email, '@')) <= 1)
    {
        return 0;
    }
    for(int i = 0; i < addressBook->contactCount; i++)
    {
        if(strcasecmp(addressBook->contacts[i].email, email) == 0)
        {
            return 0;
        }
    }
    return 1;
}

void swapContacts(Contact *a, Contact *b)
{
    Contact temp = *a;
    *a = *b;
    *b = temp;
}

void listContacts(AddressBook *addressBook, int sortCriteria) 
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts found.\n");
        return;
    }

    // Bubble sort
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        for (int j = i + 1; j < addressBook->contactCount; j++)
        {
            int cmp = 0;
            if (sortCriteria == 1)
                cmp = strcasecmp(addressBook->contacts[i].name, addressBook->contacts[j].name);
            else if (sortCriteria == 2)
                cmp = strcmp(addressBook->contacts[i].phone, addressBook->contacts[j].phone);
            else if (sortCriteria == 3)
                cmp = strcasecmp(addressBook->contacts[i].email, addressBook->contacts[j].email);

            if (cmp > 0)
            {
                swapContacts(&addressBook->contacts[i], &addressBook->contacts[j]);
            }
        }
    }

    printf("\n%-100s\n"," ______________________________ Address Book List ________________________________ ");
    printf("| %10s | %20s | %20s | %20s |\n", "Serial   ", "Name         ", "Phone         ", "Email         ");
    printf("| %10s | %20s | %20s | %20s |\n", "No     ", "", "No           ", "Id           ");
    printf("*------------*----------------------*----------------------*----------------------*\n");
    for (int i = 0; i < addressBook->contactCount; i++)
    {
        printf("|     %-6d | %-20s | %-20s | %-20s |\n", i + 1, 
            addressBook->contacts[i].name, 
            addressBook->contacts[i].phone, 
            addressBook->contacts[i].email);
        printf("*------------*----------------------*----------------------*----------------------*\n");
    }
}

void initialize(AddressBook *addressBook)
{
    addressBook->contactCount = 0;
    // populateAddressBook(addressBook);   // used to store DummyContacts
    
    // Load contacts from file during initialization (After files)
    
    loadContactsFromFile(addressBook);
}

void saveAndExit(AddressBook *addressBook)
{
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */
    if (addressBook->contactCount >= MAX_CONTACTS)
    {
        printf("Address book is full!\n");
        return;
    }

    int n;
    printf("Enter how many contact should store : ");
    scanf("%d",&n);
    for(int i = 0; i < n; i++)
    {
        Contact *newContact = &addressBook->contacts[addressBook->contactCount];

        // Name
        do 
        {
            printf("\nEnter name %d: ", i + 1);
            scanf(" %[^\n]", newContact->name);
            if (Name(newContact->name) == 0)
            {
                printf("Invalid name!. Use only alphabets and spaces and starting with uppercase only.\n");
            }
            else
            {
                formatName(newContact->name);
            }
        } while (Name(newContact->name) == 0);

        // Phone
        do 
        {
            printf("Enter phone %d: ", i + 1);
            scanf(" %s", newContact->phone);
            if (Phone(addressBook, newContact->phone) == 0)
            {
                printf("Invalid phone number!. Must be 10 digits and not start with 0 and it should not match others phone.\n");
            }
        } while (Phone(addressBook, newContact->phone) == 0);

        // Email
        do 
        {
            printf("Enter email %d: ", i + 1);
            scanf(" %s", newContact->email);
            if (Email(addressBook, newContact->email) == 0)
            {
                printf("Invalid email!. Must start with lowercase, contain '@', and end with '.com' and it should not match others email.\n");
            }
        } while (Email(addressBook, newContact->email) == 0);

        addressBook->contactCount++;
    }
    printf("\nContact added successfully!\n");
}

int searchContact(AddressBook *addressBook) 
{
    if (addressBook->contactCount == 0)
    {
        printf("No contacts to search.\n\n");
        return -1;
    }

    char searchInput[50];
    printf("Enter name/phone/email to search: ");
    scanf(" %[^\n]", searchInput);

    int match[50];
    int matchCount = 0;

    for (int i = 0; i < addressBook->contactCount; i++)
    {
        if (strcasestr(addressBook->contacts[i].name, searchInput) || strstr(addressBook->contacts[i].phone, searchInput) || strcasestr(addressBook->contacts[i].email, searchInput))
        {
            match[matchCount++] = i;
        }
    }

    if (matchCount == 0)
    {
        printf("No contact found with '%s'.\n\n", searchInput);
        return -1;
    }

    if (matchCount == 1)
    {
        int num = 1;
        int index = match[0];
        printf("\nContact Found:\n");
        printf("\n%-100s\n"," ______________________________ Address Book List ________________________________ ");
        printf("| %10s | %20s | %20s | %20s |\n", "Serial   ", "Name         ", "Phone         ", "Email         ");
        printf("| %10s | %20s | %20s | %20s |\n", "No     ", "", "No           ", "Id           ");
        printf("*------------*----------------------*----------------------*----------------------*\n");
        printf("|     %-6d | %-20s | %-20s | %-20s |\n", num, 
            addressBook->contacts[index].name, 
            addressBook->contacts[index].phone, 
            addressBook->contacts[index].email);
        printf("*------------*----------------------*----------------------*----------------------*\n");
        return index;
    }

    printf("\nMultiple contacts found:\n");
    printf("\n%-100s\n"," ______________________________ Address Book List ________________________________ ");
    printf("| %10s | %20s | %20s | %20s |\n", "Serial   ", "Name         ", "Phone         ", "Email         ");
    printf("| %10s | %20s | %20s | %20s |\n", "No     ", "", "No           ", "Id           ");
    printf("*------------*----------------------*----------------------*----------------------*\n");
    int num = 1;
    for (int i = 0; i < matchCount; i++)
    {
        int index = match[i];
        printf("|     %-6d | %-20s | %-20s | %-20s |\n", num++, 
            addressBook->contacts[index].name, 
            addressBook->contacts[index].phone, 
            addressBook->contacts[index].email);
        printf("*------------*----------------------*----------------------*----------------------*\n");
    }

    int search;
    printf("\nEnter serial number to search: ");
    scanf(" %d", &search);
    num = 1;
    for (int i = 0; i < matchCount; i++)
    {
        int index = match[i];
        if(num == search)
        {
            printf("\nContact Found:\n");
            printf("\n%-100s\n"," ______________________________ Address Book List ________________________________ ");
            printf("| %10s | %20s | %20s | %20s |\n", "Serial   ", "Name         ", "Phone         ", "Email         ");
            printf("| %10s | %20s | %20s | %20s |\n", "No     ", "", "No           ", "Id           ");
            printf("*------------*----------------------*----------------------*----------------------*\n");
            printf("|     %-6d | %-20s | %-20s | %-20s |\n", num, 
                addressBook->contacts[index].name, 
                addressBook->contacts[index].phone, 
                addressBook->contacts[index].email);
            printf("*------------*----------------------*----------------------*----------------------*\n");
            return index;
        }
        num++;
    }

    printf("No contact matched with the search detail '%d'.\n", search);
    return -1;
}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
    int index = searchContact(addressBook);

    if (index == -1) {
        printf("Contact not found.\n\n");
        return;
    }
    int editCriteria;
    do
    {
        printf("Select edit choice:\n");
        printf("1. Edit by name\n");
        printf("2. Edit by phone\n");
        printf("3. Edit by email\n");
        printf("4. Exit\n");
        printf("Enter your edit choice: ");
        scanf("%d", &editCriteria);
        printf("\n");
        char newContact[100];

        //Name
        if (editCriteria == 1)
        {
            do {
                printf("Enter new name for contact: ");
                scanf(" %[^\n]", newContact);
                if (Name(newContact) == 0)
                    printf("Invalid name. Please enter alphabets and also starting with uppercase only .\n");
                else
                {
                    formatName(newContact);
                }
            } while (Name(newContact) == 0);

            strcpy(addressBook->contacts[index].name, newContact);
            printf("Contact name edited successfully!\n\n");
        }
        //Phone
        else if (editCriteria == 2)
        {
            do {
                printf("Enter new phone number for contact: ");
                scanf(" %s", newContact);
                if (Phone(addressBook, newContact) == 0)
                    printf("Invalid phone number. Must be 10 digits and not starts with 0 and it should not be match with others phone.\n");
            } while (Phone(addressBook, newContact) == 0);

            strcpy(addressBook->contacts[index].phone, newContact);
            printf("Contact phone edited successfully!\n\n");
        }
        //Email
        else if (editCriteria == 3) // Edit Email
        {
            do {
                printf("Enter new email for contact: ");
                scanf(" %s", newContact);
                if (Email(addressBook, newContact) == 0)
                    printf("Invalid email. Must start with lowercase letter and contain '@' and '.com' and it should not match with others email.\n");
            } while (Email(addressBook, newContact) == 0);

            strcpy(addressBook->contacts[index].email, newContact);
            printf("Contact email edited successfully!\n\n");
        }
        //Exit
        else if(editCriteria == 4)
        {
            printf("Contact exited successfully!\n");
            return;
        }
        //For other incorrect option
        else
        {
            printf("Invalid edit criteria.\n");
        }
    }while(editCriteria != 4);
}

void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */
    int ret = searchContact(addressBook);
    if (ret == -1)
    return;

    printf("Do yo want to delete contact?\n");
    printf("1. Yes\n");
    printf("2. No\n");
    printf("Enter the choice: ");
    int choice;
    scanf("%d", &choice);
    printf("\n");
    switch(choice)
    {
        case 1:
            for (int i = ret; i < addressBook->contactCount; i++)
            {
                strcpy(addressBook->contacts[i].name, addressBook->contacts[i + 1].name);
                strcpy(addressBook->contacts[i].phone, addressBook->contacts[i + 1].phone);
                strcpy(addressBook->contacts[i].email, addressBook->contacts[i + 1].email);
            }
            addressBook->contactCount--;
            printf("Contact deleted successfully!\n");
            break;
        case 2:
            printf("Contact not deleted successfully!\n");
            break;
        default:
            printf("Invalid choice\n");
            break;
    }
}
