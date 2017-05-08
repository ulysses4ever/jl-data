include("ODESolver.jl")

cd(dirname(@__FILE__))

module XaosHash
  using ODESolver
  export xaos256

  const TIME_TAKEN = 16.0
  const TIME_INTERVAL = 2.0^-4
  const γNUM   = 256

  saw = (t) -> t/(2*π) - floor(t/(2*π))-0.5

  modedPopov = (γ) -> ( (t,y) -> [y[2],γ*saw(y[3])+y[1]-y[1]^7-0.1*y[2],1] )

  osilff = γ -> (x,y,t) -> RK4(modedPopov(γ),
                          [x,y,t], 0.0, TIME_TAKEN, TIME_INTERVAL)[2:4,end]

  γs = linspace(4+(1.0/64.0),8,γNUM)

  osilfs = map(osilff, γs)

  sigB = (x) -> ((uint64(round(abs(significand(x) * 2^52))) >>> 40) & 0x01)

  vix = (b) -> b/256.0
  viy = (b) -> 4.5 * (b/256.0)

  v = (b) -> b/32.0
  u = (x,b) -> (x > 0.0) ? (x - b) : (x + b)

  function pad(ℓ::BigInt)
    p = Array(Uint8,64)
    for i in 1:64
      p[65-i] = (ℓ >>> ((i-1)*8)) & 0xff
    end
    return p
  end


  function xaos256(s)
    s = map(uint8,collect(s))
    s = [s,pad(BigInt(length(s)) * 8 + 512)]

    xs = Array(Float64, γNUM)
    ys = Array(Float64, γNUM)
    ts = Array(Float64, γNUM)

    xsn = Array(Float64, γNUM)
    ysn = Array(Float64, γNUM)

    x = vix(s[1])
    y = viy(s[2])

    @simd for i = 1:γNUM
      @inbounds xs[i],ys[i],ts[i] = osilfs[i](x,y,0.0)
    end

    for j = 3:length(s)
      @simd for i = 1:γNUM
        @inbounds xsn[((i+131) % 256) + 1],ysn[((i+157) % 256) + 1],ts[i] = osilfs[i](
                      xs[i],u(ys[i],v(s[j])),ts[i])
        if ts[i] > 2*π
          ts[i] -= 2*π
        end
      end
      xs = xsn
      ys = ysn
    end
    retv = BigInt(0)
    for i = 1:γNUM
      retv = (retv << (i==1 ? 0 : 1)) + sigB(ys[i])
    end
    return retv
  end
end

using XaosHash

begin
  strs = ["", "a", "b", "aa", "ab", "ba", "bb",
          "Съешь же ещё этих мягких французских булок да выпей чаю",
          "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890",
          "The quick brown fox jumps over the lazy dog",
          "The quick brown fox jumps over the lazy doh",
          "She quick brown fox jumps over the lazy dog",
          "The quick brown fox iumps over the lazy dog",
          "The quick brown fox jumps over the lazy dog."]
  hashvs = map(xaos256, strs)
  open("XaosOutputs.tex","w") do io
    for i in 1:length(strs)
      print(io,@sprintf("\"%s\"\n%#064x\n\n",strs[i], hashvs[i]))
    end
  end
end

include("ChaosPRNG.jl")
using ChaosPRNG

function bi256toBits(h::BigInt)
  zs = Bool[]
  zs = fill(false, 256)
  for i in 0:255
    zs[i+1] = (((h >>> i) & 0x01) == 1)
  end
  zs
end

begin
  zs = Bool[]
  for count in 0x00:0x4E
    append!(zs, bi256toBits(xaos256([count])))
  end
  zs = zs[1:20000]
  monobitsTest(zs)
  pokerTest(zs)
  runsTest(zs)
end
