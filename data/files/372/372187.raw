export ft_setchars

function ft_setchars(ft_handle::Culong, eventch::UInt8, eventchen::Bool,
                                        errorch::UInt8, errorchen::Bool)
  if eventchen
    eventcharacterenable = 0x01
  else
    eventcharacterenable = 0x00
  end
  if errorchen
    errorcharacterenable = 0x01
  else
    errorcharacterenable = 0x00
  end
  ft_status = ccall((:FT_SetChars, d2xx),
                     Cuint,
                     (Culong, Cuchar, Cuchar, Cuchar, Cuchar),
                     ft_handle, eventch, eventcharacterenable, errorch, errorcharacterenable)
  checkstatus(ft_status)
  return nothing
end