#!/usr/bin/env julia

include("stringindex.jl")
using Base.Test

function test_simple()
    s = IndexedString("The lazy cat slept in the sunlight.")
    @test s[3] == "cat"
    println(s[3])
end

function test_invalid()
    s = IndexedString("The lazy cat slept in the sunlight.")
    @test s[0] == ""
    @test s[-1] == ""
end

function test_final()
    s =  IndexedString("...You...!!!@!3124131212 Hello have this is a --- string Solved !!...?")
    indices = Integer[12,-1,1,-100,4,1000,9,-1000,16,13,17,15]
    println(join([getindex(s, x) for x in indices], " "))
end

test_simple()
test_invalid()
test_final()
    

        
