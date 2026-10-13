# Laboratorium 2 - Listy dynamiczne (Python)
# W Pythonie zamiast nullptr jest None, a pamiec po usunietych wezlach
# zwalnia automatycznie garbage collector.


class Node:
    """Wezel listy: wartosc + wskaznik na nastepny wezel."""

    def __init__(self, value, next=None):
        self.value = value
        self.next = next


class LinkedList:
    """Lista jednokierunkowa. head to pierwszy wezel (None = lista pusta)."""

    def __init__(self):
        self.head = None

    # ---------------- Zadanie 1 ----------------

    def pushFront(self, value):
        # nowy wezel wskazuje na stary poczatek i sam staje sie poczatkiem
        self.head = Node(value, self.head)

    def printList(self):
        if self.head is None:
            print("(pusta lista)")
            return
        current = self.head
        while current is not None:
            print(current.value, end="")
            if current.next is not None:
                print(" -> ", end="")
            current = current.next
        print()

    def size(self):
        count = 0
        current = self.head
        while current is not None:
            count += 1
            current = current.next
        return count

    def clear(self):
        # odpinamy kolejne wezly od poczatku; nieosiagalne wezly usuwa Python
        while self.head is not None:
            self.head = self.head.next

    # ---------------- Zadanie 2 ----------------

    def pushBack(self, value):
        new_node = Node(value)
        if self.head is None:
            self.head = new_node
            return
        current = self.head
        while current.next is not None:  # idziemy do ostatniego wezla
            current = current.next
        current.next = new_node

    def contains(self, value):
        current = self.head
        while current is not None:
            if current.value == value:
                return True
            current = current.next
        return False

    def removeFirst(self, value):
        if self.head is None:  # pusta lista
            return False
        if self.head.value == value:  # usuwamy pierwszy element
            self.head = self.head.next
            return True
        current = self.head
        while current.next is not None:
            if current.next.value == value:
                current.next = current.next.next  # "przeskakujemy" usuwany wezel
                return True
            current = current.next
        return False  # wartosci nie ma w liscie

    # ---------------- Zadanie 3 ----------------

    def insertSorted(self, value):
        # pusta lista albo wartosc najmniejsza -> wstawiamy na poczatek
        if self.head is None or value <= self.head.value:
            self.pushFront(value)
            return
        # szukamy ostatniego wezla mniejszego od value i wstawiamy za nim
        current = self.head
        while current.next is not None and current.next.value < value:
            current = current.next
        current.next = Node(value, current.next)

    # ---------------- Zadanie 4 ----------------

    def reverse(self):
        prev = None
        current = self.head
        while current is not None:
            next_node = current.next  # zapamietujemy dalsza czesc listy
            current.next = prev       # odwracamy strzalke
            prev = current            # przesuwamy sie o jeden krok
            current = next_node
        self.head = prev              # ostatni wezel staje sie pierwszym


def fromValues(*values):
    """Pomocnicza: buduje liste z podanych wartosci (do przykladow)."""
    lst = LinkedList()
    for v in values:
        lst.pushBack(v)
    return lst


if __name__ == "__main__":
    print("=== Zadanie 1 ===")
    lst = LinkedList()
    lst.pushFront(5)
    lst.pushFront(8)
    lst.pushFront(2)
    lst.printList()                     # 2 -> 8 -> 5
    print("size:", lst.size())          # 3
    lst.clear()
    lst.printList()                     # (pusta lista)
    print("size po clear:", lst.size())  # 0

    print("\n=== Zadanie 2 ===")
    lst = fromValues(4, 7, 2, 7, 9)
    lst.printList()                     # 4 -> 7 -> 2 -> 7 -> 9
    lst.removeFirst(7)
    lst.printList()                     # 4 -> 2 -> 7 -> 9
    print("contains(2):", lst.contains(2))    # True
    print("contains(100):", lst.contains(100))  # False
    print("usun pierwszy (4):", lst.removeFirst(4))
    print("usun ostatni (9):", lst.removeFirst(9))
    print("usun nieobecny (100):", lst.removeFirst(100))
    lst.printList()                     # 2 -> 7
    print("removeFirst na pustej:", LinkedList().removeFirst(1))  # False

    print("\n=== Zadanie 3 ===")
    for value in (7, 1, 20):
        lst = fromValues(2, 5, 8, 12)
        lst.insertSorted(value)
        print("wstaw", value, "=> ", end="")
        lst.printList()
    lst = LinkedList()
    lst.insertSorted(3)
    print("pusta lista, wstaw 3 => ", end="")
    lst.printList()

    print("\n=== Zadanie 4 ===")
    lst = fromValues(2, 5, 8, 12)
    lst.printList()                     # 2 -> 5 -> 8 -> 12
    lst.reverse()
    lst.printList()                     # 12 -> 8 -> 5 -> 2
