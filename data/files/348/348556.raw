using Seglib
using FactCheck

facts("spdist") do
    spmap = [fill(1, (3, 3)) fill(2, (3, 4));
             fill(3, (2, 3)) fill(4, (2, 4))]

    segmap = [3 3 3 3 3 3 3;
              3 2 2 2 3 3 3;
              3 3 2 2 3 3 3;
              3 3 2 2 2 2 2;
              1 1 1 1 1 2 2]

    context("pairs") do
        sp1indices = find(x -> x == 1, spmap)
        sp2indices = find(x -> x == 2, spmap)
        @fact spdist(segmap, sp1indices, sp2indices) => roughly(7 / 18)
    end

    context("all") do
        expected = [(1, 2) => 7 / 18,
                    (1, 3) => 13 / 18,
                    (2, 4) => 7 / 8,
                    (3, 4) => 3 / 4]

        result = spdist(spmap, segmap)

        resultkeys = sort!(collect(keys(result)))
        expectedkeys = sort!(collect(keys(expected)))

        @fact typeof(result) => Dict{(Int, Int), Float64}
        @fact resultkeys => expectedkeys
        resultvals = [result[k] for k in expectedkeys]
        expectedvals = [expected[k] for k in expectedkeys]
        @fact resultvals => roughly(expectedvals)
    end
end

facts("sp2boundaryindex") do
    seg = [3 3 2 2;
           3 2 2 2;
           2 2 1 1]

    expected = Vector{(Int, Int)}[[(2,3)]  [(2,3)]  []       []     ;
                                  [(2,3)]  [(1,2)]  [(1,2)]  [(1,2)];
                                  []       [(1,2)]  []       []     ]

    @fact seg2boundaryindex(seg) => expected
end
