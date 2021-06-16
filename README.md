# EightQueenProblem
This is a solution for the Eight Queen problem using machine learning and genetic learning.


The "genetic" works like this:

Each individual holds an array of values that represents the position of the queens on the board. This is the "solution" to the problem
For instance: [1,5,7,6,3,4,2,0]: each index is the Y value on the board, and each value is the X position on the board. Decoding this info will yield
the following board: (a one means there is a queen)

0 1 0 0 0 0 0 0
0 0 0 0 0 1 0 0
0 0 0 0 0 0 0 1
0 0 0 0 0 0 1 0
0 0 0 1 0 0 0 0
0 0 0 0 1 0 0 0
0 0 1 0 0 0 0 0
1 0 0 0 0 0 0 0

The fitness function is calculated based on the number of collisions on the board. Less fitness means a better board.

Each generation creates N boards to process. After computing the fitness, half of the individuals, or N/2, are selected (based on "the less the better" fitness) and the genes are recombined. Half of the queens from one and half of the queens from the other.

Lets take the genes [1,5,7,6,3,4,2,0] and [5,3,4,6,1,2,0,7] as and example:

We split both of them into two gene equences:
[1,5,7,6,3,4,2,0] = [1,5,7,6] and [3,4,2,0]
[5,3,4,6,1,2,0,7] = [5,3,4,6] and [1,2,0,7]

Then we recombine them to make two new children:
[1,5,7,6] and [1,2,0,7] = [1,5,7,6,1,2,0,7] 
[5,3,4,6] and [3,4,2,0] = [5,3,4,6,3,4,2,0] 

Since there is always the problem of the fake-low value, we introduce a simple mutation function to make sure there are variants:
Each individual, after being born, has a low chance to be mutated (default to 10%). If a mutation ocurres, two random indexes will be selected to be swaped. Lets take the second child from above and mutate it:

First we roll for the first index, lets say 5, then we roll for the second index, a 3.
The old gene:

 0,1,2,3,4,5,6,7
[5,3,4,6,3,4,2,0]

The new gene:
 0,1,2,5,4,3,6,7
[5,3,4,4,3,6,2,0]

After that, the children is introduced back to the new generation pool. Each generation is composed from half of the old generation pool (the best fit individuals), and the offspring of them.
So:
N/2 = Parents
N/2 = Offspring
