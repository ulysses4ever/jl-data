module Punycoder
base = 36
tmin = 1
tmax = 26
skew = 38
damp = 700
initial_bias = 72
initial_n = 128
code_points = ['a':'z';'0':'9']

function getbasicstring(str)
  return join([isascii(c) ? c : "" for c in str])
end

function adapt(delta, numpoints, firsttime)
  delta = if firsttime
    div(delta, damp)
  else
    div(delta, 2)
  end
  delta += div(delta, numpoints)
  k = 0
  while delta > div((base - tmin) * tmax, 2)
    delta = div(delta, base - tmin)
    k += base
  end # while
  return k + div((base - tmin + 1) * delta, delta + skew)
end

function encode(input)
  n, delta, bias = initial_n, 0, initial_bias
  encoded_string = getbasicstring(input)
  inputLength = length(input)
  h = b = length(encoded_string)
  if h != inputLength
    encoded_string *= "-"
  end # if
  while h < inputLength
    m = input[findfirst(x->!isascii(x) && x >= n, input)]
    delta += Int(m - n) * (h + 1)
    n = m
    for c in input
      if c < n
        delta += 1
      elseif c == n
        q = delta
        for k in base:base:10000000
          t = if k <= bias
                tmin
              elseif k >= bias + tmax
                tmax
              else
                k - bias
              end # if
          if q < t
            break
          end
          encoded_string = string(encoded_string, code_points[t + 1 + ((q - t) % (base - t))])
          q = div((q - t), (base - t))
        end # for
        encoded_string = string(encoded_string, code_points[q + 1])
        bias = adapt(delta, h + 1, h == b)
        delta = 0
        h += 1
      end # if
    end # for
    delta += 1
    n += 1
  end # while
  return encoded_string
end # function

function decode(input)
  n, i, bias = initial_n, 0, initial_bias
  input_parts = split(input, '-')
  output = collect(input_parts[1])
  input = collect(input_parts[end])

  while length(input) > 0
    oldi, w = i, 1
    for k in base:base:10000000
      digit = findfirst(code_points, input[1]) - 1
      i += digit * w
      t = if k <= bias
            tmin
          elseif k >= bias + tmax
            tmax
          else
            k - bias
          end # if
      if digit < t
        break
      end # if
      w *= base - t
      input = input[2:end]
    end # for
    bias = adapt(i - oldi, length(output) + 1, oldi == 0)
    n += div(i, length(output) + 1)
    i = i % (length(output) + 1)
    if i == 0
      splice!(output, 1, [n, output[1]])
    else
      splice!(output, i, [output[i], n])
    end
    i += 1
    input = input[2:end]
  end # while
  return join(output)
end # function

end # module
