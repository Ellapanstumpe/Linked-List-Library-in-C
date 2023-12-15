/**
 * Linked List Library
 * @file linklist.c
 * @author Ella Stumpe
 * @date Thursday Dec 14,2023
 */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "linklist.h"

/**
 * Merges two sorted lists into a single
 * sorted list in acending order
 *
 * @param pointer to head of first list
 * @param pointer to head of the second list
 * @return pointer to head of merged list
 *
 */

Node *merge_sorted_lists(Node *list1, Node *list2)
{
    if (list1 == NULL)
        return list2;
    if (list2 == NULL)
        return list1;

    Node *l1current, *l2current;
    Node *new_head, *newcurrent;

    l1current = list1;
    l2current = list2;

    if (l1current->value <= l2current->value)
    {
        new_head = l1current;
        l1current = l1current->next;
    }
    else
    {
        new_head = l2current;
        l2current = l2current->next;
    }
    newcurrent = new_head;

    while (l1current != NULL && l2current != NULL)
    {
        if (l1current->value <= l2current->value)
        {
            newcurrent->next = l1current;
            newcurrent = l1current;
            l1current = l1current->next;
        }
        else
        {
            newcurrent->next = l2current;
            newcurrent = l2current;
            l2current = l2current->next;
        }
    }

    if (l1current == NULL)
    {

        newcurrent->next = l2current;
    }
    else if (l2current == NULL)
    {
        newcurrent->next = l1current;
    }

    return new_head;
}

void add_lists(Node *list1, Node *list2)
{
    if (list1 == NULL || list2 == NULL)
        return;
    list1->value = list1->value + list2->value;
    add_lists(list1->next, list2->next);
}

Node *duplicate_list(Node *node)
{

    if (node == NULL)
        return NULL;

    Node *new_node = calloc(sizeof(node), 1);

    new_node->value = node->value;
    new_node->next = duplicate_list(node->next);
    return new_node;
}

Node *delete_list(Node *node)
{
    if (node != NULL)
    {
        delete_list(node->next);
        free(node);
    }

    return NULL;
}

Node *insert_after(Node *head, int new_value, int after_value)
{
    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = new_value;

    if (head == NULL)
        return new_node;
    else
    {
        Node *current = head;
        while (current->next != NULL)
        {
            if (current->value == after_value)
            {
                new_node->next = current->next;
                current->next = new_node;
                return head;
            }
            else
                current = current->next;
        }
        // If the tail is reached, insert new node at tail.
        new_node->next = current->next;
        current->next = new_node;
        return head;
    }
}

void delete_duplicates(Node *head)
{
    if (head == NULL)
        return;
    if (head->next == NULL)
        return;

    Node *listPointer, *valuePointer, *duplicate;
    listPointer = head;

    while (listPointer != NULL && listPointer->next != NULL)
    {
        // set value Pointer starts with listPointer
        valuePointer = listPointer;
        // As long as not reach the tail of list
        while (valuePointer->next != NULL)
        {
            if (listPointer->value == valuePointer->next->value)
            {

                duplicate = valuePointer->next;
                valuePointer->next = valuePointer->next->next;
                free(duplicate);
            }
            else
                valuePointer = valuePointer->next;
        }

        listPointer = listPointer->next;
    }
}

// Use bouble sort to sort the list
void sort_list(Node *head)
{
    if (head == NULL)
        return;
    if (head->next == NULL)
        return;

    bool swapped = false;
    do
    {
        swapped = false;
        Node *current = head;
        Node *prev = NULL;

        while (current->next != NULL)
        {
            prev = current;
            current = current->next;
            if (current != NULL)
            {
                if (current->value < prev->value)
                {
                    int temp = prev->value;
                    prev->value = current->value;
                    current->value = temp;
                    swapped = true;
                }
            }
        }
    } while (swapped);
}

Node *reverse_list(Node *head)
{
    if (head == NULL)
        return NULL;
    if (head->next == NULL)
        return head;

    Node *current = head;
    Node *next_node = head->next;

    current->next = NULL;

    while (next_node != NULL)
    {
        // initialize the pointer point to after next node
        Node *afterNext = next_node->next;
        // reset current pointer
        next_node->next = current;
        // move next node to current
        current = next_node;
        // set afterNext to next_node to loop through the list
        next_node = afterNext;
    }

    return current;
}

Node *append_list(Node *head1, Node *head2)
{
    if (head1 == NULL)
        return head2;

    Node *current = head1;
    while (current->next != NULL)
        current = current->next;
    current->next = head2;
    return head1;
}

Node *efficient_delete_match(Node *head, int delete_value, int *num_deleted)
{
    *num_deleted = 0;
    if (head == NULL)
        return NULL;

    Node *current, *temp, *new_head;
    current = head;
    while (current->value == delete_value)
    {
        temp = current;
        current = current->next;
        free(temp);
        *num_deleted = *num_deleted + 1;

        if (current == NULL)
            return NULL;
    }
    new_head = current;

    while (current->next != NULL)
    {
        if (current->next->value == delete_value)
        {
            temp = current->next;
            current->next = current->next->next;
            free(temp);
            *num_deleted = *num_deleted + 1;
        }
        else
            current = current->next;
    }

    return new_head;
}

Node *delete_all_matches(Node *head, int delete_value, int *num_deleted)
{
    Node *current = head;
    bool deleted = false;
    *num_deleted = 0;

    do
    {
        current = delete_first_match(current, delete_value, &deleted);

        if (deleted)
            *num_deleted = *num_deleted + 1;
    } while (deleted);

    return current;
}

bool found(Node *node, int search_value)
{
    if (node == NULL)
        return false;
    else if (node->value == search_value)
        return true;
    else
        return found(node->next, search_value);
}

Node *delete_first_match(Node *head, int delete_value, bool *was_deleted)
{
    if (head == NULL)
    {
        *was_deleted = false;
        return NULL;
    }

    if (head->value == delete_value)
    {
        Node *temp = head;
        free(head);
        *was_deleted = true;
        return temp;
    }

    Node *current = head->next;
    Node *prev = head;

    while (current != NULL)
    {
        if (current->value == delete_value)
        {
            prev->next = current->next;
            free(current);
            *was_deleted = true;
            return head;
        }
        prev = current;
        current = current->next;
    }
    *was_deleted = false;
    return head;
}

void replace_matches(Node *node, int find_value, int replace_value)
{
    if (node != NULL)
    {
        if (node->value == find_value)
            node->value = replace_value;

        replace_matches(node->next, find_value, replace_value);
    }
}

// Recursion
int recursive_length(Node *node)
{
    if (node == NULL)
        return 0;
    else
        return 1 + recursive_length(node->next);
}

int length(Node *head)
{
    Node *current;
    current = head;
    int length = 0;
    while (current != NULL)
    {
        length++;
        current = current->next;
    }
    return length;
}

Node *deleteTail(Node *head)
{
    if (head == NULL || head->next == NULL)
        return NULL;
    else
    {
        Node *current = head;
        Node *newTail = NULL;
        while (current->next != NULL)
        {
            newTail = current;
            current = current->next;
        }
        newTail->next = NULL;
        free(current);
        return head;
    }
}

Node *deleteHeadNode(Node *head)
{
    if (head == NULL)
        return NULL;
    else
    {
        Node *newHead = head->next;
        free(head);
        return newHead;
    }
}

Node *insert_at_tail(Node *head, int new_value)
{
    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = new_value;
    if (head == NULL)
        return new_node;
    else
    {
        Node *current = head;
        while (current->next != NULL)
            current = current->next;
        current->next = new_node;
        return head;
    }
}

Node *insert_at_head(Node *head, int new_value)
{
    Node *new_node = calloc(1, sizeof(Node));
    new_node->value = new_value;
    if (head == NULL)
        return new_node;
    else
    {
        new_node->next = head;
        return new_node;
    }
}

// Initialize print_list
void print_list(Node *head)
{
    // declear current pointer
    Node *current;
    current = head; // set current pointer to head
    int i = 0;      // Initialize node index

    while (current != NULL)
    {
        printf("Node %d: %d\n", i, current->value);
        i++;
        current = current->next;
    }
}