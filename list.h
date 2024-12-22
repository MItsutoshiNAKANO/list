#ifndef LIST_H
#define LIST_H 1

#include <stdlib.h>

/// @brief List node.
struct list {
    struct list *next;
    struct list *prev;
    size_t size;
    void *data;
};

/// @brief List comparison operator.
enum list_comparison_operator {
    LIST_CMP_LT = 1,
    LIST_CMP_EQ,
    LIST_CMP_LE,
    LIST_CMP_GT,
    LIST_CMP_NE,
    LIST_CMP_GE
};

struct list *create_empty_list(void);
struct list *push_into_list(struct list *head, size_t size, const void *data);
struct list *
unshift_into_list(struct list *head, size_t size, const void *data);
struct list *pop_from_list(struct list *head);
struct list *pick_not_sorted_from_part_of_list(
    struct list *start, struct list *end, int (*cmp)(const void *, const void *)
);
struct list *pick_not_sorted_from_list(
    struct list *head, int (*cmp)(const void *, const void *)
);
struct list *get_min_from_part_of_list(
    struct list *start, struct list *end, int (*cmp)(const void *, const void *)
);
struct list *
get_min_from_list(struct list *head, int (*cmp)(const void *, const void *));
struct list *get_max_from_part_of_list(
    struct list *start, struct list *end, int (*cmp)(const void *, const void *)
);
struct list *
get_max_from_list(struct list *head, int (*cmp)(const void *, const void *));
struct list *remove_from_list(struct list *head, struct list *node);
struct list *
free_from_list(struct list *head, struct list *node, void (*free_data)(void *));
struct list *insert_into_sorted_list(
    struct list *head, size_t size, const void *data,
    int (*cmp)(const void *, const void *)
);
struct list *find_from_list(
    struct list *head, void *data, int (*cmp)(const void *, const void *),
    enum list_comparison_operator op, long long n
);
void free_list(struct list *head, void (*free_data)(void *));

#endif // End of `ifndef LIST_H`
