# Zadanie 4 - odwracanie listy bez tworzenia drugiej listy


class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def pushFront(self, value):
        new_node = Node(value)
        new_node.next = self.head
        self.head = new_node

    def printList(self):
        current = self.head
        while current is not None:
            print(current.value, end="")
            if current.next is not None:
                print(" -> ", end="")
            current = current.next
        print()

    def reverse(self):
        prev = None          # węzeł "za nami" (na początku nie ma żadnego)
        current = self.head  # węzeł, który teraz obracamy
        while current is not None:
            next_node = current.next  # 1. zapamiętujemy, gdzie jest reszta listy
            current.next = prev       # 2. odwracamy strzałkę - teraz wskazuje do tyłu
            prev = current            # 3. przesuwamy się o jeden krok do przodu
            current = next_node
        self.head = prev     # dawny ostatni węzeł jest teraz pierwszy


lista = LinkedList()
lista.pushFront(12)
lista.pushFront(8)
lista.pushFront(5)
lista.pushFront(2)
lista.printList()   # 2 -> 5 -> 8 -> 12
lista.reverse()
lista.printList()   # 12 -> 8 -> 5 -> 2
