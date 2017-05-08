immutable Table{C<:Tuple, F<:Tuple} <: AbstractArray{Any, 2}
    columns::C
    fields::Type{F}
    nrows::Int
end

function Table(curs::Cursor)
    columns, tup_colsymbs, nrows = materialize!(curs, Table)
    return Table(columns, tup_colsymbs, nrows)
end

@generated function _materialize{Co<:Tuple, Fi<:Tuple}(
    curs::Cursor{CSV.Stream, Co, Fi},
    ::Type{Table}
)
    N = length(Co.parameters)
    types = [ Co.parameters[i] for i in 1:N ]

    pre = Expr(:block)
    while_body = Expr(:block)
    post = Expr(:tuple)
    for i in 1:N
        A_symb = symbol("A_$i")
        typ = types[i]
        push!(pre.args, :( $A_symb = Vector{$typ}() ))
        push!(while_body.args,
              :( push!($A_symb, CSV.readfield(curs.io, $typ, nrows, $i)[1]) )
        )
        push!(post.args, :($A_symb))
    end

    res = quote
        $pre # allocate an empty array A_i of proper eltype for column i
        io = curs.io
        status = curs.status
        coltypes = curs.coltypes
        nrows = 0
        while !eof(curs.io)
            nrows += 1
            $while_body # push! to each A_i the respective value in current row
        end
        res = $post # set return value equal to a tuple of all A_is
        reset!(curs)
        return res, nrows
    end
    # println(res)
    return res
end

@generated function _materialize{Co<:Tuple, Fi<:Tuple}(
    curs::Cursor{SQLite3.Stmt, Co, Fi},
    ::Type{Table}
) #, coltypes::Type{T})
    N = length(Co.parameters)
    types = [ Co.parameters[i] for i in 1:N ]

    pre = Expr(:block)
    while_body = Expr(:block)
    post = Expr(:tuple)
    for i in 1:N
        A_symb = symbol("A_$i")
        typ = types[i]
        push!(pre.args, :( $A_symb = Vector{$typ}() ))
        if typ <: AbstractString
            push!(while_body.args,
                  :( push!($A_symb,
                           bytestring($(SQLite3.sqlite_get_fns[types[i]])(io.handle, $(i-1)))) )
            )
        else
            push!(while_body.args,
                  :( push!($A_symb,
                           $(SQLite3.sqlite_get_fns[types[i]])(io.handle, $(i-1))) )
            )
        end
        push!(post.args, :($A_symb))
    end

    res = quote
        $pre # allocate an empty array A_i of proper eltype for column i
        io = curs.io
        status = curs.status
        coltypes = curs.coltypes
        while status == 100
            $while_body # push! to each A_i the respective value in current row
            status = SQLite3.execute!(io)
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

Base.size(tab::Table) = (nrows(tab), length(tab.columns))
Base.ndims(::Table) = 2
nrows(tab::Table) = tab.nrows
Base.linearindexing(tab::Table) = Base.LinearSlow()

function Base.getindex(tab::Table, i::Int)
    sub = ind2sub(size(tab), i)
    getindex(tab, sub...)
end

@inline function Base.getindex(tab::Table, i::Int, j::Int)
    return tab.columns[j][i]
end

@generated function Base.getindex{C, Fi, f}(tab::Table{C, Fi},
                                            ::Type{F{f}})
    j = findfirst(Fi.parameters, f)
    return :( tab.columns[$j] )
end

@generated function Base.getindex{Co, Fi, j}(tab::Table{Co, Fi},
                                             ::Type{C{j}})
    return :( tab.columns[$j] )
end

@generated function Base.getindex{Co, Fi}(tab::Table{Co, Fi}, i::Int,
                                        ::Colon)
    colsymbs = Fi.parameters
    N = length(colsymmbs)
    res_tup = Expr(:tuple, [ :(tab[i, Fi{$f}]) for f in colsymbs ]...)
    return :( $res_tup )
end

Base.getindex{Co, Fi, f}(tab::Table{Co, Fi}, i::Int, ::Type{F{f}}) = tab[F{f}][i]
