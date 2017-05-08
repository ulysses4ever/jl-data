type sift_feature
	descriptor::Ptr{Float32}
	x::Float32
	y::Float32
	octave::Int32
	level::Int32
	scale::Float64
	angle::Float64
end

type SiftFeature
	descriptor::Array{Float32}
	x::Float32
	y::Float32
	octave::Int32
	level::Int32
	scale::Float64
	angle::Float64

  SiftFeature(f::sift_feature) = new(
    pointer_to_array(f.descriptor, (128,)),
    f.x, f.y, f.octave, f.level, f.scale, f.angle)
end

function simple_ccv_read(filename::String)
  image = ccall(
    (:simple_ccv_read, "libsimpleccv"),
    Ptr{Void},
    (Ptr{Uint8},),
    filename);
  finalizer(image, x -> ccall((:ccv_matrix_free, "libsimpleccv"), Void, (Ptr{Void},), x))
  image
end

function simple_ccv_sift(image::Ptr{Void})
  n_ptr = Array(Int32, 1)
  features = ccall(
    (:simple_ccv_sift, "libsimpleccv"),
    Ptr{sift_feature},
    (Ptr{Void}, Ptr{Int32}),
    image,
    n_ptr);

  if features == C_NULL
    error("Couldn't allocate sift feature array")
  end

  finalizer(features, x -> ccall((:ccv_matrix_free, "libsimpleccv"), Void, (Ptr{Void},), x))

  n = int64(n_ptr[1])
  result = Array(SiftFeature, n)
  for i = 1:n
    f = unsafe_ref(features + (i-1) * sizeof(sift_feature))
    result[i] = SiftFeature(f)
  end
  result
end

image = simple_ccv_read("/home/vagrant/dev/julia/test.png")
features = simple_ccv_sift(image)
println(features)
