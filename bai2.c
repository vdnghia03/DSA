#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Định nghĩa node
typedef struct NodeType {
    char data;
    struct NodeType* next;
} Node;

// Định nghĩa danh sách liên kết
typedef struct LinkedListType {
    Node* head;
} LinkedList;

// Khởi tạo danh sách liên kết
void init(LinkedList* list) {
    list->head = NULL;
}

// Hàm tạo node mới
Node* makeNode(char data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Hàm chèn node mới vào đầu danh sách
void insertHead(char data, LinkedList* list) {
    Node* newNode = makeNode(data);
    newNode->next = list->head;
    list->head = newNode;
}

void insertTail(char data, LinkedList* list)
{
    Node *node = makeNode(data);
    if(list->head == NULL)
    {
        list->head = node;
        return;
    }

    Node* cur = list->head;
    while(cur->next != NULL)
    {
        cur = cur->next;
    }
    cur->next = node;
}

// Hàm in danh sách liên kết
void printList(LinkedList* list) {
    Node* node = list->head;
    while (node != NULL) {
        printf("%c", node->data);
        node = node->next;
    }
    printf("\n");
}

int main() {

    LinkedList list;
    init(&list);
    char str[] = "DSATTHS12023";

    int i;
    for (i = 0; i < strlen(str); i++) {
        insertTail(str[i], &list);
    }

    printf("Chuoi ky tu: ");
    printList(&list);

    return 0;
}