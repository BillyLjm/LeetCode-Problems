"""
2257-Count_Unguarded_cellss_in_the_Grid.py
Billy.Ljm
02 November 2025

=======
Problem
=======
https://leetcode.com/problems/count-unguarded-cells-in-the-grid/

You are given two integers m and n representing a 0-indexed m x n grid. You are
also given two 2D integer arrays guards and walls where guards[i] = [rowi, coli]
and walls[j] = [rowj, colj] represent the positions of the ith guard and jth
wall respectively.

A guard can see every cells in the four cardinal directions (north, east, south,
or west) starting from their position unless obstructed by a wall or another
guard. A cells is guarded if there is at least one guard that can see it.

Return the number of unoccupied cells that are not guarded.

===========
My Approach
===========
We will iterate through the guards and mark which cells are guarded, up to when
a wall or another guard is present.

This has a time complexity of O(m*n*g), and a space complexity of O(m*n), where
m and n are the width and height of the grid, and g is the number of guards.
"""

from typing import List
import numpy as np

class Solution:
    def countUnguarded(self, m: int, n: int, guards: List[List[int]],
        walls: List[List[int]]) -> int:
    	grid = np.zeros((m, n)) # represent grid
    	dirs = ((0,1), (0,-1), (1,0), (-1,0)) # directions to check

    	# mark occupied cells
    	for guard in guards:
    		grid[*guard] = 2
    	for wall in walls:
    		grid[*wall] = 2

    	# check line of sight of each guard
    	for gx, gy in guards:
    		for dx, dy in dirs:
    			cx, cy = gx, gy
    			while True:
    				cx, cy = cx + dx, cy + dy
    				if cx < 0 or cy < 0 or cx >= m or cy >= n: break # bounds
    				elif grid[cx, cy] == 2: break # met wall or another guard
    				grid[cx, cy] = 1

    	return int(np.sum(grid == 0))

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    m = 4
    n = 6
    guards = [[0,0],[1,1],[2,3]]
    walls = [[0,1],[2,2],[1,4]]
    print(f"countUnguarded({m}, {n}, {guards}, {walls}) = " +
       str(sol.countUnguarded(m, n, guards, walls)))

    # test case 2
    m = 3
    n = 3
    guards = [[1,1]]
    walls = [[0,1],[1,0],[2,1],[1,2]]
    print(f"countUnguarded({m}, {n}, {guards}, {walls}) = " +
       str(sol.countUnguarded(m, n, guards, walls)))
