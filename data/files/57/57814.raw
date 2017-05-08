#! /usr/bin/env julia

write(STDOUT, "I'm writing some stuff to STDOUT\n")

f = open("stream_test.txt", "w")

write(f, "I'm writing some stuff to a file\n")

close(f)

write(STDOUT, "I should have just wrote to a file.\n")
