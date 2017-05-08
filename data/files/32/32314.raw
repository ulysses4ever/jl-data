using RunTests
using Base.Test
import MetaTools.@commutative

@testmodule ParsedFunctionTests begin

using MetaTools

type AnyLineNumber end

const ANY_LINE_NUMBER = AnyLineNumber()

Base.isequal(x::AnyLineNumber, y::AnyLineNumber) = error("Can not compare ANY_LINE_NUMBER with itself")
@commutative Base.isequal(x::AnyLineNumber, y::WeakRef) = false
@commutative Base.isequal(x::AnyLineNumber, y::LineNumberNode) = true
@commutative Base.isequal(x::AnyLineNumber, y::Expr) = (y.head == :line)
@commutative Base.isequal(x::AnyLineNumber, y::Any) = false

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

test_functions = [(ParsedFunction,), (x->ParsedFunction(emit(ParsedFunction(x))),) ]

@parameterize test_functions function test_empty_method_with_no_args(test_function)
  func = test_function(:(function hello() end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_method_with_no_args_and_bracketed_name(test_function)
  func = test_function(:(function (hello)() end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_method_with_one_untyped_arg(test_function)
  func = test_function(:(function hello(x) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_method_with_two_untyped_args(test_function)
  func = test_function(:(function hello(x,y) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :Any
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
end

@parameterize test_functions function test_empty_method_with_one_typed_arg(test_function)
  func = test_function(:(function hello(x::Integer) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_method_with_two_typed_args(test_function)
  func = test_function(:(function hello(x::Integer, y::FloatingPoint) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :FloatingPoint
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
end

@parameterize test_functions function test_empty_method_with_one_union_typed_arg(test_function)
  func = test_function(:(function hello(x::Union(Integer,FloatingPoint)) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :(Union(Integer, FloatingPoint))
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_method_with_one_untyped_default_arg(test_function)
  func = test_function(:(function hello(x=100) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test func.args[1].default == 100
end

@parameterize test_functions function test_empty_method_with_two_untyped_default_args(test_function)
  func = test_function(:(function hello(x=100,y=200) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test func.args[1].default == 100
  @test func.args[2].name == :y
  @test func.args[2].typ == :Any
  @test func.args[2].varargs == false
  @test func.args[2].default == 200
end

@parameterize test_functions function test_empty_method_with_one_typed_default_arg(test_function)
  func = test_function(:(function hello(x::Integer=100) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test func.args[1].default == 100
end

@parameterize test_functions function test_empty_method_with_two_typed_default_args(test_function)
  func = test_function(:(function hello(x::Integer=100, y::FloatingPoint=200.0) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test func.args[1].default == 100
  @test func.args[2].name == :y
  @test func.args[2].typ == :FloatingPoint
  @test func.args[2].varargs == false
  @test func.args[2].default == 200.0
end

@parameterize test_functions function test_empty_method_with_one_untyped_vararg(test_function)
  func = test_function(:(function hello(x...) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == true
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_method_with_one_typed_vararg(test_function)
  func = test_function(:(function hello(x::Integer...) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == true
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_method_with_one_untyped_default_vararg(test_function)
  func = test_function(:(function hello(x...=100) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == true
  @test func.args[1].default == 100
end

@parameterize test_functions function test_empty_method_with_one_typed_default_vararg(test_function)
  func = test_function(:(function hello(x::Integer...=100) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == true
  @test func.args[1].default == 100
end

@parameterize test_functions function test_empty_method_with_one_untyped_kwarg(test_function)
  func = test_function(:(function hello(;x=100) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Any
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
end

@parameterize test_functions function test_empty_method_with_two_untyped_kwargs(test_function)
  func = test_function(:(function hello(;x=100,y=200) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 2
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Any
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
  @test func.kwargs[2].name == :y
  @test func.kwargs[2].typ == :Any
  @test func.kwargs[2].varargs == false
  @test func.kwargs[2].default == 200
end

@parameterize test_functions function test_empty_method_with_one_typed_kwarg(test_function)
  func = test_function(:(function hello(;x::Integer=100) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Integer
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
end

@parameterize test_functions function test_empty_method_with_two_typed_kwargs(test_function)
  func = test_function(:(function hello(;x::Integer=100, y::FloatingPoint=200.0) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 2
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Integer
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
  @test func.kwargs[2].name == :y
  @test func.kwargs[2].typ == :FloatingPoint
  @test func.kwargs[2].varargs == false
  @test func.kwargs[2].default == 200.0
end

@parameterize test_functions function test_empty_method_with_one_union_typed_kwarg(test_function)
  func = test_function(:(function hello(;x::Union(Integer, FloatingPoint)=100) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :(Union(Integer, FloatingPoint))
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
end

@parameterize test_functions function test_empty_method_with_one_untyped_varkwarg(test_function)
  func = test_function(:(function hello(;x...) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Any
  @test func.kwargs[1].varargs == true
  @test isdefined(func.kwargs[1], :default) == false
end

@parameterize test_functions function test_empty_method_with_one_typed_varkwarg(test_function)
  func = test_function(:(function hello(;x::Array...) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Array
  @test func.kwargs[1].varargs == true
  @test isdefined(func.kwargs[1], :default) == false
end

@parameterize test_functions function test_empty_method_with_a_mix_of_args_and_kwargs(test_function)
  func = test_function(:(function hello(x,y::Integer,z=99,rest...;a::Integer=100,b=200,c...) end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.body == quote end

  @test length(func.args) == 4
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :Integer
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
  @test func.args[3].name == :z
  @test func.args[3].typ == :Any
  @test func.args[3].varargs == false
  @test func.args[3].default == 99
  @test func.args[4].name == :rest
  @test func.args[4].typ == :Any
  @test func.args[4].varargs == true
  @test isdefined(func.args[4], :default) == false

  @test length(func.kwargs) == 3
  @test func.kwargs[1].name == :a
  @test func.kwargs[1].typ == :Integer
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
  @test func.kwargs[2].name == :b
  @test func.kwargs[2].typ == :Any
  @test func.kwargs[2].varargs == false
  @test func.kwargs[2].default == 200
  @test func.kwargs[3].name == :c
  @test func.kwargs[3].typ == :Any
  @test func.kwargs[3].varargs == true
  @test isdefined(func.kwargs[3], :default) == false
end

@parameterize test_functions function test_empty_method_with_namespace_1_deep(test_function)
  func = test_function(:(function MetaTestModule1.hello() end))
  @test func.name == :hello
  @test func.namespace == [:MetaTestModule1]
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_method_with_namespace_2_deep(test_function)
  func = test_function(:(function MetaTestModule1.MetaTestModule2.hello() end))
  @test func.name == :hello
  @test func.namespace == [:MetaTestModule1, :MetaTestModule2]
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_method_with_namespace_3_deep(test_function)
  func = test_function(:(function MetaTestModule1.MetaTestModule2.MetaTestModule3.hello() end))
  @test func.name == :hello
  @test func.namespace == [:MetaTestModule1, :MetaTestModule2, :MetaTestModule3]
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_method_with_no_type_parameter(test_function)
  func = test_function(:(function hello() end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_method_with_one_type_parameter(test_function)
  func = test_function(:(function hello{T}() end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test func.types == [:T]
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_method_with_two_type_parameters(test_function)
  func = test_function(:(function hello{T1, T2}() end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test func.types == [:T1, :T2]
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_method_with_namespace_3_deep_and_a_type_parameter(test_function)
  func = test_function(:(function MetaTestModule1.MetaTestModule2.MetaTestModule3.hello{T}() end))
  @test func.name == :hello
  @test func.namespace == [:MetaTestModule1, :MetaTestModule2, :MetaTestModule3]
  @test func.types == [:T]
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

#############################################################################

@parameterize test_functions function test_empty_shorthand_method_with_no_args(test_function)
  func = test_function(:(hello() = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_shorthand_method_with_no_args_and_bracketed_name(test_function)
  func = test_function(:((hello)() = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_shorthand_method_with_one_untyped_arg(test_function)
  func = test_function(:(hello(x) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_two_untyped_args(test_function)
  func = test_function(:(hello(x,y) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :Any
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_one_typed_arg(test_function)
  func = test_function(:(hello(x::Integer) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_two_typed_args(test_function)
  func = test_function(:(hello(x::Integer, y::FloatingPoint) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :FloatingPoint
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_one_union_typed_arg(test_function)
  func = test_function(:(hello(x::Union(Integer,FloatingPoint)) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :(Union(Integer, FloatingPoint))
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_one_untyped_default_arg(test_function)
  func = test_function(:(hello(x=100) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test func.args[1].default == 100
end

@parameterize test_functions function test_empty_shorthand_method_with_two_untyped_default_args(test_function)
  func = test_function(:(hello(x=100,y=200) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test func.args[1].default == 100
  @test func.args[2].name == :y
  @test func.args[2].typ == :Any
  @test func.args[2].varargs == false
  @test func.args[2].default == 200
end

@parameterize test_functions function test_empty_shorthand_method_with_one_typed_default_arg(test_function)
  func = test_function(:(hello(x::Integer=100) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test func.args[1].default == 100
end

@parameterize test_functions function test_empty_shorthand_method_with_two_typed_default_args(test_function)
  func = test_function(:(hello(x::Integer=100, y::FloatingPoint=200.0) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test func.args[1].default == 100
  @test func.args[2].name == :y
  @test func.args[2].typ == :FloatingPoint
  @test func.args[2].varargs == false
  @test func.args[2].default == 200.0
end

@parameterize test_functions function test_empty_shorthand_method_with_one_untyped_vararg(test_function)
  func = test_function(:(hello(x...) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == true
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_one_typed_vararg(test_function)
  func = test_function(:(hello(x::Integer...) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == true
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_one_untyped_default_vararg(test_function)
  func = test_function(:(hello(x...=100) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == true
  @test func.args[1].default == 100
end

@parameterize test_functions function test_empty_shorthand_method_with_one_typed_default_vararg(test_function)
  func = test_function(:(hello(x::Integer...=100) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == true
  @test func.args[1].default == 100
end

@parameterize test_functions function test_empty_shorthand_method_with_one_untyped_kwarg(test_function)
  func = test_function(:(hello(;x=100) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Any
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
end

@parameterize test_functions function test_empty_shorthand_method_with_two_untyped_kwargs(test_function)
  func = test_function(:(hello(;x=100,y=200) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 2
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Any
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
  @test func.kwargs[2].name == :y
  @test func.kwargs[2].typ == :Any
  @test func.kwargs[2].varargs == false
  @test func.kwargs[2].default == 200
end

@parameterize test_functions function test_empty_shorthand_method_with_one_typed_kwarg(test_function)
  func = test_function(:(hello(;x::Integer=100) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Integer
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
end

@parameterize test_functions function test_empty_shorthand_method_with_two_typed_kwargs(test_function)
  func = test_function(:(hello(;x::Integer=100, y::FloatingPoint=200.0) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 2
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Integer
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
  @test func.kwargs[2].name == :y
  @test func.kwargs[2].typ == :FloatingPoint
  @test func.kwargs[2].varargs == false
  @test func.kwargs[2].default == 200.0
end

@parameterize test_functions function test_empty_shorthand_method_with_one_union_typed_kwarg(test_function)
  func = test_function(:(hello(;x::Union(Integer, FloatingPoint)=100) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :(Union(Integer, FloatingPoint))
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
end

@parameterize test_functions function test_empty_shorthand_method_with_one_untyped_varkwarg(test_function)
  func = test_function(:(hello(;x...) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Any
  @test func.kwargs[1].varargs == true
  @test isdefined(func.kwargs[1], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_one_typed_varkwarg(test_function)
  func = test_function(:(hello(;x::Integer...) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.args == []
  @test func.body == quote end

  @test length(func.kwargs) == 1
  @test func.kwargs[1].name == :x
  @test func.kwargs[1].typ == :Integer
  @test func.kwargs[1].varargs == true
  @test isdefined(func.kwargs[1], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_a_mix_of_args_and_kwargs(test_function)
  func = test_function(:(hello(x,y::Integer,z=99,rest...;a::Integer=100,b=200,c...) = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test func.body == quote end

  @test length(func.args) == 4
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :Integer
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
  @test func.args[3].name == :z
  @test func.args[3].typ == :Any
  @test func.args[3].varargs == false
  @test func.args[3].default == 99
  @test func.args[4].name == :rest
  @test func.args[4].typ == :Any
  @test func.args[4].varargs == true
  @test isdefined(func.args[4], :default) == false

  @test length(func.kwargs) == 3
  @test func.kwargs[1].name == :a
  @test func.kwargs[1].typ == :Integer
  @test func.kwargs[1].varargs == false
  @test func.kwargs[1].default == 100
  @test func.kwargs[2].name == :b
  @test func.kwargs[2].typ == :Any
  @test func.kwargs[2].varargs == false
  @test func.kwargs[2].default == 200
  @test func.kwargs[3].name == :c
  @test func.kwargs[3].typ == :Any
  @test func.kwargs[3].varargs == true
  @test isdefined(func.kwargs[3], :default) == false
end

@parameterize test_functions function test_empty_shorthand_method_with_namespace_1_deep(test_function)
  func = test_function(:(MetaTestModule1.hello() = begin end))
  @test func.name == :hello
  @test func.namespace == [:MetaTestModule1]
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_shorthand_method_with_namespace_2_deep(test_function)
  func = test_function(:(MetaTestModule1.MetaTestModule2.hello() = begin end))
  @test func.name == :hello
  @test func.namespace == [:MetaTestModule1, :MetaTestModule2]
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_shorthand_method_with_namespace_3_deep(test_function)
  func = test_function(:(MetaTestModule1.MetaTestModule2.MetaTestModule3.hello() = begin end))
  @test func.name == :hello
  @test func.namespace == [:MetaTestModule1, :MetaTestModule2, :MetaTestModule3]
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_shorthand_method_with_no_type_parameter(test_function)
  func = test_function(:(hello() = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_shorthand_method_with_one_type_parameter(test_function)
  func = test_function(:(hello{T}() = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test func.types == [:T]
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_shorthand_method_with_two_type_parameters(test_function)
  func = test_function(:(hello{T1, T2}() = begin end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test func.types == [:T1, :T2]
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_shorthand_method_with_namespace_3_deep_and_a_type_parameter(test_function)
  func = test_function(:(MetaTestModule1.MetaTestModule2.MetaTestModule3.hello{T}() = begin end))
  @test func.name == :hello
  @test func.namespace == [:MetaTestModule1, :MetaTestModule2, :MetaTestModule3]
  @test func.types == [:T]
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

#############################################################################

@parameterize test_functions function test_empty_lambda_with_no_args(test_function)
  func = test_function(:(() -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_lambda_with_one_untyped_arg(test_function)
  func = test_function(:((x) -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_lambda_with_two_untyped_args(test_function)
  func = test_function(:((x,y) -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :Any
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
end

@parameterize test_functions function test_empty_lambda_with_one_typed_arg(test_function)
  func = test_function(:((x::Integer) -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_lambda_with_two_typed_args(test_function)
  func = test_function(:((x::Integer, y::FloatingPoint) -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :FloatingPoint
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
end

@parameterize test_functions function test_empty_lambda_with_one_union_typed_arg(test_function)
  func = test_function(:((x::Union(Integer,FloatingPoint)) -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :(Union(Integer, FloatingPoint))
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_lambda_with_one_untyped_vararg(test_function)
  func = test_function(:((x...) -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == true
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_lambda_with_one_typed_vararg(test_function)
  func = test_function(:((x::Integer...) -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == true
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_lambda_with_a_mix_of_args(test_function)
  func = test_function(:((x,y::Integer,z...) -> begin end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test func.body == quote end

  @test length(func.args) == 3
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :Integer
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
  @test func.args[3].name == :z
  @test func.args[3].typ == :Any
  @test func.args[3].varargs == true
  @test isdefined(func.args[3], :default) == false

  @test isdefined(func, :kwargs) == false
end

#############################################################################

@parameterize test_functions function test_empty_anonymous_function_with_no_args(test_function)
  func = test_function(:(function() end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end
  @test func.args == []
end

@parameterize test_functions function test_empty_anonymous_function_with_one_untyped_arg(test_function)
  func = test_function(:(function(x) end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_anonymous_function_with_two_untyped_args(test_function)
  func = test_function(:(function(x,y) end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :Any
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
end

@parameterize test_functions function test_empty_anonymous_function_with_one_typed_arg(test_function)
  func = test_function(:(function(x::Integer) end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_anonymous_function_with_two_typed_args(test_function)
  func = test_function(:(function(x::Integer, y::FloatingPoint) end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 2
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :FloatingPoint
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
end

@parameterize test_functions function test_empty_anonymous_function_with_one_union_typed_arg(test_function)
  func = test_function(:(function(x::Union(Integer,FloatingPoint)) end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :(Union(Integer, FloatingPoint))
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_anonymous_function_with_one_untyped_vararg(test_function)
  func = test_function(:(function(x...) end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == true
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_anonymous_function_with_one_typed_vararg(test_function)
  func = test_function(:(function(x::Integer...) end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == quote end

  @test length(func.args) == 1
  @test func.args[1].name == :x
  @test func.args[1].typ == :Integer
  @test func.args[1].varargs == true
  @test isdefined(func.args[1], :default) == false
end

@parameterize test_functions function test_empty_anonymous_function_with_a_mix_of_args(test_function)
  func = test_function(:(function(x,y::Integer,z...) end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test func.body == quote end

  @test length(func.args) == 3
  @test func.args[1].name == :x
  @test func.args[1].typ == :Any
  @test func.args[1].varargs == false
  @test isdefined(func.args[1], :default) == false
  @test func.args[2].name == :y
  @test func.args[2].typ == :Integer
  @test func.args[2].varargs == false
  @test isdefined(func.args[2], :default) == false
  @test func.args[3].name == :z
  @test func.args[3].typ == :Any
  @test func.args[3].varargs == true
  @test isdefined(func.args[3], :default) == false

  @test isdefined(func, :kwargs) == false
end

#############################################################################

@parameterize test_functions function test_method_with_a_numeric_literal_body(test_function)
  func = test_function(:(function hello() 10 end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, 10)
  @test func.args == []
end

@parameterize test_functions function test_shorthand_method_with_a_numeric_literal_body(test_function)
  func = test_function(:(hello() = 10))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, 10)
  @test func.args == []
end

@parameterize test_functions function test_lambda_with_a_numeric_literal_body(test_function)
  func = test_function(:(() -> 10))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, 10)
  @test func.args == []
end

@parameterize test_functions function test_anonymous_function_with_a_numeric_literal_body(test_function)
  func = test_function(:(function() 10 end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, 10)
  @test func.args == []
end

#----------------------------------------------------------------------------

@parameterize test_functions function test_method_with_a_symbol_body(test_function)
  func = test_function(:(function hello() x end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, :x)
  @test func.args == []
end

@parameterize test_functions function test_shorthand_method_with_a_symbol_body(test_function)
  func = test_function(:(hello() = x))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, :x)
  @test func.args == []
end

@parameterize test_functions function test_lambda_with_a_symbol_body(test_function)
  func = test_function(:(() -> x))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, :x)
  @test func.args == []
end

@parameterize test_functions function test_anonymous_function_with_a_symbol_body(test_function)
  func = test_function(:(function() x end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, :x)
  @test func.args == []
end

#----------------------------------------------------------------------------

@parameterize test_functions function test_method_with_a_expression_body(test_function)
  func = test_function(:(function hello() x + 10 end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, Expr(:call, :+, :x, 10))
  @test func.args == []
end

@parameterize test_functions function test_shorthand_method_with_a_expression_body(test_function)
  func = test_function(:(hello() = x + 10))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:call, :+, :x, 10)
  @test func.args == []
end

@parameterize test_functions function test_lambda_with_a_expression_body(test_function)
  func = test_function(:(() -> x + 10))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, Expr(:call, :+, :x, 10))
  @test func.args == []
end

@parameterize test_functions function test_anonymous_function_with_a_expression_body(test_function)
  func = test_function(:(function() x + 10 end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block, ANY_LINE_NUMBER, Expr(:call, :+, :x, 10))
  @test func.args == []
end

#----------------------------------------------------------------------------

@parameterize test_functions function test_method_with_a_multiline_body(test_function)
  func = test_function(:(function hello()
                            y = x + 10
                            y += some_func(z)
                            return y
                          end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block,
                          ANY_LINE_NUMBER,
                          Expr(:(=), :y, Expr(:call, :+, :x, 10)),
                          ANY_LINE_NUMBER,
                          Expr(:(+=), :y, Expr(:call, :some_func, :z)),
                          ANY_LINE_NUMBER,
                          Expr(:return, :y),
                          )
  @test func.args == []
end

@parameterize test_functions function test_shorthand_method_with_a_multiline_body_with_begin_end(test_function)
  func = test_function(:(hello() = begin
                            y = x + 10
                            y += some_func(z)
                            return y
                          end))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block,
                          ANY_LINE_NUMBER,
                          Expr(:(=), :y, Expr(:call, :+, :x, 10)),
                          ANY_LINE_NUMBER,
                          Expr(:(+=), :y, Expr(:call, :some_func, :z)),
                          ANY_LINE_NUMBER,
                          Expr(:return, :y),
                          )
  @test func.args == []
end

@parameterize test_functions function test_shorthand_method_with_a_multiline_body_with_brackets(test_function)
  func = test_function(:(hello() = (y = x + 10;
                                     y += some_func(z);
                                     return y)))
  @test func.name == :hello
  @test isdefined(func, :namespace) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block,
                          Expr(:(=), :y, Expr(:call, :+, :x, 10)),
                          Expr(:(+=), :y, Expr(:call, :some_func, :z)),
                          Expr(:return, :y),
                          )
  @test func.args == []
end

@parameterize test_functions function test_Lambda_with_a_multiline_body_with_begin_end(test_function)
  func = test_function(:(() -> begin
                            y = x + 10
                            y += some_func(z)
                            return y
                          end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block,
                          ANY_LINE_NUMBER,
                          Expr(:(=), :y, Expr(:call, :+, :x, 10)),
                          ANY_LINE_NUMBER,
                          Expr(:(+=), :y, Expr(:call, :some_func, :z)),
                          ANY_LINE_NUMBER,
                          Expr(:return, :y),
                          )
  @test func.args == []
end

@parameterize test_functions function test_Lambda_with_a_multiline_body_with_brackets(test_function)
  func = test_function(:(() -> (y = x + 10;
                                 y += some_func(z);
                                 return y)))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block,
                          Expr(:(=), :y, Expr(:call, :+, :x, 10)),
                          Expr(:(+=), :y, Expr(:call, :some_func, :z)),
                          Expr(:return, :y),
                          )
  @test func.args == []
end

@parameterize test_functions function test_anonymous_function_with_a_multiline_body(test_function)
  func = test_function(:(function()
                            y = x + 10
                            y += some_func(z)
                            return y
                          end))
  @test isdefined(func, :name) == false
  @test isdefined(func, :types) == false
  @test isdefined(func, :kwargs) == false
  @test func.body == Expr(:block,
                          ANY_LINE_NUMBER,
                          Expr(:(=), :y, Expr(:call, :+, :x, 10)),
                          ANY_LINE_NUMBER,
                          Expr(:(+=), :y, Expr(:call, :some_func, :z)),
                          ANY_LINE_NUMBER,
                          Expr(:return, :y),
                          )
  @test func.args == []
end

end