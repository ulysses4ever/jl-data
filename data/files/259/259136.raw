typealias gpio_context Ptr{Void}

@enum(gpio_dir_t,
  GPIO_OUT = 0,
  GPIO_IN = 1,
  GPIO_OUT_HIGH = 2,
  GPIO_OUT_LOW = 3
)

function gpio_init(pin::Int)
    return ccall( (:mraa_gpio_init, libmraa), gpio_context, (Cint,), pin )
end

function gpio_dir(gpio::gpio_context, dir::gpio_dir_t)
  return Result(ccall( (:mraa_gpio_dir, libmraa), Cint, (gpio_context,Cint), gpio, dir ))
end

function gpio_write(gpio::gpio_context, val::Cint)
  return Result(ccall( (:mraa_gpio_write, libmraa), Cint, (gpio_context,Cint), gpio, val ))
end

function gpio_read(gpio::gpio_context)
  return ccall( (:mraa_gpio_read, libmraa), Cint, (gpio_context,), gpio )
end

function gpio_close(gpio::gpio_context)
  return Result(ccall( (:mraa_gpio_close, libmraa), Cint, (gpio_context,), gpio ))
end
