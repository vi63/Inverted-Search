#include "main.h"

//To save the database into a file
Status save_database(m_node * arr[])
{
    int i;
    char filename[SIZE];
    FILE *fptr;
    printf("Enter Filename to save DB : ");
    scanf("%s", filename);

    //Open a file in write mode
    fptr = fopen(filename, "w");
    if(fptr == NULL)
    {
	printf("ERROR : Unable to open the file.\n");
	return FAILURE;
    }

    //Traverse through the array
    m_node *main_temp = NULL;
    s_node *sub_temp = NULL;
    for(i = 0; i <= ALPHA_SIZE; i++)	//Run the loop upto alpha_size = 26 times
    {
	//writing main node datas
	main_temp = arr[i];
	while(main_temp != NULL)
	{
	    fprintf(fptr, "#%d;%s;%d;", i, main_temp -> word, main_temp -> file_count);

	    //writing sub node datas
	    sub_temp = main_temp -> s_link;
	    if(sub_temp != NULL)
	    {
		fprintf(fptr, "%s;%d", sub_temp -> file_name, sub_temp -> word_count);
		sub_temp = sub_temp -> sub_link;
	    }

	    //writing remaining subnodes datas
	    while(sub_temp != NULL)
	    {
		fprintf(fptr, ";%s;%d", sub_temp -> file_name, sub_temp -> word_count);
		sub_temp = sub_temp -> sub_link;
	    }

	    fprintf(fptr, "#\n");	//end with #
	    main_temp = main_temp -> m_link;
	}
    }
    fclose(fptr);
    printf("Database saved successfully to %s.\n", filename);
    return SUCCESS;
}
