#! /usr/bin/julia

# Rosetta Code, MD4

using Nettle

msg = "Rosetta Code"

h = HashState(MD4)
update!(h, msg)
h = hexdigest!(h)

println("\"", msg, "\" => ", h)
