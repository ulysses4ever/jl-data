using SharedWords
using Base.Test

# write your own tests here
mystring = "Here is a string of words, with characters@ and other! things in,.. ait"
test = "Here is another string of words, how many words do they share?"
shared = sharedwords(mystring,test)
println("These strings share "*string(shared)*" words")
@test 5 == sharedwords(mystring,test)
@test 3 == sharedwords("My words are friends","My words are frieds")
@test 4 == sharedwords("My words are friends","My words are frieds",1)
@test 0.25 == jarowinkler("My strings are friends","My strings are enemies")
@test 0.0  == jarowinkler("My strings are friends","My strings are enemies",6)
@test 0.0 == jarowinkler("This is my string","This is my other string that is obviously larger")
@test 0.25 == jarowinkler("This is my string", "This is string that is obviously larger")
@test 0.5 == jarowinkler("This is my string", "This is strung that is obviously larger")
@test 0 == jarowinkler("This is my string","This is srung that is obviously larger",2)
println("All tests passed!")
