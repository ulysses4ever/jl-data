using FactCheck
include("factor.jl")


facts("testing fact()") do
    res = fact(0)
    @fact typeof(res) => Dict{Int64, Int64}
    @fact length(res) => 0

end

facts("testing firstfactor()") do
    @fact firstfactor(8, 2) => (2, 4)

    @fact firstfactor(15, 2) => (3, 5)
    @fact firstfactor(15, 4) => (5, 3)

    # it just does as it is told
    @fact firstfactor(100, 49) => (50, 2)

    @fact firstfactor(13, 2) => (13, 1)
end
