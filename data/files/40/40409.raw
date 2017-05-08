using juliaspec

describe("Simple testing") do

  it("a passing test") do

  end

  it("a failing test") do
    throw(DomainError())
  end
  
end

describe("beforeTest and afterTest hooks") do
  x = 1
  y = 100

  beforeEach("increment") do
   x = x + 1
  end

  afterEach("decrement") do
    y = y -1
  end

  it("should have incremented x") do
    T(x, isEqualTo(2))
  end

  it("should have incremented x and decremented y - 1") do
    T(x, isEqualTo(3))
    T(y, isEqualTo(99))
  end

  it("should have incremented x and decremented y - 2") do
    T(x, isEqualTo(4))
    T(y, isEqualTo(98))
  end
end