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

const BoardSize = 8
function initBoard()
        board = zeros(Int32, BoardSize, BoardSize)
        board[4,4] = 1
        board[4,5] = -1
        board[5,4] = -1
        board[5,5] = 1
        return board
end

function displayBoard( board )
        println(" abcdefgh")
        cnt = 1
        for i in 1:BoardSize
                boardLine = board[i,:]
                print(i)
                for stone in boardLine
                        if(stone == 0)
                                print(" ")
                        elseif(stone == 1)
                                print("O")
                        elseif(stone == -1)
                                print("X")
                        else
                                print("?")
                        end
                end
                println("")
        end
end

function putStone( board, stone, pos )
        directionArray = { [1,0], [1,1], [-1,0], [-1,-1], [0,-1], [1,-1] }
        #dump( direction )
        cnt, board = turnDirection( board, stone, pos, directionArray[1] )
        println( cnt )
        displayBoard( board )
end

function turnDirection( board, stone, position, direction )
        # prepare
        turnedboard = copy(board)
        nextPos = position
        oppStone = -1 * stone

        # turn stone
        checkCount = 0
        outBoardFlag = false
        emptyFlag = false
        while( true )
                nextPos += direction
                if ( isBoarder(nextPos) )
                        outBoardFlag = true
                        break
                end
                nextStone = getStone(turnedboard, nextPos)
                if( nextStone == stone )
                        break
                elseif( nextStone == oppStone )
                        changeStone(turnedboard, stone, nextPos)
                        checkCount += 1
                else
                        # Empty
                        emptyFlag = true
                end
        end
        diff = sum( turnedboard - board )
        #check 1
        @assert (diff % 2) == 0

        count = 0
        newboard = board
        if ( !outBoardFlag && !emptyFlag )
                count = abs(diff / 2)
                #check 2
                @assert count == checkCount
                if( count != 0 )
                        @assert sign(diff) == stone
                        newboard = turnedboard
                        changeStone( newboard, stone, position ) # put stone
                end
        end
        #display(turnedboard - board)
        #println( count )
        return count, newboard
end

function getStone( board, position )
        return board[position[2], position[1]]
end

function changeStone( board, stone, position )
        board[position[2], position[1]] = stone
end

function checkStone( board, stone, position )
        return ( getStone(position) == 0 )
end

function isBoarder( position )
        ret = false
        if( (position[1] < 1) || (position[1] > BoardSize ) )
                ret = true
        end
        if( (position[2] < 1) || (position[2] > BoardSize ) )
                ret = true
        end
        return ret
end

#function isPuttable( board, stone, position )
#        return true
#end
