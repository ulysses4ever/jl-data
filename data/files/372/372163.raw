export FT_Description, FT_SerialNumber, ft_openex

#Flags (see ft_openex)
const FT_OPEN_BY_SERIAL_NUMBER = 1
const FT_OPEN_BY_DESCRIPTION = 2
const FT_OPEN_BY_LOCATION = 4

immutable FT_Description 
  d :: Array{UInt8,1}
  function FT_Description(s :: ASCIIString)
    description = Array(UInt8,64)
    if length(s) < 64
      for (pos,character) in enumerate(s)
        description[pos] = Int(character)
      end
      description[length(s)+1] = 0
    else
      error("length(desctiption) must be < 64")
    end
    new(description)
  end
end

immutable FT_SerialNumber 
  sn :: Array{UInt8,1}
  function FT_SerialNumber(s :: ASCIIString)
    serialnumber = Array(UInt8,16)
    if length(s) < 16
      for (pos,character) in enumerate(s)
        serialnumber[pos] = Int(character)
      end
      serialnumber[length(s)+1] = 0
    else
      error("length(serialnumber) must be < 16")
    end
    new(serialnumber)
  end
end

function ft_openex(location :: Unsigned)
  ft_handle = Ref{Culong}()
  ft_status = ccall((:FT_OpenEx, d2xx),
                      Cuint,
                      (Cuint,Cuint,Ref{Culong}),
                      location,FT_OPEN_BY_LOCATION,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end

function ft_openex(serialnumber :: FT_SerialNumber)
  ft_handle = Ref{Culong}()
  ft_status = ccall((:FT_OpenEx, d2xx),
                      Cuint,
                      (Ptr{UInt8},Cuint,Ref{Culong}),
                      serialnumber.sn,FT_OPEN_BY_SERIAL_NUMBER,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end

function ft_openex(description :: FT_Description)
  ft_handle = Ref{Culong}()
  ft_status = ccall((:FT_OpenEx, d2xx),
                      Cuint,
                      (Ptr{UInt8},Cuint,Ref{Culong}),
                      description.d,FT_OPEN_BY_DESCRIPTION,ft_handle)
  checkstatus(ft_status)
  return ft_handle[]
end