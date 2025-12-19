#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*  LINKED LIST  */
struct Node {
    int data;
    struct Node* next;
};

void push(struct Node** head_ref, int new_data) {
    struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
    if (new_node == NULL) return;

    new_node->data = new_data;
    new_node->next = *head_ref;
    *head_ref = new_node;
}

void deleteNode(struct Node** head_ref, int key) {
    struct Node *temp = *head_ref;
    struct Node *prev = NULL;

    if (temp != NULL && temp->data == key) {
        *head_ref = temp->next;
        free(temp);
        return;
    }

    while (temp != NULL && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) return;

    prev->next = temp->next;
    free(temp);
}

/* HANOI KULELERI */
void hanoi(int n, char kaynak, char hedef, char yardimci) {
    if (n == 1) {
        printf("Disk 1: %c -> %c\n", kaynak, hedef);
        return;
    }
    hanoi(n - 1, kaynak, yardimci, hedef);
    printf("Disk %d: %c -> %c\n", n, kaynak, hedef);
    hanoi(n - 1, yardimci, hedef, kaynak);
}

/* INFIX TO POSTFIX */
int oncelik(char ch) {
    if (ch == '^') return 3;
    if (ch == '*' || ch == '/') return 2;
    if (ch == '+' || ch == '-') return 1;
    return 0;
}

void infixToPostfix(char* infix, char* postfix) {
    char stack[100];
    int top = -1;
    int j = 0;
    int i;

    for (i = 0; i < (int)strlen(infix); i++) {
        if (isalnum(infix[i])) {
            postfix[j++] = infix[i];
        } 
        else if (infix[i] == '(') {
            stack[++top] = '(';
        } 
        else if (infix[i] == ')') {
            while (top != -1 && stack[top] != '(')
                postfix[j++] = stack[top--];
            top--;
        } 
        else {
            while (top != -1 && oncelik(stack[top]) >= oncelik(infix[i]))
                postfix[j++] = stack[top--];
            stack[++top] = infix[i];
        }
    }

    while (top != -1)
        postfix[j++] = stack[top--];

    postfix[j] = '\0';
}

/* MAX HEAPIFY*/
void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int l = 2 * i + 1;
    int r = 2 * i + 2;

    if (l < n && arr[l] > arr[largest])
        largest = l;

    if (r < n && arr[r] > arr[largest])
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

/* DFS Graph Traversal*/
void DFS(int graph[5][5], int visited[5], int start) {
    int i;
    visited[start] = 1;
    printf("%d ", start);

    for (i = 0; i < 5; i++) {
        if (graph[start][i] == 1 && !visited[i]) {
            DFS(graph, visited, i);
        }
    }
}

int main() {
    /*  Linked List */
    struct Node* head = NULL;
    push(&head, 10);
    push(&head, 20);

    printf("--- Linked List ---\n");
    printf("Liste: 20 10\n");
    deleteNode(&head, 20);
    printf("20 silindi.\n");

    /*  Hanoi */
    printf("\n--- Hanoi ---\n");
    hanoi(2, 'A', 'C', 'B');

    /*  Infix to Postfix */
    printf("\n--- Infix to Postfix ---\n");
    {
        char post[100];
        infixToPostfix("a*b+c^d", post);
        printf("Sonuc: %s\n", post);
    }

    /*  Max Heap */
    printf("\n--- Max Heap ---\n");
    {
        int heapArr[5] = {3, 10, 12, 8, 2};
        maxHeapify(heapArr, 5, 0);
        printf("Max Heap Koku: %d\n", heapArr[0]);
    }

    /*  DFS */
    printf("\n--- Graph DFS ---\n");
    {
        int graph[5][5] = {
            {0,1,1,0,0},
            {1,0,0,1,0},
            {1,0,0,1,0},
            {0,1,1,0,1},
            {0,0,0,1,0}
        };
        int visited[5] = {0,0,0,0,0};
        DFS(graph, visited, 0);
        printf("\n");
    }

    return 0;
}

