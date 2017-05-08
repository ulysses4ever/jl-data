##  |
## _|AYNIUS :: CHESS ENGINE


# MAKE A BOARD
#board = makeBoard(10,10,0)
function makeBoard(height, width, default_value)
   fill!(zeros(typeof(default_value), height, width), default_value)
end


# MOVES PIECES AROUND
# movePiece(board,3,5,8,8)
function movePiece(board, current_row, current_col, destination_row, destination_col)
    blank_square_symbol = 0
    
    piece = board[current_row,current_col]
    board[current_row,current_col] = blank_square_symbol
    board[destination_row, destination_col] = piece  
    board
end


white = [19,18,15,13,12,11]
black = [29,28,25,23,22,21]


# pieceValue(14)
function pieceValue(piece)
    # in the future this should simple return the value 
    # from a pre initialized array with keys matching pieces
    piece == 11 ? (return 10) :
    piece == 12 ? (return 30) :
    piece == 13 ? (return 33) :
    piece == 15 ? (return 50) :
    piece == 18 ? (return 90) :
    piece == 19 ? (return 99999999) :
    piece == 21 ? (return 10) :
    piece == 22 ? (return 30) :
    piece == 23 ? (return 33) : 
    piece == 25 ? (return 50) :
    piece == 28 ? (return 90) :
    piece == 29 ? (return 99999999) :
    0 #piece not found? defualts to 0
end

function humanReadable(piece)
    # in the future this should simple return the value 
    # from a pre initialized array with keys matching pieces
    piece == 11 ? (return "White pawn") :
    piece == 12 ? (return "White knight") :
    piece == 13 ? (return "White bishop") :
    piece == 15 ? (return "White rook") :
    piece == 18 ? (return "White queen") :
    piece == 19 ? (return "White king") :
    piece == 21 ? (return "Black pawn") :
    piece == 22 ? (return "Black knight") :
    piece == 23 ? (return "Black bishop") : 
    piece == 25 ? (return "Black rook") :
    piece == 28 ? (return "Black queen") :
    piece == 29 ? (return "Black king") :
    "None" #piece not found? defualts to "None"
end

function startingChessboard()
    board = makeEmptyBoard(10,10,0)
    for i = 1:8
        board[2,i] = 21
        board[2,i] = 21
    end
    for i = 1:8
        board[7,i] = 11
        board[7,i] = 11
    end
    board
end
startingChessboard()  