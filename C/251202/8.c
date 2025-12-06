#include <stdio.h>
#include <stdlib.h>

struct Node {
    int Value;
    struct Node *Next;
};

struct Node *InsertNode(struct Node *CurrentNode, int Value);

void main() {
    
    struct Node *Node0 = NULL;  // NULL로 초기화
    struct Node *Node1 = InsertNode(Node0, 100);

    if (Node1 != NULL) {
        printf("%d\n", Node1->Value);
    }
    
    // 메모리 해제
    free(Node1);

}

struct Node* InsertNode(struct Node *CurrentNode, int Value)
{
    struct Node *NextNode = (struct Node*)malloc(sizeof(struct Node));
    
    if (NextNode == NULL) {
        return NULL;  // 메모리 할당 실패 처리
    }
    
    NextNode->Value = Value;
    NextNode->Next = NULL;
    
    // CurrentNode가 NULL이 아닐 때만 연결
    if (CurrentNode != NULL) {
        struct Node *AfterNode = CurrentNode->Next;
        CurrentNode->Next = NextNode;
        NextNode->Next = AfterNode;
    }
    
    return NextNode;
}