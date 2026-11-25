#include <iostream>
#include <string>
#include <queue>
using namespace std;

queue<string> patients;   // jedna kolejka FIFO z oczekujacymi pacjentami
string windowA = "";      // okienko A: "" = wolne, w innym razie imie obslugiwanego pacjenta
string windowB = "";      // okienko B

// pacjent dolacza na koniec kolejki
void arrive(string name)
{
    patients.push(name);
}

// pierwszy pacjent z kolejki idzie do pierwszego wolnego okienka (najpierw A, potem B)
void serve()
{
    if (patients.empty())  // pusta kolejka -> nic nie robi
        return;

    if (windowA != "" && windowB != "")  // oba zajete
    {
        cout << "Brak wolnego okienka" << endl;
        return;
    }

    string name = patients.front();
    patients.pop();

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
    if (patients.empty())
    {
        cout << "(pusta)" << endl;
        return;
    }
    queue<string> copy = patients;  // kopia, zeby nie zepsuc prawdziwej kolejki
    while (!copy.empty())
    {
        cout << copy.front();
        copy.pop();
        if (!copy.empty())
            cout << " <- ";
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

    return 0;
}
