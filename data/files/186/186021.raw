import Base: reverse

export split2, split4, split8, bitcat

splitfn(S, T) =
  :($(symbol(string("split", sizeof(S)÷sizeof(T))))(x::$S) =
      ($([:((x >> $(8sizeof(T)*(i-1))) % $T) for i = (sizeof(S)÷sizeof(T)):-1:1]...),))

function bitcatfn(S, T)
  xs = [symbol(string("x", i)) for i = 1:sizeof(T)÷sizeof(S)]
  :(bitcat($([:($x::$S) for x in xs]...)) =
      |($([:($T($(xs[i])) << $(8sizeof(S)*(length(xs)-i))) for i = 1:length(xs)]...)))
end

revfn(T) =
  sizeof(T) == 1 ? :(reverse(x::$T) = x) :
  :(reverse(x::$T) =
      |($([:((x >> $(8(sizeof(T)-2i+1))) & $(T(0xff)<<8(i-1))) for i = 1:sizeof(T)÷2]...),
        $([:((x << $(8(sizeof(T)-2i+1))) & $(T(0xff)<<8(sizeof(T)-i))) for i = 1:sizeof(T)÷2]...)))

function bittwiddles(Ts)
  for i = 1:length(Ts), j = 1:i-1
    splitfn(Ts[i], Ts[j]) |> eval
    bitcatfn(Ts[j], Ts[i]) |> eval
  end
  for T in Ts
    revfn(T) |> eval
  end
end

[UInt8, UInt16, UInt32, UInt64, UInt128] |> bittwiddles
[Int8, Int16, Int32, Int64, Int128] |> bittwiddles
