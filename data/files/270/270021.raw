reload("genspd.jl")
reload("genband.jl")
reload("genba.jl")

function get_timings(A,B,C,M,nitr::Int64)
  tchol,tca,tsim = 0.0,0.0,0.0,0.0
  for i = 1:nitr
    tchol += @elapsed TallSkinnyQR.CBQR!(A,B,C,M)
    tsim  += @elapsed TallSkinnyQR.SCBQR!(A,B,C,M)
    tca   += @elapsed TallSkinnyQR.SCBQRT!(A,B,C,M)
  end
  return [tchol'/nitr;tsim'/nitr;tca'/nitr]
end

function get_orthres(A,B,C,M,nitr::Int64,chol::Bool)
  m,n = size(A)
  if chol
    orth = zeros(3)
    res = zeros(3)
  else
    orth = zeros(2)
    res = zeros(2)
  end
  A2 = copy(sdata(A))
  nrmA = norm(A2)
  for i = 1:nitr
    if chol
      A = convert(SharedArray,A2)
      R = TallSkinnyQR.CBQR!(A,B,C,M)
      res[3],orth[3] = norm(A2-A*R)/nrmA, norm(A'*(B'+triu(B,1))*A-eye(n,n))
    end

    A = convert(SharedArray,A2)
    R = TallSkinnyQR.SCBQR!(A,B,C,M)
    res[1],orth[1] = norm(A2-A*R)/nrmA, norm(A'*(B'+triu(B,1))*A-eye(n,n))

    A = convert(SharedArray,A2)
    R = TallSkinnyQR.SCBQRT!(A,B,C,M)
    res[2],orth[2] = norm(A2-A*R)/nrmA, norm(A'*(B'+triu(B,1))*A-eye(n,n))
  end
  return res,orth
end


function compile_things()
  A = convert(SharedArray,randn(1000,10))
  C = convert(SharedArray,randn(1000,10))
  B = spgenspd(1000,0.01)
  M = zeros(10,10)
  TallSkinnyQR.CBQR!(A,B,C,M)
  TallSkinnyQR.SCBQRT!(A,B,C,M)
  TallSkinnyQR.SCBQR!(A,B,C,M)
end

function make_acm(m,n)
  A = convert(SharedArray,randn(m,n))
  C = convert(SharedArray,zeros(m,n))
  M = zeros(n,n)
  return A,C,M
end

compile_things()
