module TestChange

using Phonebook, Base.Test

cd(mktempdir()) do
    f = "test.pb"

    mockpb("create $f")
    mockpb("add aname anumber $f")

    # It required the right # of arguments
    @test_throws ErrorException mockpb("change a b")
    @test_throws ErrorException mockpb("change a b c d")

    # It changes records
    @test mockpb("change aname another $f") == ""
    @test mockpb("lookup aname $f") == "aname another"

    # It doesn't add records
    @test_throws ErrorException mockpb("change another anumber $f")
    @test mockpb("lookup aname $f") == "aname another"
end

end # module
