module UTime

import Base:show
import Base.Dates: Date, DateTime, DateFormat,
           Period, DatePeriod, TimePeriod, Year, Month,
           Week, Day, Hour, Minute, Second, Millisecond,
           yearmonthday, yearmonth, monthday, year, month,
           week, day, hour, minute, second, millisecond, 
           dayofmonth, dayofweek, isleapyear, daysinmonth, 
           daysinyear, dayofyear, dayname, dayabbr,
           dayofweekofmonth, daysofweekinmonth, monthname,
           monthabbr, quarterofyear, dayofquarter,
           firstdayofweek, lastdayofweek,
           firstdayofmonth, lastdayofmonth, firstdayofyear, 
           lastdayofyear, firstdayofquarter, lastdayofquarter,
           adjust, tonext, toprev, tofirst, tolast, recur,
           format, (+), (-), (.+), (.-)
 
export ut, localtime, UT,
           Year, Month, Week, Day, Hour, Minute, Second, Millisecond,
           yearmonthday, yearmonth, monthday, year, month,
           week, day, hour, minute, second, millisecond, 
           dayofmonth, dayofweek, isleapyear, daysinmonth, 
           daysinyear, dayofyear, dayname, dayabbr,
           dayofweekofmonth, daysofweekinmonth, monthname,
           monthabbr, quarterofyear, dayofquarter,
           firstdayofweek, lastdayofweek,
           firstdayofmonth, lastdayofmonth, firstdayofyear, 
           lastdayofyear, firstdayofquarter, lastdayofquarter,
           adjust, tonext, toprev, tofirst, tolast, recur,
           format, ISOUniversalTimeFormat, (+), (-), (.+), (.-)

abstract CTmStruct

type TmCStruct <: CTmStruct
    sec  ::Int32 # 0..
    min  ::Int32 # 0..
    hour ::Int32 # 0..
    mday ::Int32 # 1..
    month::Int32 # 0..
    year ::Int32 # 1900=>0..
    wday ::Int32 # 0==Sunday..
    yday ::Int32 # 0..
    isdst::Int32
    # on some platforms the struct is 14 wordsc_gettimeofday_sec, , even though 9 are specified
    _10::Int32
    _11::Int32
    _12::Int32
    _13::Int32
    _14::Int32

    TmCStruct() = new(0,0,0,0,0,0,0,0,0,0,0,0,0,0)
end

function (==)(a::TmCStruct, b::TmCStruct)
    fields = [:sec,:min, :hour, :mday, :month, :year, :wday, :yday, :isdst]
    ans = true
    for f in fields
       if (a).(f) != (b).(f)
          print(f); ans = false
       end
    end
    ans
end

(==)(a::CTmStruct, b::CTmStruct) = (==)(a.tm, b.tm)

type LclTmStruct <: CTmStruct
    tm::TmCStruct

    LclTmStruct() = new(TmCStruct())
    LclTmStruct(tm::TmCStruct) = new(tm)
    function LclTmStruct(t::Real)
        t = floor(t)
        tm = TmCStruct()
        ccall(:localtime_r, Ptr{TmCStruct}, (Ptr{Int}, Ptr{TmCStruct}), &t, &tm)
        new(tm)
    end
end

type UtcTmStruct <: CTmStruct
    tm::TmCStruct

    UtcTmStruct() = new(TmCStruct())
    UtcTmStruct(tm::TmCStruct) = new(tm)
    function UtcTmStruct(t::Real)
        t = floor(t)
        tm = TmCStruct()
        ccall(:gmtime_r, Ptr{TmCStruct}, (Ptr{Int}, Ptr{TmCStruct}), &t, &tm)
        new(tm)
    end
end

function LclTmStruct{T<:Integer}(year::T,month=1::T,day=1::T,hour=0::T,min=0::T,sec=0::T;isdst=(-1)::T)
  lts = LclTmStruct()
  lts.tm.year  = Int32(year-1900)
  lts.tm.month = Int32(month-1)
  lts.tm.mday  = Int32(day)
  lts.tm.hour  = Int32(hour)
  lts.tm.min   = Int32(min)
  lts.tm.sec   = Int32(sec)
  lts.tm.isdst = Int32(isdst)
  lts
end

function UtcTmStruct{T<:Integer}(year::T,month=1::T,day=1::T,hour=0::T,min=0::T,sec=0::T;isdst=0::T)
  uts = UtcTmStruct()
  uts.tm.year  = Int32(year-1900)
  uts.tm.month = Int32(month-1)
  uts.tm.mday  = Int32(day)
  uts.tm.hour  = Int32(hour)
  uts.tm.min   = Int32(min)
  uts.tm.sec   = Int32(sec)
  uts.tm.isdst = Int32(isdst)
  uts
end


#=
  unbreak_{ut,lcl,std,dst}time: CTmStruct --> seconds after POSIX Epoch
  breakdn_{ut,lcl,std,dst}time: seconds after POSIX Epoch --> CTmStruct
=#

function breakdn_lcltime(sec::Int64) 
    s   = sec
    lts = LclTmStruct()
    ccall(:localtime_r, Ptr{TmCStruct}, (Ptr{Int64}, Ptr{TmCStruct}), &s, &lts.tm)
    return lts
end
breakdn_lcltime(t::Real) = breakdn_lcltime(floor(Int64,t))

breakdn_stdtime(sec::Int64) = breakdn_lcltime(unbreak_stdtime(breakdn_lcltime(sec)))
breakdn_stdtime(t::Real) = breakdn_stdtime(floor(Int64,t))

breakdn_dsttime(sec::Int64) = breakdn_lcltime(unbreak_dsttime(breakdn_lcltime(sec)))
breakdn_dsttime(t::Real) = breakdn_dsttime(floor(Int64,t))

function breakdn_uttime(sec::Int64)
    s  = sec
    uts = UtcTmStruct()
    ccall(:gmtime_r,Ptr{TmCStruct}, (Ptr{Int64}, Ptr{TmCStruct}), &s, &uts.tm)
    return uts
end
breakdn_uttime(t::Real) = breakdn_uttime(floor(Int64,t))



function unbreak_lcltime(cts::CTmStruct)
    tcs = cts.tm
    tcs.isdst = -one(Int32)    
    s = ccall(:mktime, Int64, (Ptr{TmCStruct},), &tcs)
    if s == typemax(Int64) - one(Int64)
       throw(ArgumentError("unrepresentable mktime(tm=$(tm))"))
    end
    return s   
end

function unbreak_stdtime(cts::CTmStruct)
    tcs = cts.tm
    tcs.isdst = zero(Int32)
    s = ccall(:mktime, Int64, (Ptr{TmCStruct},), &tcs)
    if s == typemax(Int64) - one(Int64)
       throw(ArgumentError("unrepresentable mktime(tm=$(tm))"))
    end
    return s   
end

function unbreak_dsttime(cts::CTmStruct)
    tcs = cts.tm
    tcs.isdst = one(Int32)
    s = ccall(:mktime, Int64, (Ptr{TmCStruct},), &tcs)
    if s == typemax(Int64) - one(Int64)
       throw(ArgumentError("unrepresentable mktime(tm=$(tm))"))
    end
    return s   
end


#=
unbreak_uttime adapted from public domain source code 
by Eric S. Raymond <esr@thyrsus.com>
at http://www.catb.org/esr/time-programming
=#
const cumdays = Int64[ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 ]

function unbreak_uttime(cts::CTmStruct)
    mon   = Int64(cts.tm.month)
    mon12 = mon % 12
    year  = 1900 + Int64(cts.tm.year) + div(mon,12)
    ans = (year - 1970) * 365 + cumdays[1+mon12];
    ans += div(year - 1968, 4)
    ans -= div(year - 1900, 100)
    ans += div(year - 1600, 400)
    if ((year % 4) == 0 && ((year % 100) != 0 || (year % 400) == 0) && (mon12 < 2))
        ans -= 1
    end
    ans += Int64(cts.tm.mday) - 1
    ans *= 24
    ans += Int64(cts.tm.hour)
    ans *= 60;
    ans += Int64(cts.tm.min)
    ans *= 60;
    ans += Int64(cts.tm.sec)
    if (cts.tm.isdst == one(Int32))
        ans -= 3600
    end
    ans    
end


# TECHNICALITY
#   these two functions are mutually inversive
#   their implementations may not be inverses

ut_from_lcltime(sec::Int64) = unbreak_lcltime(breakdn_uttime(sec))
lcl_from_uttime(sec::Int64) = unbreak_uttime(breakdn_stdtime(sec))

ut_offset(sec::Int64) = sec - ut_from_lcltime(sec)
lcl_offset(sec::Int64) = -ut_offset(sec)

# exported

ut_raw() = 
    Base.Dates.unix2datetime( 
        ut_from_lcltime( 
            floor(Int64,Base.Dates.datetime2unix(Base.Dates.now())) ))

localtime() = Base.Dates.now()


# dt as localtime --> ut (without leap seconds)
function ut_raw(dt::DateTime)
    sec = floor(Int64, Base.Dates.datetime2unix(dt))
    sec = ut_from_lcltime(sec)    
    Base.Dates.unix2datetime( sec )
end

# dt as localtime --> ut (with leap seconds)
function utc(dt::DateTime)
    warn("try ut($(dt))")
end

# dt as ut --> localtime (without leap seconds
function localtime(dt::DateTime)
    sec = floor(Int64, Base.Dates.datetime2unix(dt))
    sec = lcl_from_uttime(sec)    
    Base.Dates.unix2datetime( sec )
end

immutable UT
    value::DateTime

    UT(dt::DateTime) = new(dt)
    UT() = new(ut_raw())
end
show(io::IO, dt::UT) =
    show(io, replace(string(dt.value),"T","Z"))

convert(::DateTime, dtm::UT) = localtime(dtm.value)
#DateTime(dtm::UT) = localtime(dtm.value)
@vectorize_1arg DateTime UT
@vectorize_1arg UT DateTime


UT{T<:Integer}(yr::T) = UT(DateTime(yr))
UT{T<:Integer}(yr::T,mo::T ) = UT(DateTime(yr,mo))
UT{T<:Integer}(yr::T,mo::T,dy::T) = UT(DateTime(yr,mo,dy))
UT{T<:Integer}(yr::T,mo::T,dy::T,hr::T) = 
  UT(DateTime(yr,mo,dy,hr))
UT{T<:Integer}(yr::T,mo::T,dy::T,hr::T,mi::T) = 
  UT(DateTime(yr,mo,dy,hr,mi))
UT{T<:Integer}(yr::T,mo::T,dy::T,hr::T,mi::T,sc::T) = 
  UT(DateTime(yr,mo,dy,hr,mi,sc))
UT{T<:Integer}(yr::T,mo::T,dy::T,hr::T,mi::T,sc::T,ss::T) = 
  UT(DateTime(yr,mo,dy,hr,mi,sc,ss))


ut(dtm::DateTime) = UT(dtm)
ut() = UT()
# :Period, :DatePeriod, :TimePeriod

for fn in [:Year, :Month, :Week, :Day, :Hour, :Minute, :Second,
           :Millisecond,
           :yearmonthday, :yearmonth, :monthday, :year, :month,
           :week, :day, :hour, :minute, :second, :millisecond, 
           :dayofmonth, :dayofweek, :isleapyear, :daysinmonth, 
           :daysinyear, :dayofyear, :dayname, :dayabbr,
           :dayofweekofmonth, :daysofweekinmonth, :monthname,
           :monthabbr, :quarterofyear, :dayofquarter
          ]
    @eval ($fn)(dtm::UT) = ($fn)(dtm.value)
end

for fn in [:adjust, :tonext, :toprev, :tofirst, :tolast, :recur]
    @eval ($fn)(dtm::UT, args...) = UT(($fn)(dtm.value, args...))      
end

const ISOUniversalTimeFormat = DateFormat("yyyy-mm-ddZHH:MM:SS.s")

function format(udtm::UT, pattern::AbstractString, addUTC=true::Bool)
   s = format(UT.value, pattern)
   if addUTC
    s = s * " UT"
   end
   s 
end

(-)(udtm::UT, udtm2::UT) = (-)(udtm.value, udtm2.value)
(-)(udtm::UT, p::Period) = UT((-)(udtm.value, p))
(.-)(udtm::UT, vec::Array{UT,1}) = 
    [(-)(udtm, i) for i in vec])
(.-)(udtm::UT, vec::Array{Period,1}) = 
    [(-)(udtm, i) for i in vec]
(.-)(vec::Array{UT,1}, udtm::UT) = 
    [(-)(i,udtm) for i in vec])
(.-)(vec::Array{UT,1}, p::Period) = 
    [(-)(i,p) for i in vec])

(+)(udtm::UT, p::Period) = UT((+)(udtm.value, p))
(+)(p::Period, udtm::UT) = (+)(udtm, p)
(.+)(udtm::UT, vec::Array{Period,1}) = 
    [(+)(udtm, i) for i in vec]
(.+)(vec::Array{UT,1},p::Period) = 
    [(+)(i, p) for i in vec]

end # module
