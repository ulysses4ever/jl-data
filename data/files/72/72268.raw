module DateExtensions

using Dates
# A Timestamp type couples an Instant type with a Calendar type
# to provide convenient human-conversion rules carried out
# by multiple dispatch.
immutable Timestamp{T<:Instant,C<:Calendar} <: Dates.TimeType
    instant::T
    Timestamp(x::T) = new(x)
end


# Holidays
newyears(y) = (y,1,1)
isnewyears(dt::Dates.TimeType) = yearmonthday(dt) == newyears(year(dt))
independenceday(y) = (y,7,4)
isindependenceday(dt::Dates.TimeType) = yearmonthday(dt) == independenceday(year(dt))
veteransday(y) = (y,11,11)
isveteransday(dt::Dates.TimeType) = yearmonthday(dt) == veteransday(year(dt))
christmas(y) = (y,12,25)
ischristmas(dt::Dates.TimeType) = yearmonthday(dt) == christmas(year(dt))

function ismartinlutherking(dt::Dates.TimeType)
    # 3rd Monday of January
    dayofweek(dt) == Mon && month(dt) == Jan && dayofweekofmonth(dt) == 3
end
function ispresidentsday(dt::Dates.TimeType)
    # 3rd Monday of February
   dayofweek(dt) == Mon && month(dt) == Feb && dayofweekofmonth(dt) == 3 
end
function ismemorialday(dt::Dates.TimeType)
    # Last Monday of May
   dayofweek(dt) == Mon && month(dt) == May && dayofweekofmonth(dt) == daysofweekinmonth(dt)
end
function islaborday(dt::Dates.TimeType)
    # First Monday of September
    dayofweek(dt) == Mon && month(dt) == Sep && dayofweekofmonth(dt) == 1
end
function iscolumbusday(dt::Dates.TimeType)
    # Second Monday of October
    dayofweek(dt) == Mon && month(dt) == Oct && dayofweekofmonth(dt) == 2
end
function isthanksgiving(dt::Dates.TimeType)
    # Fourth Thursday in November
    dayofweek(dt) == Thu && month(dt) == Nov && dayofweekofmonth(dt) == 4
end

function easter(y)
    # Butcher's Algorithm: http://www.smart.net/~mmontes/butcher.html
    a=y%19
    b=div(y,100)
    c=y%100
    d=div(b,4)
    e=b%4
    f=div(b+8,25)
    g=div(b-f+1,3)
    h=(19*a+b-d-g+15)%30
    i=div(c,4)
    k=c%4
    l=(32+2*e+2*i-h-k)%7
    m=div(a+11*h+22*l,451)
    month=div(h+l-7*m+114,31)
    p=(h+l-7*m+114)%31
    return (y,month,p+1)
end
iseaster(dt::Dates.TimeType) = yearmonthday(dt) == easter(year(dt))

const HOLIDAYS = x->isnewyears(x) || isindependenceday(x) ||
                    isveteransday(x) || ischristmas(x) ||
                    ismartinlutherking(x) || ispresidentsday(x) ||
                    ismemorialday(x) || islaborday(x) ||
                    iscolumbusday(x) || isthanksgiving(x)
const OBSERVEDHOLIDAYS = x->begin 
    # If the holiday is on a weekday
    if (isnewyears(x) || isindependenceday(x) ||
       isveteransday(x) || ischristmas(x) ||
       ismartinlutherking(x) || ispresidentsday(x) ||
       ismemorialday(x) || islaborday(x) ||
       iscolumbusday(x) || isthanksgiving(x)) && dayofweek(x) < 6
        return true
    # Holiday is observed Monday if falls on Sunday
    elseif dayofweek(x) == 1 && (isnewyears(x-Day(1)) || isindependenceday(x-Day(1)) ||
       isveteransday(x-Day(1)) || ischristmas(x-Day(1)) ||
       ismartinlutherking(x-Day(1)) || ispresidentsday(x-Day(1)) ||
       ismemorialday(x-Day(1)) || islaborday(x-Day(1)) ||
       iscolumbusday(x-Day(1)) || isthanksgiving(x-Day(1)))
        return true
    # Holiday is observed Friday if falls on Saturday
    elseif dayofweek(x) == 5 && (isnewyears(x+Day(1)) || isindependenceday(x+Day(1)) ||
       isveteransday(x+Day(1)) || ischristmas(x+Day(1)) ||
       ismartinlutherking(x+Day(1)) || ispresidentsday(x+Day(1)) ||
       ismemorialday(x+Day(1)) || islaborday(x+Day(1)) ||
       iscolumbusday(x+Day(1)) || isthanksgiving(x+Day(1)))
        return true
    else
        return false
    end
end

end # module
