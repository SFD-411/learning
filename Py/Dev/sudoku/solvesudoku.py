Puzzle = [[1,0,0,0,0,7,0,9,0],
          [0,3,0,0,2,0,0,0,8],
          [0,0,9,6,0,0,5,0,0],
          [0,0,5,3,0,0,9,0,0],
          [0,1,0,0,8,0,0,0,2],
          [6,0,0,0,0,4,0,0,0],
          [3,0,0,0,0,0,0,1,0],
          [0,4,0,0,0,0,0,0,7],
          [0,0,7,0,0,0,3,0,0]]

def possibilities(y, x, n):
    global Puzzle
    for i in range (0,9):
        if Puzzle[y][i] == n:
            return False
    for i in range (0,9):
        if Puzzle[i][x] == n:
            return False
    xfloor = (x//3) * 3
    yfloor = (y//3) * 3
    for i in range(0,3):
        for j in range(0,3):
            if Puzzle[yfloor+i][xfloor+j] == n:
                return False
    return True

def solve():
    global Puzzle
    for y in range(9):
        for x in range(9):
            if Puzzle[y][x] == 0:
                for n in range (1,10):
                    if possibilities(y, x, n):
                        Puzzle[y][x] = n
                        solve()
                        Puzzle[y][x] = 0
                return
    for rows in Puzzle:
        print(rows)
    input("Try Another Solution?")

solve()
