import sys

def find_first_position(board):
    for i in range(8):
        for j in range(8):
            if board[i][j] == 1:
                return i, j

def check_sum(board):
    # Revisamos que la suma de las filas sea la misma
    suma = 0
    for i in range(8):
        if suma == 0:
            suma = sum(board[i])
        else:
            if suma != sum(board[i]):
                return False, "Filas no suman lo mismo"
    # Revisamos las columnas
    col_sum = 0
    for i in range(8):
        col = [row[i] for row in board]
        if suma != sum(col):
            return False, "Columnas no suman lo mismo"

    return True, "Ok"

def knight_movements(board, x, y, movement):
    if x < 0 or x > 7:
        return False
    if y < 0 or y > 7:
        return False
    if board[y][x] != movement:
        return False
    
    if movement == 64:
        return True
    
    x_move = [2, 1, -1, -2, -2, -1, 1, 2]
    y_move = [1, 2, 2, 1, -1, -2, -2, -1]
    for i in range(len(x_move)):
        result = knight_movements(board, x+x_move[i], y+y_move[i], movement+1)
        if result:
            return result
    return False


def is_solution(board):
    s, msg = check_sum(board)
    if not s:
        return False, msg

    y, x = find_first_position(board)
    movement = 1
    out_knight = knight_movements(board, x, y, 1)
    if not out_knight: 
        return False, "Movimiento invalido de caballo"
    return True, "Ok"



if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Modo de uso python3 check_backtracking.py obtained_output.txt")
    expected_out = sys.argv[1]
    board_out = []
    with open(expected_out, "r") as f:
        for k in range(8):
            board_out.append([int(a) for a in f.readline().strip(" \n").split(" ")])
    print(is_solution(board_out))
        