module RGlasso

export glasso

function glasso(S::Matrix, rho::Float64)
    writedlm("/tmp/RGlasso_tmp_matrix.txt", S)

    # start R and tell it to run glasso with a given rho value
    rcode = "library(glasso);" *
            "S = as.matrix(read.table('/tmp/RGlasso_tmp_matrix.txt', header=FALSE));" *
            "out = glasso(S, $rho);" *
            "write.table(out\$wi, '/tmp/RGlasso_tmp_matrix.txt', row.names=FALSE, col.names=FALSE)"
    run(`R -q -e $rcode`)

    w = readdlm("/tmp/RGlasso_tmp_matrix.txt")
    rm("/tmp/RGlasso_tmp_matrix.txt")
    w
end

end # module
