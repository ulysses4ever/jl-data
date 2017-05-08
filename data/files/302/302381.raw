
module Fractals

export burning_ship, mandelbrot

macro real_iters(c, recur)
  quote
    const max_iter = 1000.0
    const bailout = 1e10
    local r = 0.0
    local z = $c 
    for i in 1:max_iter
      z = $recur
      if abs2(z) > bailout ^ 2
        r = i - log2(log(abs(z)) * (1 / log(bailout)))
        break;
      end
    end
    r
  end
end

function mandelbrot(z1, z2)
  c = z1 + z2 * im
  @real_iters(c, (z^2 + c))
end

function burning_ship(z1, z2)
  c = z1 + z2 * im
  @real_iters(c, (abs(real(z)) + im * abs(imag(z)))^2 + c)
end

function nova(z1, z2)
  const p = 3
  const r = 1.2
  c = z1 + z2 * im
  @real_iters(c, z - r *(z^p - 1)/(p*z^(p-1))+ c)
end


end
