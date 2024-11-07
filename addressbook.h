#ifndef ADDRESSBOOK
#define ADDRESSBOOK


typedef struct user//structure defnition
{
    char name[50];
    char mobile[15];
    char email[50];
    char address[100];
} user;//new name for struct user
//function prototype
void add_data(user *);
void search_data(user *);
void print_data();
void delete_data(user *);
void edit_data(user *);

#endif 

