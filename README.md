# project1
ADDRESSBOOK

Defination :-
    An Address Book is a digital or physical system used to store, organize, and manage contact information of peoples.

2) Initialization:-

    It creates an AddressBook structure and calls:

    initialize(&addressBook);
    Inside initialize():
        -> Sets contactCount = 0
        -> Calls populateAddressBook() -> loads 10 dummy contacts from populate.c into the address book.
        -> Calls loadContactsFromFile() → loads saved contacts from contact.txt into memory.
    User has stored the 10 dummy contacts.

3)Files:-
    a) saveContactsToFile(AddressBook *addressBook)
            Purpose: Save all contacts from memory into contact.txt (overwrite file).

            How it works:
                -> Opens the file contact.txt in write mode ("w").
                -> If the file can’t be opened → shows "Error opening file for writing." and stops.
                -> Loops through every contact in addressBook->contacts (up to contactCount).
                -> Writes each contact’s details to the file in CSV format:
                        
                        name , phone , email

                -> Closes the file.
                -> Prints "Contacts saved successfully."

    b) loadContactsFromFile(AddressBook *addressBook)
            Purpose: Load contacts from contact.txt into memory.

            How it works:
                -> Opens the file contact.txt in read mode ("r").
                -> If file doesn’t exist → shows "No saved contacts found." and stops.
                -> Sets contactCount to 0 (clears memory count).
                -> Reads each line of the file using fscanf with the pattern:

                        %[^,], %[^,], %[^\n]
                        
                        // %[^,] → read characters until , (for name)
                        // %[^,] → read until , (for phone)
                        // %[^\n] → read until newline (for email)
                        
                -> After reading a contact:
                        > Stores it in contacts[contactCount]
                        > Increases contactCount
                        > Stops if it reaches MAX_CONTACTS.
                -> Closes the file.
                -> Prints "Contacts loaded successfully."

4) Menu Display:-

    The program shows:

    Address Book Menu:
    1. Create contact
    2. Search contact
    3. Edit contact
    4. Delete contact
    5. List all contacts
    6. Save & Exit

    If user enter a number from 1 to 6, and based on choice, it calls the respective function.
    if user enter any other number then it gives the "Invalid choice. Please try again.".
    
    Step 1. Creating a Contact:-

            If user press 1 in menu:
            Now asks how many n contacts you want to add.
            For each n contacts it will ask as shown in below :
                Enter Name:   // Must only contain alphabets/spaces.
                Enter Phone:  // Must be 10 digits, not starting with 0, and unique.
                Enter Email:  // Must start with lowercase letter, contain '@', end with '.com', and be unique.

            validation:-
                1. formatName(char *name)
                    Makes the name look neat: 
                        -> First letter and any letter after a space → uppercase.
                        -> All other letters → lowercase.
                        -> Uses a flag to remember when a space is found.

                2. Name(char *name)
                    Checks if the name only has:
                        -> Letters (A–Z, a–z)
                        -> Spaces
                        -> If it finds numbers or special symbols → invalid.

                3. Phone(AddressBook *addressBook, char *phone)
                    Checks if the phone number is valid:
                        -> Not already in the contact list.
                        -> Exactly 10 digits long.
                        -> Doesn’t start with 0.
                        -> Only contains numbers.
                        -> If all checks pass → valid.

                4. Email(AddressBook *addressBook, char *email)
                    Checks if the email is valid:
                        -> Starts with a lowercase letter.
                        -> Has @ somewhere.
                        -> Has .com at the end.
                        -> At least one character between @ and .com.
                        -> Not already in the contact list (case-insensitive).

    step 2. Listing Contacts:-

            If user press 5 in menu:
            it asks as shown in below :
                1. Sort by name
                2. Sort by phone
                3. Sort by email

            Uses bubble sort to list the contacts in order.

            Displays list in a table form as shown below:
           
             ______________________________ Address Book List ________________________________
            |  Serial    |        Name          |       Phone          |       Email          |
            |    No      |                      |        No            |        Id            |
            *------------*----------------------*----------------------*----------------------*
            | 1          | John Doe             | 1234567890           | john@example.com     |
            *------------*----------------------*----------------------*----------------------*

    step 3. Searching a Contact:-

            If user press 2 in menu:
            it asks as shown below:
                Enter name/phone/email to search:
                    //Searches through all contacts.
                If no match:
                    //No contact found.
                If 1 match:
                    //Displays contact details in a table.
                If multiple matches:
                    //Displays all → then asks again for phone or email to identify the exact contact.

            Returns the index of the matched contact (for editing or deleting).

    step 4. Editing Contact:-
            If user press 3 in menu:
            First it calls searchContact() → to finds contact.
            it asks as shown below:
                1. Edit by name
                2. Edit by phone
                3. Edit by email
                4. Exit

            //Based on choice, it validates and updates that contact details.

    step 5. Deleting Contact:-
            If user press 4 in menu:
            First it Calls searchContact() → to finds contact.
            it asks as shown below:
                Do you want to delete contact?
                    1. Yes
                    2. No

            If yes → shifts all contacts above it down by one index → decrements contactCount.
            If no -> it return to menu again.

    step 6. Exiting the Program
            If user press 6 in menu:
            -> Calls saveContactsToFile() → writes all contacts to contact.txt.
            -> It prints:
                //Saving and Exiting...

    Program ends....


//OUTPUT :-

Program Output:-

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Save & Exit

Enter your choice: 1
Enter how many contact should store : 2

Enter name 1: Abhishek
Enter phone 1: 6543210987 
Enter email 1: abhi@gmail.com        

Enter name 2: Rakesh
Enter phone 2: 7676763333
Enter email 2: raki@gmail.com

Contact added successfully!

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 1
Enter how many contact should store : 1

Enter name 1: Rakesh
Enter phone 1: 9123456780
Enter email 1: rakesh@gmail.com

Contact added successfully!

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 2
Enter name/phone/email to search: Rakesh

Multiple contacts found:

 ______________________________ Address Book List ________________________________
|  Serial    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Rakesh               | 7676763333           | raki@gmail.com       |
*------------*----------------------*----------------------*----------------------*
| 2          | Rakesh               | 9123456780           | rakesh@gmail.com     |
*------------*----------------------*----------------------*----------------------*

Enter serial number to search: 1

Contact Found:

 ______________________________ Address Book List ________________________________
|  Serial    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Rakesh               | 7676763333           | raki@gmail.com       |
*------------*----------------------*----------------------*----------------------*

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 2
Enter name/phone/email to search: 1112223333

Contact Found:

 ______________________________ Address Book List ________________________________
|  Serial    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Bob Johnson          | 1112223333           | bob@company.com      |
*------------*----------------------*----------------------*----------------------*

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 2
Enter name/phone/email to search: john@example.com

Contact Found:

 ______________________________ Address Book List ________________________________
|  Serial    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | John Doe             | 1234567890           | john@example.com     |
*------------*----------------------*----------------------*----------------------*

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 5
Select sort criteria:
1. Sort by name
2. Sort by phone
3. Sort by email
Enter your choice: 1

 ______________________________ Address Book List ________________________________
|  Serial    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Abhishek             | 6543210987           | abhi@gmail.com       |
*------------*----------------------*----------------------*----------------------*
| 2          | Alice Smith          | 0987654321           | alice@example.com    |
*------------*----------------------*----------------------*----------------------*
| 3          | Bob Johnson          | 1112223333           | bob@company.com      |
*------------*----------------------*----------------------*----------------------*
| 4          | Carol White          | 4445556666           | carol@company.com    |
*------------*----------------------*----------------------*----------------------*
| 5          | David Brown          | 7778889999           | david@example.com    |
*------------*----------------------*----------------------*----------------------*
| 6          | Eve Davis            | 6665554444           | eve@example.com      |
*------------*----------------------*----------------------*----------------------*
| 7          | Frank Miller         | 3334445555           | frank@example.com    |
*------------*----------------------*----------------------*----------------------*
| 8          | Grace Wilson         | 2223334444           | grace@example.com    |
*------------*----------------------*----------------------*----------------------*
| 9          | Hannah Clark         | 5556667777           | hannah@example.com   |
*------------*----------------------*----------------------*----------------------*
| 10         | Ian Lewis            | 8889990000           | ian@example.com      |
*------------*----------------------*----------------------*----------------------*
| 11         | John Doe             | 1234567890           | john@example.com     |
*------------*----------------------*----------------------*----------------------*
| 12         | Rakesh               | 7676763333           | raki@gmail.com       |
*------------*----------------------*----------------------*----------------------*
| 13         | Rakesh               | 9123456780           | rakesh@gmail.com     |
*------------*----------------------*----------------------*----------------------*

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 5
Select sort criteria:
1. Sort by name
2. Sort by phone
3. Sort by email
Enter your choice: 2

 ______________________________ Address Book List ________________________________
|  Serail    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Alice Smith          | 0987654321           | alice@example.com    |
*------------*----------------------*----------------------*----------------------*
| 2          | Bob Johnson          | 1112223333           | bob@company.com      |
*------------*----------------------*----------------------*----------------------*
| 3          | John Doe             | 1234567890           | john@example.com     |
*------------*----------------------*----------------------*----------------------*
| 4          | Grace Wilson         | 2223334444           | grace@example.com    |
*------------*----------------------*----------------------*----------------------*
| 5          | Frank Miller         | 3334445555           | frank@example.com    |
*------------*----------------------*----------------------*----------------------*
| 6          | Carol White          | 4445556666           | carol@company.com    |
*------------*----------------------*----------------------*----------------------*
| 7          | Hannah Clark         | 5556667777           | hannah@example.com   |
*------------*----------------------*----------------------*----------------------*
| 8          | Abhishek             | 6543210987           | abhi@gmail.com       |
*------------*----------------------*----------------------*----------------------*
| 9          | Eve Davis            | 6665554444           | eve@example.com      |
*------------*----------------------*----------------------*----------------------*
| 10         | Rakesh               | 7676763333           | raki@gmail.com       |
*------------*----------------------*----------------------*----------------------*
| 11         | David Brown          | 7778889999           | david@example.com    |
*------------*----------------------*----------------------*----------------------*
| 12         | Ian Lewis            | 8889990000           | ian@example.com      |
*------------*----------------------*----------------------*----------------------*
| 13         | Rakesh               | 9123456780           | rakesh@gmail.com     |
*------------*----------------------*----------------------*----------------------*

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 5
Select sort criteria:
1. Sort by name
2. Sort by phone
3. Sort by email
Enter your choice: 3

 ______________________________ Address Book List ________________________________
|  Serial    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Abhishek             | 6543210987           | abhi@gmail.com       |
*------------*----------------------*----------------------*----------------------*
| 2          | Alice Smith          | 0987654321           | alice@example.com    |
*------------*----------------------*----------------------*----------------------*
| 3          | Bob Johnson          | 1112223333           | bob@company.com      |
*------------*----------------------*----------------------*----------------------*
| 4          | Carol White          | 4445556666           | carol@company.com    |
*------------*----------------------*----------------------*----------------------*
| 5          | David Brown          | 7778889999           | david@example.com    |
*------------*----------------------*----------------------*----------------------*
| 6          | Eve Davis            | 6665554444           | eve@example.com      |
*------------*----------------------*----------------------*----------------------*
| 7          | Frank Miller         | 3334445555           | frank@example.com    |
*------------*----------------------*----------------------*----------------------*
| 8          | Grace Wilson         | 2223334444           | grace@example.com    |
*------------*----------------------*----------------------*----------------------*
| 9          | Hannah Clark         | 5556667777           | hannah@example.com   |
*------------*----------------------*----------------------*----------------------*
| 10         | Ian Lewis            | 8889990000           | ian@example.com      |
*------------*----------------------*----------------------*----------------------*
| 11         | John Doe             | 1234567890           | john@example.com     |
*------------*----------------------*----------------------*----------------------*
| 12         | Rakesh               | 9123456780           | rakesh@gmail.com     |
*------------*----------------------*----------------------*----------------------*
| 13         | Rakesh               | 7676763333           | raki@gmail.com       |
*------------*----------------------*----------------------*----------------------*

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 3
Enter name/phone/email to search: Rakesh

Multiple contacts found:

 ______________________________ Address Book List ________________________________
|  Serail    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Rakesh               | 9123456780           | rakesh@gmail.com     |
*------------*----------------------*----------------------*----------------------*
| 2          | Rakesh               | 7676763333           | raki@gmail.com       |
*------------*----------------------*----------------------*----------------------*

Enter serial number to search: 2

Contact Found:

 ______________________________ Address Book List ________________________________
|  Contact   |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Rakesh               | 7676763333           | raki@gmail.com       |
*------------*----------------------*----------------------*----------------------*

Select edit choice:
1. Edit by name
2. Edit by phone
3. Edit by email
4. Exit
Enter your edit choice: 1
Enter new name for contact: Rakesh K

Contact name edited successfully!

Select edit choice:
1. Edit by name
2. Edit by phone
3. Edit by email
4. Exit
Enter your edit choice: 2
Enter new phone number for contact: 7657657654

Contact phone edited successfully!

Select edit choice:
1. Edit by name
2. Edit by phone
3. Edit by email
4. Exit
Enter your edit choice: 3
Enter new email for contact: rakeshk@gmail.com

Contact email edited successfully!

Select edit choice:
1. Edit by name
2. Edit by phone
3. Edit by email
4. Exit
Enter your edit choice: 4

Contact exited successfully!

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 4
Enter name/phone/email to search: Rakesh

Multiple contacts found:

 ______________________________ Address Book List ________________________________
|  Serail    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Rakesh               | 9123456780           | rakesh@gmail.com     |
*------------*----------------------*----------------------*----------------------*
| 2          | Rakesh K             | 7657657654           | rakeshk@gmail.com    |
*------------*----------------------*----------------------*----------------------*

Enter serial number to search: 2

Contact Found:

 ______________________________ Address Book List ________________________________
|  Serial    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Rakesh K             | 7657657654           | rakeshk@gmail.com    |
*------------*----------------------*----------------------*----------------------*

Do yo want to delete contact?
1. Yes
2. No
Enter the choice: 2

Contact not deleted successfully!


Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 4
Enter name/phone/email to search: Rakesh

Multiple contacts found:

 ______________________________ Address Book List ________________________________
|  Serail    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Rakesh               | 9123456780           | rakesh@gmail.com     |
*------------*----------------------*----------------------*----------------------*
| 2          | Rakesh K             | 7657657654           | rakeshk@gmail.com    |
*------------*----------------------*----------------------*----------------------*

Enter serial number to search: 2

Contact Found:

 ______________________________ Address Book List ________________________________
|  Serial    |        Name          |       Phone          |       Email          |
|    No      |                      |        No            |        Id            |
*------------*----------------------*----------------------*----------------------*
| 1          | Rakesh K             | 7657657654           | rakeshk@gmail.com    |
*------------*----------------------*----------------------*----------------------*

Do yo want to delete contact?
1. Yes
2. No
Enter the choice: 1

Contact deleted successfully!

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 6
Saving and Exiting...

Address Book Menu:
1. Create contact
2. Search contact
3. Edit contact
4. Delete contact
5. List all contacts
6. Exit

Enter your choice: 7
Invalid choice. Please try again.

//End
