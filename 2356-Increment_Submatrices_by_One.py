"""
2356-Increment_Submatrices_by_One.py
Billy.Ljm
14 November 2025

=======
Problem
=======
https://leetcode.com/problems/increment-submatrices-by-one/

You are given a positive integer n, indicating that we initially have an n x n
0-indexed integer matrix mat filled with zeroes.

You are also given a 2D integer array query. For each query[i] =
[row1i, col1i, row2i, col2i], you should do the following operation:

- Add 1 to every element in the submatrix with the top left corner
  (row1i, col1i) and the bottom right corner (row2i, col2i). That is, add 1 to
  mat[x][y] for all row1i <= x <= row2i and col1i <= y <= col2i.

Return the matrix mat after performing every query.

===========
My Approach
===========
We will use a 2D difference array, marking only the edges of the submatrix on
each query, then calculating the matrix only in the last step. Specifically, we
mark the top left corner of the subarray with +1 to denote the value to the
bottom right should increase. Then we also mark one past the top right and
bottom left corners with -1 to negate the previous +1 since the subarray ended.
And lastly, we denote the bottom right corner with +1 to offset the combined
effect of the two -1 past that point. Then, we can calculate the matrix by
filling the values from top left to bottom right, adding the +-1 as we go.

This has a time complexity of O(n^2 + q) and space complexity of O(1), where n
is the size of the matrix and q the number of queries.
"""

from typing import List

class Solution:
    def rangeAddQueries(self, n: int, queries: List[List[int]]) -> List[List[int]]:
        # 2D difference matrix
        mat = [[0]*n for _ in range(n)]
        for x1, y1, x2, y2 in queries:
            mat[x1][y1] += 1
            if x2+1 < n: mat[x2+1][y1] -= 1
            if y2+1 < n: mat[x1][y2+1] -= 1
            if x2+1 < n and y2+1 < n: mat[x2+1][y2+1] += 1

        # prefix sum
        for i in range(n):
            for j in range(n):
                if i-1 >= 0: mat[i][j] += mat[i-1][j]
                if j-1 >= 0: mat[i][j] += mat[i][j-1]
                if i-1 >=0 and j-1 >= 0: mat[i][j] -= mat[i-1][j-1]
        return mat

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    n = 3
    queries = [[1,1,2,2],[0,0,1,1]]
    print(f"rangeAddQueries({n}, {queries}) = " +
        str(sol.rangeAddQueries(n, queries)))

    # test case 2
    n = 2
    queries = [[0,0,1,1]]
    print(f"rangeAddQueries({n}, {queries}) = " +
        str(sol.rangeAddQueries(n, queries)))
