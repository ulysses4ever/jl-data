"""
@default type Foo
    x::Int64=6
    y::Float64=7
end

yields...

type Foo
    x::Int64
    y::Float64
end

function Foo(;x=6, y=7)
    Foo(x,y)
end
"""
macro default(expr)
    if expr.head != symbol("type")
        error("@default only works on composite types")
    else

        field_name(a::Symbol) = a
        field_name(a::Expr) = a.args[1]

        type_name = expr.args[2]
        block = expr.args[3]
        field_names = Any[]
        defaults = Any[]
        fields = Any[]
        if block.head == :(block)
            for arg in block.args
                if arg.head == :(=)
                    val = arg.args[2]
                    field = var_name(arg.args[1])
                    push!(field_names, field)
                    push!(defaults, :($field = $val))
                    push!(fields, arg.args[1])
                end
            end
            # replace block with just fields names and type annotations
            block.args = fields
        end
        for default in defaults
            default.head = :kw
        end
        kwarg_func = :(function $type_name(;$(defaults...))
                            $type_name($(field_names...))
                       end)
        dump(kwarg_func.args[1].args)
        default_type = :(begin
                            $expr
                            $kwarg_func
                        end)
        return esc(default_type)
    end
end
