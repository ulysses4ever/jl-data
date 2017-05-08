#strings
#define with double quotes
s1 = "The quick brown fox jumps over the lazy dog"
println(s1) #adds new line
print(s1) # does not add new line

#chars in single quotes
c1 = 'a'
println(c1)

# ascii value of a char with int()
println(c1, " ascii value = ", int(c1))
#therefore be aware!!!!!
println(int('2') == 2) #returns false!

#strings converted to upper case
s1_caps = uppercase(s1)
s2_lower = lowercase(s1)

#sub strings are indexed like arrays
show(s1[11])
show(s1[1:10]) 

# use the end for the end of the array or string
show(s1[end-10:end])

# string interpolation
a = "welcome"
b = "to Julia"
println("$a to $b")

# you can use this to evaluate statements:
println("1 + 2 = $(1 + 2)")

#concatenate strings with the * operator
# NOT USING THE + operator
s2 = "this" * " and" * " that" 
println(s2)

# use the string function
s3 = string("this", " and", " that")

#string converting and formatting
# can be converted using float and int

e_str1 = "2.718"
e = float(e_str1)
5e

num_15 = int("15") # calling a string but converting inline to int

# can be converted using @printf
@printf " e = %0.2f\n" e

# create another string
e_str2 = @sprintf("%0.3f", e)

# comparing strings
println("e_str1 == e_str2: $(e_str1 == e_str2)")

# number format characters are f, e, g, c, s, p, d
# pi is math constant and must be converted to float to be formatted
@printf "fix trailing precision: %0.3f\n" float(pi)

@printf "scientific form: %0.6e\n" 1000pi

@printf "a character: %c\n" 'a'

@printf "a string: %s\n" "look I'm a string!"

@printf "right justify a string: %50s\n" "width 50, right justified!"

@printf "a pointer: %p\n" 1e10

@printf "print an integer: %d\n" 1e10

#string manipulations
s1 = "The quick brown fox jumps over the lazy dog"

# search returns the index of the character
i = search(s1, 'b')

#returns range on the string
r = search(s1, "brown")

r = replace(s1, "brown", "red")

# use regex
r = search(s1, r"b[\w]*n")
r = replace(s1, r"b[\w]*n", "red")

# regex matching
r = match(r"b[\w]*n", s1)
# regex match types hold the matched string
show(r.match)
typeof(r)

# match all returns vector of regex matches
r = matchall(r"[\w]{4,}", s1)
r = eachmatch(r"[\w]{4,}", s1)
for(i in r) print("\"$(i.match)\" ") end

# repeat strings using the repeat function
# or with the ^ operator
r = "hello "^3

#strip works the same as python taking away outer white space
r = strip("hello ")
# or with array as second argument
r = strip("hello ", ['h', ' '])

# split also works like in python
r = split("hello, there, bob", ',')

r = split("hello, there,bob", [',', ' '], 0, false)

# the opposite of split is join
r = join([1:10], ", ")























