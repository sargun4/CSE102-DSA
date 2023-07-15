from collections import deque

# Binary tree node
class Node:
    def __init__(self, val):
        self.val = val
        self.left = None
        self.right = None

# Construct binary tree from level order traversal
def construct_tree(level_order):
    if not level_order:
        return None
    root = Node(level_order[0])
    q = deque([root])
    i = 1
    while q:
        node = q.popleft()
        if node:
            if i < len(level_order) and level_order[i] != -1:
                node.left = Node(level_order[i])
                q.append(node.left)
            i += 1
            if i < len(level_order) and level_order[i] != -1:
                node.right = Node(level_order[i])
                q.append(node.right)
            i += 1
    return root

# Compute height of binary tree
def height(root):
    if not root:
        return 0
    return 1 + max(height(root.left), height(root.right))

# Compute diameter of binary tree
def diameter(root):
    if not root:
        return 0
    left_diameter = diameter(root.left)
    right_diameter = diameter(root.right)
    left_height = height(root.left)
    right_height = height(root.right)
    return max(left_diameter, right_diameter, left_height + right_height + 1)

# Read input
n = int(input())
level_order = list(map(int, input().split()))

# Construct binary tree
root = construct_tree(level_order)

# Compute height and diameter of binary tree
h = height(root)
d = diameter(root)

# Print absolute difference between height and diameter
print(abs(h - d))
