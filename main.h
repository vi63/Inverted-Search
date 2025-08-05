#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define SIZE 25
#define MAX_LENGTH_SIZE 100
#define ALPHA_SIZE 26

typedef enum
{
    FAILURE,
    SUCCESS
}Status;

typedef struct node
{
    char f_name[SIZE];
    struct node *link;
}Slist;

typedef struct sub_node
{
    int word_count;
    char file_name[SIZE];
    struct sub_node *sub_link;
}s_node;

typedef struct main_node
{
    int file_count;
    char word[SIZE];
    struct main_node *m_link;
    struct sub_node *s_link;
}m_node;

/* Function Prototypes */

/* Read and validate args from argv */
Status validate_args(Slist **head, char *argv[]);

/* Checking any duplicate files passed in CLA */
Status check_duplicate(Slist **head, char *filename);

/* Insert node into the list */
Status insert_at_last(Slist **head, char* filename);

/* To Create database */
Status create_database(m_node *arr[], Slist ** head);

/* To find the index position */
int find_index(char ch);

/* Creating Mainnode in the DB */
m_node *create_Main_node(char word[]);

/* Creating Subnode in the DB */
s_node *create_Sub_node(char filename[]);

/* To Display the database */
Status display_database(m_node *arr[]);

/* To Search the database */
Status search_database(m_node *arr[]);

void disp_sub_node(s_node * sub_node, int *total_files);

/* To Save the database to any file */
Status save_database(m_node *arr[]);

/* To Update the database from backup file */
Status update_database(m_node *arr[], Slist **head);


