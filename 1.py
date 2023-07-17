chessboard = [[0] * 8 for _ in range(8)]
visitedRook = [[0] * 8 for _ in range(8)]
visitedBishop = [[0] * 8 for _ in range(8)]
visitedKnight = [[0] * 8 for _ in range(8)]

def is_valid(x, y):
    return 0 <= x < 8 and 0 <= y < 8

def find_rook_moves(rx, ry, count_rook, moves, recursing, direction):
    if moves == 0 or not is_valid(rx, ry) or visitedRook[rx][ry]:
        return

    count_rook[0] += 1
    visitedRook[rx][ry] = 1

    next_x = rx + 1
    while next_x < 8 and chessboard[next_x][ry]:
        find_rook_moves(next_x, ry, count_rook, moves if direction == 1 else moves - recursing, 1, 1)
        next_x += 1

    next_x = rx - 1
    while next_x >= 0 and chessboard[next_x][ry]:
        find_rook_moves(next_x, ry, count_rook, moves if direction == 1 else moves - recursing, 1, 1)
        next_x -= 1

    next_y = ry + 1
    while next_y < 8 and chessboard[rx][next_y]:
        find_rook_moves(rx, next_y, count_rook, moves if direction == 2 else moves - recursing, 1, 2)
        next_y += 1

    next_y = ry - 1
    while next_y >= 0 and chessboard[rx][next_y]:
        find_rook_moves(rx, next_y, count_rook, moves if direction == 2 else moves - recursing, 1, 2)
        next_y -= 1

def find_bishop_moves(bx, by, count_bishop, moves, recursing, direction):
    if moves == 0 or not is_valid(bx, by) or visitedBishop[bx][by]:
        return

    count_bishop[0] += 1
    visitedBishop[bx][by] = 1

    next_x = bx + 1
    next_y = by + 1
    while next_x < 8 and next_y < 8 and chessboard[next_x][next_y]:
        find_bishop_moves(next_x, next_y, count_bishop, moves if direction == 1 else moves - recursing, 1, 1)
        next_x += 1
        next_y += 1

    next_x = bx - 1
    next_y = by - 1
    while next_x >= 0 and next_y >= 0 and chessboard[next_x][next_y]:
        find_bishop_moves(next_x, next_y, count_bishop, moves if direction == 1 else moves - recursing, 1, 1)
        next_x -= 1
        next_y -= 1

    next_x = bx + 1
    next_y = by - 1
    while next_x < 8 and next_y >= 0 and chessboard[next_x][next_y]:
        find_bishop_moves(next_x, next_y, count_bishop, moves if direction == 2 else moves - recursing, 1, 2)
        next_x += 1
        next_y -= 1

    next_x = bx - 1
    next_y = by + 1
    while next_x >= 0 and next_y < 8 and chessboard[next_x][next_y]:
        find_bishop_moves(next_x, next_y, count_bishop, moves if direction == 2 else moves - recursing, 1, 2)
        next_x -= 1
        next_y += 1

def find_knight_moves(kx, ky, count_knight, moves):
    diff = [
        [0, 0], [2, 1], [2, -1], [-2, 1], [-2, -1],
        [1, 2], [-1, 2], [1, -2], [-1, -2]
    ]

    curr_boxes = [[kx, ky]]
    size_curr = 1

    while size_curr != 0 and moves > 0:
        next_boxes = []
        for i in range(size_curr):
            curr_x, curr_y = curr_boxes[i]
            for j in range(9):
                dx, dy = diff[j]
                next_x = curr_x + dx
                next_y = curr_y + dy
                if is_valid(next_x, next_y) and chessboard[next_x][next_y] and not visitedKnight[next_x][next_y]:
                    next_boxes.append([next_x, next_y])
                    count_knight[0] += 1
                    visitedKnight[next_x][next_y] = 1
        size_curr = len(next_boxes)
        curr_boxes = next_boxes
        moves -= 1

bx, by = map(int, input().split())
kx, ky = map(int, input().split())
rx, ry = map(int, input().split())
M = int(input())

for i in range(8):
    row = input()
    for j in range(8):
        chessboard[i][j] = 1 if row[j] == '.' else 0
        visitedBishop[i][j] = visitedKnight[i][j] = visitedRook[i][j] = 0

bx -= 1
by -= 1
kx -= 1
ky -= 1
rx -= 1
ry -= 1

countRook = [0]
countBishop = [0]
countKnight = [0]

if chessboard[rx][ry]:
    find_rook_moves(rx, ry, countRook, M, 0, 0)

if chessboard[bx][by]:
    find_bishop_moves(bx, by, countBishop, M, 0, 0)

if chessboard[kx][ky]:
    find_knight_moves(kx, ky, countKnight, M)

print(countBishop[0], countKnight[0], countRook[0])

# #include <stdio.h>
# int chessboard[8][8], visitedRook[8][8], visitedBishop[8][8], visitedKnight[8][8];
# int isValid(int x, int y) {
#     return ((0 <= x && x < 8) && (0 <= y && y < 8));
# }
# void findRookMoves(int rx, int ry, int *countRook, int moves, int recursing, int dir) {
#     if (moves == 0 || !isValid(rx, ry) || visitedRook[rx][ry]) {
#         return;
#     }
#     (*countRook)++;
#     visitedRook[rx][ry]++;
#     int nextX, nextY;
#     nextX = rx + 1;
#     while (chessboard[nextX][ry]) {
#         findRookMoves(nextX, ry, countRook, ((dir == 1) ? moves : moves - recursing), 1, 1);
#         nextX++;
#     }
#     nextX = rx - 1;
#     while (chessboard[nextX][ry]) {
#         findRookMoves(nextX, ry, countRook, ((dir == 1) ? moves : moves - recursing), 1, 1);
#         nextX--;
#     }
#     nextY = ry + 1;
#     while (chessboard[rx][nextY]) {
#         findRookMoves(rx, nextY, countRook, ((dir == 2) ? moves : moves - recursing), 1, 2);
#         nextY++;
#     }
#     nextY = ry - 1;
#     while (chessboard[rx][nextY]) {
#         findRookMoves(rx, nextY, countRook, ((dir == 2) ? moves : moves - recursing), 1, 2);
#         nextY--;
#     }
# }
# void findBishopMoves(int bx, int by, int *countBishop, int moves, int recursing, int dir) {
#     if (moves == 0 || !isValid(bx, by) || visitedBishop[bx][by]) {
#         return;
#     }
#     (*countBishop)++;
#     visitedBishop[bx][by]++;
#     int nextX, nextY;
#     nextX = bx + 1;
#     nextY = by + 1;
#     while (chessboard[nextX][nextY]) {
#         findBishopMoves(nextX, nextY, countBishop, ((dir == 1) ? moves : moves - recursing), 1, 1);
#         nextX++;
#         nextY++;
#     }
#     nextX = bx - 1;
#     nextY = by - 1;
#     while (chessboard[nextX][nextY]) {
#         findBishopMoves(nextX, nextY, countBishop, ((dir == 1) ? moves : moves - recursing), 1, 1);
#         nextX--;
#         nextY--;
#     }
#     nextX = bx + 1;
#     nextY = by - 1;
#     while (chessboard[nextX][nextY]) {
#         findBishopMoves(nextX, nextY, countBishop, ((dir == 2) ? moves : moves - recursing), 1, 2);
#         nextX++;
#         nextY--;
#     }
#     nextX = bx - 1;
#     nextY = by + 1;
#     while (chessboard[nextX][nextY]) {
#         findBishopMoves(nextX, nextY, countBishop, ((dir == 2) ? moves : moves - recursing), 1, 2);
#         nextX--;
#         nextY++;
#     }
# }
# void findKnightMoves(int kx, int ky, int *countKnight, int moves) {
#     int diff[9][2] = {
#         {0, 0}, {+2, +1}, {+2, -1}, {-2, +1}, {-2, -1}, 
#         {+1, +2}, {-1, +2}, {+1, -2}, {-1, -2}
#     };
#     int currX, currY;
#     int nextBoxes[16][2];
#     int sizeCurr, indexNext;
#     currX = kx;
#     currY = ky;
#     sizeCurr = 1;
#     nextBoxes[0][0] = currX;
#     nextBoxes[0][1] = currY;
#     while (sizeCurr != 0 && moves--) {
#         indexNext = 0;
#         for (int i = 0; i < sizeCurr; i++) {
#             currX = nextBoxes[i][0];
#             currY = nextBoxes[i][1];
#             for (int j = 0; j < 9; j++) {
#                 int nextX = currX + diff[j][0];
#                 int nextY = currY + diff[j][1];              
#                 if (isValid(nextX, nextY) && chessboard[nextX][nextY] && !visitedKnight[nextX][nextY]) {
#                     nextBoxes[indexNext][0] = nextX;
#                     nextBoxes[indexNext][1] = nextY;
#                     (*countKnight)++;
#                 }
#                 visitedKnight[nextX][nextY]++;
#             }
#             indexNext++;
#         }
#         sizeCurr = indexNext;
#     }
# }
# int main() {
#     int bx, by, kx, ky, rx, ry, M;
#     int countRook, countBishop, countKnight;
#     char row[9]; // Increased the size by 1 for null termination
#     for (int i = 0; i < 8; i++) {
#         scanf("%s", row);
#         for (int j = 0; j < 8; j++) {
#             chessboard[i][j] = ((row[j] == '.') ? 1 : 0);
#             visitedBishop[i][j] = visitedKnight[i][j] = visitedRook[i][j] = 0;
#         }
#     }
#     scanf("%d %d", &bx, &by);
#     scanf("%d %d", &kx, &ky);
#     scanf("%d %d", &rx, &ry);
#     scanf("%d", &M);
#     bx--; by--; kx--; ky--; rx--; ry--;
#     countRook = countBishop = countKnight = 0;
#     if (chessboard[rx][ry])
#         findRookMoves(rx, ry, &countRook, M, 0, 0);
#     if (chessboard[bx][by])
#         findBishopMoves(bx, by, &countBishop, M, 0, 0);
#     if (chessboard[kx][ky])
#         findKnightMoves(kx, ky, &countKnight, M);
#     printf("%d %d %d", countBishop, countKnight, countRook);
#     return 0;
# }
