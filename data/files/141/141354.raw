# bounded_spigot.jl
# author: Bradley Mitchell

# This is an implementation of the Rabinowitz and Wagon spigot algorithm for
# calculating digits of pi as described in http://www.mathpropress.com/stan/bibliography/spigot.pdf


# Calculate a single digit of pi. All arguments are passed by reference.
function calc_digit(steps, augend, carry, sumarr, remainder)

    i = length(steps)
    carry[i] = 0
    while i>0
        sumarr[i] = augend[i] + carry[i]
        if i>1
            remainder[i] = sumarr[i] % den(steps[i])
            carry[i-1] = div(sumarr[i], den(steps[i])) * num(steps[i])
        elseif i==1
            remainder[i] = sumarr[i] % 10
        end
        i -= 1
    end
    return div(sumarr[1], 10)
end 




# number of pi digits to calculate
n = int(ARGS[1])

# estimated number of steps based formula given at 
# http://www.pi314.net/eng/goutte.php 
m = convert(Int64, ceil( 3.32 * n)) - 1

# initial array values
steps = [max(1,i)//(2*i+1) for i = 0:m]
init = [2 for i=0:m]
x10 = init.*10
carry = [0 for i=0:m]
sumarr = [0 for i=0:m]
remainder = [0 for i=0:m]

# julia has unicode characters
print(char(0x03c0))
print(" = ")

for i=1:n

    digit = calc_digit(steps, x10, carry, sumarr, remainder)

    print(digit)
    if i==1
        print(".")
    end
    
    x10 = remainder.*10
end

println("...")
