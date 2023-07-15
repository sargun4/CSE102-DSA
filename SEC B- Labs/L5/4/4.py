# # Here's the algorithm to find the minimum time required for both players to find the treasure:

# # Parse the input and create the game board matrix.

# # Initialize two empty queues, one for each player, to perform the BFS search.

# # Initialize two visited arrays, one for each player, to keep track of visited cells.

# # Find the positions of both players and add them to their respective queues.

# # Initialize two distance arrays, one for each player, to keep track of the minimum distance from each player's position to the current cell.

# # Initialize two variables, treasureFoundByPlayer1 and treasureFoundByPlayer2, to keep track of whether the treasure is found by each player. Set both variables to False initially.

# # Perform the BFS search simultaneously for both players until both players find the treasure or both player queues become empty.

# # Dequeue the current player's position from their respective queue.
# # Mark the current cell as visited for the current player.
# # Check if the current cell contains the treasure 't'. If so, mark the respective treasureFoundByPlayer variable as True.
# # Explore the neighboring cells (up, down, left, and right) of the current cell.
# # If a neighboring cell is a valid empty cell (not a wall) and has not been visited by the current player, enqueue the neighboring cell and update the distance array for the current player.
# # Repeat the above steps for both players until both players find the treasure or both player queues become empty.
# # If both players find the treasure, return the maximum value from both players' distance arrays.

# # If either player's queue becomes empty before finding the treasure, return -1 to indicate that the treasure is unreachable.

# from collections import deque

# def minimumTimeToFindTreasure(n, matrix):
#     directions = [(1, 0), (-1, 0), (0, 1), (0, -1)]  # Up, Down, Right, Left

#     def isValidCell(x, y):
#         return 0 <= x < n and 0 <= y < n and matrix[x][y] != '#'

#     # Find positions of players and treasure
#     player1Pos, player2Pos, treasurePos = None, None, None
#     for i in range(n):
#         for j in range(n):
#             if matrix[i][j] == 'p':
#                 if player1Pos is None:
#                     player1Pos = (i, j)
#                 else:
#                     player2Pos = (i, j)
#             elif matrix[i][j] == 't':
#                 treasurePos = (i, j)

#     player1Queue = deque([player1Pos])
#     player2Queue = deque([player2Pos])

#     player1Visited = [[False] * n for _ in range(n)]
#     player2Visited = [[False] * n for _ in range(n)]

#     player1Distance = [[0] * n for _ in range(n)]
#     player2Distance = [[0] * n for _ in range(n)]

#     treasureFoundByPlayer1 = False
#     treasureFoundByPlayer2 = False

#     while player1Queue and player2Queue:
#         # Player 1's turn
#         currX, currY = player1Queue.popleft()
#         player1Visited[currX][currY] = True

#         if (currX, currY) == treasurePos:
#             treasureFoundByPlayer1 = True

#         for dx, dy in directions:
#             newX, newY = currX + dx, currY + dy
#             if isValidCell(newX, newY) and not player1Visited[newX][newY]:
#                 player1Queue.append((newX, newY))
#                 player1Distance[newX][newY] = player1Distance[currX][currY] + 1
#                 player1Visited[newX][newY] = True

#         # Player 2's turn
#         currX, currY = player2Queue.popleft()
#         player2Visited[currX][currY] = True

#         if (currX, currY) == treasurePos:
#             treasureFoundByPlayer2 = True

#         for dx, dy in directions:
#             newX, newY = currX + dx, currY + dy
#             if isValidCell(newX, newY) and not player2Visited[newX][newY]:
#                 player2Queue.append((newX, newY))
#                 player2Distance[newX][newY] = player2Distance[currX][currY] + 1
#                 player2Visited[newX][newY] = True

#     if treasureFoundByPlayer1 and treasureFoundByPlayer2:
#         return max(player1Distance[treasurePos[0]][treasurePos[1]], player2Distance[treasurePos[0]][treasurePos[1]])
#     else:
#         return -1

# # Read input
# n = int(input())
# matrix = []
# for _ in range(n):
#     matrix.append(input().split())

# # Calculate minimum time to find the treasure
# result = minimumTimeToFindTreasure(n, matrix)

# # Print the result
# print(result)


# Read the input values for m, n, the binary matrix, and the number of queries.

# Create a 2D array called "time" of size m x n and initialize all cells to infinity.

# Initialize an empty queue.

# Iterate over the boundary cells (cells on the edges of the matrix) and enqueue the normal plants (cells with a value of 0) into the queue. Set their corresponding time in the "time" array to 0.

# Perform a BFS until the queue becomes empty:

# Dequeue a cell (x, y) from the front of the queue.
# If the cell is within the matrix bounds and its value is 0 (normal plant) and the current time + 1 is less than the existing time at that cell, update the time to current time + 1 and enqueue the neighboring cells (up, down, left, right) if they meet the same conditions.
# For each query, check if the plant at position (x, y) caught fire. If it did, print the corresponding time from the "time" array. Otherwise, print "infinity".
from collections import deque

# Function to check if a cell is within the matrix bounds
def is_valid(x, y, m, n):
    return 0 <= x < m and 0 <= y < n

# Function to perform BFS and update the time for each cell
def calculate_time(matrix, m, n):
    time = [[float('inf')] * n for _ in range(m)]  # Initialize time array with infinity
    queue = deque()
    # Enqueue boundary cells with normal plants and set time to 0
    for i in range(m):
        for j in range(n):
            if (i == 0 or i == m - 1 or j == 0 or j == n - 1) and matrix[i][j] == 0:
                queue.append((i, j))
                time[i][j] = 0

    # Perform BFS
    while queue:
        x, y = queue.popleft()

        # Explore neighboring cells (up, down, left, right)
        for dx, dy in [(1, 0), (-1, 0), (0, 1), (0, -1)]:
            nx, ny = x + dx, y + dy

            if is_valid(nx, ny, m, n) and matrix[nx][ny] == 0 and time[x][y] + 1 < time[nx][ny]:
                time[nx][ny] = time[x][y] + 1
                queue.append((nx, ny))

    return time

# Read input
m, n = map(int, input().split())
matrix = []
for _ in range(m):
    matrix.append(list(map(int, input().split())))
q = int(input())

# Calculate time array
time = calculate_time(matrix, m, n)

# Process queries
for _ in range(q):
    x, y = map(int, input().split())

    # Check if plant caught fire
    if time[x][y] == float('inf'):
        print("infinity")
    else:
        print(time[x][y]+1)
