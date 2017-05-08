
@linux ? begin

mraa_dir = Pkg.dir("mraa")*"/deps/mraa"
build_dir = mraa_dir*"/build/"

if !isdir(build_dir)
    mkdir(build_dir)
end

cd(build_dir)

run(`cmake ..`)

run(`make`)

try
    run(`make install`)
catch err1
    try
        run(`sudo make install`)
    catch err2
        error("mraa could not install. Root is required.")
        rethrow(err2)
    end
end

end : error("mraa is only supported on Linux systems!")
