/*
NAME : VIDYA V K
DATE : 12-04-2024
TITLE	: Inverted Search
DESCRIPTION:Inverted search organizes data to optimize retrieval by indexing content based on keywords or metadata,enabling efficient search operations.
 */
#include "main.h"

int main(int argc, char *argv[]) 
{
    int op, flag1 = 0, flag2 = 0;  //Declaring & Initializing variables
    Slist *head = NULL;            //Initialize head pointer variable and assigned it as NULL
    m_node *arr[ALPHA_SIZE] = {NULL};  //Creating array of structure pointer or Hash table array

    //To check if the argument is greater than 1
    if (argc > 1) 
	{
        // Function To validate the arguments we passed
        if (validate_args(&head, argv) == FAILURE) 
		{
            printf("ERROR: Read and validation failed.\n");
            return FAILURE;
        } else {
            printf("<-----Read and Validation Done successfully.----->\n\n");
        }
        do 
		{
            if (flag1 == 0) 
			{   //To check flag equal to 0
                flag1 = 1;
                printf("1. Create Database\n2. Display Database\n3. Search Database\n4. Save Database\n5. Update Database\n6. Exit\n");
                printf("Please enter your choice:\n");
            }
            scanf("%d", &op);   //Reading the option from user
            switch (op) 
			{
                case 1:
                    /* Creating Database */
                    if (flag2 == 0) 
					{
                        flag2 = 1;
                        //Function to create a database
                        if (create_database(arr, &head) == SUCCESS) 
						{
                            printf("<-----Database Created Successfully.----->\n\n");
                        } 
						else 
						{
                            printf("ERROR: Creating Database Failed.\n");
                            return FAILURE;
                        }
                    } 
					else 
					{
                        printf("Database was already created.\nWe can't create it again.\n<---------------**********--------------->\n\n");
                    }
                    break;

                case 2:
                    /* Display Database */
                    //Function to display the database
                    if (display_database(arr) == SUCCESS) 
					{
                        printf("<-----Database Displayed Successfully.----->\n\n");
                    } else 
					{
                        printf("ERROR: Displaying Database Failed.\n");
                        return FAILURE;
                    }
                    break;

                case 3:
                    /* Search Database */
                    //Function to search the database
                    if (search_database(arr) == SUCCESS) 
					{
                        printf("<----- Word Found Successfully.----->\n\n");
                    } 
					else 
					{
                        printf("ERROR:  Database Failed.\n");
                        return FAILURE;
                    }
                    break;

                case 4:
                    /* Save Database */
                    //Function to save the database
                    if (save_database(arr) == SUCCESS) 
					{
                        printf("<-----Database Saved Successfully.----->\n\n");
                    } 
					else 
					{
                        printf("ERROR: Saving Database Failed.\n");
                        return FAILURE;
                    }
                    break;

                case 5:
                    /* Update Database */
                    //Function to Update the database
                    if (update_database(arr, &head) == SUCCESS) 
					{
                        printf("<-----Database Updated successfully.----->\n\n");
                    } 
					else 
					{
                        printf("Error: Updating Database Failed.\n");
                        return FAILURE;
                    }
                    break;

                case 6:
                    /* Exit */
                    printf("<-----Exiting program.----->\n\n");
                    return FAILURE;

                default:
                    printf("Invalid option. Please Try Again!!\n");  //Error message
            }

            char choice;
            printf("Do you want to continue (y/n)? ");
            scanf(" %c", &choice);
            if (choice != 'y' && choice != 'Y') {
                printf("<-----Exiting program.----->\n\n");
                return FAILURE;
            }
        } while (1);  // Loop indefinitely until user chooses to exit
    } 
	else 
	{
        printf("ERROR: Please pass more than one argument in cla.\nExample: %s <filename1.txt> <filename2.txt> ... \n", argv[0]);
        return FAILURE;
    }
    return 0;
}

