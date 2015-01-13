#include <iostream>
struct Node{
    int item;
    Node* next;
    Node(int item){this->item = item;}
    Node(int item, Node* next){this->item = item; this->next = next;}
};

using namespace std;
void insertHead(Node*& head, int item);
void insertAfter(Node* afterThis, int item);
void deleteNode(Node*& head, Node* deleteThis);
Node* search(Node* head, int item);
void print(Node* head);

int main()
{
    Node* head = new Node(1,NULL);
    insertHead(head,1515);
    insertAfter(head,0);
    cout << "InsertHead and InsertAfter" << endl;
    print(head);
    cout << "Search for 0 and Search for 123124124124214" << endl;
    Node* found = search(head,0);
    cout << "0 Search: ";
    if(found) cout << found->item << endl;
    else cout << "NOT FOUND" << endl;
    found = search(head,123124124124214);
    cout << "123124124124214 Search: ";
    if(found) cout << found->item << endl;
    else cout << "NOT FOUND" << endl;

    Node* temp = head;
    temp = temp->next;
    cout << "TEMP: " << temp->item << endl;
    cout << "Delete @ Temp" << endl;
    deleteNode(head,temp);
    print(head);
    cout << "Delete @ Head" << endl;
    deleteNode(head,head);
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

void insertAfter(Node* afterThis, int item){
    Node* temp = afterThis->next;
    Node* newNode = new Node(item,temp);
    afterThis->next = newNode;
}

void deleteNode(Node*& head, Node* deleteThis){
    if(deleteThis == head){
        Node* temp = head->next;
        delete[] deleteThis;
        head = temp;
    }
    else{
        Node* walker = head;
        while(walker){
            Node* temp = walker;
            walker = walker->next;
            if(walker == deleteThis){
                walker = temp;
                break;
            }
        }
        Node* temp = deleteThis->next;
        delete[] deleteThis;
        walker->next = temp;
    }
}

Node* search(Node* head, int item){
    Node* walker = head;
    while(walker){
        if(walker->item == item) return walker;
        walker = walker->next;
    }
    return NULL;
}
