#
# stone: Black=-1, White=1. 1st turn=Black
# move: (x,y) = [column, row]
# abcdefgh
#1
#2
#3
#4   XX
#5   XO
#6
#7
#8
#
import ReversiCore
using ReversiCore

# Initialize
board = initBoard()
displayBoard( board )

# Select Opposite stone
oppStone = selectPlayerStone()
ownStone = -1 * oppStone
println("Your stone =", oppStone)
println("comp stone =", ownStone)

# Game
turnStone = -1  # Black
while( isContinue(board) )
        #numOfMoves;
        if( turnStone == ownStone )
                # Own turn
                if( isPass(board, ownStone) )
                        println("Com's turn is pass.\n")
                else
                        ownMove = getNextMove(board, ownStone)
                        num, board = putStone(board, ownStone, ownMove)
                        # Display
                        dispOwnMove = convertToString( ownMove )
                        println( "Com Move = ", dispOwnMove )
                        displayBoard( board )
                        println("")
                end
        elseif( turnStone == oppStone )
                # Opposite turn
                if( isPass(board, oppStone) )
                        println("Your turn is pass.\n")
                else
                        oppMove = getPlayerMove(board, oppStone)
                        #oppMove = getNextMove(board, oppStone) # Debug
                        num, board = putStone(board, oppStone, oppMove)

                        # Display
                        dispOppMove = convertToString( oppMove )
                        println( "Your Move = ", dispOppMove )
                        displayBoard( board )
                        println("")
                end
        else
                @assert false
        end
        turnStone *= -1
end

# Result
oppColor = (oppStone == 1) ? "White" : "Black"
resultString = ""
if( sum(board) * ownStone > 0 )
        resultString = string("You(", oppColor, ") lose. " )
elseif( sum(board) * oppStone > 0 )
        resultString = string("You(", oppColor, ") win. " )
else
        @assert (sum(board) == 0)
        resultString = "Even"
end
println( resultString )

numOfBlack = countStone( board, -1 )
numOfWhite = countStone( board, +1 )
@assert ((numOfBlack + numOfWhite) == (BoardSize * BoardSize))
println( "Black= ", numOfBlack )
println( "White= ", numOfWhite )

