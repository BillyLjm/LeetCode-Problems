"""
2169-Count_Operations_to_Obtain_Zero.py
Billy.Ljm
09 November 2025

=======
Problem
=======
https://leetcode.com/problems/count-operations-to-obtain-zero/

You are given two non-negative integers num1 and num2.

In one operation, if num1 >= num2, you must subtract num2 from num1, otherwise
subtract num1 from num2.

- For example, if num1 = 5 and num2 = 4, subtract num2 from num1, thus obtaining
  num1 = 1 and num2 = 4. However, if num1 = 4 and num2 = 5, after one operation,
  num1 = 4 and num2 = 1.

Return the number of operations required to make either num1 = 0 or num2 = 0.

===========
My Approach
===========
We use a little shortcut to the algorithm specified. If num1 > n * num2, where n
is an integer, then the algorithm would go (num1, num2) -> (num1 - num2, num2)
-> (num1 - 2 * num2, num2), etc. So we can simplify this as (num1, num2) ->
(num1 % num2, num2), with num1 // num2 steps in between.

This has a time complexity of O(log min(num1, num2)) and space complexity of
O(1), where num1 and num2 are the given numbers.
"""

class Solution:
    def countOperations(self, num1: int, num2: int) -> int:
        cnt = 0
        # make num1 bigger
        if num1 < num2:
            num1, num2 = num2, num1
        # exec algorithm
        while num1 !=0 and num2 != 0:
            cnt += num1 // num2
            num1, num2 = num2, num1 % num2
        return cnt

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    num1 = 2
    num2 = 3
    print(f"countOperations({num1}, {num2}) = " +
        str(sol.countOperations(num1, num2)))

    # test case 2
    num1 = 10
    num2 = 10
    print(f"countOperations({num1}, {num2}) = " +
        str(sol.countOperations(num1, num2)))
