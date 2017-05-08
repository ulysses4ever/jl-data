#! /usr/bin/env julia

io = open("output.txt","w")

a = "Hello, World!"

serialize(io,a)

close(io)


f = open("output.txt","r")

println(deserialize(f))

close(f)
