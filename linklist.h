/**
 * Linked List Library
 * 
 *@file linklist.h 
 * @author Ella Stumpe
 * @date Thursday Dec 14th, 2023.
 * 
*/


#include <stdbool.h>

/**
 * 
 * A node in a linked list.
 * 
 * 
 * 
*/

typedef struct node
{
    int value;/** <the value stored in the node */
    struct node *next;/** < pointer to the next node in the list */
} Node;

void print_list(Node *head);
Node *insert_at_head(Node *head, int new_value);
Node *insert_at_tail(Node *head, int new_value);
Node *deleteHeadNode(Node *head);
Node *deleteTail(Node *head);
int length(Node *head);
int recursive_length(Node *node);
int count_matches(Node *node, int find_value);
bool found(Node *node, int search_value);
void replace_matches(Node *node, int find_value, int replace_value);
Node *delete_first_match(Node *head, int delete_value, bool *was_deleted);
Node *delete_all_matches(Node *head, int delete_value, int *num_deleted);
Node *efficient_delete_match(Node *head, int delete_value, int *num_deleted);
Node *append_list(Node *head1, Node *head2);
Node *reverse_list(Node *head);
void sort_list(Node *head);
void delete_duplicates(Node *head);
Node *insert_after(Node *head, int new_value, int after_value);
Node *delete_list(Node *node);
void add_lists(Node *list1, Node *list2);
Node *duplicate_list(Node *node);
Node *merge_sorted_lists(Node *list1, Node *list2);