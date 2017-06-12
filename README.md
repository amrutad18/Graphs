# Graphs

Kruskal.c:
C implementation of kruskal's algorithm.
Data Structures used: Linked List(For set),Array(for flag,DFS)
Minimum spanning tree: Has number of edges = n-1(Only when input graph is complete.If not,it may have even less edges).
Problems faced- 
1. Cycle Detection: Done using DFS.Always break out of the outer DFS loop if cycle is detected even in any one component.
2. Number of vertices and how to end the Kruskal loop: Break out when edges are n-1 or the initial edge set is empty.
