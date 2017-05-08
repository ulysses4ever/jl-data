export ft_setdatacharacteristics
export FT_BITS_8, FT_BITS_7, FT_STOP_BITS_1, FT_STOP_BITS_2
export FT_PARITY_NONE, FT_PARITY_ODD, FT_PARITY_EVEN, FT_PARITY_MARK
export FT_PARITY_SPACE

#Word Length (see ft_setdatacharacteristics) 
const FT_BITS_8 = 8 
const FT_BITS_7 = 7

#Stop Bits (see ft_setdatacharacteristics) 
const FT_STOP_BITS_1 = 0 
const FT_STOP_BITS_2 = 2

#Parity (see ft_setdatacharacteristics) 
const FT_PARITY_NONE = 0 
const FT_PARITY_ODD = 1 
const FT_PARITY_EVEN = 2 
const FT_PARITY_MARK = 3 
const FT_PARITY_SPACE = 4

function ft_setdatacharacteristics(ft_handle::Culong, 
                                   wordlength::Integer,
                                   stopbits::Integer,
                                   parity::Integer)
  @assert (wordlength==FT_BITS_8) || (wordlength==FT_BITS_7) "invalid word length"
  @assert (stopbits==FT_STOP_BITS_1) || (stopbits==FT_STOP_BITS_2) "invalid stop bits"
  @assert parity == FT_PARITY_NONE || parity == FT_PARITY_ODD ||
          parity == FT_PARITY_EVEN || parity == FT_PARITY_MARK ||
          parity == FT_PARITY_SPACE "invalid parity"
  ft_status = ccall((:FT_SetDataCharacteristics, d2xx),
                     Cuint,
                     (Culong, Cuchar, Cuchar, Cuchar),
                     ft_handle, wordlength, stopbits, parity)
  checkstatus(ft_status)
  return nothing
end