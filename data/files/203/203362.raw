#1
#Define a function that, given a number of red and black socks, returns the probability of picking out 2 red on the first try
function redSocks(red_socks, black_socks)
        all_socks = red_socks + black_socks
        p2socks = ( red_socks/(all_socks)) * ((red_socks-1)/(all_socks-1))
end

#Now apply this function over all possible combinations of 1-100 red and black socks
function chest(n)
    sockDrawers = zeros(n,n)  #Use zeros function to initialize matrix
    for i in 1:n, j in 1:n  #Handy looping notation makes it easy to embed loops.  J is the innermost loop here, and i is outermost.  i will represent red and j black
       sockDrawers[i,j] = redSocks(i,j) #Apply the function across the matrix
    end
    results = findnz(sockDrawers .== .5)[1:2] #Find all elements equal to .5 and return their indices(i.e. #socks) (findnz).  The [1:2] subset part just eliminates the vector of true/false values

    for i in 1:length(a[1])
            red = results[1][i]
            black = results[2][i]
            print(red)
            print(" red sock[s], ")
            print(black)
            println(" black sock[s].")
    end
end

#Run all combos of 1-100 red and black socks
chest(100)
