export FT_EE_UASize

function FT_EE_UASize(ft_handle::UInt32)
  eesize = Ref{Culong}()
  ft_status = ccall((:FT_EE_UASize, "ftd2xx.dll"),
                     Culong,
                     (Culong, Ref{Culong}),
                     ft_handle, eesize)
  checkstatus(ft_status)
  return convert(Int32,eesize[])
end