from collections import deque


# Empties the stack into the queue, one element at a time.
def stack2queue(s, q):
    while s:
        q.append(s.pop())


# Empties the queue into the stack, one element at a time.
def queue2stack(q, s):
    while q:
        s.append(q.popleft())


# Reverses ("mirrors") the contents of a stack using only an auxiliary
# queue as extra storage.
def mirror(s):
    if s is None:
        raise ValueError("Stack can't be null")
    if not s:
        return

    q = deque()

    # Draining the stack into a queue (LIFO -> FIFO) and then draining
    # that queue back into the stack (FIFO -> LIFO) reverses the order
    # of the elements exactly once, which mirrors the stack.
    stack2queue(s, q)
    queue2stack(q, s)


def main():
    # A Python list is used as the stack: append() = push, pop() = pop.
    s = [1, 2, 3, 4, 5]

    print("Before mirror:", s)
    mirror(s)
    print("After mirror:", s)


main()
