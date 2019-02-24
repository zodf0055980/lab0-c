/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (q == NULL)  // dont malloc success
        return 0;
    q->size = 0;
    q->head = NULL;
    q->tail = NULL;  // point to NULL space
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (q != NULL) {
        list_ele_t *temp;
        list_ele_t *p = q->head;
        while (p != NULL) {
            temp = p;
            p = p->next;
            free(temp->value);
            free(temp);
        }
        free(q);
    }
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
    /* What should you do if the q is NULL? */
    if (q == NULL)  // q is NULL
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (newh == NULL)
        return false;
    // int len = sizeof(s) + 1;  // '/0' so +1
    int len = strlen(s) + 1;
    char *val = malloc(len * sizeof(char));
    if (val == NULL) {
        free(newh);
        return false;
    }
    memset(val, 0, len);
    strncpy(val, s, len - 1);
    newh->next = q->head;
    newh->value = val;

    if (q->head == NULL) {  // q dont have element
        q->tail = newh;
        q->head = newh;
    } else {
        newh->next = q->head;
        q->head = newh;
    }
    q->size++;

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
    if (q == NULL)  // q is NULL
        return false;
    list_ele_t *newh;
    newh = malloc(sizeof(list_ele_t));
    if (newh == NULL)
        return false;
    // int len = sizeof(s) + 1;  // '/0' so +1
    int len = strlen(s) + 1;
    char *val = malloc(len * sizeof(char));
    if (val == NULL) {
        free(newh);
        return false;
    }

    memset(val, 0, len);
    strncpy(val, s, len - 1);

    newh->value = val;
    newh->next = NULL;
    if (q->head == NULL) {  // q dont have element
        q->tail = newh;
        q->head = newh;
    } else {
        q->tail->next = newh;
        q->tail = newh;
    }
    q->size++;

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
    if (q == NULL || q->head == NULL)
        return false;

    list_ele_t *nexte = q->head;

    if (sp) {
        memset(sp, '\0', bufsize);
        strncpy(sp, nexte->value, bufsize - 1);
    }
    q->head = q->head->next;
    free(nexte->value);
    free(nexte);
    q->size--;

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
    if (q != NULL)
        return q->size;
    return 0;
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

    if (q == NULL || q->head == NULL || q->head->next == NULL)
        return;

    list_ele_t *a = NULL;
    list_ele_t *b = q->head;
    list_ele_t *c;
    list_ele_t *temp = q->head;

    while (b != NULL) {
        c = a;
        a = b;
        b = b->next;
        a->next = c;
    }
    q->head = a;
    q->tail = temp;
}
