# plunge
A "simple" funge-like esoteric language, along with interpreter written in C++

---

Plunge execution begins with the cursor at the top left of a file (x = 0, depth = 0). The cursor reads the character at its current position, executes it, and then moves.

The cursor generally moves one position to the right (increasing x), unless otherwise specified. The cursor can wrap in all directions.

Newlines are allowed, all other non-instruction characters (including spaces) are unsupported.

## Instruction overview

Plunge consists of only 13 supported characters, each corresponding to a simple instruction. These fall into 4 categories:

### Category 1: Accumulator operations
* These operations modify acc, a single 8-bit unsigned char (0-255)

| Char | Description | Pseudocode |
|:----:|:-----------:|:----------:|
|   (  |decrement acc|```acc--```|
|   )  |increment acc|```acc++```|
|   ?  |user input to acc|```getchar(acc)```|
|   :  |print acc|```print(acc)```|
|   ;  |clear acc|```acc = 0```|

### Category 2: Movement operations
* These operations modify the cursor position

| Char | Description | Pseudocode |
|:----:|:-----------:|:----------:|
|   <  |jump left|```x = 0```|
|   >  |jump right|```x = row.width - 1```|
|   v  |plunge|```depth++```|
|   ^  |climb|```depth--```|

### Category 3: Conditional operations
* These operations determine whether the next operation will execute

| Char | Description | Pseudocode |
|:----:|:-----------:|:----------:|
|   #  |execute next IFF acc is even|```skipFlag = isOdd(acc)```|
|   ~  |execute next IFF acc is greater than depth|```skipFlag = !(acc > depth)```|

### Category 4: Miscellaneous operations
* These operations don't do much

| Char | Description | Pseudocode |
|:----:|:-----------:|:----------:|
|   .  |do nothing|```/* do nothing */```|
|   x  |halt|```return 0```|

## Running plunge programs
Build interpreter: ```g++ plunge.cpp```

Run program: ```./plunge.o hello.plunge``` or ```plunge.exe hello.plunge```

### Example Hello World (hello.plunge)
* This is far from the most efficient hello world program, but it serves to give a demonstration of how plunge looks in action:
```))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))))v
.......:v
........))))))))))))))))))))))))))))):)))))))::))):v
;v
v<)))))))):;x
v.^..........#
v..))))))))..^#
v.))))))))))..^
v.^......:;)))))))#
v(((((((^)))))))
v((((((^))))))
v(((((^)))))
v((((^))))
v(((^)))
v((^))
v(^)
v^........(#
v()()()():^
v.((((((^
v.^
v.^
v.^
v.^...........(#
v.............^
v.............^
v((((((((:))):^.((()))#
v()()()()()()()()..:..^
v((((((((((((((((^#
v.........((((((((^
v((((((((.^#
v((........^#
v((((.......^#
v((((((......^#
v((((((((.....^#
v((((((((((....^#
v((((((((((((...^#
v((((((((((((((..^#
v((((((((((((((((.^#
v^.(((((((((((((((((((#
v(.....^(((((((((((((((#
v((..................^((((((((((((((#
v(((.............................^(((((((((((.#
v:;)))))))))))))))))))))))))))))))):;(((((((..^
~^)```
