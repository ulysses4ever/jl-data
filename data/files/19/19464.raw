p_cstdout = unsafe_load(cglobal(:stdout, Ptr{Void}))

function Matrix_Read_Array{T<:Integer}(arr::Array{T, 2})
	nrow, ncol = size(arr)
	pmat = Matrix_Alloc(Cuint(nrow), Cuint(ncol))
	if nrow > 0 && ncol > 0
		m = unsafe_load(pmat)
		a = pointer_to_array(m.p_Init, length(arr))
		a[:] = arr'[:]
	end
	return pmat
end