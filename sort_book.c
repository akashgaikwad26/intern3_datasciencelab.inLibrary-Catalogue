#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Merge two sorted lists
struct Book* merge(struct Book* left, struct Book* right, int (*compare)(struct Book*, struct Book*)) {
    if (!left) return right;
    if (!right) return left;
    if (compare(left, right) <= 0) {
        left->next = merge(left->next, right, compare);
        return left;
    } else {
        right->next = merge(left, right->next, compare);
        return right;
    }
}

// Split list
void split(struct Book* source, struct Book** left, struct Book** right) {
    struct Book *fast = source->next, *slow = source;
    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    *left = source;
    *right = slow->next;
    slow->next = NULL;
}

// Merge Sort
struct Book* merge_sort(struct Book* head, int (*compare)(struct Book*, struct Book*)) {
    if (!head || !head->next) return head;
    struct Book *left, *right;
    split(head, &left, &right);
    left = merge_sort(left, compare);
    right = merge_sort(right, compare);
    return merge(left, right, compare);
}

// Compare functions
int compare_title(struct Book* a, struct Book* b) { return strcasecmp(a->book_title, b->book_title); }
int compare_author(struct Book* a, struct Book* b) { return strcasecmp(a->author, b->author); }
int compare_year(struct Book* a, struct Book* b) { return a->publication_year - b->publication_year; }

// Sort Books
void sort_books() {
    if (!head) {
        printf("\nNo books to sort.\n");
        return;
    }
    int choice;
    printf("Sort by: 1. Title  2. Author  3. Year\nEnter choice: ");
    scanf("%d", &choice);

    int (*compare)(struct Book*, struct Book*) = 
        (choice == 1) ? compare_title : (choice == 2) ? compare_author : compare_year;
    
    head = merge_sort(head, compare);
    printf("Books sorted successfully.\n");
}

