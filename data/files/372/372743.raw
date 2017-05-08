require("args")

using Args
using ArgParse
using FactCheck

facts("Given a invocaction from cli") do
  function setup(f::Function, options::ASCIIString...)
    println(typeof(f))
    println(options)
    s = ArgParseSettings("Julia static site generator",
                       commands_are_required = true,
                       version = "0.1",
                       add_version = true)

    f(s)

    opts = Array(UTF8String,length(options))
    for i = 1:length(options)
      opts[i] = utf8(options[i])
    end

    parse_args(opts, s)
  end

  context("The new command verify the expected args values") do
    args = setup(Args.add_new_args, "-n", "--path", "..")

    @fact args["path"] --> ".." "The path isn't expected: `..` != $(args["path"])"
    @fact args["no-extra"] --> true "The no-extra options isn't true: $(args["no-extra"])"
    @fact args["light"] --> false "The light option value isn't expected: false != $(args["light"])"
  end

  context("The server command werify the args values") do
    args = setup(Args.add_server_args, "-p", "80")

    @fact typeof(args["port"]) --> Int "The port number isn't integer $(typeof(args["port"]))"
    @fact args["port"] --> 80 "The port isn't the expected: 80 != $(args["port"])"
    @fact args["host"] --> "127.0.0.1" "The host isn't the default: 127.0.0.1 != $(args["host"])"
  end
end
