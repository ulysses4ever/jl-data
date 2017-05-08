export ft_getlibraryversion

function ft_getlibraryversion()
  dllversion = Ref{Cuint}()
  ft_status = ccall((:FT_GetLibraryVersion, d2xx),Cuint,(Ref{Cuint},),dllversion)
  checkstatus(ft_status)
  build = (dllversion[] & 0x000000ff)
  minor = (dllversion[] & 0x0000ff00)>>8
  major = (dllversion[] & 0x00ff0000)>>16
  return VersionNumber(major,minor,build)
end