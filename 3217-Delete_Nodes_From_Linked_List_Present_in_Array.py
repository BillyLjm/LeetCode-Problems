"""
3217-Delete_Nodes_From_Linked_List_Present_in_Array.py
Billy.Ljm
01 November 2025

=======
Problem
=======
https://leetcode.com/problems/delete-nodes-from-linked-list-present-in-array/

You are given an array of integers nums and the head of a linked list. Return
the head of the modified linked list after removing all nodes from the linked
list that have a value that exists in nums.

===========
My Approach
===========
We will use a set to quickly compare the value of the linked list to the array.
Other than that, its just typical linked list deletion.

This has a time complexity of O(n), and a space complexity of O(1), where n is
the size of the linked list.
"""

from typing import List, Optional

class ListNode:
    def __init__(self, val=0, next=None):
        """ Single node in linked list """
        self.val = val
        self.next = next

    @classmethod
    def from_list(cls, vals):
        """ created linked list from list """
        head = cls(vals[0])
        crawl = head
        for val in vals[1:]:
            crawl.next = cls(val)
            crawl = crawl.next
        return head

    def __str__(self):
        vals = []
        crawl = self
        while crawl != None:
            vals.append(str(crawl.val))
            crawl = crawl.next
        return '[' + ','.join(vals) + ']'

class Solution:
    def modifiedList(self, nums: List[int], head: Optional[ListNode]) -> \
        Optional[ListNode]:
        nums = set(nums)
        prev = ListNode(0, head) # dummy node
        crawl = prev
        while crawl.next != None:
            if crawl.next.val in nums:
                crawl.next = crawl.next.next # delete node
            else:
                crawl = crawl.next # crawl to next
        return prev.next

"""
Test cases
"""
if __name__ == "__main__":
    sol = Solution()

    # test case 1
    nums = [1,2,3]
    head = ListNode.from_list([1,2,3,4,5])
    print(f"modifiedList({nums}, {head}) = " +
       str(sol.modifiedList(nums, head)))

    # test case 2
    nums = [1]
    head = ListNode.from_list([1,2,1,2,1,2])
    print(f"modifiedList({nums}, {head}) = " +
       str(sol.modifiedList(nums, head)))

    # test case 3
    nums = [5]
    head = ListNode.from_list([1,2,3,4])
    print(f"modifiedList({nums}, {head}) = " +
       str(sol.modifiedList(nums, head)))
