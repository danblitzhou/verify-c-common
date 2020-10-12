#include <seahorn/seahorn.h>
#include <aws/common/linked_list.h>
#include <linked_list_helper.h>
#include "nondet.h"
#include <stdio.h>

void old_sea_nd_init_aws_linked_list(struct aws_linked_list *list, size_t *len)
{
    list->head.next = &list->tail;
    list->head.prev = NULL;
    list->tail.prev = &list->head;
    list->tail.next = NULL;
    /*
    list:
    head<-->front-->nd_ptr ... nd_ptr <--tail
    */
    // size_t nd_len = nd_size_t();
    size_t nd_len = 1;
    // assume(nd_len >= 1);
    *len = nd_len;

    struct aws_linked_list_node *front;
    front = malloc(sizeof(struct aws_linked_list_node));
    list->head.next = front;
    front->prev = &list->head;
    front->next = &list->tail;
    list->tail.prev = front;
    // if (nd_len == 1) {
    //     front->next = &list->tail;
    //     list->tail.prev = front;
    // } else {
    //     front->next = nd_voidp();
    //     list->tail.prev = nd_voidp();
    // }
}

int main(void) {
    /* data structure */
    struct aws_linked_list list;
    
    size_t length;
    old_sea_nd_init_aws_linked_list(&list, &length);
    // sassert(aws_linked_list_node_next_is_valid(&list.head));
    sassert(list.head.next->prev == &list.head);
    printf("LHS: %p \n", list.head.next->prev);
    printf("RHS: %p \n", &list.head);
    // sassert(list.tail.prev->next == &list.tail);

}
