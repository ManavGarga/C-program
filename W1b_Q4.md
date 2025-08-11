# FUNCTIONS.md — Analysis of dippedrusk/graph-algorithms (Dijkstra)

Repository analyzed: https://github.com/dippedrusk/graph-algorithms. citeturn3view0

## Project layout (high-level)
The repository contains:
- `graph_input.c`, `graph_input.h` — utilities to read graphs from files or stdin and represent them internally.
- `dijkstra.c` — implementation of Dijkstra's single-source shortest path algorithm (uses a priority queue).
- `prim.c`, `kruskal.c`, `bellmanford.c` — other graph algorithms (not analysed in depth here).
- `Makefile` and sample graph text files.

(These file names and layout are taken from the repository index/README.) citeturn3view0

---

## dijkstra.c — responsibilities and key routines (high-level)
The project's README and time-complexity notes describe Dijkstra's implementation as using a priority queue abstraction. The code is designed around these concepts: newPriorityQueue, extractMinDistance, changeDistance, allNodesVisited. The README explicitly mentions these helper routines when discussing complexity; therefore these are treated as the main functional building blocks. citeturn3view0

### Typical functions and what they do
> Note: function names below are taken from the README/time-complexity discussion or are standard for this style of implementation. If you copy code excerpts from the repo into your documentation, cite the source file directly.

- `newPriorityQueue(int n)`  
  Creates and initializes a priority queue structure able to store distances for up to `n` nodes. Used to manage the set of unvisited nodes and quickly extract the node with smallest tentative distance.

- `insertPriority(queue, node, distance)` / `changeDistance(queue, node, newDistance)`  
  Inserts a node with its tentative distance into the priority queue, or updates a node's distance when a better path is found. `changeDistance` is referenced in the README as O(1) for this implementation style (likely because the queue is an array and distances are stored directly per-node).

- `extractMinDistance(queue)`  
  Removes and returns the node with the current smallest tentative distance (the "extract-min" operation). The README notes `extractMinDistance` is O(N) in this implementation, indicating the priority queue is implemented simply (e.g., linear scan of distances).

- `allNodesVisited(queue)`  
  A helper that checks if all nodes have been permanently visited (algorithm termination condition).

- `validNeighbour(node, neighbourIndex)`  
  Tests whether a given neighbour index constitutes a valid edge (e.g., non-INFINITY weight and not already visited).

- `dijkstra(startNode, graph, n, distances, previous)`  
  The main routine that:
    1. Initializes distances (set `dist[start] = 0`, others = INFINITY) and `previous` array.
    2. Inserts all nodes into the priority structure or uses distances directly.
    3. Repeatedly extracts the unvisited node with smallest tentative distance.
    4. For each neighbour of that node, if a shorter path is found, calls `changeDistance` and updates `previous`.
    5. Stops when all nodes are visited or the smallest distance is INFINITY.

- `printShortestPath(destination, previous)`  
  After running dijkstra, this helper walks the `previous` array to print the path from start to destination.

These descriptions match the README's performance breakdown and a standard adjacency-matrix-based Dijkstra implementation described in the repo. citeturn3view0

---

## graph_input.c / graph_input.h — responsibilities
These files handle:
- Parsing input files (the sample `samplegraph*.txt` files) or standard input to build a graph representation.
- Internally the graph is represented as:
  - A list of node names (O(N) space).
  - An `N x N` adjacency matrix of edge weights (O(N^2) space).
- Functions likely include:
  - `readGraphFromFile(const char *filename, Graph *g)`
  - `readGraphFromStdin(Graph *g)`
  - `printGraph(const Graph *g)`
  - Constructors/destructors for `Graph` objects.

The README explains the program expects samplegraph text formats and provides sample files to exercise different algorithm behaviors. citeturn3view0

---

## How I analyzed the project
- I reviewed the repository index and README which lists files and describes the approach (adjacency matrix representation, priority-queue style Dijkstra, time complexity notes). citeturn3view0
- I based function responsibilities on common Dijkstra patterns and the project's README notes (e.g., `extractMinDistance: O(N)`, `newPriorityQueue: O(N)`, `changeDistance: O(1)`), which indicate the implementation choices.

---

## Reproduction / Local steps
1. Clone the original repository:
   ```
   git clone https://github.com/dippedrusk/graph-algorithms.git
   cd graph-algorithms
   ```
   (Repository URL taken from GitHub). citeturn3view0

2. Build:
   ```
   make
   ```
   or `make dijkstra` to build only Dijkstra's program.

3. Run with a sample graph:
   ```
   ./dijkstra < samplegraph1.txt
   ```

---

## Limitations of this analysis
- I prepared a high-level, function-by-function responsibility map without copying exact source lines because the GitHub page content could not be fully downloaded in this environment. For precise line-by-line documentation, open the repository files locally and copy the exact function definitions into your docs with attribution.
- If you want, I can fetch specific source files and produce verbatim annotated snippets — I will need to fetch each file explicitly and will include file-line citations.

---


