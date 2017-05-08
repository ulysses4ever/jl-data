using VDIF

# vdif file
#dataFile = "/mnt/disks/1/0/katherine/all_r2_666.vdif"
dataFile = "/h/snowy0/EHT/data/all_r2_666.vdif"

# open file
file_ = open(dataFile,"r")

# read first header
hdrSize = 32 / 4 # in 8 B chunks
hdrWords = VDIF.readwords(file_,int(hdrSize))
frameHdr = VDIF.VDIFFrameHeader();
VDIF.from_bin(frameHdr,hdrWords)

# read first frame
seek(file_,0)
words = VDIF.readwords(file_,frameHdr.frameLength  * 2)
frame = VDIF.VDIFFrame();
VDIF.from_bin(frame,words)

# close file
#close(file_)
