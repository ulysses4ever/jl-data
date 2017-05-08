#
type Z4
  val :: Integer  
  function Z4 (val)
    val = val % 4
    val = val < 0 ? val+4%4 : val
    new(val)
  end
end

function * (lhs::Z4, rhs::Z4)
  return Z4(lhs.val * rhs.val)
end

#
function + (lhs::Z4, rhs::Z4)
  return Z4(lhs.val + rhs.val)
end

M = [
  Z4(1) Z4(7);
  Z4(0) Z4(3)
]

I = [
  Z4(1) Z4(0);
  Z4(0) Z4(2)
]

println(M * I)