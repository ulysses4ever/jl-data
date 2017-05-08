# Basic chessboard state handler
type Board
   piecesWhite::Dict{String,(Int64,Int64)}
   piecesBlack::Dict{String,(Int64,Int64)} 
end

# Returns an array of all possible moves per piece for specified player 1 (white) or 2(black)
function moves(board::Board, player::Int64)
    # Assume K+R vs K position for now
    playerPieces = Dict{String,(Int64,Int64)}
    enemyPieces = Dict{String,(Int64,Int64)}

    moves = Array{(String,(Int64,Int64))}
    
    if(player == 1)
        currPieces = board.piecesWhite
        enemyPieces = board.piecesWhite
    else
        currPieces = board.piecesBlack
        enemyPieces = board.piecesBlack
    end
    
    return currPieces
end
