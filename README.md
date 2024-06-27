# Numarare

 - Complexity:
   - Time: O(n + m)
      - Explanation: Executing a topsort (O(n + m)) and then interating through each node and through each edge (O(n) + O(m) => O(n + m)). O(n + m + n + m) = O(n + m).
   - Space: O(n + m)
      - Explanation: Graphs are represented as adjacency lists => O(n + m). Topsort, in_degree, dp are vectors of complexity O(n), q as well. O(n + m + n + n + n + n) = O(n + m).
 - We read the first graph. While reading the second graph, check if the current edge exists in the first graph. If it does, add it to the common graph.
 - This results in a graph containing only the common edges of the 2 graphs.
 - All that is left to do is count the number of paths from 1 to N in this new graph.
 - To do this, we topsort it, ensuring that during counting all the nodes before the current one have already been computed.
 - Finally, we use dynamic programming to count all paths.
 - Because the number can be very large, it is calculated modulo 'MOD'.
