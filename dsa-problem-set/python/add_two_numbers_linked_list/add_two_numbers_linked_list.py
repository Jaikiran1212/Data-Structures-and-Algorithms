import sys

# A single node of a singly linked list. Each node stores one digit.
class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


class LinkedListAdd:

    # Adds two numbers that are represented as linked lists (one digit
    # per node) and returns the head of the resulting linked list.
    @staticmethod
    def addTwoNumber(l1, l2):
        temp = Node(0)      # dummy head node, makes list building easier
        current = temp
        carry = 0

        # Keep going while either list still has nodes, or there is a
        # leftover carry to push into a new node.
        while l1 is not None or l2 is not None or carry != 0:
            if l1 is not None:
                x = l1.data
            else:
                x = 0
            if l2 is not None:
                y = l2.data
            else:
                y = 0

            sum = x + y + carry
            carry = sum // 10

            current.next = Node(sum % 10)
            current = current.next

            if l1 is not None:
                l1 = l1.next
            if l2 is not None:
                l2 = l2.next

        return temp.next  # skip the dummy head


# Prints a linked list in "a -> b -> c" format.
def printList(head):
    current = head

    while current is not None:
        print(current.data, end="")
        if current.next is not None:
            print(" -> ", end="")
        current = current.next

    print()


def main():
    # Read all input at once and split into tokens for easy parsing.
    data = sys.stdin.read().split()
    index = 0
    T = int(data[index])
    index += 1

    while T > 0:

        N = int(data[index])
        index += 1
        M = int(data[index])
        index += 1

        # Build the first linked list from N input digits.
        temp1 = Node(0)
        current1 = temp1

        for i in range(N):
            value = int(data[index])
            index += 1
            current1.next = Node(value)
            current1 = current1.next

        # Build the second linked list from M input digits.
        temp2 = Node(0)
        current2 = temp2

        for i in range(M):
            value = int(data[index])
            index += 1
            current2.next = Node(value)
            current2 = current2.next

        # Add the two lists and print the result.
        result = LinkedListAdd.addTwoNumber(
            temp1.next,
            temp2.next
        )
        printList(result)
        T -= 1


main()
