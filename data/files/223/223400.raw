module GNSS

export readsp3

function readsp3(filename::String)
    # open the file
    f = open(filename)

    data = []
    lineno = 0
    for line in eachline(f)
        lineno += 1

        # check file type
        if lineno == 1
            if line[2] != 'c'
                error("only SP3-c format is supported")
            end
            if line[3] != 'P'
                error("only position-only files are supported")
            end
            nepochs = int(line[33:39])
            nepoch = 0
            data = Array(Real, nepochs, 10, 32)
        end

        # check time system
        if lineno == 13
            if line[4:5] != "G "
                error("only GPS data files are supported")
            end
            if line[10:12] != "GPS"
                error("only GPS time is supported")
            end
        end

        if line[1:2] == "* "
            nepoch += 1
            t = [
                int(line[4:7])     # year
                int(line[9:10])    # month
                int(line[12:13])   # day
                int(line[15:16])   # hour
                int(line[18:19])   # minute
                float(line[21:31]) # second
                ]'
        end

        if line[1] == 'P'
            prn = int(line[3:4])
            p = [
                float(line[5:18])  # x (km)
                float(line[19:32]) # y (km)
                float(line[33:46]) # z (km)
                float(line[47:60]) # clock (μs)
                ]'
            data[nepoch, :, prn] = [t p]
        end
    end

    close(f)
    return data

end

end # module
