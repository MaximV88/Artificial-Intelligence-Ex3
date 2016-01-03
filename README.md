# Artificial-Intelligence-Ex3
This repository contains my solution for implementing Hierarchical clustering. <br />
Supported algorithms are:
* Single link: Distance between two clustens is the shortest distance between a pair of elements from the two clusters.
* Average link: Distance between two clusters is the average distance between each pair of elements from the two clusters.

Each dot is represented by a pair of numbers <x,y>.<br />

The program reads a collection of dots from a signel input.txt file. <br />
First row contains the requested algorithm. The second row contains the requested number of clusters. Afterwards each row will contain a dot.<br />
<br />

###Example

single link<br />
4<br />
2,10<br />
2,5<br />
8,4<br />
5,8<br />
7,5<br />
6,4<br />
1,2<br />
4,9<br />

The output is written to output.txt, with the names of clusters as numbers (1...n).<br />
Each cluster is mapped to a dot via their order in input.txt.