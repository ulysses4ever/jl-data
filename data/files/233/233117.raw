@unix_only begin
    cd(joinpath(dirname(@__FILE__), "src"))
    run(`gfortran -O3 --shared -fPIC -o libcshep2d.so src.f`)
end