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
function selectPlayerStone()
        selectedStone = 0
        while( true )
                println(STDOUT, "black(0) or white(1) ?")
                #selectedStone = int(input())
                #selectedStone = int(read(STDIN,Char)) - int('0')
                line = readline(STDIN)
                dump( line )
                selectedStone = line[1] - int('0')
                println( selectedStone )
                if( (selectedStone == 0) || (selectedStone == 1) )
                        break
                end
        end
        oppStone = (selectedStone == 1) ? 1 : -1
        return oppStone
end

function convertToString(move)
        a = int('a') + move[1] - 1
        n = int('0') + move[2]
        str = string(char(a), char(n))
        return str
end

function convertToMove(line)
        dump( line )
        println(line)
        move1 = int(line[1]) - int('a') + 1
        move2 = int(line[2]) - int('0')
        return [move2, move1]
end

function getPlayerMove(board, stone)
        move = [0,0]
        while( true )
                println(STDOUT, "input move.  example: a5")
                line = readline(STDIN)
                dump( line )
                move[1] = line[1] - int('a') + 1
                move[2] = line[2] - int('0')
                if( isPuttable(board, stone, move) )
                        break
                else
                        println("You cannot put.\n")
                end
        end
        return move
end

