# Zadanie 1 - lista jednokierunkowa: pushFront, printList, size, clear


class Node:
    def __init__(self, value):
        self.value = value  # liczba zapisana w węźle
        self.next = None    # wskaźnik na następny węzeł (None = nie ma następnego)


class LinkedList:
    def __init__(self):
        self.head = None  # wskaźnik na pierwszy węzeł (None = lista pusta)

    def pushFront(self, value):
        new_node = Node(value)     # 1. tworzymy nowy węzeł
        new_node.next = self.head  # 2. nowy węzeł wskazuje na dotychczasowy pierwszy
        self.head = new_node       # 3. nowy węzeł staje się pierwszym

    def printList(self):
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
        while self.head is not None:
            self.head = self.head.next  # odpinamy pierwszy węzeł, Python sam zwalnia jego pamięć


lista = LinkedList()
lista.pushFront(5)
lista.pushFront(8)
lista.pushFront(2)
lista.printList()                         # 2 -> 8 -> 5
print("Rozmiar:", lista.size())           # 3
lista.clear()
print("Rozmiar po clear:", lista.size())  # 0
