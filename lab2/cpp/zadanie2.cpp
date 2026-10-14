#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* next;
};

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

// dodaje element na końcu listy
void pushBack(Node*& head, int value)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (head == nullptr)  // lista pusta -> nowy element jest pierwszy
    {
        head = newNode;
        return;
    }

    Node* current = head;
    while (current->next != nullptr)  // idziemy do ostatniego elementu
        current = current->next;
    current->next = newNode;
}

// sprawdza, czy wartość występuje w liście
bool contains(Node* head, int value)
{
    Node* current = head;
    while (current != nullptr)
    {
        if (current->value == value)
            return true;
        current = current->next;
    }
    return false;
}

// usuwa pierwsze wystąpienie wartości
bool removeFirst(Node*& head, int value)
{
    if (head == nullptr)  // pusta lista
        return false;

    if (head->value == value)  // usuwamy pierwszy element
    {
        Node* temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    Node* current = head;
    while (current->next != nullptr)  // szukamy elementu PRZED usuwanym
    {
        if (current->next->value == value)
        {
            Node* temp = current->next;
            current->next = temp->next;  // omijamy usuwany element
            delete temp;
            return true;
        }
        current = current->next;
    }
    return false;  // nie ma takiej wartości
}

int main()
{
    cout << boolalpha;  // wypisuje true/false zamiast 1/0
    Node* head = nullptr;

    pushBack(head, 4);
    pushBack(head, 7);
    pushBack(head, 2);
    pushBack(head, 7);
    pushBack(head, 9);
    printList(head);  // 4 -> 7 -> 2 -> 7 -> 9

    removeFirst(head, 7);
    printList(head);  // 4 -> 2 -> 7 -> 9

    cout << "Czy jest 2? " << contains(head, 2) << endl;      // true
    cout << "Czy jest 100? " << contains(head, 100) << endl;  // false

    cout << "Usun pierwszy (4): " << removeFirst(head, 4) << endl;       // true
    cout << "Usun ostatni (9): " << removeFirst(head, 9) << endl;        // true
    cout << "Usun nieobecny (100): " << removeFirst(head, 100) << endl;  // false
    printList(head);  // 2 -> 7

    Node* empty = nullptr;
    cout << "Usun z pustej: " << removeFirst(empty, 5) << endl;  // false

    clear(head);
    return 0;
}
