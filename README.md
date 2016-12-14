# Advent of Code 2016

<h3>Day 1:</h3>

Day 2:

Day 3:

Day 4:

Day 5:
Bash script accepts starting and ending number, and iterates from "$string" + starting number to "$string" + ending number, gets the MD5 hash and compares the first five characters to "00000". 

Option "-n" in echo removes the trailing newline and pipes the string into md5sum program. 

C++ version is significantly faster, it uses the OpenSSL MD5 function.

Day 6:

Day 7:

Day 8:
Not particularly elegant, but hopefully readable code. It uses the \<chrono\> and \<thread\> libraries for pausing every 50 miliseconds, and changes color of the output while drawing the screen after each command. 

day8.dat is a slightly modified version of the original input for easier parsing and reading. 

Day 9:
Recursive version is _significantly_ faster.

Day 10:
Ridiculous class usage, and modified input file for easier parsing. 

Day 11:

Day 12:
To solve part 2of the problem, change the initialization of 'c' to 1.

Day 13:
Shortest path algorithm, uses a simple queue to keep track of moves that need to be checked. In principle it could be made faster by using a priority queue based on the distance to the target, but it fast enough for the particular problem.

Day14:
Straightforward running through hashes and memorizing them.
