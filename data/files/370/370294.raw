#! /usr/bin/julia

# Rosetta Code, Secure temporary file

msg = "Rosetta Code, Secure temporary file, implemented with Julia."

(fname, tio) = mktemp()
println(fname, " created as a temporary file.")
println(tio, msg)
close(tio)
println("\"", msg, "\" written to ", fname)

ENV["TMPDIR"] = pwd()
(fname, tio) = mktemp()
println(fname, " created as a \"temporary\" file.")
println(tio, msg)
close(tio)
println("\"", msg, "\" written to ", fname)

