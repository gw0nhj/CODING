/*

앞서 구현하였던 Node 의 단점으로 ’이 노드를 가리키는 노드’ 를 쉽게 알 수 없다는 점이다.
Node에 Prev가 포함된 형식으로 노드를 만들어보고 앞서 작성했던 모든 함수들을 다시 작성해보시오.

*/

//p464 Q2

#include <stdio.h>
#include <stdlib.h>

struct Node
{

    int var;
    struct Node *Next;
    struct Node *Prev;

};

struct Node *InsertNode(struct Node *Node, int Value);
int CountNode(struct Node *Head);
int SearchNode(struct Node *Head, struct Node *search);
int BackCountNode(struct Node *Tail); //어떤 노드 뒤의 노드의 개수를 셈(대상 노드 포함)
int PrevSearchNode(struct Node *Tail, struct Node *search); //어떤 노드 뒤의 찾고자 하는 노드의 값을 출력

void main() {

    struct Node *Head = (struct Node *)malloc(sizeof(struct Node));
    Head->var = 0;
    Head->Next = NULL;
    Head->Prev = NULL;

    struct Node *Node0 = InsertNode(Head, 100);
    struct Node *Node1 = InsertNode(Node0, 200);
    struct Node *Node2 = InsertNode(Node1, 300);
    struct Node *Node3 = InsertNode(Node2, 400);

    printf("%d\n", BackCountNode(Node1));
    printf("%d\n", PrevSearchNode(Node2, Head));
    

}

struct Node *InsertNode(struct Node *Node, int Value) {
    
    struct Node *NewNode = (struct Node *)malloc(sizeof(struct Node));
    if(Node->Next != NULL) Node->Next->Prev = NewNode;
    NewNode->Next = Node->Next;
    Node->Next = NewNode;
    NewNode->Prev = Node;
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

int BackCountNode(struct Node *Tail) {

    struct Node *temp = Tail;
    
    int count = 1;

    while(temp->Prev != NULL) {
        temp = temp->Prev;
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

int PrevSearchNode(struct Node *Tail, struct Node *search) {

    struct Node *temp = Tail;
    int Var = -1;

    while(temp != search && temp->Prev != NULL) {
        temp = temp->Prev;
    }

    if(temp == search) {
        return temp->var;
    }
    else {
        return -1;
    }

}