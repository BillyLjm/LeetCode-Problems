"""
3318-Find_X-Sum_of_All_K-Long_Subarrays_I-alt_pq.py
Billy.Ljm
08 November 2025

=======
Problem
=======
https://leetcode.com/problems/find-x-sum-of-all-k-long-subarrays-i/

You are given an array nums of n integers and two integers k and x.

The x-sum of an array is calculated by the following procedure:

- Count the occurrences of all elements in the array.
- Keep only the occurrences of the top x most frequent elements. If two elements
  have the same number of occurrences, the element with the bigger value is
  considered more frequent.
- Calculate the sum of the resulting array.

Note that if an array has less than x distinct elements, its x-sum is the sum of
the array.

===========
My Approach
===========
We used a rolling window to keep track of the number occurrences of each element
within each subarray. We also incrementally infer the x-sum as the window slides
instead of recalculating it at every iteration, which trades off code conciseness
for some run-time savings.

This has a time complexity of O(n*k), and a space complexity of O(n*k), where n
is the number of integers and  k the length of the subarray.
"""

from typing import List
from collections import Counter
import heapq

class Solution:
    def __init__(self):
        self.k = 1
        self.x = 1
        self.xsum = 0 # x-sum of rolling window
        self.ctr = Counter([]) # count elements in rolling window
        self.large_eles = set() # x most frequent element
        self.large_pq = [] # priority queue of x-most elements, as (count, element)
        self.small_pq = [] # priority queue of other elements, as maxheap

    def large_push(self, cnt, ele):
        """ push into large_pq """
        if cnt > 0:
            heapq.heappush(self.large_pq, (cnt, ele))
            self.large_eles.add(ele)
        else:
            self.large_eles.discard(ele)

    def small_push(self, cnt, ele):
        """ push into small_pq """
        if cnt > 0:
            heapq.heappush(self.small_pq, (-cnt, -ele))

    def large_peek(self):
        """ peek at least frequent element in large_pq and lazy delete """
        cnt, ele = 0, 0 # default return value
        while len(self.large_pq) > 0:
            cnt, ele = self.large_pq[0]
            if self.ctr[ele] != cnt or ele not in self.large_eles:
                heapq.heappop(self.large_pq)
            else:
                break
        return cnt, ele

    def small_peek(self):
        """ peek at most frequent element in small_pq and lazy delete  """
        cnt, ele = 0, 0 # default return value
        while len(self.small_pq) > 0:
            cnt, ele = self.small_pq[0]
            cnt, ele = -cnt, -ele
            if self.ctr[ele] != cnt or ele in self.large_eles:
                heapq.heappop(self.small_pq)
            else:
                break
        return cnt, ele

    def calcXSum(self, nums: List[int], x: int) -> int:
        """
        Compute the X-sum of a given subarray and init supporting data structs.

        Parameters
        ----------
        nums : List[int]
            The list of integers to compute the X-sum for.
        x : int
            The number of most frequent elements to include in the X-sum.

        Returns
        -------
        int
            The computed X-sum value for the given list.
        """
        # count occurrences in list
        self.ctr = Counter(nums)
        tmp = sorted(self.ctr.items(), key=lambda x: (x[1], x[0]), reverse=True)

        # separate the x-most frequent elements
        self.xsum = 0
        self.large_eles = set()
        self.large_pq = []
        for ele, cnt in tmp[:x]:
            self.xsum += ele * cnt
            self.large_push(cnt, ele)

        # separate all the other less frequent elements
        self.small_pq = []
        for ele, cnt  in tmp[x:]:
            self.small_push(cnt, ele)

        return self.xsum

    def incrXSum(self, inn: int, outt: int) -> int:
        """ incrementally calculate xsum, for a sliding window """
        # update counter
        self.ctr.update([inn,])
        self.ctr.subtract([outt,])

        # increment quantity of number being added
        if inn in self.large_eles:
            self.xsum += inn
            self.large_push(self.ctr[inn], inn)
        else:
            self.small_push(self.ctr[inn], inn)

        # decrement quantity of number being removed
        if outt in self.large_eles:
            self.xsum -= outt
            self.large_push(self.ctr[outt], outt)
        else:
            self.small_push(self.ctr[outt], outt)

        # check if large element crossed into small
        while self.large_peek() < self.small_peek() and len(self.large_pq) > 0:
            cnt, ele = self.large_peek()
            self.xsum -= ele * cnt
            self.small_push(cnt, ele)
            heapq.heappop(self.large_pq)
            self.large_eles.discard(ele)

        # refill large from small
        while len(self.large_eles) < self.x and len(self.small_pq) > 0:
            cnt, ele = self.small_peek()
            self.xsum += ele * cnt
            self.large_push(cnt, ele)
            heapq.heappop(self.small_pq)

        return self.xsum

    def findXSum(self, nums: List[int], k: int, x: int) -> List[int]:
        self.k = k
        self.x = x
        out = [] # output; list of x-sums
        out.append(self.calcXSum(nums[:k], x))
        for i in range(1, len(nums) - k + 1):
            out.append(self.incrXSum(nums[i+k-1], nums[i-1]))
        return out

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    nums = [1,1,2,2,3,4,2,3]
    k = 6
    x = 2
    print(f"findXSum({nums}, {k}, {x}) = " +
        str(sol.findXSum(nums, k, x)))

    # test case 2
    nums = [3,8,7,8,7,5]
    k = 2
    x = 2
    print(f"findXSum({nums}, {k}, {x}) = " +
        str(sol.findXSum(nums, k, x)))
