# Sokoban Solver
This program will solve Sokoban puzzles using the Puzzles.txt file. Please use the following format:<br> 
<pre>OOOOOOOO
O   OR O
O    B O
O   O  O
OOOOOBSO
    O SO
    OOOO</pre>
    
Legend: O = Obstacles :  R = Robot : B = Box : S = Storage<br>

This program will attempt to solve the Puzzle using BFS and DFS, which will generate their respective output files (BFS_Output.txt & DFS_Output.txt) <br>

Inside the output files, you will find the entire path used by BFS/DFS to arrive to the solution. As well as the amount of time it took. 
