#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct Node
{
    int value;
    Node* next;
};

// ===================== Zadanie 1 - stos =====================

// dodaje element na szczyt stosu
void push(Node*& top, int value)
{
    Node* newNode = new Node;
    newNode->value = value;
    newNode->next = top;
    top = newNode;
}

// usuwa element ze szczytu, zwraca false gdy stos jest pusty
bool pop(Node*& top)
{
    if (top == nullptr)
        return false;
    Node* temp = top;
    top = top->next;
    delete temp;
    return true;
}

// zwraca wartosc ze szczytu bez usuwania
int peek(Node* top)
{
    if (top == nullptr)
    {
        cout << "Blad: stos jest pusty!" << endl;
        return 0;
    }
    return top->value;
}

// sprawdza, czy stos jest pusty
bool isEmpty(Node* top)
{
    return top == nullptr;
}

// zwraca liczbe elementow
int size(Node* top)
{
    int count = 0;
    Node* current = top;
    while (current != nullptr)
    {
        count++;
        current = current->next;
    }
    return count;
}

// usuwa wszystkie elementy
void clear(Node*& top)
{
    while (top != nullptr)
        pop(top);
}

// wypisuje stos od szczytu
void printStack(Node* top)
{
    Node* current = top;
    while (current != nullptr)
    {
        cout << current->value;
        if (current->next != nullptr)
            cout << ", ";
        current = current->next;
    }
    cout << endl;
}

// ===================== Zadanie 2 - nawiasy =====================

// sprawdza, czy nawias otwierajacy pasuje do zamykajacego
bool matches(char open, char close)
{
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}

// zwraca true, gdy nawiasy w tekscie sa poprawne
bool checkBrackets(string text)
{
    Node* top = nullptr;  // stos na nawiasy (znak zapisujemy jako liczbe)

    for (char c : text)
    {
        if (c == '(' || c == '[' || c == '{')
        {
            push(top, c);  // nawias otwierajacy -> na stos
        }
        else if (c == ')' || c == ']' || c == '}')
        {
            // nawias zamykajacy: na szczycie musi byc pasujacy otwierajacy
            if (isEmpty(top) || !matches(peek(top), c))
            {
                clear(top);
                return false;
            }
            pop(top);
        }
    }

    bool correct = isEmpty(top);  // na koncu stos musi byc pusty
    clear(top);
    return correct;
}

void testBrackets(string text)
{
    cout << text << " => ";
    if (checkBrackets(text))
        cout << "POPRAWNE" << endl;
    else
        cout << "NIEPOPRAWNE" << endl;
}

// ===================== Zadanie 3 - ONP =====================

// sprawdza, czy token jest liczba (same cyfry)
bool isNumber(string token)
{
    if (token.empty())
        return false;
    for (char c : token)
    {
        if (c < '0' || c > '9')
            return false;
    }
    return true;
}

// liczy wartosc wyrazenia w ONP; zwraca false, gdy wyrazenie jest niepoprawne
bool evaluateRPN(string expression, int& result)
{
    Node* top = nullptr;
    stringstream ss(expression);
    string token;

    while (ss >> token)  // bierzemy kolejne tokeny oddzielone spacjami
    {
        if (isNumber(token))
        {
            push(top, stoi(token));  // liczba -> na stos
        }
        else if (token == "+" || token == "-" || token == "*" || token == "/")
        {
            // operator potrzebuje dwoch liczb na stosie
            if (top == nullptr || top->next == nullptr)
            {
                clear(top);
                return false;
            }

            int b = peek(top);  // drugi argument (byl na szczycie)
            pop(top);
            int a = peek(top);  // pierwszy argument
            pop(top);

            if (token == "+")
                push(top, a + b);
            else if (token == "-")
                push(top, a - b);
            else if (token == "*")
                push(top, a * b);
            else
            {
                if (b == 0)  // dzielenie przez zero
                {
                    clear(top);
                    return false;
                }
                push(top, a / b);
            }
        }
        else  // nieznany token
        {
            clear(top);
            return false;
        }
    }

    // na koncu na stosie musi zostac dokladnie jedna liczba
    if (top == nullptr || top->next != nullptr)
    {
        clear(top);
        return false;
    }

    result = peek(top);
    clear(top);
    return true;
}

void testRPN(string expression)
{
    int result;
    cout << expression << " => ";
    if (evaluateRPN(expression, result))
        cout << result << endl;
    else
        cout << "BLAD - niepoprawne wyrazenie" << endl;
}

// ===================== Zadanie 4 - kolejka =====================
// isEmpty() i size() dla kolejki dzialaja tak samo jak dla stosu
// (licza od pierwszego elementu), wiec uzywamy tych z zadania 1.

// dodaje element na koniec kolejki
void enqueue(Node*& front, Node*& back, int value)
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

// zwraca pierwszy element bez usuwania
int getFront(Node* front)
{
    if (front == nullptr)
    {
        cout << "Blad: kolejka jest pusta!" << endl;
        return 0;
    }
    return front->value;
}

// usuwa wszystkie elementy kolejki
void clear(Node*& front, Node*& back)
{
    while (front != nullptr)
        dequeue(front, back);
}

// wypisuje kolejke od poczatku
void printQueue(Node* front)
{
    if (front == nullptr)
    {
        cout << "(pusta)" << endl;
        return;
    }
    Node* current = front;
    while (current != nullptr)
    {
        cout << current->value;
        if (current->next != nullptr)
            cout << " -> ";
        current = current->next;
    }
    cout << endl;
}

// ===================== main =====================

int main()
{
    cout << boolalpha;  // wypisuje true/false zamiast 1/0

    // ----- Zadanie 1 -----
    cout << "--- Zadanie 1 ---" << endl;
    Node* top = nullptr;
    push(top, 5);
    push(top, 8);
    push(top, 2);
    push(top, 10);
    cout << "Stos: ";
    printStack(top);                                       // 10, 2, 8, 5
    pop(top);
    pop(top);
    push(top, 7);
    cout << "Stos koncowy: ";
    printStack(top);                                       // 7, 8, 5
    cout << "peek: " << peek(top) << endl;                 // 7
    cout << "size: " << size(top) << endl;                 // 3
    cout << "isEmpty: " << isEmpty(top) << endl;           // false
    clear(top);
    cout << "Po clear, isEmpty: " << isEmpty(top) << endl; // true
    cout << "pop na pustym stosie: " << pop(top) << endl;  // false
    cout << "peek na pustym stosie: ";
    peek(top);                                             // Blad: stos jest pusty!

    // ----- Zadanie 2 -----
    cout << "--- Zadanie 2 ---" << endl;
    testBrackets("(a + b) * [c - {d / e}]");  // POPRAWNE
    testBrackets("(a + b] * c");              // NIEPOPRAWNE
    testBrackets("((a+b)");                   // NIEPOPRAWNE
    testBrackets("([)]");                     // NIEPOPRAWNE

    // ----- Zadanie 3 -----
    cout << "--- Zadanie 3 ---" << endl;
    testRPN("2 3 +");              // 5
    testRPN("2 3 4 * +");          // 14
    testRPN("5 2 3 * +");          // 11
    testRPN("10 2 / 7 +");         // 12
    testRPN("4 2 + 3 5 1 - * +");  // 18
    testRPN("2 +");                // BLAD (za malo argumentow)
    testRPN("2 3");                // BLAD (za duzo liczb)
    testRPN("4 0 /");              // BLAD (dzielenie przez zero)

    // ----- Zadanie 4 -----
    cout << "--- Zadanie 4 ---" << endl;
    Node* front = nullptr;
    Node* back = nullptr;
    cout << "dequeue na pustej kolejce: " << dequeue(front, back) << endl;  // false
    enqueue(front, back, 5);
    enqueue(front, back, 8);
    enqueue(front, back, 2);
    enqueue(front, back, 10);
    printQueue(front);                                    // 5 -> 8 -> 2 -> 10
    dequeue(front, back);
    dequeue(front, back);
    enqueue(front, back, 7);
    printQueue(front);                                    // 2 -> 10 -> 7
    cout << "getFront: " << getFront(front) << endl;      // 2
    cout << "size: " << size(front) << endl;              // 3
    clear(front, back);

    enqueue(front, back, 1);                              // kolejka jednoelementowa
    printQueue(front);                                    // 1
    dequeue(front, back);                                 // usuwamy ostatni element
    cout << "front == nullptr: " << (front == nullptr) << endl;  // true
    cout << "back == nullptr: " << (back == nullptr) << endl;    // true
    enqueue(front, back, 4);                              // dodawanie po oproznieniu
    enqueue(front, back, 6);
    printQueue(front);                                    // 4 -> 6
    clear(front, back);

    return 0;
}
