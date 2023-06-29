"""
0864-Shortest_Path_to_Get_All_Keys.py
Billy.Ljm
29 June 2023

=======
Problem
=======
https://leetcode.com/problems/shortest-path-to-get-all-keys/

You are given an m x n grid grid where:
 - '.' is an empty cell.
 - '#' is a wall.
 - '@' is the starting point.
 - Lowercase letters represent keys.
 - Uppercase letters represent locks.

You start at the starting point and one move consists of walking one space in
one of the four cardinal directions. You cannot walk outside the grid, or walk
into a wall.

If you walk over a key, you can pick it up and you cannot walk over a lock
unless you have its corresponding key.

For some 1 <= k <= 6, there is exactly one lowercase and one uppercase letter of
the first k letters of the English alphabet in the grid. This means that there
is exactly one key for each lock, and one lock for each key; and also that the
letters used to represent the keys and locks were chosen in the same order as
the English alphabet.

Return the lowest number of moves to acquire all keys. If it is impossible,
return -1.

===========
My Approach
===========
We'll use breadth-first search to consider all paths, until all the keys are
acquired. In the typical BFS, we don't revisit spaces to reduce the complexity
of the algorithm. However, in this problem, we may need to back track to a door
after getting a key. Thus, we will need to consider the visited spaces
separately for each key possessed.

This has a time complexity of O(2^k * m * n), and a space complexity of
O(2^k * m * n), where k is the number of keys, and m and n are the width and
height of the space respectively.
"""

import queue

class Solution:
	def shortestPathAllKeys(self, grid: list[str]) -> int:
		"""
		Finds the length of the shortest path to get all the keys in a maze
		:param grid: the maze as a list of strings, where each character
		             represents an empty space/wall/etc as described above
		:returns: length of shortest path to get all keys
		"""
		# params of maze
		wx = len(grid) # height
		wy = len(grid[0]) # width
		keys = 0 # number of keys
		for x in range(wx):
			for y in range(wy):
				if grid[x][y].islower():
					keys += 1
				if grid[x][y] == '@':
					start = (x, y) # start row

		# breadth first search
		nodes = queue.Queue() # nodes to visit, as [keys, width, height]
		nodes.put((0, *start, 0))
		visited = [[[False] * wy for _ in range(wx)] for _ in range(2**keys)]
		while not nodes.empty():
			ck, cx, cy, cs = nodes.get(); # get next node
			# if all keys obtained, return
			if ck == 2**keys - 1: return cs
			# ignore visited states
			elif visited[ck][cx][cy]: continue 
			# else visit node
			visited[ck][cx][cy] = True
			# and queue neighbours
			for (nx, ny) in ((cx+1,cy), (cx-1,cy), (cx,cy+1), (cx,cy-1)): 
				# out of bounds
				if nx < 0 or nx >= wx or ny < 0 or ny >= wy: continue
				# wall
				elif grid[nx][ny] == '#': continue
				# empty space
				elif grid[nx][ny] == '.' or grid[nx][ny] == '@':
					if not visited[ck][nx][ny]: nodes.put((ck, nx, ny, cs+1))
				# found keyprint("here")
				elif grid[nx][ny].islower():
					nk = ck | (1 << (ord(grid[nx][ny]) - ord('a'))) # add key
					if not visited[nk][nx][ny]: nodes.put((nk, nx, ny, cs+1))
				# found door
				elif grid[nx][ny].isupper():
					if ck & (1 << (ord(grid[nx][ny]) - ord('A'))): # check key
						if not visited[ck][nx][ny]: nodes.put((ck, nx, ny, cs+1))

		# paths exhausted, still missing keys
		return -1

"""
Test cases
"""
if __name__ == "__main__":
	sol = Solution()

	# test case 1
	grid = ["@.a..","###.#","b.A.B"]
	print("shortestPathAllKeys(" + str(grid) + ") = " +
	   str(sol.shortestPathAllKeys(grid)))

	# test case 2
	grid = ["@..aA","..B#.","....b"]
	print("shortestPathAllKeys(" + str(grid) + ") = " +
	   str(sol.shortestPathAllKeys(grid)))

	# test case 3
	grid = ["@Aa"]
	print("shortestPathAllKeys(" + str(grid) + ") = " +
	   str(sol.shortestPathAllKeys(grid)))