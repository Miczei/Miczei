#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* next;
};

// dodaje element na początek listy
void pushFront(Node*& head, int value)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = head;
    head = newNode;
}

// wypisuje wszystkie elementy listy
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

// zwraca liczbę elementów
int size(Node* head)
{
    int count = 0;
    Node* current = head;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

// usuwa wszystkie elementy i zwalnia pamięć
void clear(Node*& head)
{
    while (head != nullptr)
    {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

int main()
{
    Node* head = nullptr;

    pushFront(head, 5);
    pushFront(head, 8);
    pushFront(head, 2);

    printList(head);                                     // 2 -> 8 -> 5
    cout << "Rozmiar: " << size(head) << endl;           // 3

    clear(head);
    cout << "Rozmiar po clear: " << size(head) << endl;  // 0

    return 0;
}
