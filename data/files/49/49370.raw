module TestCountMin

using CountMin
import CountMin: add!

if VERSION >= v"0.5-"
    using Base.Test
else
    using BaseTestNext
    const Test = BaseTestNext
end

include("testutil.jl")


@testset "CountMinSketch tests" begin
    @testset "CountMinSketch empty constructor" begin
        cms = CountMinSketch()
        @test eltype(cms.sketch) == UInt8
        @test cms.sketch == zeros(UInt8, 1000, 4)
        @test cms.tables == 4
        @test cms.tablesize == 1000
    end

    @testset "CountMinSketch normal constructor" begin
        cms = CountMinSketch{UInt16}(4, 100)
        @test eltype(cms.sketch) == UInt16
        @test size(cms.sketch) == (100, 4)
        @test cms.tables == 4
        @test cms.tablesize == 100

        # table too small @test_throws Exception CountMinSketch{UInt8}(4,0)
        # too few tables
        @test_throws Exception CountMinSketch{UInt8}(0,100)
        @test_throws Exception CountMinSketch{UInt8}(100,100)
    end

    @testset "CountMinSketch size/eltype" begin
        cms = CountMinSketch{UInt16}(4, 100)
        @test eltype(cms.sketch) == UInt16
        @test eltype(cms) == UInt16
        @test size(cms.sketch) == (100, 4)
        @test size(cms) == (4, 100)
    end

    @testset "CountMinSketch push/pop/add" begin
        cms = CountMinSketch{UInt16}(4, 100)
        @test cms[hash(1)] == UInt16(0)
        push!(cms, hash(1))
        @test cms[hash(1)] == UInt16(1)
        push!(cms, hash(1))
        @test cms[hash(1)] == UInt16(2)
        pop!(cms, hash(1))
        @test cms[hash(1)] == UInt16(1)
        add!(cms, hash(1), 100)
        @test cms[hash(1)] == UInt16(101)
        add!(cms, hash(1), -10)
        @test cms[hash(1)] == UInt16(91)
    end

    @testset "CountMinSketch getindex" begin
        cms = CountMinSketch{UInt16}(4, 100)
        item = "ABCD"
        @test cms[item] == UInt16(0)
        push!(cms, item)
        @test cms[item] == UInt16(1)
        push!(cms, item)
        @test cms[item] == UInt16(2)
        pop!(cms, item)
        @test cms[item] == UInt16(1)
        add!(cms, item, 100)
        @test cms[item] == UInt16(101)
        add!(cms, item, -10)
        @test cms[item] == UInt16(91)
    end

    @testset "CountMinSketch over/underflow" begin
        cms = CountMinSketch{UInt8}(4, 100)
        item = "ABCD"

        @test cms[item] == 0
        add!(cms, item, 256)
        @test cms[item] == 255
        add!(cms, item, -256)
        @test cms[item] == 0
    end

    @testset "CountMinSketch Read/Write" begin
        intempdir() do
            cms = CountMinSketch{UInt16}(4, 100)
            item = "ABCD"

            # Add item
            @test cms[item] == UInt16(0)
            push!(cms, item)
            @test cms[item] == UInt16(1)

            # Save and reload
            writecms("cms.h5", cms)

            newcms = readcms("cms.h5")
            # Shape & Type
            @test size(cms) == size(newcms)
            @test eltype(cms) == eltype(newcms)

            # Ensure value is preserved
            @test newcms[item] == UInt16(1)
        end
    end


    @testset "collisionrate(CountMinSketch)" begin
        cms = CountMinSketch{UInt16}(4, 100)

        # Fill the first half of each table. This is super dodgy
        for table in 1:4
            for i in 1:50
                cms.sketch[i, table] = 1
            end
        end
        # The above is to satisfy the following
        # @test sum(cms.sketch, 1) == UInt64[50 50 50 50]

        @test collisionrate(cms) == 0.5^4
    end
end # testset CountMinSketch

end # module TestCountMinSketch
