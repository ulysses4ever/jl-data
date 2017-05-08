using SharedWords
using Base.Test

# write your own tests here
mystring = "Here is a string of words, with characters@ and other! things in,.. ait"
test = "Here is another string of words, how many words do they share?"
println(mystring)
println(test)
shared = sharedwords(mystring,test)
println("These strings share "*string(shared)*"words")
@test 5 == sharedwords(mystring,test)
@test 3 == sharedwords("My words are friends","My words are frieds")
@test 4 == sharedwords("My words are friends","My words are frieds",1)


