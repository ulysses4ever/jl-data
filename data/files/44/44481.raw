using VDIF

# vdif files
dataFile = "/h/snowy0/EHT/data/all_r2_666.vdif"
newDataFile = "/h/snowy0/EHT/data/all_r2_666_new.vdif"

# open file
file_ = open(dataFile,"r")

# read first header
println("reading first header")
hdrSize = 32 / 4 # in 8 B chunks
hdrWords = VDIF.readwords(file_,int(hdrSize))
frameHdr = VDIF.VDIFFrameHeader();
VDIF.from_bin!(frameHdr,hdrWords)

# read first frame
println("reading first frame")
seek(file_,0)
words = VDIF.readwords(file_,frameHdr.frameLength  * 2)
frame = VDIF.VDIFFrame();
VDIF.from_bin!(frame,words)

# construct word array from header
myHdrWords = VDIF.to_bin(frameHdr)

# construct word array from first frame
myWords = VDIF.to_bin(frame);

# close file
close(file_)

# write new file 
println("writing new file")
file_ = open(newDataFile,"w")
for word in myWords
  write(file_,word)
end
close(file_)

# open the file and check data
file_ = open(newDataFile,"r")

# read first header
hdrSize = 32 / 4 # in 8 B chunks
w = VDIF.readwords(file_,int(hdrSize))
myframeHdr = VDIF.VDIFFrameHeader();
VDIF.from_bin!(myframeHdr,w)

# read first frame
seek(file_,0)
w = VDIF.readwords(file_,myframeHdr.frameLength  * 2)
myFrame = VDIF.VDIFFrame();
VDIF.from_bin!(myFrame,words)

close(file_)
