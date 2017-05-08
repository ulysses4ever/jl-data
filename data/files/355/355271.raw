function perlap(A,dx)
    D = padcirc(A)
    Nx = size(A)[1]
    Ny = size(A)[2]
    L = zeros(size(A))
    for j = 2:Ny+1
        for i = 2:Nx+1
            x = (1/dx^2)*(D[i-1,j] - 2*D[i,j] + D[i+1,j])
            y = (1/dx^2)*(D[i,j-1] - 2*D[i,j] + D[i,j+1])
            L[i-1,j-1] = x+y
        end
    end              
    return L
end
