using DataFrames
using YAML

type Stream
  source::AbstractString
  sink::AbstractString
  process::AbstractString
end
function Stream(s::AbstractString)
  source, pt = split(s, "-{")
  process, sink = split(pt, "}->")
  return(Stream(source, sink, process))
end

function load_streams(streamfile::AbstractString)
  return([Stream(s) for s in YAML.load(open(streamfile))["stream"]])
end

function evaluate(S::Stream)
  source = S.source
  sink = S.sink
  process = S.process
  eval(:(parse("$process")(source, sink)))
end

function copyfile(infile, outfile)
  a = readtable(infile)
  writetable(outfile, a)
end

S = load_streams("stream.yml")[1]
