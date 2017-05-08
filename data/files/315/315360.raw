export ft_close

function ft_close(ft_handle :: Culong)
  ft_status = ccall((:FT_Close, d2xx),
                      Cuint,
                      (Culong,),
                      ft_handle)
  checkstatus(ft_status)
  return nothing
end
