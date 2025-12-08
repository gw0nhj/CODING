/*

head 와 원하는 노드가 주어질 때 원하는 노드의 데이터 값을 출력하는 
int SearchNode(Node* head, Node *search) 함수를 작성하시오 

*/

//p464 Q2

#include <stdio.h>
#include <stdlib.h>

struct Node
{

    int var;
    struct Node *Next;

};

struct Node *InsertNode(struct Node *Node, int Value);
int CountNode(struct Node *Head);
int SearchNode(struct Node *Head, struct Node *search);

void main() {

    struct Node *Head = (struct Node *)malloc(sizeof(struct Node));
    Head->var = 0;
    Head->Next = NULL;

    struct Node *Node0 = InsertNode(Head, 100);
    struct Node *Node1 = InsertNode(Node0, 200);
    struct Node *Node2 = InsertNode(Node1, 300);
    struct Node *Node3 = InsertNode(Node2, 400);

    printf("%d\n", CountNode(Head));
    printf("%d\n", SearchNode(Head, Node2));
    

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

int SearchNode(struct Node *Head, struct Node *search) {

    struct Node *temp = Head;
    int Var = -1;

    while(temp != search && temp->Next != NULL) {
        temp = temp->Next;
    }

    if(temp == search) {
        return temp->var;
    }
    else {
        return -1;
    }

}