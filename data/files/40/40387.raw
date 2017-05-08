export isEqualTo, isNotEqualTo

function isEqualTo(expected::Any)
  return function (x) 
    if !isequal(x,expected)
      throw(AssertionError(string("Expected <",x , "> to be equal to <", expected,">.")))
    end
  end
end

function isNotEqualTo(expected::Any)
  return function (x) 
    if isequal(x,expected)
      throw(AssertionError(string("Expected <",x , "> to not be equal to <", expected,">.")))
    end
  end
end