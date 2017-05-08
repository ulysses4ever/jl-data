using juliaspec

describe("Equality testing") do

  it("checks two entities are equal") do
    test(1, isEqualTo(1))
    T(1, isEqualTo(1))
  end

  it("checks failure when two entities are not equal") do
    try
      T(1, isEqualTo(2))  
      throw(Failure("should have thrown error"))
    catch e
      checkAssertionError(e, "Expected <1> to be equal to <2>.")
    end
  end

  it("checks two entities are not equal") do
    T(1, isNotEqualTo(2))
  end

  it("checks failure when two entities are equal when they are Expected to be not equal") do
    try
      T(1, isNotEqualTo(1))  
      throw(Failure("should have thrown error"))
    catch e
      checkAssertionError(e, "Expected <1> to not be equal to <1>.")
    end
  end
  
end
