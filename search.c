#include "main.h"

// Func to search in the database
Status search_database(m_node *arr[])
{
    char key[SIZE]; //Declare an array
    int  total_files = 0;
    int index;

    printf("Enter the word to search : "); 
    scanf("%s", key);//it defines the word which the user wants to search
    index = find_index(key[0]);	
    //Directly assign index pos 26 for punctuations
    m_node *temp = arr[index];

    // Traverse through the list
    while (temp != NULL)
    {
	if (strcasecmp(temp -> word, key) == 0)
	{
	    printf("Word --> '%s' found in the database.\n", key);
	    disp_sub_node(temp -> s_link, &total_files);	//calling a function to check if words present in subnodes or not
	    printf("\nThe  word is  found in %d file.\n", total_files);
	    return SUCCESS;
	}
	temp = temp -> m_link;
    }

    // Key not found
    printf("Word --> '%s' not found in the database.\n", key);
    return FAILURE;
}

//To display the filename and word count of the word
void disp_sub_node(s_node * sub_node, int *total_files)
{
    printf("------------------------------------------\n");
    printf("| %-20s | %-15s |\n", "File Name", "Word Count");
    printf("------------------------------------------\n");
    while(sub_node != NULL)
    {
	printf("| %-20s | %-15d |\n", sub_node->file_name, sub_node->word_count);
	(*total_files)++;
	sub_node = sub_node -> sub_link;	//Move to next subnode
    }
    printf("------------------------------------------\n");
}
