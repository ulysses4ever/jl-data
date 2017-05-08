module TestCountMin

using CountMin

if VERSION >= v"0.5-"
    using Base.Test
else
    using BaseTestNext
    const Test = BaseTestNext
end


@testset "CountMinSketch Basic Operations" begin
    @testset "CountMinSketch empty constructor" begin
        cms = CountMinSketch{UInt16}()
        @test eltype(cms.sketch) == UInt16
        @test cms.sketch == zeros(UInt16, 0, 0)
        @test cms.tables == 0
        @test cms.tablesize == 0

        cms = CountMinSketch{UInt8}()
        @test eltype(cms.sketch) == UInt8
        @test cms.sketch == zeros(UInt8, 0, 0)
        @test cms.tables == 0
        @test cms.tablesize == 0
    end

    @testset "CountMinSketch normal constructor" begin
        cms = CountMinSketch{UInt16}(4, 100)
        @test eltype(cms.sketch) == UInt16
        @test size(cms.sketch) == (4, 100)
        @test cms.tables == 4
        @test cms.tablesize == 100

        # table too small
        @test_throws Exception CountMinSketch{UInt8}(4,0)
        # too few tables
        @test_throws Exception CountMinSketch{UInt8}(0,100)
    end

    @testset "CountMinSketch properties" begin
        cms = CountMinSketch{UInt16}(4, 100)
        @test eltype(cms) == UInt16
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
end

@testset "CountMinSketch IO" begin
    @testset "CountMinSketch Read/Write" begin
        mktempdir() do dir
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
end


end # module TestCountMinSketch
