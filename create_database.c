#include "main.h"

// Function to create a database
Status create_database(m_node *arr[], Slist  ** head)
{
    if(*head == NULL)	//Error handling 
    {
	printf("ERROR: Linked list is empty.\n");
	return FAILURE;
    }	       
    FILE *fptr;
    int index;
    char word[SIZE];
    Slist * temp = *head;	//Initialize temp pointer variable with head address
    while(temp != NULL)
    {
	// Open the file in read mode
	fptr = fopen(temp -> f_name, "r");
	if (fptr == NULL)	//Error handling 
	{
	    printf("ERROR: Unable to open the file --> %s\n", temp -> f_name);
	    return FAILURE;
	}
	// Read each word from the file 
	while (fscanf(fptr, "%s", word) != EOF) 
	{
	    //To find the index 
	    index = find_index(word[0]);
	    m_node *m_node_temp = arr[index];

	    //If matching main node found for word
	    while(m_node_temp != NULL && strcmp(m_node_temp -> word, word) != 0)	//Check if the words are equal
	    {
		m_node_temp = m_node_temp -> m_link;	//moving to next main node
	    }

	    // Create main node if not found
	    if (m_node_temp == NULL)
	    {
		m_node_temp = create_Main_node(word);	//Calling a function to create a new main node
		if (m_node_temp == NULL)
		{
		    fclose(fptr);
		    return FAILURE;
		}

		//update
		m_node_temp -> m_link = arr[index];
		arr[index] = m_node_temp;
	    }

	    //If matching sub node found for filename
	    s_node * s_node_temp = m_node_temp -> s_link;
	    while (s_node_temp != NULL && strcmp(s_node_temp -> file_name, temp -> f_name) != 0 )
	    {
		s_node_temp = s_node_temp -> sub_link;      //moving to next subnode
	    }

	    // Create subnode if not found
	    if (s_node_temp == NULL)
	    {
		s_node_temp = create_Sub_node(temp->f_name);	//Calling a function to create a new sub node
		if (s_node_temp == NULL)
		{
		    fclose(fptr);
		    return FAILURE;
		}

		//Update
		s_node_temp->sub_link = m_node_temp->s_link;
		m_node_temp->s_link = s_node_temp;
		m_node_temp->file_count++;
	    }
	    s_node_temp -> word_count++;	//Increment the word count
	}
	temp = temp -> link;    //move to the next file in the list
	fclose(fptr);	//free the memory
    }
    return SUCCESS;
}
