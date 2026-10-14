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

// wstawia wartość tak, żeby lista dalej była posortowana rosnąco
void insertSorted(Node*& head, int value)
{
    Node* newNode = new Node;
    newNode->value = value;

    // pusta lista albo wartość najmniejsza -> wstawiamy na początek
    if (head == nullptr || value < head->value)
    {
        newNode->next = head;
        head = newNode;
        return;
    }

    // idziemy, dopóki następny element jest mniejszy od value
    Node* current = head;
    while (current->next != nullptr && current->next->value < value)
        current = current->next;

    // wstawiamy nowy element za current
    newNode->next = current->next;
    current->next = newNode;
}

int main()
{
    Node* head = nullptr;
    insertSorted(head, 3);
    printList(head);  // 3   (pusta lista)
    clear(head);

    insertSorted(head, 2);
    insertSorted(head, 5);
    insertSorted(head, 8);
    insertSorted(head, 12);
    printList(head);  // 2 -> 5 -> 8 -> 12

    insertSorted(head, 7);
    printList(head);  // 2 -> 5 -> 7 -> 8 -> 12

    insertSorted(head, 1);
    printList(head);  // 1 -> 2 -> 5 -> 7 -> 8 -> 12

    insertSorted(head, 20);
    printList(head);  // 1 -> 2 -> 5 -> 7 -> 8 -> 12 -> 20

    clear(head);
    return 0;
}
