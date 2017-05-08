quien = ["Uriel-Ricardo", "Humberto", "Mario", "Laura-Arturo", "Enoc", 
        "Nacho", "Victor", "Diego", "Pedro", "Micaela", "Ilya" ]

function turno!(quien::Array{ASCIIString,1})
    l = length(quien)
    turno = similar(quien)
    for i=1:l
        ll = length(quien)
        n = rand(1:ll)
        turno[i] = quien[n]
        deleteat!(quien,n)
        # @show(i, turno[i])
    end
    turno
end

turno = turno!(quien);
