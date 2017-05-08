module UTime

import Base: show, string

import Base.Dates: Date, DateTime, DateFormat,
           Period, DatePeriod, TimePeriod,
           Year, Month, Week, Day, Hour, Minute, Second, Millisecond,
           Mon, Tue, Wed, Thu, Fri, Sat, Sun,
           Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday,
           Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec,
           January, February, March, April, May, June, July, August,
           September, October, November, December,
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

export ut, localtime, UT, LCL, utc,
           Year, Month, Week, Day, Hour, Minute, Second, Millisecond,
           Mon, Tue, Wed, Thu, Fri, Sat, Sun,
           Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday,
           Jan, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec,
           January, February, March, April, May, June, July, August,
           September, October, November, December,
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
           format, ISOUniversalTimeFormat, isoUniversalTimeFormat,
           isoDateTimeFormat,
           (+), (-), (.+), (.-)

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

function breakdn_utmtime(sec::Int64)
    s  = sec
    uts = UtcTmStruct()
    ccall(:gmtime_r,Ptr{TmCStruct}, (Ptr{Int64}, Ptr{TmCStruct}), &s, &uts.tm)
    return uts
end
breakdn_utmtime(t::Real) = breakdn_utmtime(floor(Int64,t))



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
unbreak_utmtime adapted from public domain source code
by Eric S. Raymond <esr@thyrsus.com>
at http://www.catb.org/esr/time-programming
=#
const cumdays = Int64[ 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 ]

function unbreak_utmtime(cts::CTmStruct)
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

utm_from_lcltime(sec::Int64) = unbreak_lcltime(breakdn_utmtime(sec))
lcl_from_utmtime(sec::Int64) = unbreak_utmtime(breakdn_stdtime(sec))

utm_offset(sec::Int64) = sec - utm_from_lcltime(sec)
lcl_offset(sec::Int64) = -utm_offset(sec)

function utm_from_lcltime(sec::Float64)
    isec = floor(Int64, sec)
    utm = unbreak_lcltime(breakdn_utmtime(isec))

    fsec = signbit(lcl_offset(isec)) ? isec-sec : sec-isec
    Base.Dates.unix2datetime(Base.Dates.datetime2unix(utm) + fsec)
end

function lcl_from_utmtime(sec::Float64)
    isec = floor(Int64, sec)
    lcl = unbreak_utmtime(breakdn_stdtime(isec))
    lcl # adjust for fractional secs +/- wrt local timezone
end



ut_raw() =
    Base.Dates.unix2datetime(
        utm_from_lcltime(
            floor(Int64,Base.Dates.datetime2unix(Base.Dates.now())) ))

# dt as localtime --> ut (without leap seconds)
function ut_raw(dt::DateTime)
    sec = floor(Int64, Base.Dates.datetime2unix(dt))
    sec = utm_from_lcltime(sec)
    Base.Dates.unix2datetime( sec )
end



immutable UT
    value::DateTime

    function UT(dt::DateTime)
        fsecs = Base.Dates.datetime2unix(dt)
        isecs = floor(Int64, fsecs)
        ofs   = lcl_offset(isecs)
        fsecs += ofs
        new(Base.Dates.unix2datetime(fsecs))
    end
    UT() = new(ut_raw())
end


immutable LCL
    value::DateTime

    LCL(dt::DateTime) = new(dt)
    LCL() = new(now())
end


convert(::DateTime, dtm::UT)  = localtime(dtm.value)
convert(::UT, dtm::DateTime)  = ut(dtm)
convert(::DateTime, dtm::LCL)  = dtm.value
convert(::LCL, dtm::DateTime)  = LCL(dtm)
convert(::UT, dtm::LCL)  = ut(dtm.value)
convert(::LCL, dtm::UT)  = LCL(localtime(dtm.value))

#convert(::DateTime, dtm::UTC) = localtime(dtm.value)
#convert(::UTC, dtm::DateTime) = utc(dtm)
#convert(::UTC, dtm::UT) = utc(localtime(dtm))
#convert(::UT, dtm::UTC) = ut(localtime(dtm))


promote_rule(::DateTime, ::UT) = UT
promote_rule(::LCL, ::UT) = UT
promote_rule(::DateTime, ::LCL) = LCL

#promote_rule(::DateTime, ::UTC) = UTC
#promote_rule(::UT, ::UTC) = UTC

ut(dtm::DateTime) = UT(dtm)
ut() = UT()
ut(dtm::UT) = dtm
ut(dtm::LCL) = UT(dtm.value)

# dt as localtime --> ut (with leap seconds)
function utc(dt::DateTime)
    info("try ut($(dt)), utc requires leap seconds")
end
utc() = info("try ut(), utc requires leap seconds")
utc(dt::UT) = info("try ut(), utc requires leap seconds")
utc(dt::LCL) = info("try ut(), utc requires leap seconds")

# dt as ut --> localtime (without leap seconds)
function localtime(dt::DateTime)
    sec = floor(Int64, Base.Dates.datetime2unix(dt))
    sec = lcl_from_utmtime(sec)
    LCL(Base.Dates.unix2datetime( sec ))
end

#DateTime(dtm::UT) = localtime(dtm.value)
function localtime(dtm::UT)
    sec = Base.Dates.datetime2unix(dtm.value)
    sec = lcl_from_utmtime(sec)
    LCL(Base.Dates.unix2datetime( sec ))
end

localtime(dtm::LCL) = dtm
localtime() = LCL(Base.Dates.now())



@vectorize_1arg DateTime UT
@vectorize_1arg UT DateTime
#@vectorize_1arg DateTime UTC
#@vectorize_1arg UTC DateTime
#@vectorize_1arg UTC UT
#@vectorize_1arg UT UTC

for U in [:LCL, :UT]
  @eval begin
    $(U){T<:Integer}(yr::T) = $(U)(DateTime(yr))
    $(U){T<:Integer}(yr::T,mo::T ) = $(U)(DateTime(yr,mo))
    $(U){T<:Integer}(yr::T,mo::T,dy::T) = $(U)(DateTime(yr,mo,dy))
    $(U){T<:Integer}(yr::T,mo::T,dy::T,hr::T) =
      $(U)(DateTime(yr,mo,dy,hr))
    $(U){T<:Integer}(yr::T,mo::T,dy::T,hr::T,mi::T) =
      $(U)(DateTime(yr,mo,dy,hr,mi))
    $(U){T<:Integer}(yr::T,mo::T,dy::T,hr::T,mi::T,sc::T) =
      $(U)(DateTime(yr,mo,dy,hr,mi,sc))
    $(U){T<:Integer}(yr::T,mo::T,dy::T,hr::T,mi::T,sc::T,ss::T) =
      $(U)(DateTime(yr,mo,dy,hr,mi,sc,ss))
  end
end


# :Period, :DatePeriod, :TimePeriod

for fn in [:Year, :Month, :Week, :Day, :Hour, :Minute, :Second, :Millisecond]
    @eval begin
        convert(::Type{($fn)}, (dt::LCL)) = convert(($fn),(dt.value))
        convert(::Type{($fn)}, (dt::UT))  = convert(($fn),(dt.value))
        #convert(::($fn), (dt::UTC)) = convert(::($fn),(dt.value))
    end
end

for fn in [:yearmonthday, :yearmonth, :monthday, :year, :month,
           :week, :day, :hour, :minute, :second, :millisecond,
           :dayofmonth, :dayofweek, :isleapyear, :daysinmonth,
           :daysinyear, :dayofyear, :dayname, :dayabbr,
           :dayofweekofmonth, :daysofweekinmonth, :monthname,
           :monthabbr, :quarterofyear, :dayofquarter
          ]
    @eval begin
        ($fn)(dt::LCL) = ($fn)(dt.value)
        ($fn)(dt::UT)  = ($fn)(dt.value)
        #($fn)(dt::UTC) = ($fn)(dt.value)
    end
end

for fn in [:firstdayofweek, :lastdayofweek,
           :firstdayofmonth, :lastdayofmonth, :firstdayofyear,
           :lastdayofyear, :firstdayofquarter, :lastdayofquarter
          ]
    @eval begin
        ($fn)(dt::LCL) = LCL(($fn)(dt.value))
        ($fn)(dt::UT)  = UT(($fn)(dt.value))
        #($fn)(dt::UTC) = ($fn)(dt.value)
    end
end


for fn in [:adjust, :tonext, :toprev, :tofirst, :tolast, :recur]
    @eval begin
      ($fn)(dt::LCL, args...) = UT(($fn)(dt.value, args...))
      ($fn)(dt::UT, args...)  = UT(($fn)(dt.value, args...))
    # ($fn)(dt::UTC, args...) = UT(($fn)(dt.value, args...))
    end
end

for U in [:LCL, :UT]
  @eval begin
    (-)(udt::($U), udt2::($U)) = (-)(udt.value, udt2.value)
    (-)(udt::($U), p::Period) = ($U)((-)(udt.value, p))
    (.-)(udt::($U), vec::Array{($U),1}) =
      [(-)(udt, i) for i in vec]
    (.-)(udt::($U), vec::Array{Period,1}) =
      [(-)(udt, i) for i in vec]
    (.-)(vec::Array{($U),1}, udt::($U)) =
      [(-)(i,udt) for i in vec]
    (.-)(vec::Array{($U),1}, p::Period) =
      [(-)(i,p) for i in vec]

   (+)(udt::($U), p::Period) = ($U)((+)(udt.value, p))
   (+)(p::Period, udt::($U)) = (+)(udt, p)
   (.+)(udt::($U), vec::Array{Period,1}) =
     [(+)(udt, i) for i in vec]
   (.+)(vec::Array{($U),1},p::Period) =
     [(+)(i, p) for i in vec]
  end
end



const ISOUniversalTimeFormat = DateFormat("yyyy-mm-ddTHH:MM:SS.sZ");
const ISOUnivCoordTimeFormat = DateFormat("yyyy-mm-dd HH:MM:SS.sZ");
const isoDateTimeFormat = DateFormat("yyyy-mm-dd HH:MM:SS.s");


function format(udt::UT, pattern::AbstractString, addUTC=true::Bool)
   s = format(udt.value, pattern)
end

format(udt::UT, fmt::Base.Dates.DateFormat) = format(udt.value, fmt)


function show(io::IO, dt::UT)
    dtm = dt.value
    str = string(string(dtm),"Z")
    # a = replace(a, "T", "𝘻") # using symbol
    print(io, str)
end

function show(io::IO, dt::LCL)
    dtm = dt.value
    secs = floor(Int64,Base.Dates.datetime2unix(dtm))
    utmofs = utm_offset(secs)
    hr = div(utmofs,3_600)
    mn = string(mod(utmofs,3_600))
    s,h = signbit(hr), string("0",string(abs(hr)))[end-1:end]
    m   = string("0",mn)[end-1:end]
    dtz = s ? string("-",h,":",m) : string("+",h,":",m)
    dtm = dt.value
    str = string(string(dtm),dtz)
    # a = replace(a, "T", "𝘻") # using symbol
    print(io, str)
end


# attempt to determine if this works with the local host
# Good reader, this is code to be avoided in almost any
# other circumstance; it three distinct ways, it intends
# to subvert the logic that makes this module sound.
#
function ok()
    ofs(dtm::UT) =
       UTime.lcl_offset(trunc(Int64,Dates.datetime2unix(dtm.value)))
    dofs(dtm1::UT,dtm2::UT)=
       fld(ofs(dtm1)-ofs(dtm2), 60)

    Jan1 = UT(DateTime(2000,1,1,0,0,0))
    Mar3 = UT(DateTime(2000,3,3,0,0,0))
    Jul1 = UT(DateTime(2000,7,1,0,0,0))
    Sep1 = UT(DateTime(2000,9,3,0,0,0))
    JanMar = dofs(Mar3,Jan1)
    JanJul = dofs(Jul1,Jan1)
    JanSep = dofs(Sep1,Jan1)
    MarJul = dofs(Jul1,Mar3)
    MarSep = dofs(Sep1,Mar3)
    JulSep = dofs(Sep1,Jul1)
    sumtest  = (JanMar+JanJul+JanSep+MarJul+MarSep+JulSep != 0)
    prodtest = (JanMar*JanJul*JanSep*MarJul*MarSep*JulSep == 0)
    sumtest & prodtest
end

end # module
