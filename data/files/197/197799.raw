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

board = initBoard()
displayBoard( board )
putStone( board, -1, [3,4] )
putStone( board, -1, [3,3] )
putStone( board, -1, [3,5] )

putStone( board, 1, [3,4] )
putStone( board, 1, [3,3] )
putStone( board, 1, [3,5] )

println( convertToString(getNextMove( board, 1 )) )
println( convertToString(getNextMove( board, -1 )) )
println( convertToString(getNextMove( board, -1 )) )
println( convertToString(getNextMove( board, -1 )) )

# Select Opposite stone
oppStone = selectPlayerStone()
ownStone = -1 * oppStone
println( "comp stone =", ownStone )

# Game
turnStone = -1
while( isContinue(board) )
        #numOfMoves;
        if( turnStone == ownStone )
                # Own turn
                if( isPass(board, ownStone) )
                        println("Com's turn is pass.")
                else
                        ownMove = getNextMove(board, ownStone)
                        num, board = putStone(board, ownStone, ownMove)
                end
        elseif( turnStone == oppStone )
                # Opposite turn
                if( isPass(board, oppStone) )
                        println("Your turn is pass.")
                else
                        oppMove = getNextMove(board, oppStone)
                        num, board = putStone(board, oppStone, oppMove)
                end
                #println("input move.  example: a5")
                # #line = read(STDIN,Char[2])
                #line = readline(STDIN)
                #dump( line )
                ##println(line)
                #print( int(line[1]) - int('a') + 1 )
                #print( int(line[2]) - int('0') )
                #break
        else
                @assert false
        end
        turnStone *= -1
end

# Result
println( sum(board) )
if( sum(board) * ownStone > 0 )
        println( "You lose. " )
elseif( sum(board) * oppStone > 0 )
        println( "You win." )
else
        @assert (sum(board) == 0)
        println( "Even." )
end

numOfBlack = countStone( board, -1 )
numOfWhite = countStone( board, +1 )
println( "Black= ", numOfBlack )
println( "White= ", numOfWhite )

