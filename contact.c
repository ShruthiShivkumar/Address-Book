#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

void create_name(AddressBook *addressBook,int count);
int validate_name(char *nametemp);
void create_mobile(int count,AddressBook *addressBook);
int validate_mobile(char *mobile,AddressBook *addressBook,int count);
void create_email(int count,AddressBook *addressBook);
int validate_email(char *email,AddressBook *addressBook,int count);

//list contacts saved
void listContacts(AddressBook *addressBook) 
{
    printf("Name : \t\t\tMobile :\t\temail :\n");
    // Sort contacts based on the chosen criteria
    for(int i=0;i<(addressBook->contactCount);i++)
    {
      if(strlen(addressBook->contacts[i].name)<=7)
      {
        printf("%s\t\t\t%s\t\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
      }
      else
      {
        printf("%s\t\t%s\t\t%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
      }
    }
    
}

//initialise the contacts by loading
void initialize(AddressBook *addressBook) {
    addressBook->contactCount = 0;
    //populateAddressBook(addressBook);
    
    // Load contacts from file during initialization (After files)
    loadContactsFromFile(addressBook);
}

//save and exit from addressbook
void saveAndExit(AddressBook *addressBook) {
    saveContactsToFile(addressBook); // Save contacts to file
    exit(EXIT_SUCCESS); // Exit the program
}

//create contacts
void createContact(AddressBook *addressBook)
{
    
    int count = addressBook->contactCount;
    create_name(addressBook,count); //Entering name
    create_mobile(count,addressBook);//Entering mobile
    create_email(count,addressBook); //Entering email
    addressBook->contactCount++;
}

//searching contacts
int searchContact(AddressBook *addressBook,int *index) 
{
    int n,res=0;
    char name[50],email[50],mobile[50];
    int count = addressBook->contactCount;
    do
    {
    printf("Choose the option to Search the contacts:\n");
    printf("1.Name\n2.Mobile\n3.Email\n");
    printf("Enter the option : ");
    scanf("%d",&n);
    switch(n)
    {
        //searching contacts with name
        case 1: 
            int namecount=0;
            printf("Enter name : ");
            scanf(" %[^\n]",name);
            int res1 = validate_name(name);
            if(res1!=1)
            {
              printf("Invalid input, Enter valid name\n");
              return 0;
              break;
            }  
            

            for(int i=0;i<=count;i++)
            {
               res=strcmp(addressBook->contacts[i].name,name);
               if (res==0)
               {
                *index=i;
                namecount++;
               
               }
               
            }
            
            if(namecount > 1)
            {
                printf("Multiple names exist.Search with email or mobile\n"); 
                do
                {
                    printf("Choose the option to Search the contacts:\n");
                    printf("1.Mobile\n2.Email\n");
                    printf("Enter the option : ");
                    scanf("%d",&n);
                    getchar();
                    switch(n)
                    {
                        case 1:
                         printf("Enter mobile : ");
                         scanf(" %[^\n]",mobile);
                        for(int i=0;i<=count;i++)
                        {
                           res=strcmp(addressBook->contacts[i].phone,mobile);
                           if (res==0)
                           {
                             *index=i;
                             break;
                           }
               
                        }
                        if(res==0)
                        {
                          printf("Name  : %s\n",addressBook->contacts[*index].name);
                          printf("Mobile: %s\n",addressBook->contacts[*index].phone);
                          printf("Email : %s\n",addressBook->contacts[*index].email);
                          return 1;
                        }
                        else
                        {
                          *index=count;
                          printf("Contact does not exist\n");
                          return 0;
                        }
                        break;

                        case 2:
                          printf("Enter email : ");
                          scanf(" %[^\n]",email);
                          for(int i=0;i<=count;i++)
                          {
                            res=strcmp(addressBook->contacts[i].email,email);
                            if (res==0)
                            {
                              *index=i;
                               break;
                            }
               
                          }
                         if(res==0)
                        {
                          printf("Name  : %s\n",addressBook->contacts[*index].name);
                          printf("Mobile: %s\n",addressBook->contacts[*index].phone);
                          printf("Email : %s\n",addressBook->contacts[*index].email);
                          return 1;
                        }
                        else
                        {
                          *index=count;
                          printf("Contact does not exist\n");
                          return 0;
                        }
                        break;

                      default:
                        printf("Invalid Input. Enter options from 1-2\n");
                        return 0;
                    }
    

                } while (n<1 || n>2 );
                
                break;
            }
            if(res==0 || namecount == 1)
               {
                printf("contact found\n");
                printf("Name  : %s\n",addressBook->contacts[*index].name);
                printf("Mobile: %s\n",addressBook->contacts[*index].phone);
                printf("Email : %s\n",addressBook->contacts[*index].email);
                return 1;
               }
               else
               {
                *index=count;
                printf("Contact does not exist\n");
                return 0;
               }
            break;
        
        //searching with mobile
        case 2:
            printf("Enter mobile : ");
            scanf(" %[^\n]",mobile);
            res1 = validate_mobile(mobile,addressBook,count);
            if(res1==0)
            {
                printf("Invalid input, Enter valid mobile number\n");
                return 0;
                break;
            }  
            else if(res1==1)
            {
                printf("contact not found\n");
                return 0;
                break;
            }
            
            for(int i=0;i<=count;i++)
            {
               res=strcmp(addressBook->contacts[i].phone,mobile);
               if (res==0)
               {
                *index=i;
                break;
               }
               
            }

            if(res==0)
               {
                printf("contact found\n");
                printf("Name  : %s\n",addressBook->contacts[*index].name);
                printf("Mobile: %s\n",addressBook->contacts[*index].phone);
                printf("Email : %s\n",addressBook->contacts[*index].email);
                return 1;
               }
               else
               {
                *index=count;
                printf("Contact does not exist\n");
                return 0;
               }
            break;
        
        //Searching with email
        case 3:
          printf("Enter email : ");
            scanf(" %[^\n]",email);
            res1 = validate_email(email,addressBook,count);
            if(res1==0)
            {
                printf("Invalid input, Enter valid mobile number\n");
                return 0;
                break;
            }  
            else if(res1==1)
            {
                printf("contact not found\n");
                return 0;
                break;
            }

            for(int i=0;i<=count;i++)
            {
               res=strcmp(addressBook->contacts[i].email,email);
               if (res==0)
               {
                *index=i;
                break;
               }
               
            }
               if(res==0)
               {
                printf("contact found\n");
                printf("Name  : %s\n",addressBook->contacts[*index].name);
                printf("Mobile: %s\n",addressBook->contacts[*index].phone);
                printf("Email : %s\n",addressBook->contacts[*index].email);
                return 1;
               }
               else
               {
                *index=count;
                printf("Contact does not exist\n");
                return 0;
               }
            break;

            default : 
            printf("Invalid Input. Enter options from 1-3\n");
            return 0;
    }
    }while(n<1||n>3);
}

void editContact(AddressBook *addressBook)
{
    int index=0,n,res=0,res1=0;
    char name[50],email[50],mobile[50];
    int count = addressBook->contactCount;
    do
    {
    printf("Check for the contact : \n");
	res1 = searchContact(addressBook,&index);
    if(res1==0)
    {
        return;
    }

    printf("Choose the option to edit details : \n");
    printf("1.Name\n2.Mobile\n3.Email\n");
    scanf("%d",&n);
    switch(n)
    {
        case 1 : 
            create_name(addressBook,index);
            break;

        case 2:
             create_mobile(index,addressBook);
             break; 

        case 3:
             create_email(index,addressBook);
             break; 

        default: 
             printf("Invalid input.Enter number from 1-3\n");
             break;
        
    }
    }while(n<1||n>3);
printf("Contact edited\n");
}

void deleteContact(AddressBook *addressBook)
{
    int index=0,i,res1;
	printf("Search the contacts to delete : \n");
    res1 = searchContact(addressBook,&index);
    if(res1==0)
    {
        return;
    }
    for(i=index;i<(addressBook->contactCount);i++)
    {
    strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
    strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
    strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email);
    if(i==addressBook->contactCount-1)
    {
      addressBook->contactCount--;
      printf("\nContact Deleted\n");
    }
    
    }
   
    
}

//Entering name
void create_name(AddressBook *addressBook,int count)
{
    char nametemp[50];
    while(1)
    {
    printf("Enter name : ");
    scanf(" %[^\n]",nametemp);
    int res = validate_name(nametemp);
    if(res==1)
    {
       strcpy(addressBook->contacts[count].name,nametemp);
       break;
    }  
    else
    {
    printf("Invalid input, Enter valid name\n");
    
    }
    }
}

//Name validation
int validate_name(char *nametemp)
{
    if(*nametemp==' ' || *nametemp=='\t')
    {
        return 0;
    }

    while(*nametemp!='\0')
    {
            if((*nametemp >= 'a' && *nametemp <= 'z') || (*nametemp >= 'A' && *nametemp <= 'Z') || (*nametemp ==' '))
            {
              nametemp++;
            }
            else
            {
                return 0;
            }
    }
     
    return 1;
    
}

//Mobile number input
void create_mobile(int count,AddressBook *addressBook)
{
    char mobiletemp[50];
    while(1)
    {
    printf("Enter mobile number :");
    scanf(" %[^\n]",mobiletemp);
    int res = validate_mobile(mobiletemp,addressBook,count);
    if(res==1)
    {
       strcpy(addressBook->contacts[count].phone,mobiletemp);
       break;
    }  
    else if(res==2)
    {
        printf("Mobile number exists\n");
        
    }
    else
    {
    printf("Invalid input, Enter valid mobile number\n");
    
    }
    }
}

//validating mobile number
int validate_mobile(char *mobile,AddressBook *addressBook,int count)
{
    int s;
    for(int i=0;i<count;i++)
    {
         s = strcmp(addressBook->contacts[i].phone,mobile);
         if(s==0)
         {
            return 2;
         }

    }
    int len = strlen(mobile);
    if(len!=10)
    {
        return 0;
    }
        while(*mobile!='\0')
        {
            if(*mobile>='0' && *mobile<='9')
            {
                mobile++;
            }
            else
            {
                return 0;
            }
        }
        return 1;
    }
    

//Entering email
void create_email(int count,AddressBook *addressBook)
{
    char emailtemp[50];
    while(1)
    {
    printf("Enter email id :");
    scanf(" %[^\n]",emailtemp);
    int res = validate_email(emailtemp,addressBook,count);

    if(res==1)
    {
       strcpy(addressBook->contacts[count].email,emailtemp);
       break;
    }  
    else if(res==2)
    {
        printf("Email exists exists\n");
        
    }
    else
    {
    printf("Invalid input, Enter valid email\n");
    
    }
    }
}

//Validating email
int validate_email(char *email,AddressBook *addressBook,int count)
{
    int len = strlen(email),Count=0,i=0,count1=0,s,j;

    for(int j=0;j<count;j++)
    {
         s = strcmp(addressBook->contacts[j].email,email);
         if(s==0)
         {
            return 2;
         }
    }
    if((email[i] >= 'a' && email[i] <= 'z') || (email[i] >= 'A' && email[i] <= 'Z') || (email[i] =='0' && email[i] == '9'))
    {
        i++;
        while(email[i]!='\0')
        {
            if(email[i]=='@')
            {
               i++;
               if((email[i] >= 'a' && email[i] <= 'z') || (email[i] >= 'A' && email[i] <= 'Z') || (email[i] =='0' && email[i] == '9'))
               {
                  i--;
                  Count++;  
               }
               else
               {
                  return 0;
               }   
            }
            if(email[i]=='.')
            {
                    if(email[i+1]=='c' && email[i+2]=='o' && email[i+3]=='m' && email[i+4]=='\0')
                    {
                        count1++;
                    }
            }
        i++;
        }
           
    }
    
       if(Count==1 && count1==1)
       {
        return 1;
       }
       
       else
       {
        return 0;
       }
    }