# Declare InvalidModulo Exception
type InvalidModulo <: Exception end

# Modulo Type
type Modul
  val :: Integer
  mod :: Integer

  # Constructor :: forces val to be positive, which maps all equivalence classes to the Z mod m
  function Modul (val::Integer, mod::Integer)
    if mod <= 0
      throw(InvalidModulo())
    end
    val = val % mod
    val = val < 0 ? mod + val % mod : val
    mod = mod
    new(val, mod)
  end
end

# Modul(val, mod) = val < 0 ? 

# Adding numbers modulo and forcing them to be *positive*
function + (lhs::Modul, rhs::Modul)
  if lhs.mod != rhs.mod
    throw(InvalidModulo("Invalid Modulo"))
  end
  return Modul(lhs.val + rhs.val, lhs.mod)
end

#
#
function - (lhs::Modul, rhs::Modul)
  if lhs.mod != rhs.mod
    throw(InvalidModulo("Invalid Modulo"))
  end
  return Modul(lhs.val - rhs.val, lhs.mod)
end

# Multiplication
function * (lhs::Modul, rhs::Modul)
  if lhs.mod != rhs.mod
    throw(InvalidModulo("Invalid Modulo"))
  end
  mod = lhs.mod
  val = lhs.val * rhs.val
  return Modul(val, mod)
end


m = 5

for i = 0:m-1
  for j = 0:m-1
    local a = Modul(i, m)
    local b = Modul(j, m)
    println("$(a.val) + $(b.val) = $((a+b).val)")
  end
end

for i = 0:m-1
  for j = 0:m-1
    local a = Modul(i, m)
    local b = Modul(j, m)
    println("$(a.val) * $(b.val) = $((a*b).val)")
  end
end

# A = [
#   Modul(3, 7), Modul(4, 7) ;
#   Modul(1, 7), Modul(3, 7)
# ]