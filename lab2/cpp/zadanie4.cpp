#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* next;
};

void pushFront(Node*& head, int value)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
}

void printList(Node* head)
{
    Node* current = head;
    while (current != nullptr)
    {
        cout << current->value;
        if (current->next != nullptr)
            cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

void clear(Node*& head)
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

// odwraca kolejność elementów bez tworzenia drugiej listy
void reverse(Node*& head)
{
    Node* prev = nullptr;
    Node* current = head;
    while (current != nullptr)
    {
        Node* nextNode = current->next;  // zapamiętujemy resztę listy
        current->next = prev;            // odwracamy wskaźnik
        prev = current;                  // przesuwamy się dalej
        current = nextNode;
    }
    head = prev;  // ostatni element staje się pierwszym
}

int main()
{
    Node* head = nullptr;
    pushFront(head, 12);
    pushFront(head, 8);
    pushFront(head, 5);
    pushFront(head, 2);

    printList(head);  // 2 -> 5 -> 8 -> 12
    reverse(head);
    printList(head);  // 12 -> 8 -> 5 -> 2

    clear(head);
    return 0;
}
