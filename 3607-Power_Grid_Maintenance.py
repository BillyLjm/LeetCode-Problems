"""
3607-Power_Grid_Maintenance.py
Billy.Ljm
09 November 2025

=======
Problem
=======
https://leetcode.com/problems/power-grid-maintenance/

You are given an integer c representing c power stations, each with a unique
identifier id from 1 to c (1‑based indexing).

These stations are interconnected via n bidirectional cables, represented by a
2D array connections, where each element connections[i] = [ui, vi] indicates a
connection between station ui and station vi. Stations that are directly or
indirectly connected form a power grid.

Initially, all stations are online (operational).

You are also given a 2D array queries, where each query is one of the following
two types:
- [1, x]: A maintenance check is requested for station x. If station x is online,
  it resolves the check by itself. If station x is offline, the check is
  resolved by the operational station with the smallest id in the same power
  grid as x. If no operational station exists in that grid, return -1.
- [2, x]: Station x goes offline (i.e., it becomes non-operational).

Return an array of integers representing the results of each query of type
[1, x] in the order they appear.

Note: The power grid preserves its structure; an offline (non‑operational) node
remains part of its grid and taking it offline does not alter connectivity.

===========
My Approach
===========
We will first use union-find to identify the disjoin power grids. Then, we will
use a list to map each power station to a minheap of all elements in its power
grid. This minheap allows us to find the smallest id of the power grid quickly,
and keep track of the offline stations so we can answer the query, and also to
lazy delete from the minheap.

This has a time complexity of O[(c + q) log c + m α(c)] and space complexity of
O(c + q), where c is the number of power stations, q is the number of queries,
m the number of connections, and α the inverse Ackermann function.
"""

from typing import List
import heapq

class UnionFind():
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, i):
        if (self.parent[i] == i):
            return i
        else:
            self.parent[i] = self.find(self.parent[i])
            return self.parent[i]

    def union(self, x, y):
        xroot = self.find(x)
        yroot = self.find(y)
        if self.rank[xroot] > self.rank[yroot]:
            self.parent[yroot] = xroot
        else:
            self.parent[xroot] = yroot

class Solution:
    def processQueries(self, c: int, connections: List[List[int]],
        queries: List[List[int]]) -> List[int]:
        # union-find
        uf = UnionFind(c+1)
        for conn in connections:
            uf.union(conn[0], conn[1])

        # create minheaps
        pq = [list() for i in range(c+1)]
        for i in range(c+1):
            pq[i] = pq[uf.find(i)]
            heapq.heappush(pq[i], i)

        # answer queries
        out = []
        offline = set()
        for q in queries:
            if q[0] == 1 and q[1] not in offline:
                out.append(q[1])
            elif q[0] == 1 and q[1] in offline:
                # lazy delete min heaps
                while len(pq[q[1]]) > 0 and pq[q[1]][0] in offline:
                    heapq.heappop(pq[q[1]])
                # respond to question
                if len(pq[q[1]]) > 0:
                    out.append(pq[q[1]][0])
                else:
                    out.append(-1)
            elif q[0] == 2 and q[1] not in offline:
                offline.add(q[1])

        return out

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    c = 5
    connections = [[1,2],[2,3],[3,4],[4,5]]
    queries = [[1,3],[2,1],[1,1],[2,2],[1,2]]
    print(f"processQueries({c}, {connections}, {queries}) = " +
        str(sol.processQueries(c, connections, queries)))

    # test case 2
    c = 3
    connections = []
    queries = [[1,1],[2,1],[1,1]]
    print(f"processQueries({c}, {connections}, {queries}) = " +
        str(sol.processQueries(c, connections, queries)))

