#include "main.h"

// To display the database
Status display_database(m_node* arr[]) 
{
    printf("<---------------------- Displaying Database ------------------------>\n");
    printf("---------------------------------------------------------------------\n");
    printf("| Index |   Word        | File Count |  Filename       | Word Count |\n");
    printf("---------------------------------------------------------------------\n");

    for (int i = 0; i <= ALPHA_SIZE; i++)
    {
	m_node *temp1;		//Declaring pointer variables
	s_node *temp2;
	temp1 = arr[i];
	while (temp1 != NULL)
	{
	    printf("| %-6d| %-14s| %-11d| ", i, temp1 -> word, temp1 -> file_count);
	    temp2 = temp1->s_link;
	    int flag = 1; //set flag
	    while (temp2 != NULL)
	    {
		if (!flag)
		{
		    // Print empty columns, word_count and file_count 
		    printf("|       |               |            | ");
		}
		printf("%-16s| %-11d|\n", temp2 -> file_name, temp2 -> word_count);
		temp2 = temp2 -> sub_link;
		flag = 0; //clear the  flag
	    }
	    temp1 = temp1 -> m_link;
	}
    }
    printf("---------------------------------------------------------------------\n");
    return SUCCESS;
}
