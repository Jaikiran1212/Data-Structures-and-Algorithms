import java.util.Scanner;
import java.util.Stack;

// A single song in the playlist. The playlist is a doubly linked list
// of these nodes so we can move forward (skip) and backward (go back).
class SongNode {
    String title;
    int playcount;
    SongNode next;
    SongNode prev;

    public SongNode(String title) {
        this.title = title;
        this.playcount = 0;
        this.next = null;
        this.prev = null;
    }
}

class player {
    private SongNode head;
    private SongNode tail;
    private SongNode current;

    private final Stack<SongNode> undoStack; // previous "current" songs
    private final Stack<SongNode> redoStack; // undone moves, for redo

    private SongNode favoriteSong;
    private int maxPlayCount;

    public player() {
        this.head = null;
        this.tail = null;
        this.current = null;
        this.undoStack = new Stack<>();
        this.redoStack = new Stack<>();
        this.favoriteSong = null;
        this.maxPlayCount = 0;
    }

    // Appends a new song to the end of the playlist.
    public void addsong(String title) {

        SongNode newNode = new SongNode(title);

        if (head == null) {
            head = newNode;
            tail = newNode;
            current = newNode;
        } else {
            tail.next = newNode;
            newNode.prev = tail;
            tail = newNode;
        }

        System.out.println("Added: " + title);
    }

    // Plays the current song and updates the favourite song if needed.
    public void playing() {
        if (current == null) {
            System.out.println("Playlist is empty !!");
            return;
        }
        current.playcount++;
        if (current.playcount > maxPlayCount) {
            maxPlayCount = current.playcount;
            favoriteSong = current;
        }
        System.out.println("Now Playing: " + current.title);
    }

    // Moves to the next song in the playlist.
    public void skip() {
        if (current == null || current.next == null) {
            System.out.println("No next song to skip to.");
            return;
        }
        undoStack.push(current);
        redoStack.clear();
        current = current.next;
        System.out.println("Skipped to: " + current.title);
    }

    // Moves to the previous song in the playlist.
    public void goBack() {
        if (current == null || current.prev == null) {
            System.out.println("No previous song to go back to.");
            return;
        }
        undoStack.push(current);
        redoStack.clear();
        current = current.prev;
        System.out.println("Went back to: " + current.title);
    }

    // Undoes the last skip/goBack action.
    public void undo() {
        if (undoStack.isEmpty()) {
            System.out.println("Nothing to undo.");
            return;
        }
        redoStack.push(current);
        current = undoStack.pop();
        System.out.println("Undo: Back to: " + current.title);
    }

    // Redoes the last undone action.
    public void redo() {
        if (redoStack.isEmpty()) {
            System.out.println("Nothing to redo.");
            return;
        }
        undoStack.push(current);
        current = redoStack.pop();
        System.out.println("Redo: Forward to: " + current.title);
    }

    // Reports the song with the highest play count so far.
    public void findFavourite() {
        if (favoriteSong == null || maxPlayCount == 0) {
            System.out.println("No favourite song played yet.");
        } else {
            System.out.println("Favourite song: " + favoriteSong.title + " (Play count: " + maxPlayCount + ")");
        }
    }

}

public class PlaylistManager {

    // Reads commands from stdin, one per line, until EOF:
    // A, <song name> -> add a song
    // P -> play current song
    // S / N -> skip to next song
    // G -> go back to previous song
    // U -> undo last move
    // R -> redo last undone move
    // F -> show favourite song
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        player p = new player();

        while (sc.hasNextLine()) {
            String line = sc.nextLine().trim();
            if (line.isEmpty()) {
                continue;
            }
            if (line.startsWith("A, ")) {
                String songName = line.substring(2).trim();
                p.addsong(songName);
            } else {
                switch (line.toUpperCase()) {
                    case "P":
                        p.playing();
                        break;
                    case "S":
                        p.skip();
                        break;
                    case "N":
                        p.skip();
                        break;
                    case "G":
                        p.goBack();
                        break;
                    case "U":
                        p.undo();
                        break;
                    case "R":
                        p.redo();
                        break;
                    case "F":
                        p.findFavourite();
                        break;
                    default:
                        break;
                }
            }
        }
        sc.close();
    }
}
