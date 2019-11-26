# lem_in
A pathing device for ants, with Tomas Diaz

We implemented an algorithm to solve a variant of the maximum flow problem on a graph with unit capacity edges where the bottleneck was at the vertices. One executable file outputs commands for each ant to go to a particular node in a given turn, but a more understandable format is achieved by piping this output into our visualizer. We tested a number of cases to ensure that our algorithm was always able to find the maximum number of simultaneously traversable paths under the constraints given.

## Build

On Mac or Linux: Run `make`

To use program: Run `cat maps/map_of_choice | ./lem_in | ./viz`

## Project Information

The project as presented does not obviously belong to any particular class of problems. You are presented with a number of ants to move from a start node through a collection of tunnels to an end node with discrete time steps where at each time at most one ant can be in any non-terminal node. Clearly, this is a graph algorithm, and it ends up being fairly similar to maximum flow. I highly recommend Erik DeMaine's lectures on the subject, but essentially you have a source and sink node on a graph with edges whose weights represent capacities, and your goal is to determine the maximum amount of fluid that can move from the source to the sink per unit time.

### Ford-Fulkerson Algorithm

There are a lot of interesting techniques for more complex graphs, but you can get tighter guarantees for graphs with unit capacity edges. At first glance, that was what we thought we were dealing with, so we implemented the Ford-Fulkerson algorithm. This involves repeatedly finding the shortest path in the graph via BFS (called an augmenting path) and updating the edge weights accordingly. When there are no more paths in the modified graph from source to sink, the algorithm terminates. Unfortunately, we realized we had made a mistake: in this particular problem the nodes rather than the edges had unit capacity, and this means intersecting flows are disallowed.

### Modification

When finding an augmenting flow, this does not mean its impossible to use nodes that are already part of an existing path; if so, the algorithm would no longer work. However, the BFS component has to be adapted in a particular way: when entering a node, we need to know what kind of node it is and what kind of edge we've entered from. If the node is part of an existing path and we've entered from an edge not on the path, that means we can only exit back along an edge that is part of the path. In effect, this will break the path in two:

```
>--*-->--*-->
```

becomes

```
         |
         |
>--*     *-->
   |
   |
```

However, entering from an edge along the path means that the path is already broken and thus exit along any edge is allowed. In addition to this rule, we had to update the rules for marking a node visited in a given round: since entering from a non-path edge does not allow free choice of exit edge, nodes on a path are only marked visited for BFS after they have been entered from the edge along the path. With these modifications, you can find the maximum flow in a graph where the nodes have unit capacity.

### Prep work

With no access to input reading functions, standard data structures, and `printf`, everything used here is home-brewed. Dynamic arrays are critical, the queue used for BFS is a simple wrapper around a linked list, and the hashmap used to store capacity is a very basic hash table with open addressing using MD5 written by Tomas (which might be excessive, yes). A fair amount of work had to go into preparing the environment and fitting the constraints of the problem, but the algorithmic details are much more interesting.

## Visuals

This would be better served by a gif, but in our visualization each edge lights up when it is traversed by an ant and each node lights up when it contains an ant.

![](images/no-ants.png)
![](images/ant-start.png)
![](images/ant-transit.png)
![](images/ant-end.png)
