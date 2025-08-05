#include "main.h"

// To read and validate  arguments
Status validate_args(Slist **head, char *argv[])
{
    int i;
    FILE *fptr;
    int txtCount = 0; // Counter for .txt files
    int Count = 0; // Counter for ignored files

    for (i = 1; argv[i] != NULL; i++)
    {
        // Checking whether input is a txt file or not
        if (strstr(argv[i], ".txt") != NULL)
        {
            // Increment the counter for .txt files
            txtCount++;

            // Open the file to check if the file exists or not
            fptr = fopen(argv[i], "r");
            if (fptr == NULL) // Error handling
            {
                printf("ERROR : File --> '%s' does not exist.\n", argv[i]);
                return FAILURE;
            }

            // Check if file is empty
            fseek(fptr, 0, SEEK_END); // Move file pointer to the end of the file
            long size = ftell(fptr);  // Get the current position of the file pointer
            if (size == 0) // Error handling
            {
                printf("Warning: File --> '%s' is an empty file and will not be added to the list.\n", argv[i]);
                fclose(fptr);
                Count++;
                continue; // Skip adding this file to the list and continue with next file
            }
            rewind(fptr); // Move the cursor again to the starting point

            // Check for duplicate files
            if (check_duplicate(head, argv[i]) == FAILURE) // Error handling
            {
                printf("Duplicate file found --> %s. Skipping...\n", argv[i]);
                fclose(fptr);
                Count++;
                continue; // Skip adding this file to the list and continue with next file
            }

            // Add the file to the list
            insert_at_last(head, argv[i]);
            printf("Successful : '%s' added to the list.\n", argv[i]);
            fclose(fptr); // Closing file
        }
        // Checking whether input is a shell script file
        else if (strstr(argv[i], ".sh") != NULL)
        {
            printf("Warning: File --> '%s' is a .sh file and will not be added to the list.\n", argv[i]);
            Count++;
        }
    }

    // If exactly one ignored file encountered and no .txt files, print a warning and terminate
    if (Count == 1 && txtCount == 0)
    {
        printf("Error: Exactly one  file encountered. Program will terminate.\n");
        return FAILURE;
    }

    return SUCCESS;
}





//To check the presence of any  duplicate files passed in CLA
Status check_duplicate(Slist **head, char *filename) 
{
    Slist *temp = *head;
    while (temp != NULL) 
    {
        if (strcmp(temp -> f_name, filename) == 0) {
            return FAILURE; // Duplicate found
        }
        temp = temp->link;
    }
    return SUCCESS; // No duplicate found
}


//Inserting node at the last in the list
Status insert_at_last(Slist **head, char * filename)
{
    //1.Create, 2. Valiadate, 3.Update

    Slist *new = malloc(sizeof(Slist));
    if(new == NULL)
    {
	return FAILURE;
    }
    strcpy(new -> f_name,filename);
    new -> link = NULL;

    //Check for list_empty
    if(*head == NULL)
    {
	*head = new;
	return SUCCESS;
    }
    else
    {
	//Check for List_non_empty
	//Traverse to last 
	Slist *temp = *head;
	while (temp -> link != NULL)
	{
	    temp = temp -> link;
	}
	temp -> link = new;
	return SUCCESS;
    }
}

//To create a new main node
m_node *create_Main_node(char *word)
{
    //1. Create, 2. validate, 3. Update
    m_node *new = (m_node *)malloc(sizeof(m_node));
    if (new == NULL)
    {
	printf("ERROR: Memory allocation failed for main node.\n");
	return FAILURE;
    }

    new -> file_count = 0; 
    strcpy(new -> word, word); // Copy the word into the node
    new -> m_link = NULL;
    new -> s_link = NULL;
    return new;
}

//To create a new sub node 
s_node *create_Sub_node(char *filename)
{
    //1. Create, 2. validate, 3. Update
    s_node *new = (s_node *)malloc(sizeof(s_node));
    if (new == NULL)
    {
	printf("ERROR: Memory allocation failed for sub node.\n");
	return FAILURE;
    }
    new -> word_count = 0; 
    strcpy(new -> file_name, filename); // Copy the filename into the node
    new -> sub_link = NULL;
    return new;
}

//To find the index position
int find_index(char ch)
{
    if(isalpha(ch))
    {
	ch = tolower(ch);	//making the first letter of the word into lowercase
	return ch - 97;		//To get index 
    }
    return 26;			//Directly assign index pos 26 for punctuations and digits
}
