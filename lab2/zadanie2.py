# Zadanie 2 - pushBack, contains, removeFirst


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

    def pushBack(self, value):
        new_node = Node(value)
        if self.head is None:          # lista pusta -> nowy węzeł jest pierwszy
            self.head = new_node
            return
        current = self.head
        while current.next is not None:  # idziemy aż do ostatniego węzła
            current = current.next
        current.next = new_node          # doczepiamy nowy węzeł na koniec

    def contains(self, value):
        current = self.head
        while current is not None:
            if current.value == value:
                return True
            current = current.next
        return False

    def removeFirst(self, value):
        if self.head is None:            # lista pusta -> nie ma czego usuwać
            return False
        if self.head.value == value:     # usuwamy pierwszy element
            self.head = self.head.next
            return True
        current = self.head
        while current.next is not None:  # szukamy węzła PRZED tym do usunięcia
            if current.next.value == value:
                current.next = current.next.next  # omijamy usuwany węzeł
                return True
            current = current.next
        return False                     # wartości nie ma w liście


lista = LinkedList()
for x in [4, 7, 2, 7, 9]:
    lista.pushBack(x)
lista.printList()                                # 4 -> 7 -> 2 -> 7 -> 9
lista.removeFirst(7)
lista.printList()                                # 4 -> 2 -> 7 -> 9

print("Czy jest 2?", lista.contains(2))          # True
print("Czy jest 100?", lista.contains(100))      # False

print("Usun pierwszy (4):", lista.removeFirst(4))     # True
print("Usun ostatni (9):", lista.removeFirst(9))      # True
print("Usun nieobecny (100):", lista.removeFirst(100))  # False
lista.printList()                                # 2 -> 7

pusta = LinkedList()
print("Usun z pustej:", pusta.removeFirst(5))    # False
