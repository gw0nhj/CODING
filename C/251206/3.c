/*

위와 같은 형식의 노드를 개량하여 head 가 맨 마지막 노드인 tail 을 prevNode 로 가리키는
원형의 노드를 만들어보시오. 다시 말해 노드의 처음과 끝이 없다고 볼 수 있다. 이러한 형태의
노드를 이용하여 앞서 구현하였던 모든 함수를 구현해보시오

*/

//p464 Q3

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

struct Node *searchHead(struct Node *Node);
struct Node *searchTail(struct Node *Node);

void main() {

    struct Node *Head = (struct Node *)malloc(sizeof(struct Node));
    Head->var = 0;
    Head->Next = NULL;
    Head->Prev = NULL;

    struct Node *Node0 = InsertNode(Head, 100);
    struct Node *Node1 = InsertNode(Node0, 200);
    struct Node *Node2 = InsertNode(Node1, 300);
    struct Node *Node3 = InsertNode(Node2, 400);

    printf("%d\n", PrevSearchNode(Node2, Head));
    printf("%d\n", CountNode(Node2));
    

}

struct Node *searchHead(struct Node *Node) {

    struct Node *temp = Node;
    while(temp->Next != NULL) {
        temp = temp->Next;
        if(temp == Node) {
            return NULL;
        }
    }

    return temp;
}

struct Node *searchTail(struct Node *Node) {

    struct Node *temp = Node;
    while(temp->Prev != NULL) {
        temp = temp->Prev;
        if(temp == Node) {
            return NULL;
        }
    }

    return temp;
}

struct Node *InsertNode(struct Node *Node, int Value) {
    
    struct Node *NewNode = (struct Node *)malloc(sizeof(struct Node));

    NewNode->Next = Node->Next;
    Node->Next = NewNode;
    NewNode->Prev = Node;
    NewNode->var = Value;

    struct Node *Tail;
    struct Node *Head;

    if(searchTail(Node) != NULL) { 
        Tail = searchTail(Node);
        Head = searchHead(Node);
        searchTail(Node)->Prev = searchHead(Node);
        Head->Next = Tail;
    }
    else {
        NewNode->Next->Prev = NewNode;
    }
        
    return NewNode;
}

int CountNode(struct Node *Head) {

    struct Node *temp = Head;
    
    int count = 0;

    while(temp->Next != NULL) {
        temp = temp->Next;
        count++;
        if(temp == Head) {
            return count;
        }
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