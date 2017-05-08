module EmitFunctionTests

using MetaTools
using FactCheck

module MetaTestModule1
  module MetaTestModule2
    module MetaTestModule3
      function hello()
      end
    end
    function hello()
    end
  end
  function hello()
  end
end


for (test_function, description) in [(emit, "emit function tests"),
                                     (x->emit(ParsedFunction(emit(x))), "ParsedFunction->emit->ParsedFunction roundtrip tests")]

  facts(description) do
    context("Empty method with no args") do
      pfunc = ParsedFunction(name=:hello1)
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello1
      @fact func.env.max_args => 0
      @fact func() => nothing
    end

    context("Empty method with one untyped arg") do
      pfunc = ParsedFunction(name=:hello2,
                             args=[ParsedArgument(name=:x)])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello2
      @fact func.env.max_args => 1
      @fact func(10) => nothing
    end

    context("Empty method with two untyped args") do
      pfunc = ParsedFunction(name=:hello3,
                             args=[ParsedArgument(name=:x),
                                   ParsedArgument(name=:y)])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello3
      @fact func.env.max_args => 2
      @fact func(10, 20) => nothing
    end

    context("Empty method with one typed arg") do
      pfunc = ParsedFunction(name=:hello4,
                             args=[ParsedArgument(name=:x, typ=:Integer)])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello4
      @fact func.env.max_args => 1
      @fact func(10) => nothing
    end

    context("Empty method with two typed args") do
      pfunc = ParsedFunction(name=:hello5,
                             args=[ParsedArgument(name=:x, typ=:Integer),
                                   ParsedArgument(name=:y, typ=:Integer)])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello5
      @fact func.env.max_args => 2
      @fact func(10, 20) => nothing
    end

    context("Empty method with one union typed arg") do
      pfunc = ParsedFunction(name=:hello6,
                             args=[ParsedArgument(:(x::Union(FloatingPoint, Integer)))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello6
      @fact func.env.max_args => 1
      @fact func(10) => nothing
    end

    context("Empty method with one untyped default arg") do
      pfunc = ParsedFunction(name=:hello7,
                             args=[ParsedArgument(:(x=100))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello7
      @fact func.env.max_args => 1
      @fact func() => nothing
      @fact func(100) => nothing
    end

    context("Empty method with two untyped default args") do
      pfunc = ParsedFunction(name=:hello8,
                             args=[ParsedArgument(:(x=100)),
                                   ParsedArgument(:(y=100))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello8
      @fact func.env.max_args => 2
      @fact func() => nothing
      @fact func(100) => nothing
      @fact func(100, 200) => nothing
    end

    context("Empty method with one typed default arg") do
      pfunc = ParsedFunction(name=:hello9,
                             args=[ParsedArgument(:(x::Integer=100))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello9
      @fact func.env.max_args => 1
      @fact func() => nothing
      @fact func(100) => nothing
    end

    context("Empty method with two typed default args") do
      pfunc = ParsedFunction(name=:hello10,
                             args=[ParsedArgument(:(x::Integer=100)),
                                   ParsedArgument(:(y::Integer=100))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello10
      @fact func.env.max_args => 2
      @fact func() => nothing
      @fact func(100) => nothing
      @fact func(100, 200) => nothing
    end

    context("Empty method with one untyped vararg") do
      pfunc = ParsedFunction(name=:hello11,
                             args=[ParsedArgument(:(x...))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello11
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(100) => nothing
      @fact func(100, 200) => nothing
      @fact func(100, 200, 300) => nothing
    end

    context("Empty method with one typed vararg") do
      pfunc = ParsedFunction(name=:hello12,
                             args=[ParsedArgument(:(x::Integer...))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello12
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(100) => nothing
      @fact func(100, 200) => nothing
      @fact func(100, 200, 300) => nothing
    end

    context("Empty method with one untyped default vararg") do
      pfunc = ParsedFunction(name=:hello13,
                             args=[ParsedArgument(:(x...=1))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello13
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(100) => nothing
      @fact func(100, 200) => nothing
      @fact func(100, 200, 300) => nothing
    end

    context("Empty method with one typed default vararg") do
      pfunc = ParsedFunction(name=:hello14,
                             args=[ParsedArgument(:(x::Integer...=1))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello14
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(100) => nothing
      @fact func(100, 200) => nothing
      @fact func(100, 200, 300) => nothing
    end

    context("Empty method with one untyped kwarg") do
      pfunc = ParsedFunction(name=:hello15,
                             kwargs=[ParsedArgument(:(x=10))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello15
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(x=100) => nothing
    end

    context("Empty method with two untyped kwargs") do
      pfunc = ParsedFunction(name=:hello16,
                             kwargs=[ParsedArgument(:(x=10)),
                                     ParsedArgument(:(y=20))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello16
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(x=100) => nothing
      @fact func(y=200) => nothing
      @fact func(x=100, y=200) => nothing
    end

    context("Empty method with one typed kwarg") do
      pfunc = ParsedFunction(name=:hello17,
                             kwargs=[ParsedArgument(:(x::Integer=10))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello17
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(x=100) => nothing
    end

    context("Empty method with two typed kwargs") do
      pfunc = ParsedFunction(name=:hello18,
                             kwargs=[ParsedArgument(:(x::Integer=10)),
                                     ParsedArgument(:(y::Integer=20))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello18
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(x=100) => nothing
      @fact func(y=200) => nothing
      @fact func(x=100, y=200) => nothing
    end

    context("Empty method with one union typed kwarg") do
      pfunc = ParsedFunction(name=:hello19,
                             kwargs=[ParsedArgument(:(x::Union(FloatingPoint, Integer)=10))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello19
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(x=100) => nothing
    end

    context("Empty method with one untyped varkwarg") do
      pfunc = ParsedFunction(name=:hello20,
                             kwargs=[ParsedArgument(:(x...))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello20
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(x=100) => nothing
      @fact func(y=200) => nothing
      @fact func(x=100, y=200) => nothing
    end

    context("Empty method with one typed varkwarg") do
      pfunc = ParsedFunction(name=:hello21,
                             kwargs=[ParsedArgument(:(x::Array...))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello21
      @fact func.env.max_args => 0
      @fact func() => nothing
      @fact func(x=100) => nothing
      @fact func(y=200) => nothing
      @fact func(x=100, y=200) => nothing
    end

    context("Empty method with a mix of args and kwargs") do
      pfunc = ParsedFunction(name=:hello22,
                             args=[ParsedArgument(:x),
                                   ParsedArgument(:(y::Integer)),
                                   ParsedArgument(:(z=99))],
                             kwargs=[ParsedArgument(:(a::Integer=100)),
                                     ParsedArgument(:(b=200)),
                                     ParsedArgument(:(c...))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello22
      @fact func.env.max_args => 3
      @fact func(10, 20) => nothing
      @fact func(10, 20, 30) => nothing
      @fact func(10, 20, a=99) => nothing
      @fact func(10, 20, 30, b=99, foobar=100) => nothing
    end

    context("Empty method with namespace 1 deep") do
      pfunc = ParsedFunction(name=:hello,
                             namespace=[:MetaTestModule1])
      func = eval(test_function(pfunc))
      @fact (func === MetaTestModule1.hello) => true
      @fact isgeneric(func) => true
      @fact func.env.name => :hello
      @fact func.env.max_args => 0
      @fact func() => nothing
    end

    context("Empty method with namespace 2 deep") do
      pfunc = ParsedFunction(name=:hello,
                             namespace=[:MetaTestModule1, :MetaTestModule2])
      func = eval(test_function(pfunc))
      @fact (func === MetaTestModule1.MetaTestModule2.hello) => true
      @fact isgeneric(func) => true
      @fact func.env.name => :hello
      @fact func.env.max_args => 0
      @fact func() => nothing
    end

    context("Empty method with namespace 3 deep") do
      pfunc = ParsedFunction(name=:hello,
                             namespace=[:MetaTestModule1, :MetaTestModule2, :MetaTestModule3])
      func = eval(test_function(pfunc))
      @fact (func === MetaTestModule1.MetaTestModule2.MetaTestModule3.hello) => true
      @fact isgeneric(func) => true
      @fact func.env.name => :hello
      @fact func.env.max_args => 0
      @fact func() => nothing
    end

    context("Empty method with no type parameter") do
      pfunc = ParsedFunction(name=:hello23,
                             types=Symbol[])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello23
      @fact func.env.max_args => 0
      @fact func() => nothing
    end

    context("Empty method with one type parameter") do
      pfunc = ParsedFunction(name=:hello24,
                             types=[:T],
                             args=[ParsedArgument(:(x::T))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello24
      @fact func.env.max_args => 1
      @fact func(10) => nothing
    end

    context("Empty method with two type parameters") do
      pfunc = ParsedFunction(name=:hello25,
                             types=[:T1, :T2],
                             args=[ParsedArgument(:(x::T1)),
                                   ParsedArgument(:(y::T2))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello25
      @fact func.env.max_args => 2
      @fact func(10, 20) => nothing
    end

    context("Empty method with namespace 3 deep and one type parameter") do
      pfunc = ParsedFunction(name=:hello,
                             types=[:T],
                             namespace=[:MetaTestModule1, :MetaTestModule2, :MetaTestModule3])
      func = eval(test_function(pfunc))
      @fact (func === MetaTestModule1.MetaTestModule2.MetaTestModule3.hello) => true
      @fact isgeneric(func) => true
      @fact func.env.name => :hello
      @fact func.env.max_args => 0
      @fact func() => nothing
    end
    #############################################################################

    context("Empty anonymous function with no args") do
      pfunc = ParsedFunction()
      func = eval(test_function(pfunc))
      @fact func() => nothing
    end

    context("Empty anonymous function with one untyped arg") do
      pfunc = ParsedFunction(args=[ParsedArgument(:x)])
      func = eval(test_function(pfunc))
      @fact func(10) => nothing
    end

    context("Empty anonymous function with two untyped args") do
      pfunc = ParsedFunction(args=[ParsedArgument(:x),
                                   ParsedArgument(:y)])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func(10, 20) => nothing
    end

    context("Empty anonymous function with one typed arg") do
      pfunc = ParsedFunction(args=[ParsedArgument(:(x::Integer))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func(10) => nothing
    end

    context("Empty anonymous function with two typed args") do
      pfunc = ParsedFunction(args=[ParsedArgument(:(x::Integer)),
                                   ParsedArgument(:(y::Integer))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func(10, 20) => nothing
    end

    context("Empty anonymous function with one union typed arg") do
      pfunc = ParsedFunction(args=[ParsedArgument(:(x::Union(FloatingPoint, Integer)))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func(10) => nothing
    end

    context("Empty anonymous function with one untyped vararg") do
      pfunc = ParsedFunction(args=[ParsedArgument(:(x...))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func() => nothing
      @fact func(100) => nothing
      @fact func(100, 200) => nothing
      @fact func(100, 200, 300) => nothing
    end

    context("Empty anonymous function with one typed vararg") do
      pfunc = ParsedFunction(args=[ParsedArgument(:(x::Integer...))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func() => nothing
      @fact func(100) => nothing
      @fact func(100, 200) => nothing
      @fact func(100, 200, 300) => nothing
    end

    context("Empty anonymous function with a mix of args") do
      pfunc = ParsedFunction(args=[ParsedArgument(:x),
                                   ParsedArgument(:(y::Integer)),
                                   ParsedArgument(:(z...))])
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func(10, 20) => nothing
      @fact func(10, 20, 30) => nothing
      @fact func(10, 20, 30, 40) => nothing
    end


    #############################################################################

    context("Method with a numeric literal body") do
      pfunc = ParsedFunction(name=:hello100,
                             body=Expr(:block, 10))
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello100
      @fact func.env.max_args => 0
      @fact func() => 10
    end

    context("Anonymous function with a numeric literal body") do
      pfunc = ParsedFunction(body=Expr(:block, 10))
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func() => 10
    end
    #----------------------------------------------------------------------------

    context("Method with a symbol body") do
      pfunc = ParsedFunction(name=:hello101,
                             args=[ParsedArgument(:x)],
                             body=Expr(:block, :x))
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello101
      @fact func.env.max_args => 1
      @fact func(10) => 10
      @fact func(100) => 100
    end

    context("Anonymous function with a symbol body") do
      pfunc = ParsedFunction(args=[ParsedArgument(:x)],
                             body=Expr(:block, :x))
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func(10) => 10
      @fact func(100) => 100
    end
    #----------------------------------------------------------------------------

    context("Method with a expression body") do
      pfunc = ParsedFunction(name=:hello102,
                             args=[ParsedArgument(:x)],
                             body=:(x + 10))
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello102
      @fact func.env.max_args => 1
      @fact func(10) => 20
      @fact func(100) => 110
    end

    context("Anonymous function with a expression body") do
      pfunc = ParsedFunction(args=[ParsedArgument(:x)],
                             body=:(x + 10))
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func(10) => 20
      @fact func(100) => 110
    end
    #----------------------------------------------------------------------------

    context("Method with a multiline body") do
      pfunc = ParsedFunction(name=:hello103,
                             args=[ParsedArgument(:x)],
                             body=quote
                               y = x + 10
                               z = x - 10
                               return z//y
                             end)
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => true
      @fact func.env.name => :hello103
      @fact func.env.max_args => 1
      @fact func(100) => 9//11
    end

    context("Anonymous function with a multiline body") do
      pfunc = ParsedFunction(args=[ParsedArgument(:x)],
                             body=quote
                               y = x + 10
                               z = x - 10
                               return z//y
                             end)
      func = eval(test_function(pfunc))
      @fact isgeneric(func) => false
      @fact func(100) => 9//11
    end
  end
end

end