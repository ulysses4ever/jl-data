using VDIF

ifile   = "/h/snowy0/EHT/data/all_r2_666.vdif"
ofile   = "/h/snowy0/EHT/data/out.vdif"
hdrSize = 32 # bytes
benchmarks = ("from_bin","resample",)

# get file info
file_ = open(ifile,"r")
hdr = VDIF.VDIFFrameHeader();
VDIF.from_bin!(hdr,VDIF.readwords(file_,8))
close(file_)
fileSize = filesize(ifile) # in bytes

# figure out frame size in bytes
frameSize = 8 * hdr.frameLength

# figure out number of sampler per frame
samplesPerFrame = int(8 * (8 * hdr.frameLength - hdrSize) / hdr.bitsPerSample)

# benchmark IO
if ("IO" in benchmarks)
  println("benchmarking binary I/O")
  ifile_ = open(ifile,"r")
  ofile_ = open(ofile,"w")
  bytesPerFrame = hdr.frameLength * 8
  seek(ifile_,0)
  tic()
  while ~eof(ifile_)
    words = VDIF.readwords(ifile_,hdr.frameLength * 2)
    write(ofile_,words)
  end
  t = toc()
  close(ifile_)
  close(ofile_)
  @printf "speed was %0.2fMBps\n" fileSize * 1e-6 / t
  # 60MBps reading 8 byte chunks.
  # 670MBps for cp
end

# benchmark from_bin (package)
if ("from_bin" in benchmarks)
  println("benchmarking from_bin")
  ifile_ = open(ifile,"r")
  frame = VDIF.VDIFFrame()
  t,frameN = 0,0
  while (frameN < 100) && (~eof(ifile_))
    words = VDIF.readwords(ifile_,hdr.frameLength * 2)
    t0 = time_ns()
    VDIF.from_bin!(frame,words)
    t1 = time_ns()
    t += (t1 - t0)/1e9
    frameN += 1
  end
  @printf "speed was %0.2fMBps\n" frameSize * frameN * 1e-6 / t
  close(ifile_)
  # 0.4MBps
end

# benchmark to_bin (quantize)
if ("to_bin" in benchmarks)
  println("benchmarking to_bin")
  ifile_ = open(ifile,"r")
  frame = VDIF.VDIFFrame()
  t,frameN = 0,0
  while (frameN < 100) && (~eof(ifile_))
    words = VDIF.readwords(ifile_,hdr.frameLength * 2)
    VDIF.from_bin!(frame,words)
    t0 = time_ns()
    w = VDIF.to_bin(frame)
    t1 = time_ns()
    t += (t1 - t0)/1e9
    frameN += 1
  end
  @printf "speed was %0.2fMBps" frameSize * frameN * 1e-6 / t
  close(ifile_)
  # 0.5MBps
end

# benchmark resample
if ("resample" in benchmarks)
  include("resample.jl")
  println("benchmarking resample")
  ifile_ = open(ifile,"r")
  frame = VDIF.VDIFFrame()
  t,frameN = 0,0
  sampleI,sampleF = 4096,1248
  # cycles per frame
  cyclesPerFrame = int(samplesPerFrame / sampleI)
  d1 = Array(Complex64,sampleF)
  while (frameN < 100) && (~eof(ifile_))
    words = VDIF.readwords(ifile_,hdr.frameLength * 2)
    VDIF.from_bin!(frame,words)
    t0 = time_ns()
    d1 = resample(frame.data,int(sampleF * cyclesPerFrame))
    t1 = time_ns()
    t += (t1 - t0)/1e9
    frameN += 1
  end
  @printf "speed was %0.2fMBps\n" frameSize * frameN * 1e-6 / t
  close(ifile_)
  # 3.2MBps
end
