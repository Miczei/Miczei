#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node* next;
};

// ===================== Zadanie 1 =====================

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

// ===================== Zadanie 2 =====================

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

// ===================== Zadanie 3 =====================

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

// ===================== Zadanie 4 =====================

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

// ===================== main =====================

int main()
{
    cout << boolalpha;  // wypisuje true/false zamiast 1/0
    Node* head = nullptr;

    // ----- Zadanie 1 -----
    cout << "--- Zadanie 1 ---" << endl;
    pushFront(head, 5);
    pushFront(head, 8);
    pushFront(head, 2);
    printList(head);                                     // 2 -> 8 -> 5
    cout << "Rozmiar: " << size(head) << endl;           // 3
    clear(head);
    cout << "Rozmiar po clear: " << size(head) << endl;  // 0

    // ----- Zadanie 2 -----
    cout << "--- Zadanie 2 ---" << endl;
    pushBack(head, 4);
    pushBack(head, 7);
    pushBack(head, 2);
    pushBack(head, 7);
    pushBack(head, 9);
    printList(head);  // 4 -> 7 -> 2 -> 7 -> 9
    removeFirst(head, 7);
    printList(head);  // 4 -> 2 -> 7 -> 9
    cout << "Czy jest 2? " << contains(head, 2) << endl;                 // true
    cout << "Czy jest 100? " << contains(head, 100) << endl;             // false
    cout << "Usun pierwszy (4): " << removeFirst(head, 4) << endl;       // true
    cout << "Usun ostatni (9): " << removeFirst(head, 9) << endl;        // true
    cout << "Usun nieobecny (100): " << removeFirst(head, 100) << endl;  // false
    printList(head);  // 2 -> 7
    clear(head);
    cout << "Usun z pustej: " << removeFirst(head, 5) << endl;           // false

    // ----- Zadanie 3 -----
    cout << "--- Zadanie 3 ---" << endl;
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

    // ----- Zadanie 4 -----
    cout << "--- Zadanie 4 ---" << endl;
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
