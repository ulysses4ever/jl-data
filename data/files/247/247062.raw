require("ArgParse")
require("Iterators")

using ArgParse, Iterators


function parse_commandline()
    s = ArgParseSettings()

    @add_arg_table s begin
        "--score-matrix", "-s"
            help = "an option with an argument"
            arg_type = String
            #required = true
        "--clustering", "-c"
            help = "clustering type: N for neighbour joining, U for UPGMA, W for WPGMA"
            arg_type = String
            default = "N"
            #required = false
        "--verbose"
          help = "show debug messages while processing data"
          action = :store_true
        "fasta-file"
            help = "file in .fasta format with a set of protein strings"
            required = true
        "output-file"
            help = "file in .fasta format for saving results"
            required = true
    end

    return parse_args(s)
end


type PDBAtomInfo
  serial :: Int
  atom :: String
  altLoc :: Char
  resName :: String
  chainID :: Char
  resSeq :: Int
  iCode :: Char
  x :: Float64
  y :: Float64
  z :: Float64
  occupancy :: Float64
  tempFactor :: Float64
  element :: String
  charge :: String
end

function parseAtomInfoFromString(line :: String)
  #TODO: check correctness
  #println(line)
  result = PDBAtomInfo(
      int(line[6:12]),
      strip(line[13:16]),
      line[17],
      strip(line[17:20]),
      line[22],
      int(line[23:26]),
      line[27],
      float(strip(line[31:38])),
      float(strip(line[39:46])),
      float(strip(line[47:54])),
      float(strip(line[55:60])),
      float(strip(line[61:66])),
      strip(line[76:78]),
      strip(line[79:80]))
  #println(result)
  result
end

immutable GeometryVector
  coordinates :: Array{Number, 1}
end
GeometryVector() = GeometryVector([0, 0, 0]) #by default is 3-dimensional

function GeometryVectorOp2(a :: GeometryVector, b :: GeometryVector, op)
  GeometryVector(map(op, zip(a.coordinates, b.coordinates)))
end

+(a :: GeometryVector, b :: GeometryVector) = GeometryVectorOp2(a, b, x-> x[1] + x[2])
-(a :: GeometryVector, b :: GeometryVector) = GeometryVectorOp2(a, b, x-> x[1] - x[2])
function /(a :: GeometryVector, b :: Number)
  GeometryVector(map(x -> x/b, a.coordinates))
end

function *(a :: GeometryVector, b :: Number)
  GeometryVector(map(x -> x*b, a.coordinates))
end

function *(a :: GeometryVector, b :: GeometryVector)
  sum(map(x -> x[1] * x[2], zip(a.coordinates, b.coordinates)))
end

len(a :: GeometryVector) = sqrt(a*a)
#println(len(GeometryVector([1,2,3])))

normalize(a :: GeometryVector) = a/len(a)

function projection(projected :: GeometryVector, whereToProject :: GeometryVector)
  whereToProject*(projected*whereToProject)
end

function projectToAxes(v :: GeometryVector, x :: GeometryVector, y :: GeometryVector, z :: GeometryVector)
  v_x = v*x
  v_y = (v - x*v_x)*y
  v_z = (v - x*v_x - y*v_y)*z
  GeometryVector([v_x, v_y, v_z])
end

function cross3d(a :: GeometryVector, b :: GeometryVector)
  GeometryVector([
    a.coordinates[2]*b.coordinates[3] - a.coordinates[3]*b.coordinates[2],
    -(a.coordinates[1]*b.coordinates[3] - a.coordinates[3]*b.coordinates[1]),
    a.coordinates[1]*b.coordinates[2] - a.coordinates[2]*b.coordinates[1]
    ])
end
#println(normalize(GeometryVector([1,2,3])))

type Rotamer
  atoms :: Dict{String, GeometryVector}
  center :: GeometryVector
end
Rotamer() = Rotamer(Dict{String, GeometryVector}(), GeometryVector([0, 0, 0]))


function readPDB(input_file_name :: String)
  records = Dict{Char, Dict{Int, Dict{String, PDBAtomInfo}}}()
  input_file = open(input_file_name, "r")
  while !eof(input_file)
    s = rstrip(readline(input_file), ['\r','\n'])
    if s[1:4] == "ATOM"
      atom = parseAtomInfoFromString(s)
      if !(atom.chainID in keys(records))
        records[atom.chainID] = Dict{Int, Dict{String, PDBAtomInfo}}()
      end
      if !(atom.resSeq in keys(records[atom.chainID]))
        records[atom.chainID][atom.resSeq] = Dict{String, PDBAtomInfo}()
      end
      records[atom.chainID][atom.resSeq][atom.atom] = atom
      #push!(records, parseAtomInfoFromString(s))
    end
  end
  close(input_file)
  records
end


getVector = a :: PDBAtomInfo -> GeometryVector([a.x, a.y, a.z])


function main()
    (r1, r2) = load_atom_info("2OSL.pdb")
    #parsed_args = parse_commandline()
    output_file = open("backbone.json", "w")
    println(output_file, JSON.json(r1, 1))
    close(output_file)
    output_file = open("sidechains.json", "w")
    println(output_file, JSON.json(r2, 1))
    close(output_file)
end

main()
