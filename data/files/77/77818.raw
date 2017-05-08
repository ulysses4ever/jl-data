module TestShell

using Phonebook, Base.Test

tmpdir = mktempdir()
cd(tmpdir) do
    f = "test.pb"

    mockpb("create $f")
    mockpb("add aname anumber $f")

    # Mock matches actual
    args = "reverse-lookup anumber $f"
    output = chomp(readall(`phonebook $(split(args))`))
    @test output == mockpb(args) == "aname"
end

end # module
