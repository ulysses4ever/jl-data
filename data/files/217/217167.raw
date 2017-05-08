module CPUBeacon

export read_procstats!,
       usage,
       user,
       nice,
       system,
       idle,
       iowait,
       irq,
       softirq,
       getfraction

using Compat

teeprint(x) = begin
    println(x)
    x
end

for (i, field) in enumerate(
    [:user, :nice, :system, :idle, :iowait, :irq, :softirq])

    # LOLOL
    @eval $field(x) = x[$i]
end

parse_line(line) =
    map(x -> parse(Int, x), split(line, r"\s+")[2:end])

parse_procstats(statstr) =
    map(parse_line,
        filter(x -> startswith(x, "cpu"), split(statstr, "\n")))

getfraction(stat, fields=[user, system]) =
    sum(map(f -> f(stat), fields)) / sum(stat)

read_procstats!() =
    parse_procstats(readall("/proc/stat"))

sample(dt) = begin
    s0 = read_procstats!()
    sleep(dt)
    s1 = read_procstats!()
    ds = map(-, s1, s0)
end

usage(wait=1; fields=[user, system]) =
    map(x -> getfraction(x, fields), sample(wait))

end # moduled
