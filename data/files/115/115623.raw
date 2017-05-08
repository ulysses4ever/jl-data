# Basic chessboard state handler
type Board
   piecesWhite::Dict{String,(Int64,Int64)}
   piecesBlack::Dict{String,(Int64,Int64)} 
end

# king movement
function kingMoves(pos)
    newPositions = (Int64,Int64)[]
    for i = -1:1
        for j = -1:1
            if( i == 0 && j == 0 )
                continue
            end
            posNew = (pos[1]+i, pos[2]+j)

            if(posNew[1] > 0 && posNew[1] < 9 && posNew[2] > 0 && posNew[2] < 9) # board bounds
                push!(newPositions, posNew)
            end
        end
    end    
    return newPositions
end

# rook movement
function rookMoves(pos,otherPiece)
    newPositions = (Int64,Int64)[];
    x = pos[1]
    y = pos[2]
    
    # move right
    for i = x+1:8  
        posNew = (i,y)
        if(posNew == otherPiece)
            break
        end
        push!(newPositions,posNew) 
    end
    
    # move left    
    for i = x-1:-1:1
        posNew = (i,y)
        if(posNew == otherPiece)
            break
        end
        push!(newPositions,posNew) 
    end
    
    # move up    
    for j = y+1:8  
        posNew = (x,j)
        if(posNew == otherPiece)
            break
        end
        push!(newPositions,posNew) 
    end
    
    # move down        
    for j = y-1:-1:1
        posNew = (x,j)
        if(posNew == otherPiece)
            break
        end
        push!(newPositions,posNew) 
    end
    
    return newPositions
end

# Move generation
function moves(board::Board, player::Int64)
    # Assumes K+R vs K position for move generation/validation simplicity
    
    currPieces = Dict{String,(Int64,Int64)}
    enemyPieces = Dict{String,(Int64,Int64)}

    possibleMoves = (String,(Int64,Int64))[]
    
    if(player == 1) # white move
        currPieces = board.piecesWhite
        enemyPieces = board.piecesBlack
    else # black move
        currPieces = board.piecesBlack
        enemyPieces = board.piecesWhite
    end
    
    
    # Loop over the pieces
    for (piece,pos) in currPieces 
        if piece == "King"
            candidateMoves = kingMoves(pos)
            # Do not overlap your own pieces!
            filter!(x -> !in(x,values(currPieces)), candidateMoves)
            checks = (Int64,Int64)[]
            for (enemyPiece,enemyPos) in enemyPieces
                if(enemyPiece == "King")
                    checks = [checks, kingMoves(enemyPos)] 
                end
                if(enemyPiece == "Rook")
                    checks = [checks, rookMoves(enemyPos,enemyPieces["King"])]
                end
            end
            
            # Filter out placing king in check
            filter!(x->!in(x,checks),candidateMoves)
            
            [push!(possibleMoves,("King", move)) for move in candidateMoves]
            
        elseif piece == "Rook"
            candidateMoves = rookMoves(pos,currPieces["King"])
            [push!(possibleMoves,("Rook", move)) for move in candidateMoves]
        else
            println("ERROR: piece type not implemented")
        end        
    end
   
    return possibleMoves
end


function randSquare()
    return (rand(1:8),rand(1:8))
end

function validPos(board::Board)
    whitePieces = board.piecesWhite
    blackPieces = board.piecesBlack
    
    totalPieces = [whitePieces,blackPieces]
    if(length(unique(totalPieces)) != length(totalPieces))
        return false
    end
    if(length(moves(board,2)) == 0)  # king cannot move
        return false
    end
    
    whiteMoves = moves(board,1)
    for m in whiteMoves
        if(m[2] == blackPieces["King"])
            return false
        end
    end
    return true
end

function blackInCheck(board::Board)
    whitePieces = board.piecesWhite
    blackPieces = board.piecesBlack
    whiteMoves = moves(board,1)
    for m in whiteMoves
        if m[2] == blackPieces["King"]
            return true
        end
    end
    return false
end

function randomState()
    board = Board(["King"=>randSquare(),"Rook"=>randSquare()],["King"=>randSquare()])
    while(!validPos(board))
        board = Board(["King"=>randSquare(),"Rook"=>randSquare()],["King"=>randSquare()])
    end
    return board
end

# This assumes that the move has already been deemed valid so has no error checking
function makeMove!(board::Board, move::(String,(Int64,Int64)), player::Int64)
    piece = move[1]
    loc = move[2]
    if(player == 1) # white
        board.piecesWhite[piece] = loc
    else  # black
        board.piecesBlack[piece] = loc
        for (p,l) in board.piecesWhite
            if(l == loc)  # captured a piece
                delete!(board.piecesWhite,p)
            end
        end
    end
end
