module CommutativeTests

using MetaTools
using FactCheck

module MetaTestModule1
  function baz()
  end
  function boo()
  end
end

facts("MetaTools.@commutative tests") do
  context("@commutative method") do
    @commutative function foo(s::String, i::Integer)
      return "$s -> $i"
    end

    @fact length(methods(foo)) => 2
    @fact foo("hello", 42) => "hello -> 42"
    @fact foo(42, "hello") => "hello -> 42"
  end

  context("@commutative with wrong type of function") do
    @fact_throws eval(:(@commutative function foo(s::String) end))
    @fact_throws eval(:(@commutative function foo(s1::String, s2::String) end))
    @fact_throws eval(:(@commutative function foo(s::String, i::Integer...) end))
    @fact_throws eval(:(@commutative function foo(s::String, i::Integer=10) end))
    @fact_throws eval(:(@commutative function foo(s1::String, s2::Integer, s3::FloatingPoint) end))
    @fact_throws eval(:(@commutative function foo(s::String, i::Integer; special=false) end))
    @fact_throws eval(:(@commutative function(s::String, i::Integer) end))
    @fact_throws eval(:(@commutative (s::String, i::Integer) -> begin end))
  end

  context("@commutative shorthand method") do
    @commutative bar(s::String, i::Integer) = "$s -> $i"

    @fact length(methods(bar)) => 2
    @fact bar("hello", 42) => "hello -> 42"
    @fact bar(42, "hello") => "hello -> 42"
  end

  context("@commutative method in namespace") do
    @commutative function MetaTestModule1.baz(s::String, i::Integer)
      return "$s -> $i"
    end

    @fact MetaTestModule1.baz("hello", 42) => "hello -> 42"
    @fact MetaTestModule1.baz(42, "hello") => "hello -> 42"
  end

  context("@commutative shorthand method in namespace") do
    @commutative MetaTestModule1.boo(s::String, i::Integer) = "$s -> $i"

    @fact MetaTestModule1.boo("hello", 42) => "hello -> 42"
    @fact MetaTestModule1.boo(42, "hello") => "hello -> 42"
  end

  context("@commutative method with an Any arg makes 3 methods") do
    @commutative function hmmm(a::Any, s::String)
      return "$s -> $a"
    end

    @fact length(methods(hmmm)) => 3
    @fact hmmm("hello", "world") => "hello -> world"
    @fact hmmm("hello", 42) => "hello -> 42"
    @fact hmmm(42, "hello") => "hello -> 42"
  end
end

end