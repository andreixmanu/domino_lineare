# Linear Domino

#### created by Andrei Manu

Interactive game written in C language where you have a set of n cards of given combinations, and can place them on
a table. Every piece has two sides, and you can only place a piece beside another piece if the adjacent sides have the same
number. The game ends when you don't have any more pieces, or when you cannot place any more pieces. 

### Welcome to Linear Domino

There are two main gamemodes:
- Linear Domino
- (Not) Linear Domino

As the names suggest, **Linear Domino** develops on a 1-dimension table, where you can play your cards either
on the left side, or on the right side.

In **(Not) Linear Domino** you can also place your pieces 'vertically', which develops your table in 2 dimensions.
One side of the piece will be on the same row, while the other will be placed on the row below. You can create more than one
binary tree in this way, and any tree can be as long as you can. 

### Play against yourself or let the computer play!

If you don't feel like playing, you can make the computer play, and see how it solves the puzzle with the 
given pieces.

### Up for a challenge?

In the 'Puzzle' mode you can solve 3+1 difficult puzzles, but be careful: they are 
not easy at all! Only if you beat the three first puzzles you gain access to the fourth and
most difficult.

---

### Toolchain

- **OS**
    - **Windows**: 10+
    - **Ubuntu**: 20.04.5 LTS
- **Builder**
    - **CMake**: 3.25
- **Language**
    - **C**: C99

> NOTE: it is suggested to use the built-in tools of CLion to integrate the
> project with fewer problems

### Dependencies

No other dependencies are needed.

### Documentation

[Generated documentation](docs/html/index.html) by Doxygen