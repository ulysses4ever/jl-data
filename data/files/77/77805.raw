module TestCreate

using Phonebook, Base.Test

cd(mktempdir()) do
    f = "test.pb"

    # It required the right # of arguments
    @test_throws ErrorException mockpb("create")
    @test_throws ErrorException mockpb("create a b")

    # It creates a phonebook file
    @test !isfile(f)
    mockpb("create $f")
    @test isfile(f)

    mockpb("add aname anumber $f")

    # It doesn't overwrite or change existing files
    @test_throws ErrorException mockpb("create $f")
    @test mockpb("lookup aname $f") == "aname anumber"
end

end # module
