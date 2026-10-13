# Zadanie 3 - wstawianie do listy posortowanej rosnąco


class Node:
    def __init__(self, value):
        self.value = value
        self.next = None


class LinkedList:
    def __init__(self):
        self.head = None

    def printList(self):
        current = self.head
        while current is not None:
            print(current.value, end="")
            if current.next is not None:
                print(" -> ", end="")
            current = current.next
        print()

    def insertSorted(self, value):
        new_node = Node(value)

        # lista pusta albo nowa wartość jest najmniejsza -> wstawiamy na początek
        if self.head is None or value < self.head.value:
            new_node.next = self.head
            self.head = new_node
            return

        # idziemy dalej, dopóki następny węzeł jest mniejszy od nowej wartości
        current = self.head
        while current.next is not None and current.next.value < value:
            current = current.next

        # wstawiamy nowy węzeł zaraz za current
        new_node.next = current.next
        current.next = new_node


lista = LinkedList()
lista.insertSorted(3)
lista.printList()      # 3   (wstawianie do pustej listy)

lista = LinkedList()
for x in [2, 5, 8, 12]:
    lista.insertSorted(x)
lista.printList()      # 2 -> 5 -> 8 -> 12

lista.insertSorted(7)
lista.printList()      # 2 -> 5 -> 7 -> 8 -> 12

lista.insertSorted(1)
lista.printList()      # 1 -> 2 -> 5 -> 7 -> 8 -> 12

lista.insertSorted(20)
lista.printList()      # 1 -> 2 -> 5 -> 7 -> 8 -> 12 -> 20
