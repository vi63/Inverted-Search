#include "main.h"

//To Update databse from backup file
Status update_database(m_node *arr[], Slist **head)
{
    char backupfile[MAX_LENGTH_SIZE];
    FILE* fptr = NULL;

    //Read backfile from user
    printf("Enter the Backupfile, eg --> <filename.txt> : ");
    scanf("%s", backupfile);

    //To check for backfile is .txt or not
    if(strstr(backupfile, ".txt") == NULL)
    {
	printf("ERROR : Given file is not a .txt file.\n");
	return FAILURE;
    }
    //To open backup file
    fptr = fopen(backupfile, "r");
    if(fptr == NULL)
    {
	printf("ERROR : Unable to open the backup file !.\n");
	return FAILURE;
    }

    //create character array to store line from backupfile
    char buffer[MAX_LENGTH_SIZE];

    //read lines from file
    int i, index;	//Decaling variables

    //loop for fetch entire data from backup file
    while(fgets(buffer, MAX_LENGTH_SIZE, fptr) != NULL)
    {
	//checking first and last char of line with '#'
	if(buffer[0] != '#' && buffer[strlen(buffer)-2] != '#')
	{
	    printf("ERROR : backupfile having Incorrect format.\nUsage : #<index>;<word>;<file_count>;<file_name>;<word_count>\n1\n");
	    fclose(fptr);
	    return FAILURE;
	}
	else
	{
	    //To get index from backupfile
	    index = atoi(strtok(&buffer[1], ";"));

	    //create main node and update the members
	    if(arr[index] == NULL)
	    {
		m_node *main_new = malloc(sizeof(m_node));
		if(main_new == NULL)
		{
		    printf("ERROR : memory allocation failed for new mainnode.\n");
		    fclose(fptr);
		    return FAILURE;
		}

		//update mainnode members
		arr[index] = main_new;
		strcpy(main_new -> word, strtok(NULL, ";"));		//to get the word from backup file
		main_new -> file_count = atoi(strtok(NULL, ";"));	//To get the file count from backup file

		s_node *s_temp = NULL;	//Initializing subnode temp variable as NULL

		//Run the loop as file count times for creating subnodes 
		for(i=0; i < main_new -> file_count; i++)
		{
		    //creating subnode and update members
		    s_node *sub_new = malloc(sizeof(s_node));
		    if(sub_new == NULL)
		    {
			printf("ERROR : memory alloacation failed for new subnode.\n");
			fclose(fptr);
			return FAILURE;
		    }
		    sub_new -> sub_link = NULL;

		    if(i == 0)
		    {
			//To link subnode to main node
			main_new -> s_link = sub_new;	//first time only
		    }
		    else
		    {
			s_temp -> sub_link = sub_new;	//Remaining times
		    }

		    //update mainnode members
		    strcpy(sub_new -> file_name, strtok(NULL, ";"));	//To get the filename from backup file

		    //Run the Loop for Comparing backupfiles with list filenames, if equal free node from the list
		    Slist *temp = *head;
		    Slist *prev = NULL;
		    while(temp != NULL)
		    {
			//comparing the subnode file with list
			if(strcmp(sub_new -> file_name, temp -> f_name) == 0)
			{
			    if(prev == NULL)
			    {
				*head = temp -> link;
				free(temp);	//free the node
				temp = *head;
				continue;
			    }
			    else
			    {
				prev -> link = temp -> link;
				free(temp);	//free the node
				temp = prev -> link;
				continue;
			    }
			}
			prev = temp;
			temp = temp -> link;	//Move to the next nodee
		    }
		    sub_new -> word_count = atoi(strtok(NULL, ";"));
		    s_temp = sub_new;
		}
	    }
	    //if arr[index] not equal to NULL
	    else
	    {
		m_node *m_temp = arr[index];	//assign temp equal to arrindex addrr
		m_node *m_prev = NULL;
		while(m_temp != NULL)
		{
		    m_prev = m_temp;		//update varibales
		    m_temp = m_temp -> m_link;
		}
		m_node *main_new = malloc(sizeof(m_node));
		if(main_new == NULL)
		{
		    printf("ERROR : Memory allocation failed for creating new mainnode.\n");
		    fclose(fptr);
		    return FAILURE;
		}

		//update mainnode members
		strcpy(main_new -> word, strtok(NULL, ";"));
		main_new -> file_count = atoi(strtok(NULL, ";"));
		m_prev -> m_link = main_new;

		s_node *s_temp = NULL;
		//Run the loop as file count times for creating subnodes 
		for(i=0; i < main_new -> file_count; i++)
		{
		    //create subnode and update fields
		    s_node *sub_new = malloc(sizeof(s_node));
		    if(sub_new == NULL)
		    {
			printf("ERROR : Memory allocation failed for creating new subnode.\n");
			fclose(fptr);
			return FAILURE;
		    }

		    if(i == 0)
		    {
			//To link subnode to main node
			main_new -> s_link = sub_new;		//first time only
		    }
		    else
		    {
			s_temp->sub_link = sub_new;		//Remaining time only
		    }

		    //update subnode members
		    strcpy(sub_new -> file_name, strtok(NULL, ";"));	//To get the filename from backup file
		    Slist *temp = *head;
		    Slist *prev = NULL;

		    //Run the Loop for Comparing backupfiles with list filenames, if equal free node from the list
		    while(temp)
		    {
			//comparing the subnode file with linkedlist file
			if(strcmp(sub_new -> file_name, temp -> f_name) == 0)
			{
			    if(prev == NULL)
			    {
				*head = temp -> link;
				free(temp);	//Free the node
				temp = *head;
				continue;
			    }
			    else
			    {
				prev -> link = temp -> link;
				free(temp);
				temp = prev -> link;
				continue;
			    }
			}
			prev = temp;
			temp = temp -> link;	
		    }
		    sub_new -> word_count = atoi(strtok(NULL, ";"));	//to make the string to int we use atoi
		    s_temp = sub_new;
		}
	    }
	}
    }
    fclose(fptr);
    return SUCCESS;
}
