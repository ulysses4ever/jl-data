module Dates

export Date, greater_than, less_than, date_sort
end

type Date
    year::Int64
    month::Int64
    day::Int64
    hour::Int64
    minute::Int64
    second::Int64
end

#if date 1 is greater than date 2, returns true
function greater_than(d1::Date, d2::Date)
    if d1.year > d2.year
        return true
    elseif d1.year < d2.year
        return false
    end
    if d1.month > d2.month
        return true
    elseif d1.month < d2.month
        return false
    end
    if d1.day > d2.day
        return true
    elseif d1.day < d2.day
        return false
    end
    if d1.hour > d2.hour
        return true
    elseif d1.hour < d2.hour
        return false
    end
    if d1.minute > d2.minute
        return true
    elseif d1.minute < d2.minute
        return false
    end
    if d1.second > d2.second
        return true
    elseif d1.second < d2.second
        return false
    else
        return false
    end
end

function less_than(d1::Date, d2::Date)
    if d1.year < d2.year
        return true
    elseif d1.year > d2.year
        return false
    end
    if d1.month < d2.month
        return true
    elseif d1.month > d2.month
        return false
    end
    if d1.day < d2.day
        return true
    elseif d1.day > d2.day
        return false
    end
    if d1.hour < d2.hour
        return true
    elseif d1.hour > d2.hour
        return false
    end
    if d1.minute < d2.minute
        return true
    elseif d1.minute > d2.minute
        return false
    end
    if d1.second < d2.second
        return true
    elseif d1.second > d2.second
        return false
    else
        return false
    end
end

#uses a quicksort for dates
function date_sort(a::Array{Date,1})
    more = Date[]
    pivot_arr = Date[]
    less = Date[]

    if length(a) <= 1
        return a
    else
        pivot = a[1]

        for i in a
            #if i greater than pivot
            if greater_than(i, pivot)
                push!(more, i)
            elseif greater_than(pivot, i)
                push!(less, i)
            else
                push!(pivot_arr, a[1])
            end
        end

        less = date_sort(less)
        more = date_sort(more)

        return append!(append!(less, pivot_arr), more)
    end
end