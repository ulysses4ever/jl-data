
@compat abstract type WrappedDateTime<:AbstractTime end

immutable UT <: WrappedDateTime
    value::DateTime

    function UT(dt::DateTime)
        fsecs = Base.Dates.datetime2unix(dt)
        isecs = floor(Int64, fsecs)
        ofs   = lcl_offset(isecs)
        fsecs += ofs
        new(Base.Dates.unix2datetime(fsecs))
    end
    UT() = new(utm_unwrapped())
end


immutable LCL <: WrappedDateTime
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

gmt(dtm::DateTime) = UT(dtm)
gmt() = UT()
gmt(dtm::UT) = dtm
gmt(dtm::LCL) = UT(dtm.value)

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
