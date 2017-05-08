input_1 = """
          30 1 0 120
          50 1 150 90
          60 1 60 90
          70 1 180 180
          90 1 180 60
          """
input_2 = """
        30 1 350 350
        180 1 10 100
        35 1 67 23
        31 1 30 4
        32 1 50 7
        """
input = input_1
type Disk
  speed::Int
  openings::Set{Int}
  function Disk(s::Int, o::Vector{(Int,Int)})
    opens = Set{Int}()
    for (start,length) in o
      for i in start:(start + length)
        push!(opens,i % 360)
      end
    end
    new(s,opens)
  end
end

function first_range!(numbers)
  start = numbers[1]
  stop = shift!(numbers)
  while !isempty(numbers) && stop + 1 == numbers[1]
    stop = shift!(numbers)
  end
  return start:stop
end

function Base.show(io::IO, disk::Disk)
  print(io,"Disk: $(disk.speed)\n\t")
  numbers = sort!([o for o in disk.openings])
  ranges = Any[]
  while !isempty(numbers)
   push!(ranges, first_range!(numbers))
  end
  println(io,ranges)
end

lines = split(input,"\n")
disks = Disk[]
for line in lines
  if line == ""
    continue
  end
  nums = [int(n) for n in split(line)]
  speed = shift!(nums)
  num_openings = shift!(nums)
  openings = (Int,Int)[]
  for i in 1:num_openings
    push!(openings, (shift!(nums),shift!(nums)))
  end
  push!(disks, Disk(speed, openings))
end

# Each argument is vector of Set{Int}, one Set per disk.
function allows_light(ds...)
  !isempty(intersect(ds...))
end

# Advance the disk by one second.
function advance!(disk::Disk)
  next_set = Set{Int}()
  for n in disk.openings
    m = n + disk.speed # advance by one second
    push!(next_set, m % 360)
  end
  disk.openings = next_set
end  

found_light = -1
for i = 1:(360*5)
  if allows_light([disk.openings for disk in disks]...)
    found_light = i - 1
    break
  end
  for disk in disks
    advance!(disk)
  end
end

if found_light == -1
  println("none")
else
  println(found_light)
end
