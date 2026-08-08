# A single song in the playlist. The playlist is a doubly linked list
# of these nodes so we can move forward (skip) and backward (go back).
class SongNode:
    def __init__(self, title):
        self.title = title
        self.playCount = 0
        self.next = None
        self.prev = None


class Player:
    def __init__(self):
        self.head = None
        self.tail = None
        self.current = None
        self.undoStack = []       # keeps track of previous "current" songs
        self.redoStack = []       # keeps track of undone moves, for redo
        self.favouriteSong = None
        self.maxPlayCount = 0

    # Appends a new song to the end of the playlist.
    def addSong(self, title):
        newNode = SongNode(title)
        if self.head is None:
            self.head = newNode
            self.tail = newNode
            self.current = newNode

        else:
            self.tail.next = newNode
            newNode.prev = self.tail
            self.tail = newNode
        print("Added: ", title)

    # Plays the current song and updates the favourite song if needed.
    def play(self):
        if self.current is None:
            print("Playlist is empty !!")
            return
        self.current.playCount += 1
        if self.current.playCount > self.maxPlayCount:
            self.maxPlayCount = self.current.playCount
            self.favouriteSong = self.current

        print("Now Playing:", self.current.title)

    # Moves to the next song in the playlist.
    def skip(self):
        if self.current is None or self.current.next is None:
            print("No next song to skip to.")
            return

        self.undoStack.append(self.current)
        self.redoStack.clear()
        self.current = self.current.next
        print("Skipped to:", self.current.title)

    # Moves to the previous song in the playlist.
    def goBack(self):
        if self.current is None or self.current.prev is None:
            print("No previous song to go back to.")
            return

        self.undoStack.append(self.current)
        self.redoStack.clear()
        self.current = self.current.prev
        print("Went back to:", self.current.title)

    # Undoes the last skip/goBack action.
    def undo(self):
        if len(self.undoStack) == 0:
            print("Nothing to undo.")
            return
        self.redoStack.append(self.current)
        self.current = self.undoStack.pop()
        print("Undo: Back to:", self.current.title)

    # Redoes the last undone action.
    def redo(self):
        if len(self.redoStack) == 0:
            print("Nothing to redo.")
            return

        self.undoStack.append(self.current)
        self.current = self.redoStack.pop()
        print("Redo: Forward to:", self.current.title)

    # Reports the song with the highest play count so far.
    def findFavourite(self):
        if self.favouriteSong is None or self.maxPlayCount == 0:
            print("No favourite song played yet.")
        else:
            print("Favourite song:", self.favouriteSong.title, "(Play count:", self.maxPlayCount, ")")


def main():
    player = Player()

    # Reads commands from stdin, one per line, until EOF:
    #   A, <song name>  -> add a song
    #   P                -> play current song
    #   S / N            -> skip to next song
    #   G                -> go back to previous song
    #   U                -> undo last move
    #   R                -> redo last undone move
    #   F                -> show favourite song
    while True:
        try:
            line = input().strip()
        except EOFError:
            break

        if line == "":
            continue

        if line.startswith("A, "):
            songName = line[3:].strip()
            player.addSong(songName)

        elif line == "P" or line == "p":
            player.play()

        elif line == "S" or line == "s":
            player.skip()

        elif line == "N" or line == "n":
            player.skip()

        elif line == "G" or line == "g":
            player.goBack()

        elif line == "U" or line == "u":
            player.undo()

        elif line == "R" or line == "r":
            player.redo()

        elif line == "F" or line == "f":
            player.findFavourite()


main()
