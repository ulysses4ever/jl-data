export FT_Close

function FT_Close(ft_handle :: UInt32)
  ft_status = ccall((:FT_Close, d2xx),
                      Cuint,
                      (Cuint,),
                      ft_handle)
  checkstatus(ft_status)
  return nothing
end