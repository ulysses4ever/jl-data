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

getNextMove( board, 1 )
getNextMove( board, -1 )

# Select Opposite stone
selectedStone = 0
while( true )
        println(STDOUT, "black(0) or white(1) ?")
        #selectedStone = int(input())
        selectedStone = int(read(STDIN,Char)) - int('0')
        #print( selectedStone )
        if( (selectedStone == 0) || (selectedStone == 1) )
                break
        end
end
oppStone = (selectedStone == 0) ? 1 : -1
ownStone = -1 * oppStone
println( ownStone )

# Game
turnStone = -1
while( isContinue(board) )
        #numOfMoves;
        if( turnStone == ownStone )
                # Own turn
        elseif( turnStone == oppStone )
                # Opposite turn
                println("input move.  example: a5")
                line = read(STDIN,Char[2])
                println(line)
        else
                @assert false
        end
        turnStone *= -1
end

# Result
numOfOwnStones = countStone( board, ownStone )
numOfOppStones = countStone( board, oppStone )
if( numOfOwnStones > numOfOppStones )
        println( "You lose." )
elseif( numOfOwnStones < numOfOppStones )
        println( "You win." )
else
        println( "Even." )
end

