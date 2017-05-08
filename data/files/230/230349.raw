# Estimated the possible positions in Chess

board_size    = BigInt(8*8)
println("The board has ", board_size, " squares")
player_pieces = BigInt[8,2,2,2,1,1]
all_pieces    = vcat(player_pieces, player_pieces)

num_pieces = reduce(+, all_pieces)
println("There are ", num_pieces, " chess pieces")

num_empty = board_size - num_pieces

position_selections = factorial(board_size)/(factorial(board_size-num_empty)*factorial(num_empty))
println("There are ", position_selections, " ways to select the squares for these pieces")
ways_to_place_all_pieces = position_selections*factorial(num_pieces)/reduce(*, [factorial(x) for x=all_pieces])
println("There are ", ways_to_place_all_pieces, " ways to place all the pieces")
println("Note, this assumes that there's no restrictions on where pieces can be placed and that no pieces are removed from the board")