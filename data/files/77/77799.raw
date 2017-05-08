module TestAdd

using Phonebook, Base.Test

cd(mktempdir()) do
    f = "test.pb"

    mockpb("create $f")

    # It required the right # of arguments
    @test_throws ErrorException mockpb("add a b")
    @test_throws ErrorException mockpb("add a b c d")

    # It adds records but doesn't change them
    @test mockpb("add aname anumber $f") == ""
    @test_throws ErrorException mockpb("add aname another $f")
    @test mockpb("lookup aname $f") == "aname anumber"
end

end # module
