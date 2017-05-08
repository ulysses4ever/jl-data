using PersistentArrays
using Base.Test

default_array = PersistentArray(4)
default_array[2] = 3.5

@test version(default_array) == 1

commit!(default_array)
@test version(default_array) == 2

# println("$(default_array.data), $(typeof(default_array[1]))")
@test default_array[1] == 0.0
@test default_array[2] == 3.5

default_array[2] = 2.5
commit!(default_array)
@test version(default_array) == 3

@test default_array[:] == [0.0, 2.5, 0.0, 0.0]
# println("$(typeof(default_array))")
# for i in 0:version(default_array)
#    println("Array v$(i) state: $(lookup(default_array, i, :))")
# end
@test lookup(default_array, 1, :) == [0.0, 3.5, 0.0, 0.0]
