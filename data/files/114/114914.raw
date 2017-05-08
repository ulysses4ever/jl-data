# Fisher Yates exact test for Julia
# Ported by: Matias Guzmán Naranjo

##############################################################################
# Following functions have been taken from the DendroPy library from:
##
##  DendroPy Phylogenetic Computing Library.
##
##  Copyright 2010 Jeet Sukumaran and Mark T. Holder.
##  All rights reserved.
##
##  See "LICENSE.txt" for terms and conditions of usage.
##
##  If you use this work or any portion thereof in published work,
##  please cite it as:
##
##     Sukumaran, J. and M. T. Holder. 2010. DendroPy: a Python library
##     for phylogenetic computing. Bioinformatics 26: 1569-1571.
##
##############################################################################

module Fisher

export right_tail_p, left_tail_p, two_tail_p, Table

function hypergeometric_pmf(x::Int64, m::Int64, n::Int64, k::Int64)
    #Given a population consisting of `m` items of class M and `n` items of class N,
    #this returns the probability of observing `x` items of class M when sampling
    #`k` times without replacement from the entire population (i.e., {M,N})

    #p(x) = (choose(m, x) * choose(n, k-x)) / choose(m+n, k)

    # following fails with 'OverflowError: long int too large to convert to
    # float' with large numbers
    # return float(binomial_coefficient(m, x) * binomial_coefficient(n, k-x))/binomial_coefficient(m+n, k)

    #a = log(binomialM(BigInt(m), BigInt(x)))
    #b = log(binomialM(BigInt(n), BigInt(k-x)))
    #c = log(binomialM(BigInt(m+n), BigInt(k)))

    a = log(binomial_coefficient(m, x))
    b = log(binomial_coefficient(n, k-x))
    c = log(binomial_coefficient(m+n, k))

    return exp(a+b-c)
end

function binomial_coefficient(population::Int64, sample::Int64)
    #Returns 'population' choose 'sample'.

    s = max(sample, population-sample)

    if s > population
        println(string("population = ", population, ", sample = ", sample, ", s = ", s))
    end
    @assert s <= population
    @assert population > -1

    if s == population
        return 1
    end
    numerator = BigInt(1)
    denominator = BigInt(1)
    for i in (s+1): (population)
        numerator = numerator *i
        denominator = denominator * (i-s)

    end
    res = (convert(Float64, numerator/denominator))
    if res == Inf
        return 1
    else
        return res
    end
end

type Table
    a::Int64
    b::Int64
    c::Int64
    d::Int64
    minv::Int64
    maxv::Int64
    Table(a,b,c,d)= new(a,b,c,d,min(a,b,c,d), max(a,b,c,d))
end

function totable(table::Matrix)
    a = table[1,1]
    b = table[1,2]
    c = table[2,1]
    d = table[2,2]
    return Table(a,b,c,d)
end

function totable(table::Array{Int64,1})
    a = table[1]
    b = table[2]
    c = table[3]
    d = table[4]
    return Table(a,b,c,d)
end

function flat_table(table::Table)
    return [table.a, table.b, table.c,table.d]
end


function probability_of_table(table::Table)
    hyper = hypergeometric_pmf(table.a, table.a+table.b, table.c+table.d,table.a+table.c)
    return  hyper

end

function rotate_cw(table::Table)
    # Rotates the table clockwise
    return Table(table.c, table.a, table.d, table.b)
end

function min_rotation(table::Table)
    # Returns rotation of the table such that the smalles value is in the first upper left cell.

    if table.a==table.minv
        return table
    else
        min_rotation(rotate_cw(table))
    end
end

function max_rotation(table::Table)
    # Returns rotation of the table such that the smalles value is in the first upper left cell.

    if table.a==table.maxv
        return table
    else
        max_rotation(rotate_cv(table))
    end
end

function get_left_tail_probs(table::Table)
    table = min_rotation(table)
    row_totals = [table.a+table.b,table.c+table.d]
    col_totals = [table.a+table.c,table.b+table.d]
    pvals = Float64[]

    while true
        table.a -=1
        if table.a <0
            break
        end
        table.b = row_totals[1]-table.a
        table.c = col_totals[1]-table.a
        table.d = row_totals[2]-table.c

        push!(pvals, probability_of_table(table))
    end
    return pvals
end

function get_right_tail_probs(table::Table)
    table = min_rotation(table)
    row_totals = [table.a+table.b,table.c+table.d]
    col_totals = [table.a+table.c,table.b+table.d]
    pvals = Float64[]

    while true
        table.a +=1
        table.b = row_totals[1]-table.a
        if table.b < 0
            break
        end
        table.c = col_totals[1]-table.a
        if table.c < 0
            break
        end
        table.d = row_totals[2]-table.c
        if table.d <0
            break
        end

        push!(pvals, probability_of_table(table))
    end
    return pvals
end

function get_left_tail_tables(table::Table)
    table = min_rotation(table)
    row_totals = [table.a+table.b,table.c+table.d]
    col_totals = [table.a+table.c,table.b+table.d]
    left_tail_tables = Table[]

    while true
        table.a -=1
        if table.a < 0
            break
        end
        table.b = row_totals[1] - table.a
        table.c = col_totals[1] - table.a
        table.d = row_totals[2] - table.c
        push!(left_tail_tables, table)
    end
    println(left_tail_tables)
    return left_tail_tables
end

function get_right_tail_tables(table::Table)
    table = min_rotation(table)
    row_totals = [table.a+table.b,table.c+table.d]
    col_totals = [table.a+table.c,table.b+table.d]
    right_tail_tables = Table[]

    while true
        table.a += 1
        table.b = row_totals[1] - table.a
        if table.b < 0
            break
        end
        table.c = col_totals[1] - table.a
        if table.c < 0
            break
        end
        table.d = row_totals[2] - table.c
        if table.d < 0
            break
        end
        push!(right_tail_tables, table)
    end
    return right_tail_tables
end

function left_tail_p(table::Table)
    # Returns the sum of probabilities of this table and all others more extreme

    return probability_of_table(table) + sum(get_left_tail_probs(table))
end

left_tail_p(a::Int64,b::Int64,c::Int64,d::Int64) = left_tail_p(Table(a,b,c,d))

left_tail_p(arr::Array{Int64, 1}) = left_tail_p(totable(arr))

left_tail_p(matr::Matrix) = left_tail_p(totable(matr))


function right_tail_p(table::Table)
    # Returns the sum of probabilities of this table and all others more extreme

    return probability_of_table(table) + sum(get_right_tail_probs(table))
end

right_tail_p(a::Int64,b::Int64,c::Int64,d::Int64) = right_tail_p(Table(a,b,c,d))

right_tail_p(arr::Array{Int64, 1}) = right_tail_p(totable(arr))

right_tail_p(matr::Matrix) = right_tail_p(totable(matr))


function two_tail_p(table::Table)
    p0 = probability_of_table(table)
    all_p_vals = cat(1,get_left_tail_probs(table), get_right_tail_probs(table))
    pvals=Float64[]

    for p in all_p_vals
        if p <= p0
            push!(pvals,p)
        end
    end
    return sum(pvals) + p0
end

two_tail_p(a::Int64,b::Int64,c::Int64,d::Int64) = two_tail_p(Table(a,b,c,d))

two_tail_p(arr::Array{Int64, 1}) = two_tail_p(totable(arr))

two_tail_p(matr::Matrix) = two_tail_p(totable(matr))

end
