# Build script based off: https://github.com/stevengj/Cubature.jl/blob/master/deps/build.jl
using BinDeps

# version of Cuba package to use
cubavers = "4.1"

tagfile = "installed_vers"
if !isfile(tagfile) || readchomp(tagfile) != cubavers
    if OS_NAME == :Linux
        if !isfile("Cuba-$cubavers.tar.gz")
            run(download_cmd("http://www.feynarts.de/cuba/Cuba-$cubavers.tar.gz", "Cuba-$cubavers.tar.gz"))
        end
        run(unpack_cmd("Cuba-$cubavers.tar.gz", ".", ".gz", ".tar"))
        cd("Cuba-$cubavers") do
            run(`./configure`)
            run(`make`)
        end
    else
        println("Non-Linux OS not currently supported.")
    end
    run(`echo $cubavers` |> tagfile)
end
