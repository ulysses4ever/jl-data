using RunTests
using Base.Test
import MetaTools.@commutative

@testmodule CommutativeTests begin
  using MetaTools

  module MetaTestModule1
    function baz()
    end
    function boo()
    end
  end

  function commutative_method()
    @commutative function foo(s::String, i::Integer)
      return "$s -> $i"
    end

    @test length(methods(foo)) == 2
    @test foo("hello", 42) == "hello -> 42"
    @test foo(42, "hello") == "hello -> 42"
  end

  function commutative_with_wrong_type_of_function()
    @test_throws eval(:(@commutative function foo(s::String) end))
    @test_throws eval(:(@commutative function foo(s1::String, s2::String) end))
    @test_throws eval(:(@commutative function foo(s::String, i::Integer...) end))
    @test_throws eval(:(@commutative function foo(s::String, i::Integer=10) end))
    @test_throws eval(:(@commutative function foo(s1::String, s2::Integer, s3::FloatingPoint) end))
    @test_throws eval(:(@commutative function foo(s::String, i::Integer; special=false) end))
    @test_throws eval(:(@commutative function(s::String, i::Integer) end))
    @test_throws eval(:(@commutative (s::String, i::Integer) -> begin end))
  end

  function commutative_shorthand_method()
    @commutative bar(s::String, i::Integer) = "$s -> $i"

    @test length(methods(bar)) == 2
    @test bar("hello", 42) == "hello -> 42"
    @test bar(42, "hello") == "hello -> 42"
  end

  function commutative_method_in_namespace()
    @commutative function MetaTestModule1.baz(s::String, i::Integer)
      return "$s -> $i"
    end

    @test MetaTestModule1.baz("hello", 42) == "hello -> 42"
    @test MetaTestModule1.baz(42, "hello") == "hello -> 42"
  end

  function commutative_shorthand_method_in_namespace()
    @commutative MetaTestModule1.boo(s::String, i::Integer) = "$s -> $i"

    @test MetaTestModule1.boo("hello", 42) == "hello -> 42"
    @test MetaTestModule1.boo(42, "hello") == "hello -> 42"
  end

  function commutative_method_with_an_any_arg_makes_3_methods()
    @commutative function hmmm(a::Any, s::String)
      return "$s -> $a"
    end

    @test length(methods(hmmm)) == 3
    @test hmmm("hello", "world") == "hello -> world"
    @test hmmm("hello", 42) == "hello -> 42"
    @test hmmm(42, "hello") == "hello -> 42"
  end

end