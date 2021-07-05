
#include <stdlib.h>

/* Linked list implementation */
struct linked_list_disjoint_set_node;

// Representative
struct linked_list_disjoint_set_rep {
    size_t count;
    struct linked_list_disjoint_set_node *head;
    struct linked_list_disjoint_set_node *tail;
};

// Node
struct linked_list_disjoint_set_node
{
    struct linked_list_disjoint_set_rep *set;
    char element;
    struct linked_list_disjoint_set_node *next;
};

// Make a set
struct linked_list_disjoint_set_rep *make_set(struct linked_list_disjoint_set_node *ele)
{
    struct linked_list_disjoint_set_rep *rep = (struct linked_list_disjoint_set_rep *)
        malloc(sizeof(struct linked_list_disjoint_set_rep));
    rep->head = ele;
    rep->tail = ele;

    ele->next = NULL;
    ele->set = rep;

    // Rep count
    rep->count = 1;

    return rep;
}

// Find we are in which set
struct linked_list_disjoint_set_rep *find_set(struct linked_list_disjoint_set_node *ele)
{
    return ele->set;
}

// Union two sets
struct linked_list_disjoint_set_rep *union_set(
    struct linked_list_disjoint_set_rep *a,
    struct linked_list_disjoint_set_rep *b)
{
    struct linked_list_disjoint_set_node *node = b->head;
    // O(n)
    while (node != b->tail)
    {
        node->set = a;
        node = node->next;
    }
    a->tail->next = b->head;
    a->tail = b->tail;
    
    b->head = NULL;
    b->tail = NULL;

    return a;
}

// Heuristic methods
// Union two sets
struct linked_list_disjoint_set_rep *union_set_heuristic(
    struct linked_list_disjoint_set_rep *_a,
    struct linked_list_disjoint_set_rep *_b)
{
    size_t count_a = _a->count;
    size_t count_b = _b->count;

    if (count_a == 0) return _b;
    if (count_b == 0) return _a;

    // Assume a is the longer one
    struct linked_list_disjoint_set_rep *b = (count_a >= count_b ? _b : _a);
    struct linked_list_disjoint_set_rep *a = (count_a >= count_b ? _a : _b);

    struct linked_list_disjoint_set_node *node = b->head;
    // O(n)
    while (node != b->tail)
    {
        node->set = a;
        node = node->next;
    }
    a->tail->next = b->head;
    a->tail = b->tail;
    
    b->head = NULL;
    b->tail = NULL;

    a->count = count_a + count_b;
    b->count = 0;

    return a;
}
