#include <stdio.h>
#include <string.h>
#include "addressbook.h"


//Function to add new user's data
void add_data(user *usr)  
{
    int count;//variable to get no.of entries from file
    FILE *ptr = fopen("addressbook.csv", "r+");//open the file in read and write mode 
    if (ptr == NULL)//check if file does not exist 
    {
        ptr = fopen("addressbook.csv", "w+");//if file not exist create new file
        if (ptr == NULL)//check if failed to create file
        {
            printf("Error opening file!\n");
            return;
        }
        count = 0;//take count as 0 because new file is created
        fprintf(ptr, "%d\n", count);//make count first character of file
    } 
    else 
    {
        fscanf(ptr, "%d\n", &count);//if file exist read first character to the variable count
    }
    //prompt user to type new  user information
    printf("\nEnter the name: ");
    scanf(" %[^\n]", usr->name);
    printf("Enter the mobile no.: ");
    scanf(" %[^\n]", usr->mobile);
    printf("Enter the email address: ");
    scanf(" %[^\n]", usr->email);
    printf("Enter the address: ");
    scanf(" %[^\n]", usr->address);

    fseek(ptr, 0, SEEK_END);//seek pointer to the end of file to add new user info
    fprintf(ptr, "%s,%s,%s,%s\n", usr->name, usr->mobile, usr->email, usr->address);//writing to file
    fseek(ptr, 0, SEEK_SET);//seek pointer to the first character to update the count varible.
    fprintf(ptr, "%d\n", count + 1);//increment and update the count variable
    fclose(ptr);//close the file
    printf("USER added successfully!\n");
}
//Function to search particular users data
void search_data(user *usr)
{
    char searchdata[100];//variable to store the new name to be searched
    int count;//variable to store no.of entries from file
    //prompt user to type the data to be searched  
    printf("Enter the data to search: ");
    scanf(" %[^\n]", searchdata);
    FILE *fp = fopen("addressbook.csv", "r");//open the file  in read mode
    if (fp == NULL) //check if file exist 
    {
        printf("Error opening file!\n");
        return;
    }
    fscanf(fp, "%d\n", &count);//read first character to count variable
    int found = 0;//flag variable to detect presence of searchdata in file
    while (count != 0)//loop through count no.of entries
    {
        fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", usr->name, usr->mobile, usr->email, usr->address);//read each line of data
        if ((strcmp(usr->name, searchdata) == 0)||(strcmp(usr->mobile,searchdata)==0)||(strcmp(usr->email,searchdata)==0)||(strcmp(usr->address,searchdata))==0) //check if searchdata present
        {
            found = 1;//if found update found variable
            printf("Name: %s\tMobile: %s\tEmail: %s\tAddress: %s\n", usr->name, usr->mobile, usr->email, usr->address);//printing user info to console
            break;
        }
        count--;
    }

    if (!found) //if data not found
    {
        printf("User does not exist\n");
    }

    fclose(fp);
}

// Function to print all user data
void print_data() 
{
    user usr;//new structure vaiable to store each user info from file
    int count;//variable to store no.of entries from file
    FILE *fp = fopen("addressbook.csv", "r");// open file in read mode
    if (fp == NULL) //if file does not exist
    {
        printf("Error opening file!\n");
        return;
    }
    fscanf(fp, "%d\n", &count);//reading no.of entries from first character of file to count variable
    printf("\n--- All User Data ---\n");
    if (count == 0) //if no entries in file
    {
        printf("No data available\n");
    }
    while (count != 0) //loop using count variable read all data
    {
        fscanf(fp, "%[^,],%[^,],%[^,],%[^\n]\n", usr.name, usr.mobile, usr.email, usr.address);//read each user data from file
        printf("Name: %s\tMobile: %s\tEmail: %s\tAddress: %s\n", usr.name, usr.mobile, usr.email, usr.address);//print to console
        count--;
    }
    fclose(fp);//close the file
}

//Function to delete a particular user's data
void delete_data(user *usr)
{
    char deletedata[100];//variable to store the data to be searched and deleted
    int count;//variable to store no.of entries in file
    printf("Enter data is to be deleted: ");//prompt user to type the data to be deleted
    scanf(" %[^\n]", deletedata);

    FILE *ptr = fopen("addressbook.csv", "r");//open file in read mode
    if (ptr == NULL)//if file doesn't exist
    {
        printf("Error opening file!\n");
        return;
    }
    fseek(ptr, 0, SEEK_SET);//seek to th first character to read entry count 
    fscanf(ptr, "%d\n", &count);//read count
    if (count == 0) //if no use info in file
    {
        printf("\nNo entries in file!\n");
        fclose(ptr);
        return;
    }

    FILE *temp = fopen("temp.csv", "w");//open a temporary file in write mode
    if (temp == NULL) //if file does not exist
    {
        printf("Error opening temp file!\n");
        fclose(ptr);//close addressbook.csv file
        return;
    }

    int found = 0;//flag variable to detect presence of searched data in file
    int temp_count = count;//store count variable in another temporary variable
    while (count != 0)//loop using count variable to get all data from file
    {
        fscanf(ptr, "%[^,],%[^,],%[^,],%[^\n]\n", usr->name, usr->mobile, usr->email, usr->address);//fetch each line from file
        //write everydata to temporary file except data to be deleted
        if ((strcmp(deletedata,usr->name) == 0)||(strcmp(deletedata,usr->mobile) == 0)||(strcmp(deletedata,usr->email) == 0)||(strcmp(deletedata,usr->address) == 0)) 
        {
            found = 1;//update found variable
            temp_count--;//update and decrement temerory count variable to update new entry count in file
            
        }
        else //if fetched data not the data to be deleted
        {
          fprintf(temp, "%s,%s,%s,%s\n", usr->name, usr->mobile, usr->email, usr->address); 
        }
        count--;
    }
    //close both the file
    fclose(ptr);
    fclose(temp);

    if (!found)//if data not found
    {
        printf("Data not found!\n");
    }
    else //if data present in file
    {
        ptr = fopen("addressbook.csv", "w");//open file in write mode
        if (ptr == NULL)//if failed to open
        {
            printf("Error opening file!\n");
            return;
        }

        temp = fopen("temp.csv", "r");//open temp in read mode
        if (temp == NULL)//if failed to open
        {
            printf("Error opening temp file!\n");
            fclose(ptr);
            return;
        }

        fprintf(ptr, "%d\n", temp_count);//write count variable as the first entry in file
        //copy content of temp to addessbook.csv file again
        while (fscanf(temp, "%[^,],%[^,],%[^,],%[^\n]\n", usr->name, usr->mobile, usr->email, usr->address) != EOF)
        {
            fprintf(ptr, "%s,%s,%s,%s\n", usr->name, usr->mobile, usr->email, usr->address);
        }
        //close files
        fclose(temp);
        fclose(ptr);
        printf("Data deleted successfully!\n");
    }
}


void edit_data(user *usr)
{
    int count;//variable to store no.of entries in file
    char editname[50];//variable to store name of the user whose data to be edited
     //prompt user to type name of the person
    printf("Enter the name of the person whose data is to be edited: ");
    scanf(" %[^\n]", editname);

    FILE *ptr = fopen("addressbook.csv", "r");//open file in read mode
    if (ptr == NULL)
    {
        printf("Error opening file!\n");
        return;
    }
    fscanf(ptr, "%d\n", &count);//read count variable from first character of file

    FILE *temp = fopen("temp.csv", "w");//open a temporary file in write mode
    if (temp == NULL)//if failed to open
    {
        printf("Error opening temp file!\n");
        fclose(ptr);
        return;
    }

    int found = 0;//flag variable to detect presence data to be edited 
    fprintf(temp, "%d\n", count);//write count to file as first line
    while (count != 0) //loop using count variable to read info from file
    {
        fscanf(ptr, "%[^,],%[^,],%[^,],%[^\n]\n", usr->name, usr->mobile, usr->email, usr->address);//read each line from file
        if (strcmp(editname, usr->name) == 0) //if data found
        {
            printf("Editing Contact:\n");
            found = 1;//updating found variable
            char c = 'y';
            //prompt user to get new details
            do
            {
                int choice;
                printf("\n--------Choose the field to edit----------\n1. Name\n2. Mobile\n3. Email\n4. Address\nEnter choice: ");
                scanf("%d", &choice);
                getchar(); // Consume the newline character after choice input
                
                switch (choice) 
                {
                    case 1:
                        printf("Enter new name: ");
                        scanf(" %[^\n]", usr->name);
                        break;

                    case 2:
                        printf("Enter new mobile: ");
                        scanf(" %[^\n]", usr->mobile);
                        break;

                    case 3:
                        printf("Enter new email: ");
                        scanf(" %[^\n]", usr->email);
                        break;

                    case 4:
                        printf("Enter new address: ");
                        scanf(" %[^\n]", usr->address);
                        break;
                    default:
                        printf("\nInvalid choice\n");
                }
                printf("Do you want to continue editing fields? (y/n): ");
                scanf(" %c", &c);
                getchar(); // Consume the newline character after yes/no input
            } while (c == 'y' || c == 'Y');
        }
        fprintf(temp, "%s,%s,%s,%s\n", usr->name, usr->mobile, usr->email, usr->address);//write to temp file the updated data
        count--;
    }
    //close all file
    fclose(ptr);
    fclose(temp);

    if (!found)//if data not found
    {
        printf("Name not found!\n");
    } 
    else //if data found
    {
        ptr = fopen("addressbook.csv", "w");//open addressbook.csv in write mode
        if (ptr == NULL)//if failed to open
        {
            printf("Error opening file!\n");
            return;
        }

        temp = fopen("temp.csv", "r");//open temporary file in read mode again
        if (temp == NULL)//if failed to open
        {
            printf("Error opening temp file!\n");
            fclose(ptr);
            return;
        }
        fscanf(temp, "%d\n", &count);//get count from temp file
        fprintf(ptr, "%d\n", count);//write count to address.csv file

        while (fscanf(temp, "%[^,],%[^,],%[^,],%[^\n]\n", usr->name, usr->mobile, usr->email, usr->address) != EOF) //fetch each line of data until end of temp file
        {
            fprintf(ptr, "%s,%s,%s,%s\n", usr->name, usr->mobile, usr->email, usr->address);//write to addressbook.csv file
        }
        //close all file
        fclose(temp);
        fclose(ptr);
        printf("Contact edited successfully!\n");
    }
}

