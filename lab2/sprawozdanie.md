# Sprawozdanie – Laboratorium 2: Listy dynamiczne

Język: Python. Kod: `listy.py` (uruchomienie: `python listy.py`).

## Opis implementacji

Lista jednokierunkowa składa się z dwóch klas:

- `Node` – węzeł, przechowuje `value` (wartość) i `next` (wskaźnik na następny węzeł).
- `LinkedList` – przechowuje `head`, czyli wskaźnik na pierwszy węzeł. Pusta lista: `head is None`.

W Pythonie odpowiednikiem `nullptr` jest `None`. Pamięć po węźle, na który nic już nie wskazuje,
zwalnia automatycznie garbage collector (odpowiednik `delete` z C++). Wszystkie funkcje są metodami
klasy `LinkedList`, dzięki czemu mogą zmieniać `head` (odpowiednik `Node*& head` z C++).

## Zadanie 1

| Funkcja       | Złożoność | Uzasadnienie                                             |
|---------------|-----------|----------------------------------------------------------|
| `pushFront()` | O(1)      | tworzy węzeł i przestawia `head` – nie zależy od n       |
| `printList()` | O(n)      | przechodzi przez wszystkie elementy                      |
| `size()`      | O(n)      | liczy elementy, przechodząc przez całą listę             |
| `clear()`     | O(n)      | odłącza kolejno każdy z n węzłów                         |

Przykład: `pushFront(5)`, `pushFront(8)`, `pushFront(2)` → `2 -> 8 -> 5`.

## Zadanie 2

- `pushBack()` – przechodzi do ostatniego węzła i dopina za nim nowy (dla pustej listy ustawia `head`).
- `contains()` – przechodzi po liście, aż znajdzie wartość albo dojdzie do końca.
- `removeFirst()` – szuka węzła **poprzedzającego** szukaną wartość i ustawia jego `next`
  na węzeł za usuwanym. Osobno obsłużone: pusta lista, usuwanie pierwszego elementu
  (zmiana `head`), brak wartości (zwraca `False`).

Przykład: `4 -> 7 -> 2 -> 7 -> 9`, `removeFirst(7)` → `4 -> 2 -> 7 -> 9`.

**Odpowiedzi:**

1. `pushBack()` ma złożoność **O(n)** – trzeba dojść od `head` do ostatniego elementu.
2. `contains()` ma złożoność **O(n)** (najlepszy przypadek O(1), gdy wartość jest na początku).
3. `removeFirst()` ma złożoność **O(n)** – samo przepięcie wskaźnika to O(1), ale najpierw trzeba znaleźć element.
4. **Tak** – wystarczy pamiętać dodatkowy wskaźnik `tail` na ostatni element. Wtedy nowy węzeł
   dopinamy od razu za `tail`, bez przechodzenia przez listę, i `pushBack()` ma złożoność **O(1)**
   (trzeba tylko pilnować aktualizacji `tail`, np. przy usuwaniu ostatniego elementu).

## Zadanie 3 – `insertSorted()`

Jeśli lista jest pusta albo nowa wartość jest ≤ pierwszemu elementowi – wstawiamy na początek.
W przeciwnym razie idziemy po liście, dopóki następny element jest mniejszy od wstawianej wartości,
i wstawiamy nowy węzeł za bieżącym.

Przykłady: wstaw 7 → `2 -> 5 -> 7 -> 8 -> 12`, wstaw 1 → `1 -> 2 -> 5 -> 8 -> 12`,
wstaw 20 → `2 -> 5 -> 8 -> 12 -> 20`, pusta lista – wstaw 3 → `3`.

- **Najlepszy przypadek:** lista pusta lub wartość najmniejsza (wstawienie na początek) – **O(1)**.
- **Najgorszy przypadek:** wartość największa (wstawienie na koniec) – trzeba przejść całą listę – **O(n)**.
- **Złożoność czasowa:** **O(n)**. Pamięciowa: O(1) (tylko jeden nowy węzeł).

## Zadanie 4 – `reverse()`

Używamy trzech wskaźników: `prev`, `current`, `next_node`. Dla każdego węzła zapamiętujemy dalszą
część listy (`next_node`), odwracamy jego strzałkę (`current.next = prev`) i przesuwamy się dalej.
Na końcu `head` wskazuje na dawny ostatni element. Nie tworzymy żadnej nowej listy ani tablicy.

Przykład: `2 -> 5 -> 8 -> 12` → `12 -> 8 -> 5 -> 2`.

**Odpowiedzi:**

1. Przez listę przechodzimy **jeden raz**.
2. Złożoność czasowa: **O(n)**.
3. Złożoność pamięciowa: **O(1)** – tylko kilka pomocniczych wskaźników, niezależnie od długości listy.
4. Bo każdy węzeł nadal wskazuje (`next`) na element, który był za nim w starej kolejności.
   Gdybyśmy tylko ustawili `head` na ostatni element, to jego `next` jest `None`, więc lista
   miałaby jeden element, a reszta zostałaby zgubiona. W liście jednokierunkowej nie da się iść
   wstecz – trzeba odwrócić kierunek **wszystkich** wskaźników `next`.

## Wnioski

Lista jednokierunkowa pozwala szybko (O(1)) dodawać i usuwać elementy na początku, ale dostęp
do dalszych elementów, wyszukiwanie i dodawanie na końcu (bez wskaźnika `tail`) wymagają przejścia
przez listę – O(n). Wybór między listą a tablicą zależy od tego, które operacje są wykonywane najczęściej.
