#%%
x = 'x'

# board construction ([[]], start x, start y, starting number) 

board1 =  ([[0,x,4,x,x,x],
            [3,x,1,x,5,x],
            [x,29,x,7,x,x],
            [x,2,x,x,x,6],
            [x,x,x,x,x,x]], 2, 3, 7)

board2 =  ([[0,x,x,x,x,x],
            [x,x,1,x,x,x],
            [x,x,x,x,x,x],
            [x,2,x,x,x,x],
            [x,x,x,x,x,x]], 2, 3, 2)

board3 =  ([[0,x,x,x,x,x],[x,x,x,x,x,x],[x,x,x,x,x,x],[x,x,x,x,x,x],[x,x,x,x,x,x]], 0, 0, 0)

board4 = ([[0,x,x,x],[x,x,x,x],[x,x,x,x],[x,x,x,x]], 0, 0, 0)


def fill_board(boardstate, debug=False):
    ''' brute force algorithm returns either the found solution as a board or nothing at all if fails.
    to find a closed loop add the last entry to the board manually'''

    (board, px, py, count) = boardstate
    if debug: print(board)

    count += 1
    if debug: print(count)

    # stop algorithm if last number of board is found (goes backwards recursive from here)
    if count == (len(board) * len(board[0])): 
        if debug: print('solution! found')
        return board
    
    # (a, b) are the 8 possible knight's moves
    a_,b_ = [1,-1,-2,-2,-1,1,2,2], [2,2,1,-1,-2,-2,-1,1]

    # iterate over all moves
    for i in range(8):
        a,b = a_[i],b_[i]

        if debug: print(f'x={px}, y={py}, x+a={px+a}, y+b={py+b}, a={a}, b={b}, Count={count}, State={i}')

        # skip loop if index out of bounds
        if ((px+a > (len(board[0])-1)) or (px+a < 0)) or (py+b > (len(board)-1) or py+b < 0): 
            if debug: print('out of index')
            continue

        # skip loop if current number is on the board but in a different place
        elif any([count in l for l in board]) and (board[px+a][py+b] != count):
            if debug: print('not the right position')
            continue

        # skip loop if looked at field is already occupied
        elif (board[px+a][py+b] != x) and (board[px+a][py+b] != count):
            if debug: print('already owned')
            continue

        else: 
            if debug: print('write ' + str(count))

            # copy variable this way because for some reason it shares memory space even if using .copy()
            # might be obsolete
            new_board = [[b for b in bo] for bo in board]
            
            # add number to board in new position
            new_board[px+a][py+b] = count

            # check all paths with new board
            result = fill_board((new_board, px+a, py+b, count), debug)

            if debug: print('result: ' + str(result))

            if result: return result

    if debug: print('exit at ' + str(count))

fill_board(board4, debug=True)

# %%
x = 3
y = 1
print(board[x][y])