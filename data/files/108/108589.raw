using BinDeps

if OS_NAME == :Linux
    run(`git submodule init`)
    run(`git submodule update`)
    cd("cuba") do
        run(`./configure`)
        run(`cp makefile.shared makefile`)
        run(`make`)
    end
else
    println("Non-Linux OS not currently supported.")
end
