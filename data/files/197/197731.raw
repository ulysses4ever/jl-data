function getNextMove(board, stone)
        moveList = {}
        for x in 1:BoardSize
                for y in 1: BoardSize
                        move = [x,y]
                        if ( isPuttable(board, stone, move) )
                                append!( moveList, {move} )
                        end
                end
        end
        dump( moveList )
        return moveList
end
