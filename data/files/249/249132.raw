tests = [
    "tables",
    "randtn"]

print_with_color(:blue, "Running tests:\n")

srand(345678)

for t in tests
    test_fn = "$t.jl"
    print_with_color(:green, "* $test_fn\n")
    let
        include(test_fn)
    end
end