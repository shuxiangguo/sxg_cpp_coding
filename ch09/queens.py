# N 皇后问题，8皇后有92组解
N = 8
queens = [0] * 8
count = 0


def can_place(k, i): # 将k号皇后放到i列
    for j in range(k):
        # 不能放置的情形：同一列，对角线，反对角线
        if queens[j] == i or queens[j] -i == j -k or queens[j] - i == k - j:
            return False
    return True

# recurcive
def place(k):
    if k == N: # 放置完了
        global count
        count = count + 1
        print(count, queens)
    else: # 没放置完
        for i in range(N):
            if can_place(k, i): # k行i列
                queens[k] = i
                place(k+1)

place(0)
