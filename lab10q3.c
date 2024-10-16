#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Node structure for doubly linked list
typedef struct Node {
    char data[100]; // Data field to store strings
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node
Node* createNode(const char* data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        strncpy(newNode->data, data, sizeof(newNode->data));
        newNode->next = NULL;
        newNode->prev = NULL;
    }
    return newNode;
}

// Function to reverse the doubly linked list
void reverseDoublyLinkedList(Node** head) {
    Node* temp = NULL;
    Node* current = *head;

    // Swap next and prev for all nodes
    while (current != NULL) {
        temp = current->prev;
        current->prev = current->next;
        current->next = temp;
        current = current->prev; // Move to the next node
    }

    // Check if the list is not empty, then update the head
    if (temp != NULL) {
        *head = temp->prev;
    }
}

// Function to print the list
void printList(Node* head) {
    Node* current = head;
    while (current != NULL) {
        printf("%s ", current->data);
        current = current->next;
    }
    printf("\n");
}

// Function to create a doubly linked list based on user input
Node* createList(int n) {
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = 0; i < n; i++) {
        char input[100];
        printf("Enter string for node %d: ", i + 1);
        scanf("%s", input); // Read input string

        Node* newNode = createNode(input);
        if (head == NULL) {
            head = newNode; // Set head for the first node
            tail = newNode; // Initialize tail for the first node
        } else {
            tail->next = newNode; // Link new node to the end
            newNode->prev = tail; // Set previous pointer of new node
            tail = newNode; // Move tail to the new node
        }
    }

    return head;
}

// Example usage
int main() {
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n); // Read number of nodes

    Node* head = createList(n); // Create the list from user input

    printf("Original List: ");
    printList(head); // Print the original list

    reverseDoublyLinkedList(&head); // Reverse the doubly linked list

    printf("Reversed List: ");
    printList(head); // Print the reversed list

    // Free allocated memory (not shown for brevity)

    return 0;
}

