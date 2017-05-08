
const XON = Char(17)
const XOFF = Char(19)

@doc """
Initialize an interactive serial console.
Calling conventions are identical to `SerialPort`.
""" ->
function serialconsole(s::SerialPort)
    @async serialreader(s)
    while true
        print_with_color(:magenta, "\nserial> ")
        c = readline()
        !isspace(c) && write(s, c) # Don't send newlines
        sleep(1) # wait 1 second to allow output
    end
end

function serialconsole(args...)
    serialconsole(SerialPort(args...))
end

function serialreader(s::SerialPort)
    while true
        print(String(readavailable(s)))
    end
end

function serialsend(s::SerialPort, file::IO)
    c = Channel{String}(20)
    t = @async serialsend_proc(s, c)
    while !eof(file)
        str = readuntil(file, '\n')
        put!(c, str)
    end
    wait(t)
end

function serialsend_proc(s::SerialPort, c::Channel, out::IO=STDOUT)
    transmitting = true
    for msg in c
        @show msg
        write(s, msg)
        while true
            if nb_available(s) > 0
                b = readavailable(s)
                for r in b
                    write(out, r)
                    if r == XOFF
                        transmitting = false
                        print_with_color(:blue,"\nXOFF")
                    elseif !transmitting && r == XON
                        transmitting = true
                        print_with_color(:blue, "\nXON")
                    end
                end
            end
            sleep(0.05)
            transmitting && isready(c) && break
        end
    end
end
