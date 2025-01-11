#include <stdio.h>
#include "file.h"

//save contacts in file
void saveContactsToFile(AddressBook *addressBook) 
{
int i,count = addressBook->contactCount;
FILE *fp;
//saving data in file save.csv
fp = fopen("save.csv","w");
if(fp==NULL)
{
    perror("ERROR");
    return;
}
fprintf(fp,"%d\n",count);
for(i=0;i<count;i++)
{
    fprintf(fp,"%s",addressBook->contacts[i].name);
    fprintf(fp,"%c",',');
    fprintf(fp,"%s",addressBook->contacts[i].phone);
    fprintf(fp,"%c",',');
    fprintf(fp,"%s",addressBook->contacts[i].email);
    fprintf(fp,"%c",'\n');

}
fclose(fp);
}

//load contacts from file
void loadContactsFromFile(AddressBook *addressBook) 
{
int i;
FILE *fp;
//reading data from save.csv
fp = fopen("save.csv","r");
if(fp==NULL)
{
    perror("ERROR");
    return;
}
fscanf(fp,"%d\n",&(addressBook->contactCount));
for(i=0;i<addressBook->contactCount;i++)
{
    fscanf(fp,"%[^,],",addressBook->contacts[i].name);
    fscanf(fp,"%[^,],",addressBook->contacts[i].phone);
    fscanf(fp,"%[^\n]\n",addressBook->contacts[i].email);

}
fclose(fp);
}
