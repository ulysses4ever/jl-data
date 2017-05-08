immutable NullableTable{C<:Tuple, F<:Tuple} <: AbstractArray{Any, 2}
    columns::C
    fields::Type{F}
    nrows::Int
end

function NullableTable(curs::Cursor)
    columns, tup_colsymbs, nrows = materialize!(curs, NullableTable)
    return NullableTable(columns, tup_colsymbs, nrows)
end

@generated function _materialize{Co<:Tuple, Fi<:Tuple}(
    curs::Cursor{SQLite3.Stmt, Co, Fi},
    ::Type{NullableTable}
) #, coltypes::Type{T})
    N = length(T.parameters)
    types = [ T.parameters[i] for i in 1:N ]

    pre = Expr(:block)
    while_body = Expr(:block)
    post = Expr(:tuple)
    for i in 1:N
        A_symb = symbol("A_$i")
        typ = types[i]
        push!(pre.args, :( $A_symb = NullableVector{$typ}() ))
        if typ <: AbstractString
            push!(while_body.args,
                  quote
                      if sqlite3_column_type(stmt.handle, $(i-1)) == 5
                          push!($A_symb, Nullable())
                      else
                          push!($A_symb, bytestring($(sqlite_get_fns[types[i]])(stmt.handle, $(i-1))))
                      end
                  end
            )
        else
            push!(while_body.args,
                  quote
                      if sqlite3_column_type(stmt.handle, $(i-1)) == 5
                          push!($A_symb, Nullable())
                      else
                          push!($A_symb, $(sqlite_get_fns[types[i]])(stmt.handle, $(i-1)))
                      end
                  end
            )
        end
        push!(post.args, :($A_symb))
    end

    res = quote
        $pre # allocate an empty array A_i of proper eltype for column i
        stmt = curs.stmt
        status = curs.status
        coltypes = curs.coltypes
        while status == 100
            $while_body # push! to each A_i the respective value in current row
            status = execute!(stmt)
        end
        # res = Vector[]
        res = $post # set return value equal to a tuple of all A_is
        return res, length(res[1])
    end
    # println(res)
    return res
end

function Base.summary{C, F}(tab::Table{C, F})
    dims = Base.dims2string(size(tab))
    colsymbs = F.parameters
    colstrings = UTF8String[ string(colsymb) for colsymb in colsymbs ]
    fieldnames = gen_fieldnames(colstrings)
    return "$dims Table with columns\n $fieldnames"
end

function Base.show(io::IO, tab::Table)
    println(io, summary(tab))
    Base.showlimited(io, tab)
end

Base.size(tab::NullableTable) = (nrows(tab), length(tab.columns))
Base.ndims(::NullableTable) = 2
nrows(tab::NullableTable) = tab.nrows
Base.linearindexing(tab::NullableTable) = Base.LinearSlow()

function Base.getindex(tab::NullableTable, i::Int)
    sub = ind2sub(size(tab), i)
    getindex(tab, sub...)
end

@inline function Base.getindex(tab::NullableTable, i::Int, j::Int)
    return tab.columns[j][i]
end

@generated function Base.getindex{C, Fi, f}(tab::NullableTable{C, Fi},
                                            ::Type{F{f}})
    j = findfirst(Fi.parameters, f)
    return :( tab.columns[$j] )
end

@generated function Base.getindex{Co, Fi, j}(tab::NullableTable{Co, Fi},
                                             ::Type{C{j}})
    return :( tab.columns[$j] )
end

@generated function Base.getindex{Co, Fi}(tab::NullableTable{Co, Fi}, i::Int,
                                        ::Colon)
    colsymbs = Fi.parameters
    N = length(colsymmbs)
    res_tup = Expr(:tuple, [ :(tab[i, Fi{$f}]) for f in colsymbs ]...)
    return :( $res_tup )
end

Base.getindex{Co, Fi, f}(tab::NullableTable{Co, Fi}, i::Int, ::Type{F{f}}) = tab[F{f}][i]
