"""
0146-LRU_Cache.py
Billy.Ljm
28 October 2025

=======
Problem
=======
https://leetcode.com/problems/lru-cache/

Design a data structure that follows the constraints of a Least Recently Used
(LRU) cache (https://en.wikipedia.org/wiki/Cache_replacement_policies#LRU).

Implement the LRUCache class:
- `LRUCache(int capacity)`: Initialize the LRU cache with positive size capacity.
- `int get(int key)`: Return the value of the key if the key exists, otherwise
   return -1.
- `void put(int key, int value)`: Update the value of the key if the key exists.
   Otherwise, add the key-value pair to the cache. If the number of keys exceeds
   the capacity from this operation, evict the least recently used key.

The functions get and put must each run in O(1) average time complexity.

===========
My Approach
===========
We will use a hashed doubly-linked list, where a hashmap maps the key to nodes
in a linked list. The hash allows us to get keys in O(1) time complexity. The
doubly-linked list remembers the order and LRU, and allows us to delete from it
in O(1) time after the key is identified via the hashmap.

This has a time complexity of O(1), and a space complexity of O(n), where n is 
the size of the cache.
"""

class LinkedNode:
    """ Single node in the linked list """
    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.prev = None
        self.next= None

class LRUCache(object):
    """ Least recently used cache """
    def __init__(self, capacity):
        """
        :type capacity: int
        """
        self.capacity = capacity
        self.dictt = dict() # hash map
        self.head = None # doubly linked list
        self.tail = None

    def delete(self, key):
        """
        delete a key from the cache
        """
        node = self.dictt[key]
        # join neighbours
        if node.next: node.next.prev = node.prev
        if node.prev: node.prev.next = node.next
        # reset tail if needed
        if self.tail == node:
            self.tail = node.prev
            if self.tail:
                self.tail.next = None
        # reset head if needed:
        if self.head == node:
            self.head = node.next
            if self.head:
                self.head.prev = None
        # update hashmap
        self.dictt.pop(key)
        self.capacity += 1
        del node

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """
        # if key doesn't exist, return -1
        if key not in self.dictt:
            return -1
        # else reorder
        else:
            val = self.dictt[key].value
            self.delete(key)
            self.put(key, val)
            return val

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: None
        """
        # if key already exists, just overwrite and reorder
        if key in self.dictt:
            self.delete(key)
        # else if full evict lru
        elif self.capacity == 0:
            self.delete(self.tail.key)
        # add new node to head
        self.capacity -= 1
        self.dictt[key] = LinkedNode(key, value)
        self.dictt[key].next = self.head
        if self.head:
            self.head.prev = self.dictt[key]
        self.head = self.dictt[key]
        # if no prevous tail
        if not self.tail:
            self.tail = self.dictt[key]


"""
Test cases
"""
if __name__ == "__main__":
    # test case 1
    cmds = ["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
    args = [[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
    for cmd, arg in zip(cmds, args):
        print(f">> {cmd}({','.join(map(str, arg))  }):")
        if cmd == "LRUCache":
            lru  = LRUCache(*arg)
        elif cmd == "get":
            print(lru.get(*arg))
        elif cmd == "put":
            lru.put(*arg)