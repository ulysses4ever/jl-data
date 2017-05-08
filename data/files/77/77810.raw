module TestRemove

using Phonebook, Base.Test

cd(mktempdir()) do
    f = "test.pb"

    mockpb("create $f")
    mockpb("add aname anumber $f")

    # It required the right # of arguments
    @test_throws ErrorException mockpb("remove a")
    @test_throws ErrorException mockpb("remove a b c")

    # It removes records but doesn't pretend to remove nonexistent records
    @test mockpb("remove aname $f") == ""
    @test_throws ErrorException mockpb("remove aname $f")
end

end # module
