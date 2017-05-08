export ft_purge
export FT_PURGE_RX, FT_PURGE_TX

#Purge RX and TX Buffers (see ft_purge) 
const FT_PURGE_RX = 1 
const FT_PURGE_TX = 2

function ft_purge(ft_handle::Culong, mask::Integer)
  ft_status = ccall((:FT_Purge, d2xx),
                     Cuint,
                     (Culong, Cuint),
                     ft_handle, mask)
  checkstatus(ft_status)
  return nothing
end