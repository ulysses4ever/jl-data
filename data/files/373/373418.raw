using HttpServer

include("sudoku.jl")

http = HttpHandler() do req::Request, res::Response
  if ismatch(r"^/solve/", req.resource)
    splitrequest = split(req.resource, "/")
    problemstring = splitrequest[3]
    if length(problemstring) != 81
      return Response(400, "Error: Expected 81 numbers.")
    end

    problem = zeros(Int, 9, 9)
    pos = 1
    try
      for row = 1:9
        for col = 1:9
          value = Int(problemstring[pos])-48
          if value < 0 || value > 10
            return Response(422, "Error: Number out of range 0:9.")
          end
          problem[row, col] = value
          pos += 1
        end
      end
    catch
      return Response(422, "Error: Couldn't parse puzzle digits.")
    end

    try
      solution = SolveSudoku(problem)
      return Response(join(transpose(solution), ""))
    catch e
      return Response(422, "Error: No valid solution.")
    end
  else
    return Response(404)
  end
end

server = Server(http)
run(server, 8001)
