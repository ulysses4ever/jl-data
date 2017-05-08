module TestProjectTemplate
    using ProjectTemplate

    createproject("tmp")

    path = joinpath("tmp", "data", "foo.csv")
    io = open(path, "w")
    println(io, "A,B")
    println(io, "1,2")
    println(io, "3,NA")
    close(io)

    p = loadproject("tmp")

    run(`rm -rf ./tmp`)
end
