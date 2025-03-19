def create_chessboard(n, m):
    board = []
    for i in range(n):
        row = []
        for j in range(m):
            if (i + j) % 2 == 0:
                row.append('.')
            else:
                row.append('*')
        board.append(row)
    return board


def print_chessboard(board):
    for row in board:
        print(' '.join(row))


height = 4
width = 5
chessboard = create_chessboard(height, width)
print_chessboard(chessboard)
