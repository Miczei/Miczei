#include <iostream>
#include <string>
using namespace std;

// wezel kolejki (jak w laborce 3, tylko trzyma imie zamiast liczby)
struct Node
{
    string value;
    Node* next;
};

Node* front = nullptr;    // pierwszy pacjent (najblizej obslugi)
Node* back = nullptr;     // ostatni pacjent
string windowA = "";      // okienko A: "" = wolne, w innym razie imie obslugiwanego pacjenta
string windowB = "";      // okienko B

// ===================== kolejka (z laborki 3) =====================

// dodaje element na koniec kolejki
void enqueue(Node*& front, Node*& back, string value)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = nullptr;

    if (back == nullptr)  // kolejka pusta -> nowy element jest i pierwszy, i ostatni
    {
        front = newNode;
        back = newNode;
    }
    else
    {
        back->next = newNode;  // doczepiamy za ostatnim
        back = newNode;
    }
}

// usuwa element z poczatku kolejki, zwraca false gdy kolejka jest pusta
bool dequeue(Node*& front, Node*& back)
{
    if (front == nullptr)
        return false;

    Node* temp = front;
    front = front->next;
    delete temp;

    if (front == nullptr)  // usunelismy ostatni element
        back = nullptr;
    return true;
}

// sprawdza, czy kolejka jest pusta
bool isEmpty(Node* front)
{
    return front == nullptr;
}

// ===================== okienka =====================

// pacjent dolacza na koniec kolejki
void arrive(string name)
{
    enqueue(front, back, name);
}

// pierwszy pacjent z kolejki idzie do pierwszego wolnego okienka (najpierw A, potem B)
void serve()
{
    if (isEmpty(front))  // pusta kolejka -> nic nie robi
        return;

    if (windowA != "" && windowB != "")  // oba zajete
    {
        cout << "Brak wolnego okienka" << endl;
        return;
    }

    string name = front->value;  // pierwszy w kolejce
    dequeue(front, back);

    if (windowA == "")
    {
        windowA = name;
        cout << "Obsłużono: " << name << " w okienku A" << endl;
    }
    else
    {
        windowB = name;
        cout << "Obsłużono: " << name << " w okienku B" << endl;
    }
}

// okienko X konczy obsluge i staje sie wolne
void freeWindow(string x)
{
    if (x == "A")
        windowA = "";
    else if (x == "B")
        windowB = "";
}

// wypisuje kolejke od pierwszego (najblizej obslugi): P1 <- P2 <- P3
void showQueue()
{
    cout << "Kolejka: ";
    if (isEmpty(front))
    {
        cout << "(pusta)" << endl;
        return;
    }
    Node* current = front;
    while (current != nullptr)
    {
        cout << current->value;
        if (current->next != nullptr)
            cout << " <- ";
        current = current->next;
    }
    cout << endl;
}

// wypisuje stan obu okienek
void status()
{
    cout << "A: " << (windowA == "" ? "wolne" : "zajęte (" + windowA + ")");
    cout << ", B: " << (windowB == "" ? "wolne" : "zajęte (" + windowB + ")") << endl;
}

int main()
{
    arrive("Anna");
    arrive("Bartek");
    serve();          // A obsluguje Anne
    serve();          // B obsluguje Bartka
    arrive("Celina");
    serve();          // brak wolnego okienka
    freeWindow("A");
    serve();          // A obsluguje Celine
    status();
    showQueue();

    // sprzatanie pamieci (gdyby ktos zostal w kolejce)
    while (dequeue(front, back)) {}

    return 0;
}
