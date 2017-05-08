using VDIF

# vdif file
dataFile = "/mnt/disks/1/0/katherine/all_r2_666.vdif"

# open file
file_ = open(dataFile,"r")

# read first header
hdrSize = 32
pkt = readbytes(file_,hdrSize)
frameHdr = VDIF.VDIFFrameHeader()
VDIF.from_bin(frameHdr,pkt)

# close file
#close(file_)
