/// @file
/// @brief List implementation.

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

/// @brief Create an empty list.
struct list *
create_empty_list(void)
{
    struct list *head = calloc(1, sizeof(struct list));
    if (head == NULL) {
        return NULL;
    }
    head->next = head->prev = head;
    head->data = NULL;
    return head;
}

/// @brief Push a node to the list.
/// @param head List head.
/// @param size Size of the data.
/// @param data Data to add.
/// @return Pointer to the new node.
struct list *
push_into_list(struct list *head, size_t size, const void *data)
{
    struct list *adding = calloc(1, sizeof(struct list));
    if (adding == NULL) {
        return NULL;
    }
    if ((adding->data = malloc(size)) == NULL) {
        free(adding);
        return NULL;
    }
    memcpy(adding->data, data, size);
    adding->size = size;

    adding->next = head;
    adding->prev = head->prev;
    head->prev->next = adding;
    head->prev = adding;

    return adding;
}

/// @brief Unshift a node to the list.
/// @param head List head.
/// @param size Size of the data.
/// @param data Data to add.
/// @return Pointer to the new node.
struct list *
unshift_into_list(struct list *head, size_t size, const void *data)
{
    struct list *adding = calloc(1, sizeof(struct list));
    if (adding == NULL) {
        return NULL;
    }
    if ((adding->data = malloc(size)) == NULL) {
        free(adding);
        return NULL;
    }
    memcpy(adding->data, data, size);
    adding->size = size;

    adding->next = head->next;
    adding->prev = head;
    head->next->prev = adding;
    head->next = adding;

    return adding;
}

struct list *
pop_from_list(struct list *head)
{
    if (head->prev == head) {
        return NULL;
    }
    struct list *popped = head->prev;
    head->prev = popped->prev;
    popped->prev->next = head;
    return popped;
}

/// @brief Pick a node that is not sorted.
/// @param start Start node.
/// @param end End node.
/// @param cmp Comparison function.
/// @return The first node that is not sorted.
struct list *
pick_not_sorted_from_part_of_list(
    struct list *start, struct list *end, int (*cmp)(const void *, const void *)
)
{
    for (struct list *current = start; current != end;
         current = current->next) {
        if (cmp(current->data, current->next->data) > 0) {
            return current;
        }
    }
    return NULL;
}

/// @brief Pick a node that is not sorted.
/// @param head List head.
/// @param cmp Comparison function.
/// @return
///   If the list is sorted, return NULL;
///   otherwise, return the first node that is not sorted.
struct list *
pick_not_sorted_from_list(
    struct list *head, int (*cmp)(const void *, const void *)
)
{
    return pick_not_sorted_from_part_of_list(head->next, head->prev, cmp);
}

/// @brief Get the minimum node from the part of the list.
/// @param start Start node.
/// @param end End node.
/// @param cmp Comparison function.
/// @return The minimum node.
struct list *
get_min_from_part_of_list(
    struct list *start, struct list *end, int (*cmp)(const void *, const void *)
)
{
    struct list *min = start;
    for (struct list *current = start->next; current != end;
         current = current->next) {
        if (cmp(current->data, min->data) < 0) {
            min = current;
        }
    }
    return min;
}

/// @brief Get the minimum node from the list.
/// @param head List head.
/// @param cmp Comparison function.
/// @return The minimum node.
struct list *
get_min_from_list(struct list *head, int (*cmp)(const void *, const void *))
{
    return get_min_from_part_of_list(head->next, head->prev, cmp);
}

/// @brief Get the maximum node from the part of the list.
/// @param start Start node.
/// @param end End node.
/// @param cmp Comparison function.
/// @return The maximum node.
struct list *
get_max_from_part_of_list(
    struct list *start, struct list *end, int (*cmp)(const void *, const void *)
)
{
    struct list *max = start;
    for (struct list *current = end->prev; current != start;
         current = current->prev) {
        if (cmp(current->data, max->data) > 0) {
            max = current;
        }
    }
    return max;
}

/// @brief Get the maximum node from the list.
/// @param head List head.
/// @param cmp Comparison function.
/// @return The maximum node.
struct list *
get_max_from_list(struct list *head, int (*cmp)(const void *, const void *))
{
    return get_max_from_part_of_list(head->next, head->prev, cmp);
}

/// @brief Remove a node from the list.
/// @param head List head.
/// @param node Target node.
/// @return If the node is found, return the node; otherwise, return NULL.
struct list *
remove_from_list(struct list *head, struct list *node)
{
    for (struct list *current = head->next; current != head;
         current = current->next) {
        if (current == node) {
            current->prev->next = current->next;
            current->next->prev = current->prev;
            return current;
        }
    }
    return NULL;
}

/// @brief Free a node from the list.
/// @param head List head.
/// @param node Target node.
/// @param free_data Function to free the data.
/// @return If the node is found, return the head; otherwise, return NULL.
struct list *
free_from_list(struct list *head, struct list *node, void (*free_data)(void *))
{
    struct list *removed = remove_from_list(head, node);
    if (removed == NULL) {
        return NULL;
    }
    free_data(removed->data);
    removed->data = NULL;
    free(removed);
    return head;
}

/// @brief Insert a node into the sorted list.
/// @param head List head.
/// @param size Size of the data.
/// @param data Data to insert.
/// @param cmp Comparison function.
/// @return Pointer to the new node.
struct list *
insert_into_sorted_list(
    struct list *head, size_t size, const void *data,
    int (*cmp)(const void *, const void *)
)
{
    struct list *adding = calloc(1, sizeof(struct list));
    if (adding == NULL) {
        return NULL;
    }
    if ((adding->data = malloc(size)) == NULL) {
        free(adding);
        return NULL;
    }
    memcpy(adding->data, data, size);
    adding->size = size;

    struct list *current;
    for (current = head->prev; current != head && cmp(data, current->data) < 0;
         current = current->prev) {
        // Empty loop body.
    }

    adding->next = current->next;
    adding->prev = current;
    current->next->prev = adding;
    current = adding;

    return adding;
}

/// @brief Find a node in the list.
/// @param head List head.
/// @param size Size of the data.
/// @param data Data to find.
/// @param cmp Comparison function.
/// @param op Comparison operator.
/// @param n Number of nodes to skip.
/// @return Pointer to the found node.
struct list *
find_from_list(
    struct list *head, void *data, int (*cmp)(const void *, const void *),
    enum list_comparison_operator op, long long n
)
{
    long long counter = 0;
    for (struct list *current = head->next; current != head;
         current = current->next) {
        int result = cmp(current->data, data);
        if ((result < 0 &&
             (op == LIST_CMP_LT || op == LIST_CMP_LE || op == LIST_CMP_NE)) ||
            (result > 0 &&
             (op == LIST_CMP_GT || op == LIST_CMP_GE || op == LIST_CMP_NE)) ||
            (op == LIST_CMP_EQ || op == LIST_CMP_LE || op == LIST_CMP_GE)) {
            ++counter;
        }
        if (counter >= n) {
            return current;
        }
    }
    return NULL;
}

/// @brief Remove a node from the list.
/// @param head List head.
/// @param free_data Function to free the data.
void
free_list(struct list *head, void (*free_data)(void *))
{
    for (struct list *current = head->prev; current != head;) {
        free_data(current->data);
        struct list *two_spots_ahead = current->prev;
        free(current);
        current = two_spots_ahead;
    }
    head->next = head->prev = NULL;
    free(head);
}
