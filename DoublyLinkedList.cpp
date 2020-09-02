#include <iostream>
using namespace std;
struct Node{
int data;
struct Node* next;
struct Node* prev;
};

struct Node* Begin;
struct Node* End;

struct Node* GetNode(int x){
    struct Node* temp=new Node();
    temp->data=x;
    temp->next=NULL;
    temp->prev=NULL;
    return temp;
}

void InsertAtBeg(int x){
    struct Node* pointer = GetNode(x);
    if(Begin==NULL)
        End=pointer;
    else{
    Begin->prev=pointer;
    pointer->next=Begin;
    }
    Begin=pointer;
}
void InsertAtEnd(int x){
    struct Node* pointer = GetNode(x);
    if(End==NULL)
        Begin=pointer;
    else{
    End->next=pointer;
    pointer->prev=End;
    }
    End=pointer;
}
void DeleteNode(int x){
    if(Begin==NULL)
        return;
    if(Begin->data==x) //Delete first node
    {
        struct Node* temp= Begin;
        Begin=Begin->next;
        Begin->prev=NULL;
        delete temp;
        return;
    }
    struct Node* pointer = Begin;
    while(pointer->next!=NULL && pointer->data!=x)
        pointer=pointer->next;
    if(pointer->next==NULL){
        struct Node* prev = pointer->prev;
        prev->next=NULL;
        End=prev;
    }
    else{
        struct Node* prev = pointer->prev;
        struct Node* next = pointer->next;
        prev->next=next;
        next->prev=prev;
    }
    delete pointer;
}
int main(){
    Begin=NULL;
    End=NULL;
    InsertAtBeg(4);
    InsertAtBeg(2);
    InsertAtBeg(1);
    InsertAtBeg(6);
    InsertAtEnd(19);
    DeleteNode(6);
//-------For traversing backwards---
//    struct Node* pointer = End;
//    while(pointer!=NULL){
//        cout<<pointer->data;
//        pointer=pointer->prev;
//    }

//-----------traversing forward--------
    struct Node* pointer = Begin;
    while(pointer!=NULL){
        cout<<pointer->data;
        pointer=pointer->next;
    }
}
