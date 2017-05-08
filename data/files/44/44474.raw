module VDIF

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

function from_bin(inst::VDIFFrameHeader,pkt)
  # Convert byte array pkt to VDIF Frame header type

  # construct 4 byte words
  words = zeros(Uint32,4)
  for i=1:4  
    word = 0
    for j=1:4
      word += uint32( pkt[j + 4*(i-1)] ) <<  (8*(j-1))
    end
    words[i] = word
  end

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
    # parse extended user data
    words = zeros(Uint32,4)
    for i=1:4  
      word = 0
      for j=1:4
        word += uint32( pkt[j + 16] ) <<  (8*(j-1))
      end
      words[i] = word
    end

    # words 4-7
    inst.eudVers = int((words[1] >> 24) & 0xff)
    inst.eud[1] = words[1] & 0xffffff
    inst.eud[2:end] = words[2:end]
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
end

function check(file_::IOStream)
  using Dates
  # time check
  println("start time:")
  println("stop time:")
end

end

