export FT_SetChars

function FT_SetChars(ft_handle::UInt32, eventch::UInt8, eventchen::Bool,
                                        errorch::UInt8, errorchen::Bool)
  if eventchen
    event = 0x01
  else
    event = 0x00
  end
  if errorchen
    error = 0x01
  else
    error = 0x00
  end
  ft_status = ccall((:FT_SetChars, d2xx),
                     Cuint,
                     (Cuint, Cuchar, Cuchar, Cuchar, Cuchar),
                     ft_handle, eventch, event, errorch, error)
  checkstatus(ft_status)
  return nothing
end