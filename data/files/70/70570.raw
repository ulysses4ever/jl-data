# Julia Types

type ModInt{n} <: Integer
  k::Int
  ModInt(k) = new(mod(k,n))
end

# Create an instance of the new type
a = ModInt{11}(2012)

# Create addition dispatch rule
+{n}(a::ModInt{n}, b::ModInt{n}) = ModInt{n}(a.k+b.k)

# Create subtraction dispatch rule
-{n}(a::ModInt{n}, b::ModInt{n}) = ModInt{n}(a.k-b.k)

