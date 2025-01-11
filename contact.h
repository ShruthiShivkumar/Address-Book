#ifndef CONTACT_H
#define CONTACT_H

#define MAX_CONTACTS 100
//structure for contacts
typedef struct {
    char name[50];
    char phone[20];
    char email[50];
} Contact;

typedef struct {
    Contact contacts[100];
    int contactCount;
} AddressBook;

//functions of addressbook
void createContact(AddressBook *addressBook);
int searchContact(AddressBook *addressBook,int *index);
void editContact(AddressBook *addressBook);
void deleteContact(AddressBook *addressBook);
void listContacts(AddressBook *addressBook);
void initialize(AddressBook *addressBook);
void saveContactsToFile(AddressBook *AddressBook);

#endif
