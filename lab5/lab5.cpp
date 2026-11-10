#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <chrono>
#include <iomanip>
using namespace std;

// ===================== Zadanie 1 =====================

// sortowanie babelkowe (wersja klasyczna)
void bubbleSort(vector<int>& data)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j] > data[j + 1])
                swap(data[j], data[j + 1]);
        }
    }
}

// sortowanie babelkowe - wersja zoptymalizowana:
// jesli w calym przejsciu nie bylo zadnej zamiany, tablica jest juz posortowana
void bubbleSortOptimized(vector<int>& data)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j] > data[j + 1])
            {
                swap(data[j], data[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

// sortowanie przez wybieranie: szukam najmniejszego w nieposortowanej czesci
// i zamieniam go z pierwszym elementem tej czesci
void selectionSort(vector<int>& data)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (data[j] < data[minIndex])
                minIndex = j;
        }
        if (minIndex != i)
            swap(data[i], data[minIndex]);
    }
}

// sortowanie przez wstawianie: biore kolejny element (key), przesuwam wieksze
// elementy o jedno miejsce w prawo i wstawiam key w powstala luke
void insertionSort(vector<int>& data)
{
    int n = data.size();
    for (int i = 1; i < n; i++)
    {
        int key = data[i];
        int j = i - 1;
        while (j >= 0 && data[j] > key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = key;
    }
}

void printVector(vector<int> data)
{
    if (data.empty())
        cout << "(pusta)";
    for (int x : data)
        cout << x << " ";
    cout << endl;
}

// sortuje kopie tych samych danych kazdym algorytmem i wypisuje wyniki
void testZad1(string name, vector<int> data)
{
    vector<int> a = data;
    vector<int> b = data;
    vector<int> c = data;
    vector<int> d = data;
    bubbleSort(a);
    bubbleSortOptimized(b);
    selectionSort(c);
    insertionSort(d);

    cout << name << ": ";
    printVector(data);
    cout << "   Bubble:           ";
    printVector(a);
    cout << "   Bubble (zoptym.): ";
    printVector(b);
    cout << "   Selection:        ";
    printVector(c);
    cout << "   Insertion:        ";
    printVector(d);
}

// ===================== Zadanie 2 =====================
// te same algorytmy co w zad. 1, tylko z licznikami
// (funkcja o tej samej nazwie, ale z dodatkowym parametrem stats -
//  C++ sam wybiera wlasciwa wersje po parametrach)

struct SortStats
{
    long long comparisons = 0;  // porownania elementow
    long long operations = 0;   // zamiany (Bubble, Selection) albo przesuniecia (Insertion)
};

// Bubble Sort (wersja zoptymalizowana)
void bubbleSort(vector<int>& data, SortStats& stats)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++)
    {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++)
        {
            stats.comparisons++;
            if (data[j] > data[j + 1])
            {
                swap(data[j], data[j + 1]);
                stats.operations++;
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

void selectionSort(vector<int>& data, SortStats& stats)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            stats.comparisons++;
            if (data[j] < data[minIndex])
                minIndex = j;
        }
        if (minIndex != i)
        {
            swap(data[i], data[minIndex]);
            stats.operations++;
        }
    }
}

void insertionSort(vector<int>& data, SortStats& stats)
{
    int n = data.size();
    for (int i = 1; i < n; i++)
    {
        int key = data[i];
        int j = i - 1;
        while (j >= 0)
        {
            stats.comparisons++;
            if (data[j] > key)
            {
                data[j + 1] = data[j];  // przesuniecie
                stats.operations++;
                j--;
            }
            else
                break;
        }
        data[j + 1] = key;
    }
}

// generatory danych
vector<int> randomData(int n)
{
    vector<int> data(n);
    for (int i = 0; i < n; i++)
        data[i] = rand() % 100000;
    return data;
}

vector<int> ascendingData(int n)
{
    vector<int> data(n);
    for (int i = 0; i < n; i++)
        data[i] = i + 1;
    return data;
}

vector<int> descendingData(int n)
{
    vector<int> data(n);
    for (int i = 0; i < n; i++)
        data[i] = n - i;
    return data;
}

// rosnace, ale co 10 elementow zamieniam dwa, np. 1 2 3 4 5 8 7 6 9 10
vector<int> almostSortedData(int n)
{
    vector<int> data = ascendingData(n);
    for (int i = 5; i + 2 < n; i += 10)
        swap(data[i], data[i + 2]);
    return data;
}

// sortuje dane jednym algorytmem, mierzy czas i wypisuje wiersz tabeli
// (data przekazane przez wartosc -> algorytm dostaje wlasna kopie)
void measure(string label, string algorithm, vector<int> data)
{
    SortStats stats;
    auto start = chrono::high_resolution_clock::now();

    if (algorithm == "Bubble Sort")
        bubbleSort(data, stats);
    else if (algorithm == "Selection Sort")
        selectionSort(data, stats);
    else
        insertionSort(data, stats);

    auto end = chrono::high_resolution_clock::now();
    double ms = chrono::duration<double, milli>(end - start).count();

    cout << setw(16) << label << setw(16) << algorithm
         << setw(14) << stats.comparisons << setw(14) << stats.operations
         << setw(12) << fixed << setprecision(3) << ms << endl;
}

// ta sama tablica (jej kopie) dla wszystkich trzech algorytmow
void measureAll(string label, vector<int> data)
{
    measure(label, "Bubble Sort", data);
    measure(label, "Selection Sort", data);
    measure(label, "Insertion Sort", data);
}

void printHeader(string firstColumn)
{
    cout << setw(16) << firstColumn << setw(16) << "Algorytm"
         << setw(14) << "Porownania" << setw(14) << "Operacje"
         << setw(12) << "Czas [ms]" << endl;
}

// ===================== Zadanie 3 =====================

struct Record
{
    int key;
    char id;
};

void printRecords(vector<Record> data)
{
    for (Record r : data)
        cout << "(" << r.key << "," << r.id << ") ";
    cout << endl;
}

// te same algorytmy co w zad. 1, tylko porownujemy pole key
void bubbleSort(vector<Record>& data)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (data[j].key > data[j + 1].key)
                swap(data[j], data[j + 1]);
        }
    }
}

void selectionSort(vector<Record>& data)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++)
    {
        int minIndex = i;
        for (int j = i + 1; j < n; j++)
        {
            if (data[j].key < data[minIndex].key)
                minIndex = j;
        }
        if (minIndex != i)
            swap(data[i], data[minIndex]);
    }
}

void insertionSort(vector<Record>& data)
{
    int n = data.size();
    for (int i = 1; i < n; i++)
    {
        Record current = data[i];
        int j = i - 1;
        while (j >= 0 && data[j].key > current.key)
        {
            data[j + 1] = data[j];
            j--;
        }
        data[j + 1] = current;
    }
}

// w danych wejsciowych id ida po kolei (A, B, C...), wiec sortowanie jest
// stabilne, jesli przy rownych kluczach id dalej ida alfabetycznie
bool isStable(vector<Record> data)
{
    int n = data.size();
    for (int i = 0; i < n - 1; i++)
    {
        if (data[i].key == data[i + 1].key && data[i].id > data[i + 1].id)
            return false;
    }
    return true;
}

void testZad3(string name, vector<Record> data)
{
    cout << name << ": ";
    printRecords(data);
    cout << "   stabilne? " << (isStable(data) ? "TAK" : "NIE") << endl;
}

// ===================== main =====================

int main()
{
    // ----- Zadanie 1 -----
    cout << "===== Zadanie 1 =====" << endl;
    testZad1("losowe", {7, 2, 9, 4, 1, 8, 3});
    testZad1("uporzadkowane", {1, 2, 3, 4, 5, 6, 7});
    testZad1("odwrotnie", {7, 6, 5, 4, 3, 2, 1});
    testZad1("z powtorzeniami", {5, 2, 8, 2, 5, 1, 8});
    testZad1("jeden element", {42});
    testZad1("pusta", {});

    // ----- Zadanie 2 -----
    cout << endl << "===== Zadanie 2 =====" << endl;
    srand(123);  // stale ziarno -> za kazdym razem te same "losowe" dane

    cout << "Eksperyment 1 - dane losowe" << endl;
    printHeader("n");
    int sizes[] = {100, 1000, 5000, 10000};
    for (int n : sizes)
    {
        vector<int> input = randomData(n);  // jeden zestaw dla wszystkich algorytmow
        measureAll(to_string(n), input);
    }

    int n = 5000;
    cout << endl << "Eksperyment 2 - rodzaj danych (n = " << n << ")" << endl;
    printHeader("Dane");
    measureAll("losowe", randomData(n));
    measureAll("rosnace", ascendingData(n));
    measureAll("malejace", descendingData(n));
    measureAll("prawie posort.", almostSortedData(n));

    // ----- Zadanie 3 -----
    cout << endl << "===== Zadanie 3 =====" << endl;
    vector<Record> records = {{3, 'A'}, {1, 'B'}, {3, 'C'}, {2, 'D'}, {1, 'E'}, {3, 'F'}};
    cout << "Dane: ";
    printRecords(records);

    vector<Record> r1 = records;
    vector<Record> r2 = records;
    vector<Record> r3 = records;
    bubbleSort(r1);
    selectionSort(r2);
    insertionSort(r3);
    testZad3("Bubble Sort   ", r1);
    testZad3("Selection Sort", r2);
    testZad3("Insertion Sort", r3);

    return 0;
}
