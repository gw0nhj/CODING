//head 가 주어질 때 전체 노드의 개수를 세는 int CountNode(Node* head) 함수를 작성하시오
//p464 Q1

#include <stdio.h>
#include <stdlib.h>

struct Node
{

    int var;
    struct Node *Next;

};

struct Node *InsertNode(struct Node *Node, int Value);
int CountNode(struct Node *Head);

void main() {

    struct Node *Head = (struct Node *)malloc(sizeof(struct Node));
    Head->var = 0;
    Head->Next = NULL;

    struct Node *Node0 = InsertNode(Head, 100);
    struct Node *Node1 = InsertNode(Node0, 100);
    struct Node *Node2 = InsertNode(Node1, 100);
    struct Node *Node3 = InsertNode(Node2, 100);

    printf("%d", CountNode(Head));
    

}

struct Node *InsertNode(struct Node *Node, int Value) {
    
    struct Node *NewNode = (struct Node *)malloc(sizeof(struct Node));
    NewNode->Next = Node->Next;
    Node->Next = NewNode;
    NewNode->var = Value;

    return NewNode;
}

int CountNode(struct Node *Head) {

    struct Node *temp = Head;
    
    int count = 1;

    while(temp->Next != NULL) {
        temp = temp->Next;
        count++;
    }

    return count;
}
