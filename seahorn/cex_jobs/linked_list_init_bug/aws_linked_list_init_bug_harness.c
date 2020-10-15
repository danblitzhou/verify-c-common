#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include "nondet.h"
#include <stdio.h>

// build trivial head--front--tail linked list
void old_sea_nd_init_aws_linked_list(struct aws_linked_list *list, size_t *len)
{
    list->head.next = &list->tail;
    list->head.prev = NULL;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
    size_t nd_len = 1;
    *len = nd_len;

    struct aws_linked_list_node *front;
    front = malloc(sizeof(struct aws_linked_list_node));
    list->head.next = front;
    front->prev = &list->head;
    front->next = &list->tail;
    list->tail.prev = front;
}

int main(void) {
    /* data structure */
    struct aws_linked_list list;
    size_t length;
    old_sea_nd_init_aws_linked_list(&list, &length);
    // sassert(aws_linked_list_node_next_is_valid(&list.head));
    sassert(&list.head != NULL && list.head.next != NULL);
    sassert(list.head.next->prev == &list.head);
    printf("LHS: %p \n", list.head.next->prev);
    printf("RHS: %p \n", &list.head);
}
