 open("src/RandomTestMatrix.jl") do file
    s = false
    
    while !eof(file) 
        l = readline(file)
        if length(l) >= 3 && l[1:3] == "\"\"\""
           s = !s
           l = l[3:end]
        end 
        if s
            print(readline(file));
        end
    end
end

