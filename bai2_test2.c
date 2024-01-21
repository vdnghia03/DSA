#include<stdio.h>
#include<stdlib.h>

// Dinh nghia node
typedef struct NodeType
{
    int data;
    struct NodeType* next;
} Node;

// Tao node moi
Node* makeNode(int data) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data=data;
    temp->next=NULL;
    return temp;
}

// Dinh nghia stack
typedef struct StackType
{
    Node* top;
} Stack;

// Khoi tao gia tri ban dau cho stack
void init(Stack* st)
{
    st->top = NULL;
}

// Kiem tra xem stack co rong
int isEmpty(Stack* s)
{
    return s->top == NULL;
}

// Them phan tu vao mot stack
void push(int data, Stack *s)
{
    Node* node = makeNode(data);
    // Neu stack rong rong node la vi tri top trong stack
    if(isEmpty(s))
    {
        s->top = node;
    }
    else
    {
        // node vua tao lien ket voi node dau cua stack
        // cap nhap lai vi tri top cua stack
        node->next = s->top;
        s->top = node;
    }

}

// Xoa pop stack
int pop(Stack *s)
{
    if(isEmpty(s))
    {
        printf("Stack is empty\n");
        return -1;
    }
    // Node chay node nhan gia tri dau stack
    Node* node = s->top;

    // cap nhap lai vi tri top trong stack
    s->top = node->next;
    // Lay ra gia tri trong node dau stack va giai phong no khoi vung nho
    int value = node->data;
    // Giai phong vung nho cua node
    node->next = NULL;
    free(node);
    // tra ve gia tri tai dinh stack
    return value;
}

// Hien thi stack
void displayStack(Stack *s)
{
    Node *temp = s->top;
    printf("\nStack: ");
    while(temp != NULL)
    {
        printf(" %d", temp->data);
        temp = temp->next;
    }
    
}
int main()
{
    // Khoi tao stack
    Stack s;
    init(&s);
    // day vao stack cac gia tri
    // push(3,&s);
    // push(1,&s);
    // push(2,&s);
    // push(7,&s);
    // push(5,&s);

    // hien thi stack
    displayStack(&s);

    // pop
    printf("\nPop: %d\n", pop(&s));
    displayStack(&s);

    // push 10
    printf("\nPush 10\n");
    push(10,&s);
    displayStack(&s);
    return 0;
}