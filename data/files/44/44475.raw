module VDIF

function readwords!(s::IO, w::AbstractArray{Uint32}, nw=length(w))
  olw = lw = length(w)
  nr = 0
  while nr < nw && !eof(s)
    a = read(s, Uint32)
    nr += 1
    if nr > lw
      lw = nr * 2
      resize!(w, lw)
    end
    w[nr] = a
  end
  if lw > olw
   resize!(w, nr) # shrink to just contain input data if was resized
  end
  return nr
end

function readwords(s::IO, nw=typemax(Int))
  # read up to nw words from s, return a vector{Uint32} of words read.
  w = Array(Uint32, nw == typemax(Int) ? 1024 : nw)
  nr = readwords!(s, w, nw)
  resize!(w, nr)
end

type VDIFFrameHeader

  sampleRate

  # word 0
  invalidData
  legacyMode
  secsSinceEpoch

  # word 1
  refEpoch
  dataFrame

  # word 2
  vdifVers
  log2Chans
  frameLength

  # word 3
  isComplex
  bitsPerSample
  threadId
  stationId

  # words 4-7
  eudVers
  eud

end

# outer constructor for header
VDIFFrameHeader() = VDIFFrameHeader(
  4096e6,
  false,
  false,
  0,
  0,
  0,
  0,
  0,
  0,
  false,
  0,
  0,
  0,
  0,
  [0,0,0,0])

type VDIFFrame
  header::VDIFFrameHeader
  data
end

# constructor
VDIFFrame() = VDIFFrame(VDIFFrameHeader(),[])

function from_bin(inst::VDIFFrameHeader,words::AbstractArray{Uint32})
  # Convert byte array pkt to VDIF Frame header type

  # construct 4 byte words
  #words = zeros(Uint32,4)
  #for i=1:4  
  #  word = 0
  #  for j=1:4
  #    word += uint32( pkt[j + 4*(i-1)] ) <<  (8*(j-1))
  #  end
  #  words[i] = word
  #end

  # word 0
  inst.invalidData = bool((words[1] >> 31) & 0x1)
  inst.legacyMode = bool((words[1] >> 30) & 0x1)
  inst.secsSinceEpoch = int(words[1] & 0x3fffffff)

  # word 1
  inst.refEpoch = int((words[2] >> 24) & 0x3f)
  inst.dataFrame = int(words[2] & 0xffffff)

  # word 2
  inst.vdifVers = int((words[3] >> 29) & 0x7)
  inst.log2Chans = int((words[3] >> 24) & 0x1f)
  inst.frameLength = int((words[3] & 0xffffff))

  # word 3
  inst.isComplex = bool((words[4] >> 31) & 0x1)
  inst.bitsPerSample = int(1 + ((words[4] >> 26) & 0x1f))
  inst.threadId = int((words[4] >> 16) & 0x3ff)
  inst.stationId = int(words[4] & 0xffff)

  if ~inst.legacyMode
    # words 4-7
    inst.eudVers = int((words[5] >> 24) & 0xff)
    inst.eud[1] = words[5] & 0xffffff
    inst.eud[2:end] = words[6:end]
  end

  return inst
end

function datetime(inst::VDIFFrameHeader)
  # how many words per frame
  headerSize = (inst.legacyMode ? 2 : 4) 
  dataWords = 2 * (inst.frameLength - headerSize)

  # now how many time samples per frame
  sampPerWord = 32 / inst.bitsPerSample
  tsampPerWord = sampPerWord / (int(inst.isComplex) + 1)
  tsampPerFrame = tsampPerWord * dataWords

  # how many us per frame
  usPerFrame = 1e6 * (tsamp_per_frame / inst.sampleRate)
  
  # get the date
  date = DateTime(2000 + inst.refEpoch/2, 
           1 + (inst.refEpoch & 1) * 6,
           1)

  # get seconds from start of day
  secs = inst.secsSinceEpoch

  # get the microseconds from the second
  #off = end ? usecs_per_frame : 0.
  #usecs = usecsPerFrame * dataFrame + off
  println("datetime does not deal with end of VDIF properly")
  usecs = usecsPerFrame

  return date + secs + usecs
end

function from_bin(inst::VDIFFrame,words::AbstractArray{Uint32})
  # find out where the data start and end in binary frame
  dataStart = int.header.legacyMode ? 16 : 32
  dataStop  = inst.header.frameLength * 8
  dataSize  = dataStop - dataStart # in bytes
  dataWords = dataSize / 4
  headerWords = dataStart / 4

  # create empy data buffer
  sampPerWord = 32 / inst.header.bitsPerSample
  inst.data = zeros(Uint32, sampPerWord * dataWords)

  # interpret the data given our bits-per-sample
  sampMax = 2^inst.header.bitsPerSample - 1
  for wordN = 1:dataWords
    for sampN = 1:sampPerWord
      shiftBy = inst.header.bitsPerSample * (sampN - 1)
      foo = (words[headerWords + wordN] >> shift_by) & sampMax
      # interpret as offset binary
      inst.data[sampN + (wordN-1) * sampPerWord] =  foo - 2^(inst.bitsPerSample - 1)
    end
  end

  return inst
end

function check(file_::IOStream)
  using Dates
  # time check
  println("start time:")
  println("stop time:")
end

end

