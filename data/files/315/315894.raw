export FT_Purge
export FT_PURGE_RX, FT_PURGE_TX

#Purge RX and TX Buffers (see FT_Purge) 
const FT_PURGE_RX = 1 
const FT_PURGE_TX = 2

function FT_Purge(ft_handle::Culong, mask::Integer)
  ft_status = ccall((:FT_Purge, d2xx),
                     Cuint,
                     (Culong, Cuint),
                     ft_handle, mask)
  checkstatus(ft_status)
  return nothing
end