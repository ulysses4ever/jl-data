# Wrap gpio API

typealias gpio_context Ptr{Void}

function gpio_init(pin::Int32)
    return ccall( (:mraa_gpio_init, libmraa), gpio_context, (Cint,), pin )
end

function gpio_init_raw(pin::Int32)
    return ccall( (:mraa_gpio_init_raw, libmraa), gpio_context, (Cint,), pin )
end

function gpio_edge_mode(gpio::gpio_context,mode::GpioEdge)
  return Result(ccall( (:mraa_gpio_edge_mode, libmraa), Cint, (gpio_context,Cint),
    gpio, mode ))
end

#--- TODO ---#
# mraa_result_t mraa_gpio_isr 	( 	mraa_gpio_context  	dev,		mraa_gpio_edge_t  	edge,		void(*)(void *)  	fptr,		void *  	args 	)
# mraa_result_t mraa_gpio_isr_exit 	( 	mraa_gpio_context  	dev	)

function gpio_mode(gpio::gpio_context, mode::GpioMode)
  return Result(ccall( (:mraa_gpio_mode, libmraa), Cint, (gpio_context,Cint),
    gpio, mode ))
end

function gpio_dir(gpio::gpio_context, dir::GpioDir)
  return Result(ccall( (:mraa_gpio_dir, libmraa), Cint, (gpio_context,Cint), gpio, dir ))
end

function gpio_read_dir(gpio::gpio_context)
  dir = Ref{Cint}()
  succ = Result(ccall( (:mraa_gpio_read_dir, libmraa), Cint, (gpio_context,Ptr{Cint}),
    gpio, dir ))
  succ != mraa.SUCCESS && (display(succ); error("Error calling mraa_gpio_read_dir."))
  return GpioDir(dir[])
end

function gpio_close(gpio::gpio_context)
  return Result(ccall( (:mraa_gpio_close, libmraa), Cint, (gpio_context,), gpio ))
end

function gpio_read(gpio::gpio_context)
  return ccall( (:mraa_gpio_read, libmraa), Cint, (gpio_context,), gpio )
end

function gpio_write(gpio::gpio_context, val::Int32)
  return Result(ccall( (:mraa_gpio_write, libmraa), Cint, (gpio_context,Cint), gpio, val ))
end

function gpio_owner(gpio::gpio_context, owner::Bool)
  return Result(ccall( (:mraa_gpio_owner, libmraa), Cint, (gpio_context,Cint),
    gpio, Cint(owner) ))
end

function gpio_use_mmaped(gpio::gpio_context, ismmap::Bool)
  return Result(ccall( (:mraa_gpio_use_mmaped, libmraa), Cint, (gpio_context,Cint),
    gpio, Cint(ismmap) ))
end

function gpio_get_pin(gpio::gpio_context)
  return ccall( (:mraa_gpio_get_pin, libmraa), Cint, (gpio_context,), gpio )
end

function gpio_get_pin_raw(gpio::gpio_context)
  return ccall( (:mraa_gpio_get_pin_raw, libmraa), Cint, (gpio_context,), gpio )
end
