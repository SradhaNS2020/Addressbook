#include <stdio.h>
#include <stdlib.h>
#include "addressbook.h"  

int main() 
{
    user user1;  //structure variable

    while (1) 
    {
        int ch;

        printf("----------------------Menu--------------------\n");
        printf("1. Add Data\n2. Search a person's data\n3. Print all data \n4. Delete a person's data\n5. Edit a person's data\n6. Exit\nEnter choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1:
                add_data(&user1); //function call to add_data()
                break;
            case 2:
                search_data(&user1);//function call to search_data()
                break;
            case 3:
                print_data();//function call to print_data()
                break;
            case 4:
                delete_data(&user1);//function call to delete_data()
                break;
            case 5:
                edit_data(&user1);//function call to edit_data()
                break;
            case 6:
                printf("\nExited\n");
                exit(0);
            default:
                printf("\nInvalid choice\n");
        }
    }

    return 0;
}

