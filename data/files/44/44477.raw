module VDIF

function readwords!(s::IO, w::AbstractArray{Uint32}, nw=length(w))
  # 1 word == 4 Bytes
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

function readwords(s::IO, nw=typemax(Uint32))
  # read up to nw words from s, return a vector{Uint32} of words read.
  #w = Array(Uint32, nw == typemax(Int) ? 1024 : nw)
  w = Array(Uint32, nw)
  nr = readwords!(s, w, nw)
  resize!(w, nr)
end

type VDIFFrameHeader
  # size:  72 bytes

  sampleRate

  # word 0
  invalidData::Bool
  legacyMode::Bool
  secsSinceEpoch::Uint32

  # word 1
  refEpoch::Uint32
  dataFrame::Uint32

  # word 2
  vdifVers::Uint32
  log2Chans::Uint32
  frameLength   # in units of 8 Bytes

  # word 3
  isComplex::Bool
  bitsPerSample::Uint32
  threadId::Uint32
  stationId::Uint32

  # words 4-7
  eudVers::Uint32
  eud::AbstractArray{Uint32,1}

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
  Uint32[0,0,0,0])

type VDIFFrame
  header::VDIFFrameHeader
  data::AbstractArray
end

# constructor
VDIFFrame() = VDIFFrame(VDIFFrameHeader(),[])

function from_bin!(inst::VDIFFrameHeader,words::AbstractArray{Uint32})
  # Convert word array to VDIF frame header

  # word 0
  inst.invalidData = bool((words[1] >> 31) & 0x1)
  inst.legacyMode = bool((words[1] >> 30) & 0x1)
  inst.secsSinceEpoch = (words[1] & 0x3fffffff)

  # word 1
  inst.refEpoch = ((words[2] >> 24) & 0x3f)
  inst.dataFrame = (words[2] & 0xffffff)

  # word 2
  inst.vdifVers = ((words[3] >> 29) & 0x7)
  inst.log2Chans = ((words[3] >> 24) & 0x1f)
  inst.frameLength = ((words[3] & 0xffffff))

  # word 3
  inst.isComplex = bool((words[4] >> 31) & 0x1)
  inst.bitsPerSample = (1 + ((words[4] >> 26) & 0x1f))
  inst.threadId = ((words[4] >> 16) & 0x3ff)
  inst.stationId = (words[4] & 0xffff)

  if ~inst.legacyMode
    # words 4-7
    inst.eudVers = ((words[5] >> 24) & 0xff)
    inst.eud[1] = words[5] & 0xffffff
    inst.eud[2:end] = words[6:8]
  end

  return inst
end


function from_bin!(inst::VDIFFrame,words::AbstractArray{Uint32})
  # Convert word array to VDIF frame (header + data)

  # construct header
  from_bin!(inst.header,words)

  # convert binary data to array of Int32 type (save memory by parametrizing this?)

  # find out where the data start and end in binary frame
  dataStart = inst.header.legacyMode ? 16 : 32 # in bytes
  dataStop  = inst.header.frameLength * 8
  dataSize  = dataStop - dataStart # in bytes
  dataWords = dataSize / 4    # in words
  headerWords = dataStart / 4 # in words

  # create empy data buffer
  sampPerWord = 32 / inst.header.bitsPerSample
  inst.data = zeros(Int32, int(sampPerWord * dataWords))

  # interpret the data given our bits-per-sample
  sampMax = int(2^inst.header.bitsPerSample - 1)
  for wordN = 1:dataWords
    for sampN = 1:sampPerWord
      shiftBy = int(inst.header.bitsPerSample * (sampN - 1))
      foo = (words[headerWords + wordN] >> shiftBy) & sampMax
      # interpret as offset binary
      inst.data[sampN + (wordN-1) * sampPerWord] =  foo - 2^(inst.header.bitsPerSample - 1)
    end
  end

  return inst
end

function to_bin(inst::VDIFFrameHeader)
  # Construct word array from VDIF frame header

  words = Uint32[]

  # word 0
  append!(words,[uint32(((inst.invalidData & 0x1) << 31) +
                        ((inst.legacyMode & 0x1) << 30) +
                        (inst.secsSinceEpoch & 0x3fffffff))])

  # word 1
  append!(words, [uint32(((inst.refEpoch & 0x3f) << 24) + 
                         (inst.dataFrame & 0xffffff))])

  # word 2
  append!(words, [uint32(((inst.vdifVers & 0x7) << 29) +
                         ((inst.log2Chans & 0x1f) << 24) + 
                         (inst.frameLength & 0xffffff))])

  # word 3
  append!(words, [uint32(((inst.isComplex & 0x1) << 31) +
                         (((inst.bitsPerSample-1) & 0x1f) << 26) + 
                         ((inst.threadId & 0x3ff) << 16) +
                         (inst.stationId & 0xffff))])

  if ~inst.legacyMode
    # words 4-7
    append!(words,[uint32(((inst.eudVers & 0xff) << 24) + 
                   (inst.eud[1] & 0xffffff))])
    append!(words,[uint32(inst.eud[2] & 0xffffffff)])
    append!(words,[uint32(inst.eud[3] & 0xffffffff)])
    append!(words,[uint32(inst.eud[4] & 0xffffffff)])
  end

  return words
end

function to_bin(inst::VDIFFrame)

  # Construct word array from VDIF frame

  # header first
  words = to_bin(inst.header)

  # find out where the data start and end in binary frame
  dataStart = inst.header.legacyMode ? 16 : 32 # in bytes
  dataStop  = inst.header.frameLength * 8
  dataSize  = dataStop - dataStart # in bytes
  dataWords = dataSize / 4    # in words
  headerWords = dataStart / 4 # in words

  # reinterpret data given our bits-per-sample
  sampMax = 2^inst.header.bitsPerSample - 1
  sampPerWord = int(32 / inst.header.bitsPerSample)

  for wordN=0:dataWords-1
    word = 0x00000000
    for sampN = 1:sampPerWord
      samp = inst.data[wordN * sampPerWord + sampN]
      # reinterpret sample as offset-binary
      samp = (samp + 2^(inst.header.bitsPerSample-1)) & sampMax
      # add the sample data to the word
      shiftBy = uint32(inst.header.bitsPerSample * (sampN-1))
      word += uint32(samp << shiftBy)
    end

    # append to word array
    append!(words,[word])
  end


  return words

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

function check(file_::IOStream)
  using Dates
  # time check
  println("start time:")
  println("stop time:")
end

end

