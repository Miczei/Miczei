#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <climits>
#include <iomanip>
#include <algorithm>
using namespace std;

// jeden typ wezla dla BST i AVL; pole height wykorzystuje tylko AVL (zad. 3)
struct Node
{
    int value;
    Node* left;
    Node* right;
    int height;
};

bool showRotations = false;  // czy wypisywac wykonane rotacje AVL

// tworzy nowy wezel bez dzieci
Node* createNode(int value)
{
    Node* node = new Node;
    node->value = value;
    node->left = nullptr;
    node->right = nullptr;
    node->height = 0;  // wysokosc liczona w krawedziach: lisc ma 0
    return node;
}

// ===================== Zadanie 1 - BST =====================

// dodaje wartosc: mniejsze ida w lewo, wieksze w prawo; duplikaty pomijam
void insert(Node*& root, int value)
{
    if (root == nullptr)
    {
        root = createNode(value);
        return;
    }
    if (value < root->value)
        insert(root->left, value);
    else if (value > root->value)
        insert(root->right, value);
    // value == root->value -> duplikat, nic nie robie
}

// szuka wartosci: mniejsza -> idzie w lewo, wieksza -> w prawo
bool contains(Node* root, int value)
{
    Node* current = root;
    while (current != nullptr)
    {
        if (value == current->value)
            return true;
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return false;
}

// najmniejszy element jest najbardziej na lewo
Node* findMin(Node* root)
{
    if (root == nullptr)
        return nullptr;
    Node* current = root;
    while (current->left != nullptr)
        current = current->left;
    return current;
}

// najwiekszy element jest najbardziej na prawo
Node* findMax(Node* root)
{
    if (root == nullptr)
        return nullptr;
    Node* current = root;
    while (current->right != nullptr)
        current = current->right;
    return current;
}

// LEWO -> KORZEN -> PRAWO; dla BST wypisuje wartosci rosnaco
void inorder(Node* root)
{
    if (root == nullptr)
        return;
    inorder(root->left);
    cout << root->value << " ";
    inorder(root->right);
}

// KORZEN -> LEWO -> PRAWO; pokazuje ksztalt drzewa (korzen jest pierwszy)
void preorder(Node* root)
{
    if (root == nullptr)
        return;
    cout << root->value << " ";
    preorder(root->left);
    preorder(root->right);
}

// wysokosc = liczba krawedzi na najdluzszej drodze od korzenia do liscia
// (puste drzewo ma -1, pojedynczy wezel 0)
int height(Node* root)
{
    if (root == nullptr)
        return -1;
    return 1 + max(height(root->left), height(root->right));
}

// usuwa cale drzewo metoda postorder: najpierw dzieci, potem wezel
void deleteTree(Node*& root)
{
    if (root == nullptr)
        return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
    root = nullptr;
}

// ===================== Zadanie 2 - usuwanie i isBST =====================

// usuwa wartosc z BST i zwraca nowy korzen (pod)drzewa
Node* remove(Node* root, int value)
{
    if (root == nullptr)  // nie ma takiej wartosci
        return nullptr;

    if (value < root->value)
        root->left = remove(root->left, value);
    else if (value > root->value)
        root->right = remove(root->right, value);
    else
    {
        // przypadek 1: lisc -> po prostu usuwam
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            return nullptr;
        }
        // przypadek 2: jedno dziecko -> dziecko zajmuje miejsce usuwanego wezla
        if (root->left == nullptr)
        {
            Node* child = root->right;
            delete root;
            return child;
        }
        if (root->right == nullptr)
        {
            Node* child = root->left;
            delete root;
            return child;
        }
        // przypadek 3: dwoje dzieci -> wstawiam wartosc nastepnika inorder
        // (najmniejszy w prawym poddrzewie) i usuwam tego nastepnika
        Node* successor = findMin(root->right);
        root->value = successor->value;
        root->right = remove(root->right, successor->value);
    }
    return root;
}

// sprawdza, czy kazdy wezel miesci sie w dozwolonym zakresie (minValue, maxValue)
bool isBSTRange(Node* node, long long minValue, long long maxValue)
{
    if (node == nullptr)
        return true;
    if (node->value <= minValue || node->value >= maxValue)
        return false;
    // w lewym poddrzewie wszystko musi byc < node->value, w prawym > node->value
    return isBSTRange(node->left, minValue, node->value) &&
           isBSTRange(node->right, node->value, maxValue);
}

bool isBST(Node* root)
{
    return isBSTRange(root, LLONG_MIN, LLONG_MAX);
}

// liczy, ile wezlow trzeba porownac, zeby znalezc wartosc
int searchComparisons(Node* root, int value)
{
    int count = 0;
    Node* current = root;
    while (current != nullptr)
    {
        count++;
        if (value == current->value)
            break;
        if (value < current->value)
            current = current->left;
        else
            current = current->right;
    }
    return count;
}

Node* buildBST(vector<int> values)
{
    Node* root = nullptr;
    for (int v : values)
        insert(root, v);
    return root;
}

// ===================== Zadanie 3 - AVL =====================

// wysokosc zapisana w wezle (puste poddrzewo = -1)
int getHeight(Node* node)
{
    if (node == nullptr)
        return -1;
    return node->height;
}

// wspolczynnik rownowagi BF = h_left - h_right
int getBalance(Node* node)
{
    if (node == nullptr)
        return 0;
    return getHeight(node->left) - getHeight(node->right);
}

// przelicza wysokosc wezla na podstawie wysokosci dzieci
void updateHeight(Node* node)
{
    node->height = 1 + max(getHeight(node->left), getHeight(node->right));
}

// rotacja w prawo: lewe dziecko staje sie nowym korzeniem
Node* rotateRight(Node* node)
{
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// rotacja w lewo: prawe dziecko staje sie nowym korzeniem
Node* rotateLeft(Node* node)
{
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    updateHeight(node);
    updateHeight(newRoot);
    return newRoot;
}

// dodaje jak w zwyklym BST, a potem w drodze powrotnej sprawdza BF i robi rotacje
Node* insertAVL(Node* node, int value)
{
    if (node == nullptr)
        return createNode(value);

    if (value < node->value)
        node->left = insertAVL(node->left, value);
    else if (value > node->value)
        node->right = insertAVL(node->right, value);
    else
        return node;  // duplikat

    updateHeight(node);
    int balance = getBalance(node);

    // LL: za ciezka lewa strona, nowa wartosc poszla w lewo-lewo
    if (balance > 1 && value < node->left->value)
    {
        if (showRotations)
            cout << "   LL przy " << node->value << " -> rotacja w prawo" << endl;
        return rotateRight(node);
    }
    // RR: za ciezka prawa strona, nowa wartosc poszla w prawo-prawo
    if (balance < -1 && value > node->right->value)
    {
        if (showRotations)
            cout << "   RR przy " << node->value << " -> rotacja w lewo" << endl;
        return rotateLeft(node);
    }
    // LR: za ciezka lewa strona, nowa wartosc poszla w lewo-prawo
    if (balance > 1 && value > node->left->value)
    {
        if (showRotations)
            cout << "   LR przy " << node->value << " -> rotacja w lewo, potem w prawo" << endl;
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // RL: za ciezka prawa strona, nowa wartosc poszla w prawo-lewo
    if (balance < -1 && value < node->right->value)
    {
        if (showRotations)
            cout << "   RL przy " << node->value << " -> rotacja w prawo, potem w lewo" << endl;
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* buildAVL(vector<int> values)
{
    Node* root = nullptr;
    for (int v : values)
        root = insertAVL(root, v);
    return root;
}

// dane rosnace 1, 2, ..., n
vector<int> ascendingData(int n)
{
    vector<int> data(n);
    for (int i = 0; i < n; i++)
        data[i] = i + 1;
    return data;
}

// liczby 1..n w losowej kolejnosci (bez powtorzen)
vector<int> shuffledData(int n)
{
    vector<int> data = ascendingData(n);
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        swap(data[i], data[j]);
    }
    return data;
}

// buduje BST i AVL z tych samych danych i wypisuje ich wysokosci
void compareBSTandAVL(string dataName, vector<int> values)
{
    Node* bst = buildBST(values);
    Node* avl = buildAVL(values);
    cout << setw(6) << values.size() << setw(10) << dataName
         << setw(14) << height(bst) << setw(14) << height(avl) << endl;
    deleteTree(bst);
    deleteTree(avl);
}

// pokazuje jeden przypadek rotacji na 3 wartosciach
void testRotation(string name, vector<int> values)
{
    cout << name << " (dodaje";
    for (int v : values)
        cout << " " << v;
    cout << "):" << endl;

    Node* root = buildAVL(values);
    cout << "   preorder po rownowazeniu: ";
    preorder(root);
    cout << "(korzen = " << root->value << ")" << endl;
    deleteTree(root);
}

// ===================== main =====================

int main()
{
    cout << boolalpha;  // true/false zamiast 1/0
    srand(123);

    // ----- Zadanie 1 -----
    cout << "===== Zadanie 1 - BST =====" << endl;
    Node* root = buildBST({8, 3, 12, 1, 6, 10, 15, 4, 7});
    cout << "inorder:  ";
    inorder(root);
    cout << endl;
    cout << "preorder: ";
    preorder(root);
    cout << endl;

    int toFind[] = {6, 10, 15, 5, 100};
    for (int v : toFind)
        cout << "contains(" << v << ") = " << contains(root, v) << endl;

    cout << "findMin = " << findMin(root)->value << endl;
    cout << "findMax = " << findMax(root)->value << endl;
    cout << "height = " << height(root) << endl;

    // ----- Zadanie 2 -----
    cout << endl << "===== Zadanie 2 - usuwanie i isBST =====" << endl;
    cout << "isBST(drzewo z zad. 1) = " << isBST(root) << endl;

    root = remove(root, 100);
    cout << "remove(100) - nie ma takiej wartosci: ";
    inorder(root);
    cout << endl;

    root = remove(root, 1);
    cout << "remove(1)   - lisc:                   ";
    inorder(root);
    cout << "| isBST = " << isBST(root) << endl;

    root = remove(root, 3);
    cout << "remove(3)   - jedno dziecko:          ";
    inorder(root);
    cout << "| isBST = " << isBST(root) << endl;

    root = remove(root, 8);
    cout << "remove(8)   - dwoje dzieci (korzen):  ";
    inorder(root);
    cout << "| isBST = " << isBST(root) << endl;
    cout << "nowy korzen = " << root->value << ", preorder: ";
    preorder(root);
    cout << endl;
    deleteTree(root);

    // niepoprawne BST z tresci zadania: 6 lezy w prawym poddrzewie 10
    Node* bad = createNode(10);
    bad->left = createNode(5);
    bad->right = createNode(15);
    bad->right->left = createNode(6);
    cout << "isBST(10, 5, 15, 6 pod 15) = " << isBST(bad) << endl;
    deleteTree(bad);

    cout << endl << "Wplyw kolejnosci danych:" << endl;
    Node* treeA = buildBST({1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
    Node* treeB = buildBST({6, 3, 8, 2, 4, 7, 9, 1, 5, 10});
    cout << "A (1 2 3 ... 10):           wysokosc = " << height(treeA)
         << ", porownania przy szukaniu 10 = " << searchComparisons(treeA, 10) << endl;
    cout << "B (6 3 8 2 4 7 9 1 5 10):   wysokosc = " << height(treeB)
         << ", porownania przy szukaniu 10 = " << searchComparisons(treeB, 10) << endl;
    deleteTree(treeA);
    deleteTree(treeB);

    // ----- Zadanie 3 -----
    cout << endl << "===== Zadanie 3 - AVL =====" << endl;
    showRotations = true;
    testRotation("LL", {30, 20, 10});
    testRotation("RR", {10, 20, 30});
    testRotation("LR", {30, 10, 20});
    testRotation("RL", {10, 30, 20});
    showRotations = false;

    cout << endl << "Porownanie wysokosci BST i AVL:" << endl;
    cout << setw(6) << "n" << setw(10) << "Dane"
         << setw(14) << "Wys. BST" << setw(14) << "Wys. AVL" << endl;
    compareBSTandAVL("rosnace", ascendingData(10));
    compareBSTandAVL("rosnace", ascendingData(100));
    compareBSTandAVL("rosnace", ascendingData(1000));
    compareBSTandAVL("losowe", shuffledData(100));
    compareBSTandAVL("losowe", shuffledData(1000));

    return 0;
}
