#include <iostream>
using namespace std;

struct Node{
    int item;
    Node* next;
    Node(int item){this->item = item;}
    Node(int item, Node* next){this->item = item; this->next = next;}
};

void insertHead(Node*& head, int item);
void insertAfter(Node *head, Node* afterThis, int item);
void deleteNode(Node*& head, Node* deleteThis);
Node* search(Node* head, int item);
void print(Node* head);
Node* previousNode(Node* head, Node* beforeThis);
Node* removeNode(Node*& head, Node* removeThis);
bool isNodeInList(Node* head, Node* checkThis);

int main()
{
    Node* head = NULL;
    for(int i = 0; i < 10; i++) insertHead(head,i);
    cout << "The List: " << endl;
    print(head);
    cout << "Insert After Head: " << endl;
    insertAfter(head,head,20);
    print(head);
    cout << "Insert After Middle: " << endl;
    Node* temp = head->next->next->next->next; //(5)
    insertAfter(head,temp,50);
    print(head);
    cout << "Remove: " << endl;
    Node* temp2 = removeNode(head,temp);
    cout << temp2->item << endl;
    cout << "Delete: " << endl;
    deleteNode(head,head);
    print(head);

    Node* notInList = new Node(1,NULL);
    bool check = isNodeInList(head,notInList);
    if(check) cout << "Node is In List. (FUNCTION IS WRONG)" << endl;
    else cout << "Node is not list. FUNCTION WORKING" << endl;
    insertAfter(head,notInList,25);
    print(head);
    removeNode(head,notInList);
    print(head);



    return 0;
}
void print(Node* head){
    Node* walker = head;
    while(walker){
        cout << walker->item << " | ";
        walker = walker->next;
    }
    cout << endl;
}

void insertHead(Node*& head, int item){
    Node* newNode = new Node(item,head);
    head = newNode;
}

void insertAfter(Node* head, Node* afterThis, int item){
    if(!isNodeInList(head,afterThis)) return;
    Node* newNode = new Node(item,afterThis->next);
    afterThis->next = newNode;
}

Node* removeNode(Node*& head, Node* removeThis){
    if(head == NULL) return NULL;
    if(!isNodeInList(head,removeThis)) return NULL;
    if(removeThis == head){
        Node* temp = head;
        head = head->next;
        return temp;
    }
    Node* before = previousNode(head,removeThis);
    Node* temp = removeThis;
    before->next = removeThis->next;
    return temp;
}

bool isNodeInList(Node* head, Node* checkThis){
    Node* walker = head;
    while(walker){
        if(walker == checkThis) return true;
        walker = walker->next;
    }
    return false;
}

Node* previousNode(Node* head, Node* beforeThis){
    if(beforeThis == head) return NULL;
    if(!isNodeInList(head,beforeThis)) return NULL;
    Node* walker = head;
    while(walker){
        Node* temp = walker;
        walker = walker->next;
        if(walker == beforeThis){
            return temp;
        }
    }
}

void deleteNode(Node*& head, Node* deleteThis){
    Node* temp = removeNode(head,deleteThis);
    if(temp) delete temp;
}

Node* search(Node* head, int item){
    Node* walker = head;
    while(walker){
        if(walker->item == item) return walker;
        walker = walker->next;
    }
    return NULL;
}
