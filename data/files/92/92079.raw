using DataFrames

const DATADIR = "data"

# Get samples from a patient from a specific file
function get_samples(patient, patient_id, hour, channels, range)
    function splice(hour, range, direction)
        function read_channel(c)
            filepath(d, c) =
                DATADIR * "/pat$(lpad(patient, 3, 0) * d)" *
                "/$(patient_id)_$(lpad(hour, 4, 0))_$(c).asc"

            if isfile(filepath("Iktal", c))
                readtable(filepath("Iktal", c), header=false)
            else
                readtable(filepath("Interictal", c), header=false)
            end
        end

        if direction == :forward
            if range.start > 0
                df = reduce(hcat, map(read_channel, channels))
                n = size(df, 1)
                remaining = range.start + range.len - n-1
                if remaining > 0
                    df = vcat(df[range.start:n, :],
                              splice(hour+1, 1:remaining, :forward))
                else
                    df = df[range, :]
                end
            else
                # range.start is negative
                df = vcat(splice(hour-1, 0:-(range.start+1), :backward),
                          splice(hour, 1:range.start+range.len-1, :forward))
            end
            
        elseif direction == :backward
            df = reduce(hcat, map(read_channel, channels))
            n = size(df, 1)
            remaining = range.len - n
            if remaining > 0
                df = vcat(splice(hour-1, 0:remaining, :backward), df)
            else
                df = df[n-range.len:n, :]
            end
        end
        df
    end
    splice(hour, range, :forward)
end

# Return a DataFrame containing info about all the seizures
function seizures()
    SEIZURE_LINE = r"^\s*([0-9a-f_]+)\s+([0-9]+)\s+([0-9]+)\s*$"
    patientfiles = filter(x -> ismatch(r"pat.*\.txt", x), readdir(DATADIR))
    table = DataFrame()
    get_num = p -> int(match(r"([0-9]+)", p).captures[1])
    for p in patientfiles
        lines = open(readlines, DATADIR * "/" * p)
        for line in lines
            parts = match(SEIZURE_LINE, line)
            if parts != nothing
                c = parts.captures
                row = DataFrame()
                row[:patient] = [get_num(p)]
                row[:patient_id] = [split(c[1], "_")[1]]
                row[:hour] = [int(split(c[1], "_")[2])]
                row[:onset] = [int(c[2])]
                row[:offset] = [int(c[3])]
                table = vcat(table, row)
            end
        end
    end
    if isfile(DATADIR * "/patient_meta.csv")
        meta = readtable(DATADIR * "/patient_meta.csv")
        table = join(table, meta, on=:patient)
    end
    table
end
