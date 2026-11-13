#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

// Globalne liczniki - dzieki nim funkcje maja dokladnie takie naglowki jak w tresci zadania
struct Stats
{
    long long comparisons = 0;  // porownania elementow
    long long swaps = 0;        // zamiany (Quick Sort)
    int maxDepth = 0;           // maksymalna glebokosc rekurencji Quick Sort
};

Stats stats;
int depth = 0;              // aktualna glebokosc rekurencji Quick Sort
bool randomPivot = false;   // false = pivot to ostatni element, true = pivot losowy
bool showSteps = false;     // czy wypisywac podzialy i scalania w Merge Sort

void resetStats()
{
    stats.comparisons = 0;
    stats.swaps = 0;
    stats.maxDepth = 0;
    depth = 0;
}

void printVector(vector<int> data)
{
    if (data.empty())
        cout << "(pusta)";
    for (int x : data)
        cout << x << " ";
    cout << endl;
}

// wypisuje fragment tablicy od left do right, np. [3 8]
void printRange(vector<int>& data, int left, int right)
{
    cout << "[";
    for (int i = left; i <= right; i++)
    {
        cout << data[i];
        if (i < right)
            cout << " ";
    }
    cout << "]";
}

// ===================== Zadanie 1 - Merge Sort =====================

// scala dwa posortowane fragmenty: data[left..mid] i data[mid+1..right]
void merge(vector<int>& data, int left, int mid, int right)
{
    vector<int> temp;  // pomocnicza tablica na scalony fragment
    int i = left;      // indeks w lewej czesci
    int j = mid + 1;   // indeks w prawej czesci

    // biore mniejszy z dwoch pierwszych elementow, dopoki obie czesci maja elementy
    while (i <= mid && j <= right)
    {
        stats.comparisons++;
        if (data[i] <= data[j])
        {
            temp.push_back(data[i]);
            i++;
        }
        else
        {
            temp.push_back(data[j]);
            j++;
        }
    }

    // dopisuje to, co zostalo w jednej z czesci
    while (i <= mid)
    {
        temp.push_back(data[i]);
        i++;
    }
    while (j <= right)
    {
        temp.push_back(data[j]);
        j++;
    }

    // przepisuje scalony fragment z powrotem do data
    for (int k = 0; k < (int)temp.size(); k++)
        data[left + k] = temp[k];
}

// dzieli fragment na pol, sortuje obie polowy rekurencyjnie i je scala
void mergeSort(vector<int>& data, int left, int right)
{
    if (left >= right)  // przypadek bazowy: 0 albo 1 element
        return;

    int mid = (left + right) / 2;

    if (showSteps)
    {
        cout << "podzial: ";
        printRange(data, left, right);
        cout << " -> ";
        printRange(data, left, mid);
        cout << " | ";
        printRange(data, mid + 1, right);
        cout << endl;
    }

    mergeSort(data, left, mid);
    mergeSort(data, mid + 1, right);

    if (showSteps)
    {
        cout << "scalam ";
        printRange(data, left, mid);
        cout << " i ";
        printRange(data, mid + 1, right);
    }

    merge(data, left, mid, right);

    if (showSteps)
    {
        cout << " -> ";
        printRange(data, left, right);
        cout << endl;
    }
}

void testMerge(string name, vector<int> data)
{
    int n = data.size();
    cout << name << ": ";
    printVector(data);
    mergeSort(data, 0, n - 1);
    cout << "   Merge Sort: ";
    printVector(data);
}

// ===================== Zadanie 2 - Quick Sort =====================

// ustawia pivot na jego docelowym miejscu: mniejsze od pivota na lewo, reszta na prawo;
// zwraca pozycje pivota
int partition(vector<int>& data, int left, int right)
{
    if (randomPivot)
    {
        // losowy element przenosze na koniec i dalej dziala tak samo jak dla ostatniego
        int r = left + rand() % (right - left + 1);
        swap(data[r], data[right]);
        stats.swaps++;
    }

    int pivot = data[right];
    int i = left - 1;  // koniec czesci z elementami mniejszymi od pivota

    for (int j = left; j < right; j++)
    {
        stats.comparisons++;
        if (data[j] < pivot)
        {
            i++;
            swap(data[i], data[j]);
            stats.swaps++;
        }
    }

    swap(data[i + 1], data[right]);  // pivot wstawiam zaraz za mniejszymi
    stats.swaps++;
    return i + 1;
}

// partycjonuje fragment i rekurencyjnie sortuje czesc na lewo i na prawo od pivota
void quickSort(vector<int>& data, int left, int right)
{
    if (left >= right)  // przypadek bazowy: 0 albo 1 element
        return;

    depth++;
    if (depth > stats.maxDepth)
        stats.maxDepth = depth;

    int p = partition(data, left, right);
    quickSort(data, left, p - 1);
    quickSort(data, p + 1, right);

    depth--;
}

void testQuick(string name, vector<int> data)
{
    int n = data.size();
    cout << name << ": ";
    printVector(data);
    quickSort(data, 0, n - 1);
    cout << "   Quick Sort: ";
    printVector(data);
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

// Quick Sort na tych samych danych z pivotem ostatnim i losowym; wypisuje 2 wiersze tabeli
void quickExperiment(string dataName, vector<int> original)
{
    int n = original.size();
    for (int strategy = 0; strategy < 2; strategy++)
    {
        vector<int> data = original;  // kazda strategia dostaje te same dane
        randomPivot = (strategy == 1);
        resetStats();
        quickSort(data, 0, n - 1);

        cout << setw(10) << dataName << setw(8) << n
             << setw(10) << (randomPivot ? "losowy" : "ostatni")
             << setw(14) << stats.comparisons << setw(12) << stats.swaps
             << setw(16) << stats.maxDepth << endl;
    }
    randomPivot = false;
}

// ===================== Zadanie 4 - k-ty najmniejszy =====================

// Czesc A: sortuje kopie (Merge Sort) i odczytuje element o indeksie k-1
int kthBySorting(vector<int> data, int k)
{
    int n = data.size();
    mergeSort(data, 0, n - 1);
    return data[k - 1];
}

// Czesc B: partycjonuje i szuka dalej tylko w tej czesci, w ktorej jest k-ty element
int quickSelect(vector<int>& data, int left, int right, int k)
{
    int p = partition(data, left, right);  // pivot stoi na swoim docelowym miejscu p

    if (p == k - 1)
        return data[p];                                // pivot jest wynikiem
    else if (p > k - 1)
        return quickSelect(data, left, p - 1, k);     // szukam po lewej
    else
        return quickSelect(data, p + 1, right, k);    // szukam po prawej
}

void testKth(vector<int> data, int k)
{
    int n = data.size();
    if (k < 1 || k > n)
    {
        cout << "k = " << k << ": poza zakresem" << endl;
        return;
    }
    vector<int> copy = data;  // quickSelect zmienia kolejnosc, wiec daje mu kopie
    int resultA = kthBySorting(data, k);
    int resultB = quickSelect(copy, 0, n - 1, k);
    cout << "k = " << k << ": przez sortowanie = " << resultA
         << ", quickSelect = " << resultB << endl;
}

// ===================== main =====================

int main()
{
    srand(123);  // stale ziarno -> za kazdym razem te same "losowe" dane

    // ----- Zadanie 1 -----
    cout << "===== Zadanie 1 - Merge Sort =====" << endl;
    vector<int> example = {8, 3, 6, 2};
    cout << "Kroki dla 8 3 6 2:" << endl;
    showSteps = true;
    mergeSort(example, 0, 3);
    showSteps = false;
    cout << endl;

    testMerge("przyklad", {8, 3, 6, 2, 7, 1, 5, 4});
    testMerge("losowe", {7, 2, 9, 4, 1, 8, 3});
    testMerge("rosnace", {1, 2, 3, 4, 5, 6, 7});
    testMerge("malejace", {7, 6, 5, 4, 3, 2, 1});
    testMerge("powtorzenia", {5, 2, 8, 2, 1, 5, 8});
    testMerge("jeden element", {42});
    testMerge("pusta", {});

    // ----- Zadanie 2 -----
    cout << endl << "===== Zadanie 2 - Quick Sort =====" << endl;
    cout << "Czesc A (pivot = ostatni element):" << endl;
    testQuick("losowe", {7, 2, 9, 4, 1, 8, 3});
    testQuick("rosnace", {1, 2, 3, 4, 5, 6, 7});
    testQuick("malejace", {7, 6, 5, 4, 3, 2, 1});
    testQuick("powtorzenia", {5, 2, 8, 2, 1, 5, 8});
    testQuick("jeden element", {42});
    testQuick("pusta", {});

    cout << endl << "Czesc B - strategie wyboru pivota:" << endl;
    cout << setw(10) << "Dane" << setw(8) << "n" << setw(10) << "Pivot"
         << setw(14) << "Porownania" << setw(12) << "Zamiany"
         << setw(16) << "Maks. glebokosc" << endl;
    int sizesB[] = {100, 1000, 5000, 10000};
    for (int n : sizesB)
    {
        quickExperiment("losowe", randomData(n));
        quickExperiment("rosnace", ascendingData(n));
        quickExperiment("malejace", descendingData(n));
    }

    // ----- Zadanie 4 -----
    cout << endl << "===== Zadanie 4 - k-ty najmniejszy =====" << endl;
    vector<int> arr = {8, 3, 1, 7, 4, 9, 2};
    cout << "Tablica: ";
    printVector(arr);
    testKth(arr, 1);
    testKth(arr, 3);
    testKth(arr, 7);

    vector<int> dup = {5, 2, 8, 2, 1, 5, 8};
    cout << "Tablica z powtorzeniami: ";
    printVector(dup);
    testKth(dup, 1);
    testKth(dup, 3);
    testKth(dup, 4);
    testKth(dup, 7);

    return 0;
}
