module TestLookup

using Phonebook, Base.Test

cd(mktempdir()) do
    f = "test.pb"

    # It requires the right # of arguments
    @test_throws ErrorException mockpb("create")
    @test_throws ErrorException mockpb("create a b")

    mockpb("create $f")
    mockpb("add aname anumber $f")

    # It finds the names
    @test mockpb("lookup aname $f") == "aname anumber"

    # It doesn't pull names from thin air
    @test mockpb("lookup another $f") == ""
end

end # module
