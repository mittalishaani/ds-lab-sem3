#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for a circular doubly linked list
typedef struct Node {
    int data;
    struct Node *prev;
    struct Node *next;
} Node;


// Header node structure
typedef struct {
    int count; // Number of digits in the list
    Node *head; // Pointer to the first digit node
} CDLinkedList;

// Function to create a new list with a header node
CDLinkedList* createList() {
    CDLinkedList* list = (CDLinkedList*)malloc(sizeof(CDLinkedList));
    list->count = 0;
    list->head = NULL;
    return list;
}

// Function to insert a digit at the front (for easier representation)
void insertFront(CDLinkedList* list, int digit) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = digit;
    if (list->head == NULL) {
        newNode->next = newNode;
        newNode->prev = newNode;
        list->head = newNode;
    } else {
        Node* tail = list->head->prev;
        newNode->next = list->head;
        newNode->prev = tail;
        tail->next = newNode;
        list->head->prev = newNode;
    }
    list->count++;
}

// Function to add two circular doubly linked lists
CDLinkedList* addLists(CDLinkedList* list1, CDLinkedList* list2) {
    CDLinkedList* result = createList();
    Node *ptr1, *ptr2;

    // Using if-else to determine the starting point for ptr1
    if (list1->head) {
        ptr1 = list1->head->prev; // Start from the tail
    } else {
        ptr1 = NULL;
    }

    // Using if-else to determine the starting point for ptr2
    if (list2->head) {
        ptr2 = list2->head->prev; // Start from the tail
    } else {
        ptr2 = NULL;
    }

    int carry = 0;

    // Perform addition until all digits are processed or carry remains
    while (ptr1 != NULL || ptr2 != NULL || carry != 0) {
        int sum = carry;
        if (ptr1 != NULL) {
            sum += ptr1->data;
            ptr1 = (ptr1 == list1->head) ? NULL : ptr1->prev;
        }
        if (ptr2 != NULL) {
            sum += ptr2->data;
            ptr2 = (ptr2 == list2->head) ? NULL : ptr2->prev;
        }

        carry = sum / 10;
        int digit = sum % 10;
        insertFront(result, digit);
    }

    return result;
}

// Function to display the list in correct order
void displayList(CDLinkedList* list) {
    if (list->head == NULL) {
        printf("List is empty.\n");
        return;
    }

    Node* current = list->head;
    // Move to the head to start displaying
    while (current->next != list->head) {
        current = current->next;
    }

    // Now current is at the tail, print the digits from head to tail
    do {
        printf("%d", current->data);
        current = current->prev; // Move towards the head
    } while (current != list->head);

    printf("%d\n", current->data); // Print the head node's data
}

// Function to create a list from a string of digits
CDLinkedList* createListFromInput(const char* input) {
    CDLinkedList* list = createList();
    int length = strlen(input);
    for (int i = 0; i < length; i++) {
        // Convert character to integer
        int digit = input[i] - '0';
        insertFront(list, digit);
    }
    return list;
}

// Example usage
int main() {
    char input1[100], input2[100];

    // Get user input for the first number using scanf
    printf("Enter the first number: ");
    scanf("%s", input1); // Note: This does not check buffer size

    // Get user input for the second number using scanf
    printf("Enter the second number: ");
    scanf("%s", input2); // Note: This does not check buffer size

    // Create lists from user input
    CDLinkedList* list1 = createListFromInput(input1);
    CDLinkedList* list2 = createListFromInput(input2);

    // Add the two lists
    CDLinkedList* result = addLists(list1, list2);

    // Display the result
    printf("Sum: ");
    displayList(result);

    // Free allocated memory (optional, for good practice)
    // Memory cleanup would typically be needed here, but is omitted for brevity

    return 0;
}
