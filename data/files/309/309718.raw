# include helper functions
include("stft.jl")
include("istft.jl")
include("solver_irls.jl")
include("convmtx.jl")

function alg_mclp_derev(xRev, refMic, tau, Lg, nFFT, nShift, winType, myeps, itMax, itTol, p)
  # An algorithm for multiple-input single-output (MISO).
  # Dereverberation is based by maximizing sparsity of the output STFT
  # coefficients. Processing is performed in each frequency bin
  # independently.
  #
  # INPUT
  #   xRev       : signals on microphones, each column corresponds to
  #                     one microphone
  #   refMic     : reference microphone
  #   tau        : prediction delay in frames (equal for all frequencies) or a set of delays
  #                (individual value for each of the bins).
  #                [2]
  #   Lg         : order of regression filters (equal for all frequencies)
  #                or a set of orders of regression filters
  #                (individual value for each of the bins)
  #                [default=20, equal for all freq. bins]
  #   nFFT       : frame length (in samples)
  #                [1024]
  #   nShift     : frame shift (in samples)
  #                [256]
  #   winType    : window type for the STFT
  #                ['hamming']
  #   myeps      : lower bound for estimation of variance,
  #                small positive constant to avoid zero division
  #                [1e-8]
  #   itMax      : maximal number of iterations
  #                [10]
  #   itTol      : tolerance on relative change of the estimate
  #                [1e-4]
  #   p          : parameter for updating weights/variances, corresponds
  #                to ell_p norm that is used as the objective function
  #                for the desired speech signal
  #
  # OUTPUT
  #   d          : estimated desired speech signal
  #   D          : STFT of the estimated desired speech signal
  #
  # Author: Zichao Wang
  # Date  : Aug 4, 2015

  # number of microphones
  M = convert(Int, size(xRev,2))

  #STFT transform
  #X = spectrogram(xRev[:,1], convert(Int, nFFT), convert(Int, nShift); window=winType)
  X_temp = mySTFT(xRev[:,1], nFFT, nShift)
  K = convert(Int, size(X_temp,1)) # number of freq bins
  N = convert(Int, size(X_temp,2)) # number of time frames
  X = zeros(K,N,M)+im*zeros(K,N,M) # initialize STFT matrix
  for m = 1:M
    X[:,:,m] = mySTFT(xRev[:,m], nFFT, nShift) # using hamming window, defined in stft.jl
  end

  # prediction delay
  # DID NOT implement numerical check here
  tau = tau .* ones(K,1)
  Lg  = Lg  .* ones(K,1)

  # initialize estimated speech signal in STFT domain
  D = zeros(K,N) + im*zeros(K,N)

  # dereverberation
  # for each frequency bin
  for k = 1:K

    # reference signal
    xref = X[k,1:N,refMic] # DID NOT implement squeeze function here
    xref = xref[:]

    # build the convolution matrix
    XX = zeros(N, M.*convert(Int, Lg[k])) + im*zeros(N, M.*convert(Int, Lg[k]))
    for m=1:M # M is the number of microphones
        # construct the conv matrix for each mic
        tmp = convmtx( [ zeros(convert(Int, tau[k]), 1) ; X[k,:,m].' ] , convert(Int, Lg[k]) ); # DID NOT implement squeeze function here
        tmp = tmp[1:N,:];
        # assign the conv matrix for each micr to the proper columns in the collected conv matrix XX
        XX[ 1:N , (m-1).*convert(Int,Lg[k])+1 : m.*convert(Int,Lg[k]) ] = tmp;
    end

    # IRLS solver
    gk = solver_irls(xref,XX,p,xref,itMax,itTol,myeps,k)
    D[k,:] = xref - XX*gk

  end

  # ISTFT
  d = myISTFT(D, nFFT, nShift) # using hamming window, defined in stft.jl

  return d, D
  # return D
end
