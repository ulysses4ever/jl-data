# Developing a stochastic model from a deterministic model.
# Take a deterministic ODE, instantiate a model instance,
# and create a new stochastic model.

# Requires terms to not be separated by a space. Can't have brackets - each
# term must be explicitly written.

M = fromOdeFile("SarOde.ode")

# Expand brackets
function expandBrackets()
  # All the ODEs in the model
  for j in keys(M.odes)
    rhs = M.odes[j]
    println(rhs)
    # Look for brackets
    if contains(rhs, "(") # Need to expand
      firstOpen = search(rhs, '(')
      println(firstOpen)
      firstClose = search(rhs, ')')
      println(firstClose)
      embraced = rhs[firstOpen+1:firstClose-1]
      println(embraced)
      # Find all the terms that are embraced
      parts = split(embrace, ['+', '-'])
      if length(parts) == 1 # only one term

      else

      end






    else # Don't need to expand

    end

  end

end


# Flatten the expression
function flattenExpress(expr)
  op = expr.args[1]
  po1 = expr.args[2]
  po2 = expr.args[3]
  if op == * && (typeof(po1)==Expr) && typeof(po2)==Symbol
    #flatten
    if it is + or -...
      symbolic link...

      ###
      if op == :* && typeof(po2)==Expr && typeof(po1) == Symbol
       newExpr = :($po1 * $(po2.args[2]) + $po1 * $( po2.args[3]))end       
       #####



    newExpr = :(po2*po1.args[2] + po2*po1.args[3])
    #flatten
  elseif op == * && typeof(po2)==Expr && typeof(po1)==Symbol
    newExpr = :(po1*po2.args[2] + po1*po2.args[3])
  elseif op == * && typeof(po1)==Expr && typeof(po2)==Expr
    if po1.args[1] == +

    elseif po1.args == -

    else if po1.args == *

    else # /

  else #flattened
    return newExpr
  end
end




# for i in keys(M.odes)
#   println("$(M.odes[i])")
#   parts = split(M.odes[i], "+")
#   print(parts)
# end



v = []

propNum = 12
# First generate code for cumulative reactions
cumProp = []
for j in 1:propNum



end

# Choose a reaction randomly

# Time for next reaction

# Determine what order each term in the propensity function is
