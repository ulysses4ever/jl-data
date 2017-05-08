# Wrap aio API

typealias aio_context Ptr{Void}

function aio_init(pin::UInt32)
  return ccall( (:mraa_aio_init, libmraa), aio_context, (Cuint,), pin )
end

function aio_read(aio::aio_context)
  return ccall( (:mraa_aio_read, libmraa), Cint, (aio_context,), aio )
end

function aio_read_float(aio::aio_context)
  return ccall( (:mraa_aio_read_float, libmraa), Cfloat, (aio_context,), aio )
end

function aio_close(aio::aio_context)
  return Result(ccall( (:mraa_aio_close, libmraa), Cint, (aio_context,), aio ))
end

function aio_set_bit(aio::aio_context,bits::Int32)
  return Result(ccall( (:mraa_aio_set_bit, libmraa), Cint, (aio_context,Cint), aio, bits ))
end

function aio_get_bit(aio::aio_context)
  return ccall( (:mraa_aio_get_bit, libmraa), Cint, (aio_context,), aio )
end
