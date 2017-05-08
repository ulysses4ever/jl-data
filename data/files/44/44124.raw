# This is a method to read a 2-by-(n+1) integer matrix from a CSV file
# and produce a probability density plot. First column is 0:n; second
# column is counts.

using PyPlot

function histomaker(filename::String)
    f = open(filename)
    A = readcsv(f,Int)
    x = A[:,1]
    y = A[:,2]
    y /= sum(y)
    plot(x,y)
end

# Add annotations to the plot
function decorate()
    xlabel("Out degree")
    ylabel("Probability")
    grid()
end
