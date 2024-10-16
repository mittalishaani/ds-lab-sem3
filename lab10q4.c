#include <stdio.h>
#include <stdlib.h>

// Structure for polynomial term
typedef struct Node {
    int coefficient;
    int exponent;
    struct Node* next;
} Node;

// Structure for header node
typedef struct {
    int count; // Number of nodes
    Node* next; // Pointer to first node of polynomial terms
} HeaderNode;

// Function prototypes
HeaderNode* createPolynomial();
void insertTerm(HeaderNode* head, int coeff, int exp);
void displayPolynomial(HeaderNode* head);
HeaderNode* subtractPolynomials(HeaderNode* poly1, HeaderNode* poly2);
HeaderNode* multiplyPolynomials(HeaderNode* poly1, HeaderNode* poly2);

int main() {
    HeaderNode* poly1 = NULL;
    HeaderNode* poly2 = NULL;
    HeaderNode* result = NULL;
    int choice;

    while (1) {
        printf("\nMenu:\n");
        printf("1. Input Polynomial 1\n");
        printf("2. Input Polynomial 2\n");
        printf("3. Subtract Polynomials\n");
        printf("4. Multiply Polynomials\n");
        printf("5. Display Polynomials\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                poly1 = createPolynomial();
                printf("Polynomial 1 created successfully.\n");
                break;
            case 2:
                poly2 = createPolynomial();
                printf("Polynomial 2 created successfully.\n");
                break;
            case 3:
                if (poly1 && poly2) {
                    result = subtractPolynomials(poly1, poly2);
                    printf("Subtraction result: ");
                    displayPolynomial(result);
                } else {
                    printf("Please input both polynomials first.\n");
                }
                break;
            case 4:
                if (poly1 && poly2) {
                    result = multiplyPolynomials(poly1, poly2);
                    printf("Multiplication result: ");
                    displayPolynomial(result);
                } else {
                    printf("Please input both polynomials first.\n");
                }
                break;
            case 5:
                printf("Polynomial 1: ");
                displayPolynomial(poly1);
                printf("Polynomial 2: ");
                displayPolynomial(poly2);
                break;
            case 6:
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}

// Function to create a polynomial (linked list with header node)
HeaderNode* createPolynomial() {
    HeaderNode* head = (HeaderNode*)malloc(sizeof(HeaderNode));
    head->count = 0;
    head->next = NULL;
    int coeff, exp;
    char cont;

    do {
        printf("Enter coefficient and exponent: ");
        scanf("%d%d", &coeff, &exp);
        insertTerm(head, coeff, exp);
        printf("Add another term? (y/n): ");
        scanf(" %c", &cont);
    } while (cont == 'y' || cont == 'Y');

    return head;
}

// Function to insert a term into the polynomial in descending order of exponents
void insertTerm(HeaderNode* head, int coeff, int exp) //DIFFERENT FROM WHAT IS IN THE NOTEBOOK
{
    // If the coefficient is zero, no need to add the term
    if (coeff == 0) {
        return;
    }

    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->coefficient = coeff;
    newNode->exponent = exp;

    if (head->next == NULL) {
        // List is empty, add the first term.
        newNode->next = newNode; // Circular link for the first node
        head->next = newNode;
    } else {
        Node* temp = head->next;
        Node* prev = NULL;

        // Traverse to find the right place to insert or add coefficients
        do {
            // If a term with the same exponent is found, add the coefficients
            if (temp->exponent == exp) {
                temp->coefficient += coeff;

                // If the new coefficient becomes zero, remove the node
                if (temp->coefficient == 0) {
                    // Handle node deletion (if only one term exists)
                    if (temp->next == temp) {
                        head->next = NULL;
                    } else {
                        if (prev == NULL) {
                            // Removing the first term in a non-empty list
                            Node* last = head->next;
                            while (last->next != head->next) {
                                last = last->next;
                            }
                            head->next = temp->next;
                            last->next = head->next;
                        } else {
                            prev->next = temp->next;
                        }
                    }
                    free(temp);
                    head->count--;
                }
                free(newNode);
                return;
            }

            if (temp->exponent < exp) {
                break;
            }
            prev = temp;
            temp = temp->next;
        } while (temp != head->next);

        // If no matching exponent was found, insert the new node
        if (prev == NULL) {
            // Insert at the beginning
            newNode->next = head->next;
            head->next = newNode;
        } else {
            prev->next = newNode;
            newNode->next = temp;
        }
    }
    head->count++;
}


// Function to display a polynomial
void displayPolynomial(HeaderNode* head) {
    if (!head || head->next == NULL) {
        printf("0\n");
        return;
    }

    Node* temp = head->next;
    do {
        printf("%dx^%d", temp->coefficient, temp->exponent);
        temp = temp->next;
        if (temp != head->next) {
            printf(" + ");
        }
    } while (temp != head->next);
    printf("\n");
}

// Function to subtract two polynomials
HeaderNode* subtractPolynomials(HeaderNode* poly1, HeaderNode* poly2) {
    HeaderNode* result = (HeaderNode*)malloc(sizeof(HeaderNode));
    result->count = 0;
    result->next = NULL;

    Node* temp1 = poly1->next;
    Node* temp2 = poly2->next;

    do {
        if (temp1->exponent > temp2->exponent) {
            insertTerm(result, temp1->coefficient, temp1->exponent);
            temp1 = temp1->next;
        } else if (temp1->exponent < temp2->exponent) {
            insertTerm(result, -temp2->coefficient, temp2->exponent);
            temp2 = temp2->next;
        } else {
            int coeff = temp1->coefficient - temp2->coefficient;
            if (coeff != 0) {
                insertTerm(result, coeff, temp1->exponent);
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
    } while (temp1 != poly1->next && temp2 != poly2->next);

    while (temp1 != poly1->next) {
        insertTerm(result, temp1->coefficient, temp1->exponent);
        temp1 = temp1->next;
    }

    while (temp2 != poly2->next) {
        insertTerm(result, -temp2->coefficient, temp2->exponent);
        temp2 = temp2->next;
    }

    return result;
}

// Function to multiply two polynomials
HeaderNode* multiplyPolynomials(HeaderNode* poly1, HeaderNode* poly2) {
    HeaderNode* result = (HeaderNode*)malloc(sizeof(HeaderNode));
    result->count = 0;
    result->next = NULL;

    Node* temp1 = poly1->next;

    do {
        Node* temp2 = poly2->next;
        do {
            int coeff = temp1->coefficient * temp2->coefficient;
            int exp = temp1->exponent + temp2->exponent;
            insertTerm(result, coeff, exp);
            temp2 = temp2->next;
        } while (temp2 != poly2->next);
        temp1 = temp1->next;
    } while (temp1 != poly1->next);

    return result;
}
