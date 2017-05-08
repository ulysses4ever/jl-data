export FT_EE_UASize

function FT_EE_UASize(ft_handle::UInt32)
  eesize = Ref{Cuint}()
  ft_status = ccall((:FT_EE_UASize, d2xx),
                     Cuint,
                     (Cuint, Ref{Cuint}),
                     ft_handle, eesize)
  checkstatus(ft_status)
  return convert(Int32,eesize[])
end