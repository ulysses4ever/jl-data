using PersistentArrays
using Base.Test

default_array = PersistentArray(4)
default_array[2] = 3.5

@test version(default_array) == 1

commit!(default_array)
@test version(default_array) == 2

@test default_array[1] == 0.0
@test default_array[2] == 3.5

default_array[2] = 2.5
commit!(default_array)
@test version(default_array) == 3

@test default_array[:] == [0.0, 2.5, 0.0, 0.0]
@test lookup(default_array, 1, :) == [0.0, 3.5, 0.0, 0.0]

# Test that we can still overwrite previous version of indices if necessary
update!(default_array, 4.5, 1, 2)
@test lookup(default_array, 1, :) == [0.0, 4.5, 0.0, 0.0]

# Run show
show(default_array)

# Check that everying still works for more than 1 dimension
ndim_array = PersistentArray(3,2)
ndim_array[1,1] = 3.5
commit!(ndim_array)

tmp_array = zeros(3,2)
tmp_array[1,1] = 3.5
@test ndim_array[:,:] == tmp_array

commit!(ndim_array)

# Check that regular array assignments also still work
tmp_array[1,:] = ones(2)
ndim_array[1,:] = ones(2)

@test ndim_array[:,:] == tmp_array
@test lookup(ndim_array, 1, :,:) != tmp_array[:,:]

# Check that size still works
@test size(ndim_array) == (3,2)
@test size(ndim_array, 1) == 3

println(ndim_array)

# Check that sub works
sub_array = sub(ndim_array, 1:2, :)
sub_tmp_array = sub(tmp_array, 1:2, :)
println(sub_array)
println(sub_tmp_array)
@test sub_array[1,1] == sub_tmp_array[1,1]
