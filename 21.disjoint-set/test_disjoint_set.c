#include "disjoint_set.h"

#include <stdio.h>

#define EDGE_LENGTH 7

int main() {
    struct linked_list_disjoint_set_node nodes[10];
    struct linked_list_disjoint_set_rep *reps[10];
    for (int i = 0; i < 10; i++)
    {
        nodes[i].element = 'a' + i;
        nodes[i].next = NULL;
        nodes[i].set = NULL;
        
        // Make set
        reps[i] = make_set(&nodes[i]);
    }

    // Edges
    struct linked_list_disjoint_set_node *in_nodes[EDGE_LENGTH];
    struct linked_list_disjoint_set_node *out_nodes[EDGE_LENGTH];

    // Handle edge
    in_nodes[0] = &nodes['b' - 'a'];    out_nodes[0] = &nodes['d' - 'a'];
    in_nodes[1] = &nodes['e' - 'a'];    out_nodes[1] = &nodes['g' - 'a'];
    in_nodes[2] = &nodes['a' - 'a'];    out_nodes[2] = &nodes['c' - 'a'];
    in_nodes[3] = &nodes['h' - 'a'];    out_nodes[3] = &nodes['i' - 'a'];
    in_nodes[4] = &nodes['a' - 'a'];    out_nodes[4] = &nodes['b' - 'a'];
    in_nodes[5] = &nodes['e' - 'a'];    out_nodes[5] = &nodes['f' - 'a'];
    in_nodes[6] = &nodes['b' - 'a'];    out_nodes[6] = &nodes['c' - 'a'];

    for (int i = 0; i < EDGE_LENGTH; i++)
    {
        struct linked_list_disjoint_set_rep *in_rep = find_set(in_nodes[i]);
        struct linked_list_disjoint_set_rep *out_rep = find_set(out_nodes[i]);
        if (in_rep != out_rep)
        {
            // union_set(in_rep, out_rep);
            union_set_heuristic(in_rep, out_rep);
        }
        // printf("After %c, %c:\n", in_nodes[i]->element, out_nodes[i]->element);
        // for (int i = 0; i < 10; i++) {
        //     struct linked_list_disjoint_set_node *node = reps[i]->head;
        //     printf("( ");
        //     while (node != NULL) {
        //         printf("%c ", node->element);
        //         node = node->next;
        //     }
        //     printf(")\n");
        // }
    }

    // Clear representative
    for (int i = 0; i < 10; i++) {
        struct linked_list_disjoint_set_node *node = reps[i]->head;
        printf("( ");
        while (node != NULL) {
            printf("%c ", node->element);
            node = node->next;
        }
        printf(")\n");
        free(reps[i]);
    }

    return 0;
}

