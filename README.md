# Floyd-Warshall Algorithm in C++

This C++ program implements the Floyd-Warshall algorithm for finding the shortest paths between all pairs of nodes in a weighted graph. The graph data is read from a file named `graf.txt`, where each line represents a connection between nodes along with their respective weights.

## Usage

1. **Graph Data File (`graf.txt`):** Create a text file named `graf.txt` containing graph data in the format: `node1 node2 weight`.

    Example:
    ```
    1 2 8
    1 4 1
    2 3 1
    3 1 4
    4 2 2
    4 3 9 
    ```

2. **Run the Program:** Open and run the `main.cpp` file in your IDE.

3. **Menu Options:**
   - **1:** Load graph data from `graf.txt`.
   - **2:** Run the Floyd-Warshall algorithm to find the shortest paths.
   - **3:** Display the shortest path between specified nodes.
   - **4:** Exit the program.

## Example

Suppose `graf.txt` contains the following data:

```
1 2 8
1 4 1
2 3 1
3 1 4
4 2 2
4 3 9 
```

1. Select option **1** to load graph data.
2. Select option **2** to run the algorithm.
3. Select option **3** and enter start node `1` and end node `4` to see the shortest path.
