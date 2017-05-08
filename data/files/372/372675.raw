# check if FTD2XX function library is in 
# src directory.  If not get correct driver
# from FTDI website

function haveftd2xx()
  @windows? isfile("ftd2xx.dll"):false
end

function getftd2xx()
  function putdriverhere()
    (path,line) = functionloc("FTD2XX.haveftd2xx")
    (dir,file) = splitdir(path)
    return dir
  end
  function win()
    using ZipFile
    driver = download("http://www.ftdichip.com/Drivers/CDM/CDM v2.12.06 WHQL Certified.zip")
    r = ZipFile.Reader(driver)
    indexofdll = findfirst(x->x.name=="i386/ftd2xx.dll",r.files)
    uncompressedsize = r.files[indexofdll].uncompressedsize
    dllbytearray = Array(UInt8,uncompressedsize)
    read(r.files[indexofdll],dllbytearray)
    io = open(joinparts(putdriverhere(),"ftd2xx.dll"),"w")
    write(io,dllbytearray)
    close(io)
  end
  @windows? win() : nothing
end

#=
if ~haveftd2xx()
  println("Downloading driver from FTDI")
  getftd2xx()
end
=#