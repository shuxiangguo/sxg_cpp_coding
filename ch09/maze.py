# 迷宫问题
"""
8 8
*0******
*00**0**
**0**0**
**0**0**
*00000**
******0*
*000000*
******0*
0 1
7 6
"""
maze = list()
m, n = map(int, input().split())

for i in range(m):
    a = list(intput())
    maze.append(a)

entx, enty = map(int, input().split())
extx, exty = map(int, input().split())
incx = [-1, 1, 0, 0] # x方向
incy = [0, 0, -1, 1] # y方向

hist = list()
x = entx # x入口
y = enty # y入口
maze[x][y] = 'x'
dir = 0
while x != extx and y != exty:
    if dir <= 3:
        xx = x + incx[dir]
        yy = y + incy[dir]
        if 0 <= xx < m and 0 <= yy < n and maze[xx][yy] == '0': # 可以走
            hist.append(x, y, dir)
            x = xx
            y = yy
            maze[x][y] = 'x'
            dir = 0
        else:
            dir = dir + 1
    else:
        # 4个方向都试过，不合法
        tmp = hist.pop()
        x = tmp[0]
        y = tmp[1]
        dir = tmp[2] + 1

for x in hist:
    print('(%d,%d)-> '%(x[0],x[1]), end='')
print('(%d,%d)-> '%(extx, exty))