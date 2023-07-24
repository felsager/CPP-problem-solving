def frog_hop(board, idx, n, m, h)
    move = board[idx]
    return "magic\n#{h}" if move == m
    return "cycle\n#{h}" if move == 0
    board[idx] = 0
    idx += move
    h += 1
    return "left\n#{h}" if idx < 0;
    return "right\n#{h}" if idx >= n
    frog_hop(board, idx, n, m, h)
end

n, s, m = gets.split.map(&:to_i)
h = 0
s -= 1
board = gets.split.map(&:to_i)
puts frog_hop(board, s, n, m, h)