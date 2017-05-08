using JuMP

function SolveSudoku(initialgrid)
  model = Model()

  @defVar(model, 0 <= x[1:9, 1:9, 1:9] <= 1, Int)

  for row in 1:9
    for col in 1:9
      if initialgrid[row, col] > 0
        @addConstraint(model, x[row, col, initialgrid[row, col]] == 1)
      end
    end
  end

  # Each cell contains exactly one value.
  for row in 1:9
    for col in 1:9
      @addConstraint(model, sum{x[row, col, val], val=1:9} == 1)
    end
  end

  # Each row contains exactly one instance of each value.
  for row in 1:9
    for val in 1:9
      @addConstraint(model, sum{x[row, col, val], col=1:9} == 1)
    end
  end

  # Each column contains exactly one instance of each value.
  for col in 1:9
    for val in 1:9
      @addConstraint(model, sum{x[row, col, val], row=1:9} == 1)
    end
  end

  # Each block contains exactly one instance of each value.
  for val in 1:9
    for blockrow in 1:3
      for blockcol in 1:3
        @addConstraint(model, sum{x[3*blockrow-a, 3*blockcol-b, val], a=0:2, b=0:2} == 1)
      end
    end
  end

  status = solve(model)

  if status == :Infeasible
    error("No valid solution.")
  else
    solveroutput = getValue(x)
    solution = zeros(Int, 9, 9)
    for row in 1:9
      for col in 1:9
        for val in 1:9
          # solveroutput is stored as floats.
          if solveroutput[row, col, val] >= 0.99
            solution[row, col] = val
          end
        end
      end
    end
    return solution
  end
end
