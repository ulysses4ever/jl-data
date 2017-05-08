using CircularArrays
using Base.Test

# @test 1 == 1

# # getindex test
# x = reshape([i for i in 1:15],3,5)
# carray = CircularArray(x)
# advance_head!(carray,2)
# @test getindex(carray,1:2,2:5) == [10 13 1 4; 11 14 2 5];

# # shorthand test
# @test carray[1:2,2:5] == [10 13 1 4; 11 14 2 5];


# # setindex! test
# c2 = CircularArray(reshape([i for i in 1:28],4,7))
# advance_head!(c2,3)
# setindex!(c2,[3:6],1:4,3)
# @test c2.data == 
# [1  5   9  13  17  3  25; 
#  2  6  10  14  18  4  26; 
#  3  7  11  15  19  5  27; 
#  4  8  12  16  20  6  28]


# different slicing dimension test
cdim = 1
X = falses(4,3,5)
C = CircularArray(X,cdim)
advance_head!(C,1)
C[1,1:3,1:5] = trues(3,5)
@test reshape(C.data[2,:,:],3,5) == trues(3,5)