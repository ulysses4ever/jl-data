function displayBoard( boardData )
        println(" abcdefgh")
        cnt = 1
        for i in 1:8
                boardLine = boardData[i,:]
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

function search( boardData, pos )
        direction = { [1,0], [1,1], [-1,0], [-1,-1], [0,-1], [1,-1] }
        #dump( direction )
        print( direction[1][2] )
end

function searchDirection( boardData, pos, direction )
        direction = { [1,0], [1,1], [-1,0], [-1,-1], [0,-1], [1,-1] }
        #dump( direction )
        print( direction[1][2] )
end

boardData = zeros(Int32, 8, 8)
boardData[4,4] = 1
boardData[4,5] = -1
boardData[5,4] = -1
boardData[5,5] = 1

displayBoard( boardData )
search( boardData )

println(STDOUT, "black(0) or white(1) ?")
#initMove = int(read(STDIN,Char)) - int('0')
#initMove = int(input())
#enum Turn
#    own = 0
#    opposite = 1
#end
#const TurnOwn = 0
#const TurnOpposite = 1

#print( initMove )
