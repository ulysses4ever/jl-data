# Here's simple addition
1 + 2 # 3

# Operators lik `+` are just functions in Julia
+ # + (generic function with 171 methods)

# So, you can do this (where 1 and 2 are arguments to the function `+`)
+(1, 2) # 3

# Or even this (Does this remind you of Lisp?)
+(1, 2, 3, 4) # 10

# Let's define a function
function add(a, b)
    # Julia function returns the value of the last expression, 'return' is only optional
    +(a, b)
end

add # add (generic function with 1 method)
add(1, 2) # 3

# With a nested function
function add2(a)
    function nested(b)
        +(a, b)
    end
end

add2 # add2 (generic function with 1 method)
add2(1)(2) # 3

# Anonymous function
add3 = ((a, b) -> +(a, b))

add3 # (anonymous function)
add3(1, 2) # 3

# Anonymous function with multi-line body
add4 = begin
    (a, b) ->
    +(a, b)
end

add4 # (anonymous function)
add4(1, 2) # 3

# With "varargs"
function add5(a, b, c...)
    +(a, b, sum(c))
end

add5 # (anonymous function)
add5(1, 2, 3, 4) # 10

# With optional arguments
function add6(a, b, c=0)
    +(a, b, c)
end

add6 # (anonymous function)
add6(1, 2, 3) # 6
add6(1, 2, c=3) # ERROR: ArgumentError: function add6 does not accept keyword arguments

# With keyword arguments
function add7(a, b; c=0)
    +(a, b, c)
end

add7(1, 2, c=3) # 6
