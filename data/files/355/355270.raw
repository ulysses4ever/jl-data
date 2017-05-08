function padcirc(C)

    Nx = size(C)[1]
    Ny = size(C)[2]
    D = zeros(Nx+2,Ny+2)

    D[2:Nx+1,2:Ny+1] = C
    D[Nx+2,Ny+2] = C[1,1]
    D[Nx+2,1] = C[1,Ny]
    D[1,Ny+2] = C[Nx,1]
    D[1,1] = C[Nx,Ny]
    D[Nx+2,2:Ny+1] = C[1,:]
    D[1,2:Ny+1] = C[Nx,:]
    D[2:Nx+1,1] = C[:,Ny]
    D[2:Nx+1,Ny+2] = C[:,1]

    return D

end
