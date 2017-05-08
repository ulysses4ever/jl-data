function Hermitian(n)
    #construimos primero una matriz cuadrada, nxn , con entradas en los complejos. 
    a=rand(n,n)+1im*rand(n,n)
    #Posteriormente se utiliza la función triu(a,1) para obtener la matriz triangular superior a partir de la entrada 1
    b=triu(a,1)
    M=b+transpose(conj(b))+Diagonal(rand(n,n))
    return M
end

function daga(state::Array{Complex{Float64},1})
    return transpose(conj(state))
end

function proyector(n)
    mat = Hermitian(n)
    A = zeros(n,n)
    V = eigvecs(mat)
    for i in 1:n
        A += kron(V[:,i], daga(V[:,i]))
    end
    return A
end

function identidad(n)
    H = proyector(n)
    I = eye(n)
    if norm(H-I) == 0 
        "Sí, es la identidad"
    else 
        "No, no es la identidad"
    end
end
