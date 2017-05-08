# Reference:
# http://elib.zib.de/pub/Packages/mp-testdata/mincost/netg/index.html

if !isfile("data/netg.tar.gz")
    println("Downloading netg.tar.gz...")
    download("http://elib.zib.de/pub/Packages/mp-testdata/mincost/netg.tar.gz", "data/netg.tar.gz")
end

println("Unpacking...")
run(`tar zxf data/netg.tar.gz --directory data --strip 1`)

println("Cleanup...")

files = [
         "cap6.net",
         "cap7.net",
         "cap8.net",
         "cap9.net",
         "cap10.net",
         "stndrd6.net",
         "stndrd7.net",
         "stndrd8.net",
         "stndrd9.net",
         "stndrd10.net",
         "transp6.net",
         "transp7.net",
         "transp8.net",
         "transp9.net",
         "transp10.net",
         "big4.net",
         "big5.net",
         "big6.net",
         "big7.net",
         "big8.net",
         ]

blacklist = [ "cap6.net", "transp10.net" ]

for f in readdir("data")
    endswith(f, ".net") && !(f in files) || continue
    println("Removing $f...")
    rm("data/$f")
end

for f in blacklist
    isfile("data/$f") || continue
    println("Quarantining $f...")
    mv("data/$f", "data/$(f)_")
end
