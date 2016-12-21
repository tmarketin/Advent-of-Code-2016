# Advent of Code 2016

<h4>Day 1:</h4>

<h4>Day 2:</h4>

<h4>Day 3:</h4>

<h4>Day 4:</h4>

<h4>Day 5:</h4>
Bash script accepts starting and ending number, and iterates from "$string" + starting number to "$string" + ending number, gets the MD5 hash and compares the first five characters to "00000". 

Option "-n" in echo removes the trailing newline and pipes the string into md5sum program. 

C++ version is significantly faster, it uses the OpenSSL MD5 function.

<h4>Day 6:</h4>

<h4>Day 7:</h4>

<h4>Day 8:</h4>
Not particularly elegant, but hopefully readable code. It uses the \<chrono\> and \<thread\> libraries for pausing every 50 miliseconds, and changes color of the output while drawing the screen after each command. 

day8.dat is a slightly modified version of the original input for easier parsing and reading. 

<h4>Day 9:</h4>
Recursive version is _significantly_ faster.

<h4>Day 10:</h4>
Ridiculous class usage, and modified input file for easier parsing. 

<h4>Day 11:</h4>
First version (_day11.cc_) is a naive implementation of a search with overengineered classes and runs embarassingly slowly.

After reading about other solutions and some thought, I built a version where the state is contained as bits in a single long int, and all operations are performed with bitwise operators - <i>day11_v3.cc</i>. It requires approx. two _order of magnitude_ less time to execute (cca. 1.2 seconds for part 1 and 16.2 seconds for part 2).

<h4>Day 12:</h4>
To solve part 2 of the problem, change the initialization of 'c' to 1.

<h4>Day 13:</h4>
Shortest path algorithm, uses a simple queue to keep track of moves that need to be checked. In principle it could be made faster by using a priority queue based on the distance to the target, but it fast enough for the particular problem.

<h4>Day 14:</h4>
Straightforward running through hashes and memorizing them.

<h4>Day 15:</h4>
Very straightforward solution, incrementing time by the size of the first disc (could be better by incrementing by the size of the largest, but it already finishes in 0.1 s).

<h4>Day 16:</h4>
Quick solution.

<h4>Day 17:</h4>

<h4>Day 18:</h4>
A simple solution using strings. One could do a bitwise representation of the problem, but I don't think could make it more elegant than <a href="https://www.reddit.com/r/adventofcode/comments/5iyp50/2016_day_18_solutions/dbc0l6j/">this solution</a>.

<h4>Day 19:</h4>
Solution using circular linked list.

<h4>Day 20:</h4>
One pass through the input file that is modified (removed '-' and sorted) for easier parsing.

<h4>Day 21:</h4>
For part 2 I iterate over all permutations of the starting string until I find the correct one. The permutations are done by the std::next_permutation from <algorithm>. Input file is simplified for easier parsing.
