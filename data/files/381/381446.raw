module TinyG

using JSON,
      SerialPorts

const versions = Dict("master" => "440.20",
                      "master-candidate" => 
                      "edge" => "449.01")

abstract AbstractTinyGDevice

immutable TinyGDevice{T} <: AbstractTinyGDevice
    port::T
end



function init(s::TinyGDevice)

end

@doc """
Download the latest release versions of TinyG firmware. This will get all
available branches, currently 'master' and 'edge'.
"""
function download_firmware()
    for k in keys(versions)
        download_firmware(k)
    end
end

@doc """
Download the latest release versions for either 'master' or 'edge'.
"""
function download_firmware(v::String)
    m = Pkg.dir("TinyG","deps","firmware",v)
    if !isdir(m)
        mkpath(m)
    end
    hex = "tinyg-$v-$(versions[v]).hex"
    url = "http://synthetos.github.io/binaries/$hex"
    download(url, joinpath(m,hex))
end

function upload_firmware(branch, path, port, hex)
    run(`avrdude -p x192a3 -c avr109 -b 115200 -P $port -U flash:w:$hex`)
end

@doc """

"""
function parse_tinyg_output(line::String)

end

"""
[fb]  firmware build            380.08
[fv]  firmware version            0.96
[hv]  hardware version            8.00
[id]  TinyG ID                    2X2660-FNZ
[ja]  junction acceleration  100000 mm
[ct]  chordal tolerance           0.001 mm
[st]  switch type                 0 [0=NO,1=NC]
[mt]  motor disble timeout       60 Sec
[ej]  enable json mode            0 [0=text,1=JSON]
[jv]  json verbosity              4 [0=silent,1=footer,2=messages,3=configs,4=linenum,5=verbose]
[tv]  text verbosity              0 [0=silent,1=verbose]
[qv]  queue report verbosity      0 [0=off,1=filtered,2=verbose]
[sv]  status report verbosity     1 [0=off,1=filtered,2=verbose]
[si]  status interval           250 ms
[ic]  ignore CR or LF on RX       0 [0=off,1=CR,2=LF]
[ec]  expand LF to CRLF on TX     0 [0=off,1=on]
[ee]  enable echo                 0 [0=off,1=on]
[ex]  enable flow control         1 [0=off,1=XON/XOFF, 2=RTS/CTS]
[baud] USB baud rate              5 [1=9600,2=19200,3=38400,4=57600,5=115200,6=230400]
[gpl] default gcode plane         0 [0=G17,1=G18,2=G19]
[gun] default gcode units mode    1 [0=G20,1=G21]
[gco] default gcode coord system  1 [1-6 (G54-G59)]
[gpa] default gcode path control  2 [0=G61,1=G61.1,2=G64]
[gdi] default gcode distance mode 0 [0=G90,1=G91]
[1ma] m1 map to axis              0 [0=X,1=Y,2=Z...]
[1sa] m1 step angle               1.800 deg
[1tr] m1 travel per revolution   40.000 mm
[1mi] m1 microsteps               4 [1,2,4,8]
[1po] m1 polarity                 1 [0=normal,1=reverse]
[1pm] m1 power management         0 [0=remain powered,1=shut off when idle]
[2ma] m2 map to axis              1 [0=X,1=Y,2=Z...]
[2sa] m2 step angle               1.800 deg
[2tr] m2 travel per revolution   40.000 mm
[2mi] m2 microsteps               4 [1,2,4,8]
[2po] m2 polarity                 0 [0=normal,1=reverse]
[2pm] m2 power management         0 [0=remain powered,1=shut off when idle]
[3ma] m3 map to axis              2 [0=X,1=Y,2=Z...]
[3sa] m3 step angle               1.800 deg
[3tr] m3 travel per revolution    1.250 mm
[3mi] m3 microsteps               4 [1,2,4,8]
[3po] m3 polarity                 0 [0=normal,1=reverse]
[3pm] m3 power management         0 [0=remain powered,1=shut off when idle]
[4ma] m4 map to axis              1 [0=X,1=Y,2=Z...]
[4sa] m4 step angle               1.800 deg
[4tr] m4 travel per revolution   40.000 mm
[4mi] m4 microsteps               4 [1,2,4,8]
[4po] m4 polarity                 0 [0=normal,1=reverse]
[4pm] m4 power management         1 [0=remain powered,1=shut off when idle]
[xam] x axis mode                 1 [standard]
[xvm] x velocity maximum        600.000 mm/min
[xfr] x feedrate maximum        600.000 mm/min
[xtm] x travel maximum          150.000 mm
[xjm] x jerk maximum       20000000 mm/min^3
[xjh] x jerk homing        20000000 mm/min^3
[xjd] x junction deviation        0.0500 mm (larger is faster)
[xsn] x switch min                1 [0=off,1=homing,2=limit,3=limit+homing]
[xsx] x switch max                0 [0=off,1=homing,2=limit,3=limit+homing]
[xsv] x search velocity         500.000 mm/min
[xlv] x latch velocity          100.000 mm/min
[xlb] x latch backoff             2.000 mm
[xzb] x zero backoff              1.000 mm
[yam] y axis mode                 1 [standard]
[yvm] y velocity maximum        600.000 mm/min
[yfr] y feedrate maximum        600.000 mm/min
[ytm] y travel maximum          150.000 mm
[yjm] y jerk maximum       20000000 mm/min^3
[yjh] y jerk homing        20000000 mm/min^3
[yjd] y junction deviation        0.0500 mm (larger is faster)
[ysn] y switch min                1 [0=off,1=homing,2=limit,3=limit+homing]
[ysx] y switch max                0 [0=off,1=homing,2=limit,3=limit+homing]
[ysv] y search velocity         500.000 mm/min
[ylv] y latch velocity          100.000 mm/min
[ylb] y latch backoff             2.000 mm
[yzb] y zero backoff              1.000 mm
[zam] z axis mode                 1 [standard]
[zvm] z velocity maximum        600.000 mm/min
[zfr] z feedrate maximum        600.000 mm/min
[ztm] z travel maximum           75.000 mm
[zjm] z jerk maximum       20000000 mm/min^3
[zjh] z jerk homing        20000000 mm/min^3
[zjd] z junction deviation        0.0500 mm (larger is faster)
[zsn] z switch min                0 [0=off,1=homing,2=limit,3=limit+homing]
[zsx] z switch max                1 [0=off,1=homing,2=limit,3=limit+homing]
[zsv] z search velocity         400.000 mm/min
[zlv] z latch velocity          100.000 mm/min
[zlb] z latch backoff             2.000 mm
[zzb] z zero backoff              1.000 mm
[aam] a axis mode                 3 [radius]
[avm] a velocity maximum     172800.000 deg/min
[afr] a feedrate maximum     172800.000 deg/min
[atm] a travel maximum           -1.000 deg
[ajm] a jerk maximum     5760000000 deg/min^3
[ajh] a jerk homing      5760000000 mm/min^3
[ajd] a junction deviation        0.0500 deg (larger is faster)
[ara] a radius value              0.1989 deg
[asn] a switch min                1 [0=off,1=homing,2=limit,3=limit+homing]
[asx] a switch max                0 [0=off,1=homing,2=limit,3=limit+homing]
[asv] a search velocity         600.000 deg/min
[alv] a latch velocity          100.000 deg/min
[alb] a latch backoff             5.000 deg
[azb] a zero backoff              2.000 deg
[bam] b axis mode                 0 [disabled]
[bvm] b velocity maximum       3600.000 deg/min
[bfr] b feedrate maximum       3600.000 deg/min
[btm] b travel maximum           -1.000 deg
[bjm] b jerk maximum       20000000 deg/min^3
[bjd] b junction deviation        0.0500 deg (larger is faster)
[bra] b radius value              1.0000 deg
[cam] c axis mode                 0 [disabled]
[cvm] c velocity maximum       3600.000 deg/min
[cfr] c feedrate maximum       3600.000 deg/min
[ctm] c travel maximum           -1.000 deg
[cjm] c jerk maximum       20000000 deg/min^3
[cjd] c junction deviation        0.0500 deg (larger is faster)
[cra] c radius value              1.0000 deg
[p1frq] pwm frequency          2500.000 Hz
[p1csl] pwm cw speed lo        5500.000 RPM
[p1csh] pwm cw speed hi       12000.000 RPM
[p1cpl] pwm cw phase lo           0.080 [0..1]
[p1cph] pwm cw phase hi           0.900 [0..1]
[p1wsl] pwm ccw speed lo       1000.000 RPM
[p1wsh] pwm ccw speed hi       2000.000 RPM
[p1wpl] pwm ccw phase lo          0.125 [0..1]
[p1wph] pwm ccw phase hi          0.200 [0..1]
[p1pof] pwm phase off             0.000 [0..1]
[g54x] g54 x offset               0.000 mm
[g54y] g54 y offset               0.000 mm
[g54z] g54 z offset               0.000 mm
[g54a] g54 a offset               0.000 deg
[g54b] g54 b offset               0.000 deg
[g54c] g54 c offset               0.000 deg
[g55x] g55 x offset              75.000 mm
[g55y] g55 y offset              75.000 mm
[g55z] g55 z offset               0.000 mm
[g55a] g55 a offset               0.000 deg
[g55b] g55 b offset               0.000 deg
[g55c] g55 c offset               0.000 deg
[g56x] g56 x offset               0.000 mm
[g56y] g56 y offset               0.000 mm
[g56z] g56 z offset               0.000 mm
[g56a] g56 a offset               0.000 deg
[g56b] g56 b offset               0.000 deg
[g56c] g56 c offset               0.000 deg
[g57x] g57 x offset               0.000 mm
[g57y] g57 y offset               0.000 mm
[g57z] g57 z offset               0.000 mm
[g57a] g57 a offset               0.000 deg
[g57b] g57 b offset               0.000 deg
[g57c] g57 c offset               0.000 deg
[g58x] g58 x offset               0.000 mm
[g58y] g58 y offset               0.000 mm
[g58z] g58 z offset               0.000 mm
[g58a] g58 a offset               0.000 deg
[g58b] g58 b offset               0.000 deg
[g58c] g58 c offset               0.000 deg
[g59x] g59 x offset               0.000 mm
[g59y] g59 y offset               0.000 mm
[g59z] g59 z offset               0.000 mm
[g59a] g59 a offset               0.000 deg
[g59b] g59 b offset               0.000 deg
[g59c] g59 c offset               0.000 deg
[g92x] g92 x offset               0.000 mm
[g92y] g92 y offset               0.000 mm
[g92z] g92 z offset               0.000 mm
[g92a] g92 a offset               0.000 deg
[g92b] g92 b offset               0.000 deg
[g92c] g92 c offset               0.000 deg
[g28x] g28 x location             0.000 mm
[g28y] g28 y location             0.000 mm
[g28z] g28 z location             0.000 mm
[g28a] g28 a location             0.000 deg
[g28b] g28 b location             0.000 deg
[g28c] g28 c location             0.000 deg
[g30x] g30 x location             0.000 mm
[g30y] g30 y location             0.000 mm
[g30z] g30 z location             0.000 mm
[g30a] g30 a location             0.000 deg
[g30b] g30 b location             0.000 deg
[g30c] g30 c location             0.000 deg
"""

end # module
