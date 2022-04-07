/* 
 * Developed by R. E. Bryant, 2017
 * Extended to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q =  malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL){
      return NULL;
    }

    // Instantiates all the properties of our queue
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
  // Cannot operate on a null q, so check that first
  if (q == NULL){
    return;
  }

  // Make a temporary node used to traverse through the list
  list_ele_t *currNode = q->head;
  /* How about freeing the list elements and the strings? */
  while (currNode != NULL){
    // Access the next node while we still can.
    list_ele_t *prevNode = currNode;
    currNode = currNode->next;

    // make sure that the string inside is not null, then free it
    if (prevNode->value != NULL){
      free(prevNode->value);
    }
    // free our prev node and its pointers
    free(prevNode);
  }
  /* Free queue structure */
  free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    // return false is the queue is NULL
    if (q == NULL){
      return false;
    }

    // In case of failed newh malloc, return false
    list_ele_t *newNode;
    newNode = malloc(sizeof(list_ele_t));
    if (newNode == NULL){
      return false;
    }

    /* Don't forget to allocate space for the string and copy it */
    // If this fails we need to free newh, otherwise we will get an error
    char* data = (char*)malloc((strlen(s) + 1) * sizeof(char));
    if (data == NULL){
      free(newNode);
      return false;
    }
    strcpy(data, s);
    newNode->value = data;

    // If there is only one element, set tail to point to this node
    if (q->head == NULL){
      q->tail = newNode;
      newNode->next = NULL;
    }else{
      // Sets our new node as the head, and links it to the old head
      newNode->next = q->head;
    }
    q->head = newNode;
    q->size += 1;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */

    // If either arugment is NULL
    if (q == NULL || s == NULL){
      return false;
    }

    // Creates a new node and allocates its memory. Returns false if malloc fails
    list_ele_t *newNode;
    newNode = malloc(sizeof(list_ele_t));
    if (newNode == NULL){
      return false;
    }

    // Creates a temporary string with the size of the argument
    char* data = (char*)malloc((strlen(s)+1) * sizeof(char));
    if (data == NULL)
    {
      free(newNode);
      return false;
    }
    // Copies argument string into our temporary variable and sets the node value to that string
    strcpy(data, s);
    newNode->value = data;


    // We have to account for an empty queue
    if (q->tail == NULL){
      q->head = newNode;
    }else{
      q->tail->next = newNode;
    }
    
    newNode->next = NULL;
    q->tail = newNode;
    q->size += 1;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if (q == NULL || q->head == NULL){
      return false;
    }

    // If sp is non-NULL, copy string to be removed to sp. bufsize-1 is the upper bound for our string, 
    // so we also need to append a null terminator ourselves
    if (sp != NULL){
      strncpy(sp, q->head->value, bufsize-1);
      *(sp + bufsize -1) = '\0';
    }

    // Create a tempNode to hold our removed node
    list_ele_t *tempNode;
    // circumvent the old head by setting the queue head to the next node
    tempNode = q->head;
    q->head = q->head->next;
    // free the values of the old head
    if (tempNode->value != NULL){
      free(tempNode->value);
    }
    free(tempNode);
    q->size -= 1;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (q == NULL)
      return 0;
    else
      return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    // Checks if queue is NULL or empty
    if (q == NULL || q->head == NULL){
      return;
    }

    list_ele_t *tempNode, *prevNode, *nextNode;
    // set our three node variables
    tempNode = q->head->next;
    prevNode = q->head;

    // Switch the head and tail as step 1
    q->head->next = NULL;
    q->tail = q->head;

    // Starting at the head, make tempNode point to the node before it until tempNode is at the end of the queue
    while (tempNode != NULL){
      nextNode = tempNode->next;
      tempNode->next = prevNode;
      prevNode = tempNode;
      tempNode = nextNode;
    }

    // Makes sure the head is set to the new head of the reversed queue
    q->head = prevNode;

}

