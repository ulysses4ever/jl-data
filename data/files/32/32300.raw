using RunTests
using Base.Test

@testmodule EmitFunctionTests begin

using MetaTools

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

test_functions = [(emit,),
                  (x->emit(ParsedFunction(emit(x))),)]

@parameterize test_functions function test_empty_method_with_no_args(test_function)
  pfunc = ParsedFunction(name=:hello1)
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello1
  @test func.env.max_args == 0
  @test func() == nothing
end

@parameterize test_functions function test_empty_method_with_one_untyped_arg(test_function)
  pfunc = ParsedFunction(name=:hello2,
                         args=[ParsedArgument(name=:x)])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello2
  @test func.env.max_args == 1
  @test func(10) == nothing
end

@parameterize test_functions function test_empty_method_with_two_untyped_args(test_function)
  pfunc = ParsedFunction(name=:hello3,
                         args=[ParsedArgument(name=:x),
                               ParsedArgument(name=:y)])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello3
  @test func.env.max_args == 2
  @test func(10, 20) == nothing
end

@parameterize test_functions function test_empty_method_with_one_typed_arg(test_function)
  pfunc = ParsedFunction(name=:hello4,
                         args=[ParsedArgument(name=:x, typ=:Integer)])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello4
  @test func.env.max_args == 1
  @test func(10) == nothing
end

@parameterize test_functions function test_empty_method_with_two_typed_args(test_function)
  pfunc = ParsedFunction(name=:hello5,
                         args=[ParsedArgument(name=:x, typ=:Integer),
                               ParsedArgument(name=:y, typ=:Integer)])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello5
  @test func.env.max_args == 2
  @test func(10, 20) == nothing
end

@parameterize test_functions function test_empty_method_with_one_union_typed_arg(test_function)
  pfunc = ParsedFunction(name=:hello6,
                         args=[ParsedArgument(:(x::Union(FloatingPoint, Integer)))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello6
  @test func.env.max_args == 1
  @test func(10) == nothing
end

@parameterize test_functions function test_empty_method_with_one_untyped_default_arg(test_function)
  pfunc = ParsedFunction(name=:hello7,
                         args=[ParsedArgument(:(x=100))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello7
  @test func.env.max_args == 1
  @test func() == nothing
  @test func(100) == nothing
end

@parameterize test_functions function test_empty_method_with_two_untyped_default_args(test_function)
  pfunc = ParsedFunction(name=:hello8,
                         args=[ParsedArgument(:(x=100)),
                               ParsedArgument(:(y=100))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello8
  @test func.env.max_args == 2
  @test func() == nothing
  @test func(100) == nothing
  @test func(100, 200) == nothing
end

@parameterize test_functions function test_empty_method_with_one_typed_default_arg(test_function)
  pfunc = ParsedFunction(name=:hello9,
                         args=[ParsedArgument(:(x::Integer=100))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello9
  @test func.env.max_args == 1
  @test func() == nothing
  @test func(100) == nothing
end

@parameterize test_functions function test_empty_method_with_two_typed_default_args(test_function)
  pfunc = ParsedFunction(name=:hello10,
                         args=[ParsedArgument(:(x::Integer=100)),
                               ParsedArgument(:(y::Integer=100))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello10
  @test func.env.max_args == 2
  @test func() == nothing
  @test func(100) == nothing
  @test func(100, 200) == nothing
end

@parameterize test_functions function test_empty_method_with_one_untyped_vararg(test_function)
  pfunc = ParsedFunction(name=:hello11,
                         args=[ParsedArgument(:(x...))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello11
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(100) == nothing
  @test func(100, 200) == nothing
  @test func(100, 200, 300) == nothing
end

@parameterize test_functions function test_empty_method_with_one_typed_vararg(test_function)
  pfunc = ParsedFunction(name=:hello12,
                         args=[ParsedArgument(:(x::Integer...))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello12
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(100) == nothing
  @test func(100, 200) == nothing
  @test func(100, 200, 300) == nothing
end

@parameterize test_functions function test_empty_method_with_one_untyped_default_vararg(test_function)
  pfunc = ParsedFunction(name=:hello13,
                         args=[ParsedArgument(:(x...=1))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello13
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(100) == nothing
  @test func(100, 200) == nothing
  @test func(100, 200, 300) == nothing
end

@parameterize test_functions function test_empty_method_with_one_typed_default_vararg(test_function)
  pfunc = ParsedFunction(name=:hello14,
                         args=[ParsedArgument(:(x::Integer...=1))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello14
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(100) == nothing
  @test func(100, 200) == nothing
  @test func(100, 200, 300) == nothing
end

@parameterize test_functions function test_empty_method_with_one_untyped_kwarg(test_function)
  pfunc = ParsedFunction(name=:hello15,
                        kwargs=[ParsedArgument(:(x=10))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello15
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(x=100) == nothing
end

@parameterize test_functions function test_empty_method_with_two_untyped_kwargs(test_function)
  pfunc = ParsedFunction(name=:hello16,
                        kwargs=[ParsedArgument(:(x=10)),
                                 ParsedArgument(:(y=20))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello16
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(x=100) == nothing
  @test func(y=200) == nothing
  @test func(x=100, y=200) == nothing
end

@parameterize test_functions function test_empty_method_with_one_typed_kwarg(test_function)
  pfunc = ParsedFunction(name=:hello17,
                        kwargs=[ParsedArgument(:(x::Integer=10))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello17
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(x=100) == nothing
end

@parameterize test_functions function test_empty_method_with_two_typed_kwargs(test_function)
  pfunc = ParsedFunction(name=:hello18,
                        kwargs=[ParsedArgument(:(x::Integer=10)),
                                 ParsedArgument(:(y::Integer=20))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello18
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(x=100) == nothing
  @test func(y=200) == nothing
  @test func(x=100, y=200) == nothing
end

@parameterize test_functions function test_empty_method_with_one_union_typed_kwarg(test_function)
  pfunc = ParsedFunction(name=:hello19,
                        kwargs=[ParsedArgument(:(x::Union(FloatingPoint, Integer)=10))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello19
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(x=100) == nothing
end

@parameterize test_functions function test_empty_method_with_one_untyped_varkwarg(test_function)
  pfunc = ParsedFunction(name=:hello20,
                        kwargs=[ParsedArgument(:(x...))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello20
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(x=100) == nothing
  @test func(y=200) == nothing
  @test func(x=100, y=200) == nothing
end

@parameterize test_functions function test_empty_method_with_one_typed_varkwarg(test_function)
  pfunc = ParsedFunction(name=:hello21,
                        kwargs=[ParsedArgument(:(x::Array...))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello21
  @test func.env.max_args == 0
  @test func() == nothing
  @test func(x=100) == nothing
  @test func(y=200) == nothing
  @test func(x=100, y=200) == nothing
end

@parameterize test_functions function test_empty_method_with_a_mix_of_args_and_kwargs(test_function)
  pfunc = ParsedFunction(name=:hello22,
                         args=[ParsedArgument(:x),
                               ParsedArgument(:(y::Integer)),
                               ParsedArgument(:(z=99))],
                        kwargs=[ParsedArgument(:(a::Integer=100)),
                                 ParsedArgument(:(b=200)),
                                 ParsedArgument(:(c...))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello22
  @test func.env.max_args == 3
  @test func(10, 20) == nothing
  @test func(10, 20, 30) == nothing
  @test func(10, 20, a=99) == nothing
  @test func(10, 20, 30, b=99, foobar=100) == nothing
end

@parameterize test_functions function test_empty_method_with_namespace_1_deep(test_function)
  pfunc = ParsedFunction(name=:hello,
                         namespace=[:MetaTestModule1])
  func = eval(test_function(pfunc))
  @test (func === MetaTestModule1.hello) == true
  @test isgeneric(func) == true
  @test func.env.name == :hello
  @test func.env.max_args == 0
  @test func() == nothing
end

@parameterize test_functions function test_empty_method_with_namespace_2_deep(test_function)
  pfunc = ParsedFunction(name=:hello,
                         namespace=[:MetaTestModule1, :MetaTestModule2])
  func = eval(test_function(pfunc))
  @test (func === MetaTestModule1.MetaTestModule2.hello) == true
  @test isgeneric(func) == true
  @test func.env.name == :hello
  @test func.env.max_args == 0
  @test func() == nothing
end

@parameterize test_functions function test_empty_method_with_namespace_3_deep(test_function)
  pfunc = ParsedFunction(name=:hello,
                         namespace=[:MetaTestModule1, :MetaTestModule2, :MetaTestModule3])
  func = eval(test_function(pfunc))
  @test (func === MetaTestModule1.MetaTestModule2.MetaTestModule3.hello) == true
  @test isgeneric(func) == true
  @test func.env.name == :hello
  @test func.env.max_args == 0
  @test func() == nothing
end

@parameterize test_functions function test_empty_method_with_no_type_parameter(test_function)
  pfunc = ParsedFunction(name=:hello23,
                         types=Symbol[])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello23
  @test func.env.max_args == 0
  @test func() == nothing
end

@parameterize test_functions function test_empty_method_with_one_type_parameter(test_function)
  pfunc = ParsedFunction(name=:hello24,
                         types=[:T],
                         args=[ParsedArgument(:(x::T))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello24
  @test func.env.max_args == 1
  @test func(10) == nothing
end

@parameterize test_functions function test_empty_method_with_two_type_parameters(test_function)
  pfunc = ParsedFunction(name=:hello25,
                         types=[:T1, :T2],
                         args=[ParsedArgument(:(x::T1)),
                               ParsedArgument(:(y::T2))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello25
  @test func.env.max_args == 2
  @test func(10, 20) == nothing
end

@parameterize test_functions function test_empty_method_with_namespace_3_deep_and_one_type_parameter(test_function)
  pfunc = ParsedFunction(name=:hello,
                         types=[:T],
                         namespace=[:MetaTestModule1, :MetaTestModule2, :MetaTestModule3])
  func = eval(test_function(pfunc))
  @test (func === MetaTestModule1.MetaTestModule2.MetaTestModule3.hello) == true
  @test isgeneric(func) == true
  @test func.env.name == :hello
  @test func.env.max_args == 0
  @test func() == nothing
end
#############################################################################

@parameterize test_functions function test_empty_anonymous_function_with_no_args(test_function)
  pfunc = ParsedFunction()
  func = eval(test_function(pfunc))
  @test func() == nothing
end

@parameterize test_functions function test_empty_anonymous_function_with_one_untyped_arg(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:x)])
  func = eval(test_function(pfunc))
  @test func(10) == nothing
end

@parameterize test_functions function test_empty_anonymous_function_with_two_untyped_args(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:x),
                               ParsedArgument(:y)])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func(10, 20) == nothing
end

@parameterize test_functions function test_empty_anonymous_function_with_one_typed_arg(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:(x::Integer))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func(10) == nothing
end

@parameterize test_functions function test_empty_anonymous_function_with_two_typed_args(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:(x::Integer)),
                               ParsedArgument(:(y::Integer))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func(10, 20) == nothing
end

@parameterize test_functions function test_empty_anonymous_function_with_one_union_typed_arg(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:(x::Union(FloatingPoint, Integer)))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func(10) == nothing
end

@parameterize test_functions function test_empty_anonymous_function_with_one_untyped_vararg(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:(x...))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func() == nothing
  @test func(100) == nothing
  @test func(100, 200) == nothing
  @test func(100, 200, 300) == nothing
end

@parameterize test_functions function test_empty_anonymous_function_with_one_typed_vararg(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:(x::Integer...))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func() == nothing
  @test func(100) == nothing
  @test func(100, 200) == nothing
  @test func(100, 200, 300) == nothing
end

@parameterize test_functions function test_empty_anonymous_function_with_a_mix_of_args(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:x),
                               ParsedArgument(:(y::Integer)),
                               ParsedArgument(:(z...))])
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func(10, 20) == nothing
  @test func(10, 20, 30) == nothing
  @test func(10, 20, 30, 40) == nothing
end


#############################################################################

@parameterize test_functions function test_method_with_a_numeric_literal_body(test_function)
  pfunc = ParsedFunction(name=:hello100,
                         body=Expr(:block, 10))
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello100
  @test func.env.max_args == 0
  @test func() == 10
end

@parameterize test_functions function test_anonymous_function_with_a_numeric_literal_body(test_function)
  pfunc = ParsedFunction(body=Expr(:block, 10))
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func() == 10
end
#----------------------------------------------------------------------------

@parameterize test_functions function test_method_with_a_symbol_body(test_function)
  pfunc = ParsedFunction(name=:hello101,
                         args=[ParsedArgument(:x)],
                         body=Expr(:block, :x))
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello101
  @test func.env.max_args == 1
  @test func(10) == 10
  @test func(100) == 100
end

@parameterize test_functions function test_anonymous_function_with_a_symbol_body(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:x)],
                         body=Expr(:block, :x))
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func(10) == 10
  @test func(100) == 100
end
#----------------------------------------------------------------------------

@parameterize test_functions function test_method_with_a_expression_body(test_function)
  pfunc = ParsedFunction(name=:hello102,
                         args=[ParsedArgument(:x)],
                         body=:(x + 10))
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello102
  @test func.env.max_args == 1
  @test func(10) == 20
  @test func(100) == 110
end

@parameterize test_functions function test_anonymous_function_with_a_expression_body(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:x)],
                         body=:(x + 10))
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func(10) == 20
  @test func(100) == 110
end
#----------------------------------------------------------------------------

@parameterize test_functions function test_method_with_a_multiline_body(test_function)
  pfunc = ParsedFunction(name=:hello103,
                         args=[ParsedArgument(:x)],
                         body=quote
                           y = x + 10
                           z = x - 10
                           return z//y
                         end)
  func = eval(test_function(pfunc))
  @test isgeneric(func) == true
  @test func.env.name == :hello103
  @test func.env.max_args == 1
  @test func(100) == 9//11
end

@parameterize test_functions function test_anonymous_function_with_a_multiline_body(test_function)
  pfunc = ParsedFunction(args=[ParsedArgument(:x)],
                         body=quote
                           y = x + 10
                           z = x - 10
                           return z//y
                         end)
  func = eval(test_function(pfunc))
  @test isgeneric(func) == false
  @test func(100) == 9//11
end

end