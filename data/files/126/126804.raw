module Handler

require("src/loadcsv.jl")
require("src/parser.jl")

using LoadCsv, Parser

export startStreaming

function startStreaming(data#=, sock=#)

    let headerLine = Array{ASCIIString}, parsed = 0

        function printStats()
            print("\n***\n")
            print("Finished: $(position(data))\n")
            print("Parsed: $parsed\n")
            print("Time: $(time_ns() - tinit)\n")
        end

        function finish()
            #...
            printStats()
        end

        function storeLine(line)
            #@async write(sock, "\\c3a:store|" * line)
            parsed += 1
        end

        function parseFailure(line)
            #...
        end

        function parseLine(line)
            @async Parser.parseLine(line, storeLine, parseFailure)
            (!eof(data)) ? (@async readLine()) : (finish())
        end

        function readLine()
            @async LoadCsv.readLine(data, parseLine)
        end

        function setHeader(line)
            headerLine = line
        end

        function getHeader()
            LoadCsv.readLine(data, setHeader)
        end

        tinit = time_ns()
        getHeader()
        @async readLine()
    end
end

end
