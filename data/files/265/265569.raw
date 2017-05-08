#! /usr/bin/env julia

sub_vol_list = open(`sudo btrfs subvolume list /`)

wait(sub_vol_list[2])

subvols = String[]

for line in eachline(sub_vol_list[1])
    if ismatch(r"var/lib/docker/btrfs/subvolumes/", line)
        vol = split(line)[9]
        push!(subvols, vol)
    end
end

print(subvols)

for vol in subvols
    run(`sudo btrfs subvolume delete -C /$vol`)
end
