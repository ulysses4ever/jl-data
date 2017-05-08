using Base.Test
#using Debug

# testdir
require("test/constants.jl")

# srcdir
require("src/types.jl")
require("src/cell.jl")

function testcells()
    newcell = Cell()
    @test newcell.genome==falses(GL)
    @test newcell.promoter==ones(GL)
end

testcells()
