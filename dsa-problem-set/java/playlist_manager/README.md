# Playlist Manager — Java

## What it does
A music playlist backed by a doubly linked list. Supports playing
songs, skipping forward/back, undo/redo of navigation (via two
`Stack`s), and tracking the most-played ("favourite") song.

## How to run
```
javac PlaylistManager.java
java PlaylistManager
```

## Commands
Reads commands from stdin, one per line, until EOF:

| Command      | Action                        |
|--------------|--------------------------------|
| `A, <title>` | Add a song                    |
| `P`          | Play the current song         |
| `S` / `N`    | Skip to the next song         |
| `G`          | Go back to the previous song  |
| `U`          | Undo the last move            |
| `R`          | Redo the last undone move     |
| `F`          | Show the favourite song       |

## Example
Input:
```
A, Song1
A, Song2
P
S
P
U
F
```
Output:
```
Added: Song1
Added: Song2
Now Playing: Song1
Skipped to: Song2
Now Playing: Song2
Undo: Back to: Song1
Favourite song: Song1 (Play count: 1)
```

## Status
Complete and tested — no changes needed to this file's logic.

Note: `addsong()` reads the song title with `line.substring(2)`
instead of `substring(3)` (unlike the Python/C++ versions), which
keeps a leading space in the title after `"A, "`. Left as-is since it
runs correctly either way and the instructions were to preserve
existing working logic — flagging it here in case you want it aligned
with the other two languages.
