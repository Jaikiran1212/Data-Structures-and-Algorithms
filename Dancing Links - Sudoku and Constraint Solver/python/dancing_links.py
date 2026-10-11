"""
dancing_links.py
-----------------
A general "exact cover" solver using Knuth's Dancing Links (DLX) idea.

What is exact cover?
    We have some COLUMNS (things that must be covered) and some ROWS
    (choices). Each row covers a few columns. We must pick rows so that
    EVERY column is covered EXACTLY ONCE.

How the data is stored (plain lists used as arrays, no classes for nodes):
    Every "1" in the matrix is a node. A node has 4 links:
    left, right, up, down  -> they form circular doubly linked lists.
    Node 0                 -> the root (the start of the column-header list)
    Nodes 1..num_columns   -> the column headers
    Nodes after that       -> the real data nodes (one per "1")
"""


class DancingLinks:

    def __init__(self, num_columns, max_nodes):
        """
        num_columns = number of constraints (columns) to cover
        max_nodes   = total number of "1"s that will be added
        """
        self.num_columns = num_columns
        total = num_columns + 1 + max_nodes

        # the 4 link arrays + extra info about every node
        self.left = [0] * total
        self.right = [0] * total
        self.up = [0] * total
        self.down = [0] * total
        self.column_of = [0] * total     # which column header does this node belong to?
        self.row_id_of = [0] * total     # which user-given row id does this node belong to?
        self.column_size = [0] * (num_columns + 1)   # nodes still left in each column

        # Build the header row: root(0) <-> 1 <-> 2 <-> ... <-> num_columns <-> root
        for c in range(num_columns + 1):
            self.up[c] = c               # empty column: points to itself
            self.down[c] = c
            self.column_of[c] = c
            self.left[c] = c - 1
            self.right[c] = c + 1
        self.left[0] = num_columns       # make the header list circular
        self.right[num_columns] = 0

        self.node_count = num_columns + 1    # next free node index

        # search state
        self.chosen_rows = [0] * (num_columns + 1)
        self.first_solution = []
        self.solution_count = 0
        self.max_solutions = 1
        self.search_steps = 0

    def add_row(self, row_id, columns):
        """
        Adds one row (one choice) to the matrix.
        row_id  = any number that identifies this row (we get it back in the answer)
        columns = the columns this row covers, numbered from 0
        """
        first_node_in_row = -1

        for column_number in columns:
            col = column_number + 1          # +1 because node 0 is the root
            node = self.node_count
            self.node_count += 1

            self.column_of[node] = col
            self.row_id_of[node] = row_id

            # put the node at the BOTTOM of its column
            self.up[node] = self.up[col]
            self.down[node] = col
            self.down[self.up[col]] = node
            self.up[col] = node
            self.column_size[col] += 1

            # link the node into the circular list for this row
            if first_node_in_row == -1:
                first_node_in_row = node
                self.left[node] = node
                self.right[node] = node
            else:
                self.left[node] = self.left[first_node_in_row]
                self.right[node] = first_node_in_row
                self.right[self.left[first_node_in_row]] = node
                self.left[first_node_in_row] = node

    def solve(self, limit):
        """
        Searches for solutions and stops after "limit" of them.
        Use 1 to just solve, 2 to check "is the solution unique?".
        Returns how many solutions were found.
        """
        self.max_solutions = limit
        self.solution_count = 0
        self.search_steps = 0
        self.first_solution = []

        self._search(0)
        return self.solution_count

    def get_first_solution(self):
        """Returns the row ids of the first solution found (empty list if none)."""
        return list(self.first_solution)

    def get_search_steps(self):
        """How many row attempts the last search made."""
        return self.search_steps

    # ------------------------------------------------------------------
    # The recursive search (Knuth's Algorithm X)
    # ------------------------------------------------------------------
    def _search(self, depth):
        # No columns left in the header list -> everything is covered -> a solution!
        if self.right[0] == 0:
            self.solution_count += 1
            if self.solution_count == 1:
                self.first_solution = self.chosen_rows[:depth]
            return

        # Pick the column with the FEWEST nodes. This is what makes DLX fast:
        # we always attack the most constrained column first.
        best_column = self.right[0]
        c = self.right[0]
        while c != 0:
            if self.column_size[c] < self.column_size[best_column]:
                best_column = c
            c = self.right[c]

        # A column with zero rows can never be covered -> dead end, go back.
        if self.column_size[best_column] == 0:
            return

        self._cover(best_column)

        # Try every row that covers this column
        r = self.down[best_column]
        while r != best_column:
            self.search_steps += 1
            self.chosen_rows[depth] = self.row_id_of[r]

            # choosing row r means all its other columns are now covered too
            j = self.right[r]
            while j != r:
                self._cover(self.column_of[j])
                j = self.right[j]

            self._search(depth + 1)

            # undo in the OPPOSITE order (this order is important!)
            j = self.left[r]
            while j != r:
                self._uncover(self.column_of[j])
                j = self.left[j]

            if self.solution_count >= self.max_solutions:
                break       # we have enough solutions, stop trying more rows

            r = self.down[r]

        self._uncover(best_column)

    # Remove a column from the header list, and remove every row that
    # uses this column from all the OTHER columns.
    def _cover(self, col):
        self.right[self.left[col]] = self.right[col]
        self.left[self.right[col]] = self.left[col]

        i = self.down[col]
        while i != col:
            j = self.right[i]
            while j != i:
                self.down[self.up[j]] = self.down[j]
                self.up[self.down[j]] = self.up[j]
                self.column_size[self.column_of[j]] -= 1
                j = self.right[j]
            i = self.down[i]

    # Exactly undoes _cover(). Everything goes in reverse order.
    def _uncover(self, col):
        i = self.up[col]
        while i != col:
            j = self.left[i]
            while j != i:
                self.column_size[self.column_of[j]] += 1
                self.down[self.up[j]] = j
                self.up[self.down[j]] = j
                j = self.left[j]
            i = self.up[i]

        self.right[self.left[col]] = col
        self.left[self.right[col]] = col
