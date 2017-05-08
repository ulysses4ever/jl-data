export FT_Read

function FT_Read(ft_handle::UInt32, bytestoread::Integer)
  buffer = Array(UInt8,bytestoread)
  bytesreturned = Ref{Cuint}()
  ft_status = ccall((:FT_Read, d2xx),
                      Cuint,
                      (Cuint, Ptr{UInt8}, Cuint, Ref{Cuint}),
                      ft_handle, buffer, bytestoread, bytesreturned)
  checkstatus(ft_status) 
  return (bytesreturned[], convert(ASCIIString,buffer[1:bytesreturned[]]))
end
