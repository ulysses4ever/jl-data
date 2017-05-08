# based on: tests.py from https://github.com/gquere/stringsearch - Copyright (c) 2014 gquere  The MIT License (MIT)


function do_simple_test(runs, fct, isccall)
    i = 0
    local a
    if isccall
        tic()
        while i < runs
            a = Int(ccall(fct, Ptr{UInt8}, (Ptr{UInt8}, Ptr{UInt8}), "more_spring_concerning_string".data,  "string".data))
            i+=1
        end
        execution_time = toq()
    else
        tic()
        while i < runs
            a = fct("more_spring_concerning_string",  "string")
            i+=1
        end
        execution_time = toq()
    end
    assert(a==23)
    return round(execution_time, 4)
end

function do_medium_test(runs, fct, isccall)
    i = 0
    local a
    data_ = replace(readall("./tests/medium_text.txt"), "\n", "")
    if isccall
        tic()
        while i < runs
            a = Int(ccall(fct, Ptr{UInt8}, (Ptr{UInt8}, Ptr{UInt8}), data_.data,  "blob".data))
            i+=1
        end
        execution_time = toq()
    else
        tic()
        while i < runs
            a = fct(data_,  "blob")
            i+=1
        end
        execution_time = toq()
    end
    assert(a==291)
    return round(execution_time, 4)
end


function do_huge_test(runs, fct, isccall)
    i = 0
    local a
    data_ = replace(readall("./tests/huge_text.txt"), "\n", "")
    if isccall
        tic()
        while i < runs
            a = Int(ccall(fct, Ptr{UInt8}, (Ptr{UInt8}, Ptr{UInt8}), data_.data,  "string".data))
            i+=1
        end
        execution_time = toq()
    else
        tic()
        while i < runs
            a = fct(data_,  "string")
            i+=1
        end
        execution_time = toq()
    end
    assert(a==11120)
    return round(execution_time, 4)
end



function do_adn(runs, fct, isccall)
    i = 0
    local a
    data_ = replace(readall("./tests/adn_text.txt"), "\n", "")
    pattern = replace(readall("./tests/adn_pattern.txt"), "\n", "")
    if isccall
        tic()
        while i < runs
            a = Int(ccall(fct, Ptr{UInt8}, (Ptr{UInt8}, Ptr{UInt8}), data_.data,  pattern.data))
            i+=1
        end
        execution_time = toq()
    else
        tic()
        while i < runs
            a = fct(data_,  pattern)
            i+=1
        end
        execution_time = toq()
    end
    assert(a==775286)
    return round(execution_time, 4)
end


# strstr from libc
const strstr = Libdl.dlsym(Libdl.dlopen("./strstr/libstrstr.so", Libdl.RTLD_LOCAL), "strstr2")

# julia result = searchindex(str, tofind_str)
function jsearchidx(str::ASCIIString, tofind_str::ASCIIString)
    return searchindex(str, tofind_str) - 1
end

# tests to run
const fcts = [
    (strstr, "strstr", true),
    (jsearchidx, "julia search idx", false),
    ]


const tests = [
    (do_simple_test, 1000000, "SIMPLE"),
    (do_medium_test, 1000000, "MEDIUM"),
    (do_huge_test, 100000, "HUGE"),
    (do_adn, 1000, "ADN"),
]



function run_tests()
    # do tests and print results
    print("\t")
    for (fct, fctname) in fcts
        print("$fctname\t")
    end

    for (test, reps, testname) in tests
        println("")
        print("$testname\t")
        for (fct, fctname, isccall) in fcts
            extime = test(reps, fct, isccall)
            print("$extime\t")
        end

    end
    return nothing
end
run_tests()
