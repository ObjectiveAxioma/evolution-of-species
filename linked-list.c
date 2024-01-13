#include <stdio.h>
#include <stdlib.h>
#include "xmalloc.h"
#include "linked-list.h"

conscell *ll_push(conscell *list, void *data)
{
    conscell *new = xmalloc(sizeof *new);
    new->data = data;
    new->next = list;
    return new;
}

conscell *ll_pop(conscell *list)
{
    if (list == NULL) return NULL;
    
    conscell *node = list;
    void *data = node->data;
    list = node->next;
    free(node);
    
    return data;
}

void ll_free(conscell *list)
{
    if (list != NULL)
    {
        conscell *p = list->next;
        free(list);
        ll_free(p);
    }
}

conscell *ll_reverse(conscell *list)
{
    if (list == NULL) return NULL;
    
    conscell *prev = NULL;
    conscell *current = list;
    conscell *next = NULL;

    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    return prev;
}

conscell *ll_sort(conscell *list, int (*cmp)(const void *a, const void *b, void *params), void *params)
{
    conscell *list1 = NULL;
    conscell *list2 = NULL;
    conscell *p, *q, *head;
    if (list == NULL)
        return list;
    head = list;
    p = list-> next;
    while (p != NULL)
    {
        q = p->next;
        if (cmp(p->data, head->data, params) < 0)
        {
            p->next = list1;
            list1 = p;
        } else {
            p->next = list2;
            list2 = p;
        }
        p = q;
    }
    list1 = ll_sort(list1, cmp, params);
    list2 = ll_sort(list2, cmp, params);
    head->next = list2;

    if (list1 == NULL)
        return head;

    for (p = list1; p->next != NULL; p = p->next)
        ;

    p->next = head;
    return list1;
}

conscell *ll_filter(conscell *list, int (*filter)(const void *a), conscell **removed)
{
    if (list == NULL)
        return list;
    else if (filter(list->data))
    {
        conscell *p = list->next;
        list->next = *removed;
        *removed = list;
        return ll_filter(p, filter, removed);
    } else {
        list->next = ll_filter(list->next, filter, removed);
    }
}

int ll_length(conscell *list)
{
    int length = 0;
    if (list == NULL) return 0;

    conscell *current = list;
    while (current != NULL)
    {
        ++length;
        current = current->next;
    }

    return length;
}