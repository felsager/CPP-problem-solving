def frog_hop(board, idx, n, m, h):
    move = board[idx]
    print(f"move = {move}")
    if move == m:
        return f"magic\n{h}"
    elif not move:
        return f"cycle\n{h}"
    board[idx] = 0
    idx += move
    h += 1
    if idx < 0:
        return f"left\n{h}"
    elif idx > n - 1:
        return f"right\n{h}"  
    return frog_hop(board, idx, n, m, h)

n, s, m = map(int, input().split())
h = 0
s -= 1
board = list(map(int, input().split()))
print(frog_hop(board, s, n, m, h))