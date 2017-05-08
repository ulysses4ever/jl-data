module TestReverse

using Phonebook, Base.Test

cd(mktempdir()) do
    f = "test.pb"

    mockpb("create $f")
    mockpb("add aname anumber $f")

    # It required the right # of arguments
    @test_throws ErrorException mockpb("reverse-lookup a")
    @test_throws ErrorException mockpb("reverse-lookup a b c")

    # It finds records but comes up empty when it should
    @test mockpb("reverse-lookup anumber $f") == "aname"
    @test mockpb("reverse-lookup another $f") == ""
end

end # module
