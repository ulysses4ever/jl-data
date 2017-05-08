module Collatz
# using Debug
export slow_finder, fast_finder, make_chain, collatz_chain

function collatz(n::Int64)
	if iseven(n)
		div(n,2)
	else
	   3n + 1
   end
end

function make_chain(start_num :: Int64, memo :: Dict{Int64, Int64})
   n = start_num
   chain = [n]
   
   while n != 1
      if !haskey(memo, n)
         println("memo doesn't have $n, but contains $memo")
      end
      # @assert(haskey(memo, n), "memo doesn't have key $n, but contains $memo")
      # assert(haskey(memo, n))
      
      n = memo[n]
      push!(chain, n)
   end
   return chain
end

function collatz_chain(start_num :: Int64, memo :: Dict{Int64, Int64})
   
   n = collatz(start_num)
   memo[start_num] = n
   chain = [start_num, n]
   for i in 1:typemax(Int64)
      if n == 1
         return chain
      end
      m = collatz(n)
      if haskey(memo, n)
         return [chain, make_chain(m, memo)]
      end
      memo[n] = m
      n = m
      push!(chain, n)
   end
   return chain
end

function slow_collatz_chain(start_num :: Int64)
   n = collatz(start_num)
   chain = [start_num, n]
   for i in 1:typemax(Int64)
      if n == 1
         return chain
      end
      n = collatz(n)
      push!(chain, n)
   end
   return chain
end

function slow_collatz_chain_length(start_num :: Int64)
   n = collatz(start_num)
   chain_len = 0
   for i in 1:typemax(Int64)
      if n == 1
         return chain_len
      end
      n = collatz(n)
      chain_len += 1
   end
   return chain_len
end


function slow_finder(max::Int64)
   max_len = 0
   first_num = 0
   for i = 1:max
      chain_len = slow_collatz_chain_length(i)
      if chain_len > max_len
         max_len = chain_len
         first_num = i
      end
   end
   return first_num, max_len
end

# NOTE: never updated fast finder, so this is actually much slower than slow_finder
# and not needed
function fast_finder(max::Int64)
   memo = Dict{Int64, Int64}()
   sizehint(memo, 2200000)
   max_len = 0
   max_chain = Int64[]
   for i = 1:max
      chain = collatz_chain(i, memo)
      len = length(chain)
      if len > max_len
         max_len = len
         max_chain = chain
      end
   end
   return max_chain
end

end
 # @time fast_finder(1000000)