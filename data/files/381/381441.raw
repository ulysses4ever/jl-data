# ZenFab command line implementation


function parse_commandline(args)
    s = ArgParseSettings(commands_are_required = false,
        version = VER,
        add_version = true,
        description = "ZenFab is a tool for digital manufacturing orchestration")
    @add_arg_table s begin
        "--console"
            help = ""
            action = :store_true
        "--port", "-p"
            help = "Serial port for device"
            arg_type = String
            default = ""
        "--baud", "-b"
            help = "Baudrate for serial port"
            arg_type = Int
            default = 115200
    end

    parsed_args = parse_args(args, s)

    if parsed_args["console"]
        serialconsole(parsed_args["port"],parsed_args["baud"])
    end
end
