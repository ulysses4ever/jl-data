include("../src/Hash.jl")
include("testing.jl")

fname = tempname()
test_strings = ["foo", "foobar", "baz", "this is a test", ""]
function check_hash(algorithm, fn)
    print("checking " * algorithm * " sums ")
    for value in test_strings
        f = open(fname, "w")
        write(f, value)
        close(f)

        command_line = strip(split(readall(`openssl dgst -$algorithm $fname`), " ")[2])
        library_with_passed_vaue = Hash.hex(fn(value))

        @assert_equal(command_line, library_with_passed_vaue)

        f = open(fname, "r")
        library_from_file = Hash.hex(fn(f))
        close(f)

        @assert_equal(command_line, library_from_file)
    end
    println()
end


check_hash("md4", Hash.md4)
check_hash("md5", Hash.md5)
check_hash("mdc2", Hash.mdc2)
check_hash("sha1", Hash.sha1)
check_hash("sha224", Hash.sha224)
check_hash("sha256", Hash.sha256)
check_hash("sha384", Hash.sha384)
check_hash("sha512", Hash.sha512)
println()