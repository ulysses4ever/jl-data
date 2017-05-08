module VKL

using Shannon

export vdp_t
export draw_data_points_uniform, draw_data_points_normal
export add_sample_to_data!
export p_by_counts, p_by_paper, p_by_decay
export get_avg

type vdp_t
  point::Vector{Float64}
  points::Matrix{Float64}
  n::Int64
end

function draw_data_points_uniform(n::Int64, dim::Int64)
  points = []
  for i=1:n
    v = vdp_t([rand() for i=1:dim], zeros(1,dim), 0)
    points = [points, v]
  end
  return points
end

function draw_data_points_normal(n::Int64, dim::Int64)
  points = []
  for i=1:n
    p = [-1.0, 2.0]
    while minimum(p) < 0.0 || maximum(p) > 1.0
      p = [randn() * 0.125 for i=1:dim] + [0.75, 0.25]
    end
    v = vdp_t(p, zeros(1,dim), 0)
    points = [points, v]
  end
  return points
end

function add_sample_to_data!(
  p::Vector{Float64}, data::Vector{vdp_t})
  m = sqrt(sum((p - data[1].point).^2))
  c = data[1]
  for d in data[2:end]
    t = sqrt(sum((p - d.point).^2))
    if t < m
      c = d
      m = t
    end
  end

  if c.points == zeros(1,length(c.point))
    for i=1:length(c.point)
      c.points[1,i] = p[1]
      c.n = 1
    end
  else
    c.points = vcat(c.points, p')
    c.n = c.n + 1
  end
end

fx(counts::Int64, N::Int64, dim::Int64)    = (counts > 0 ? (N / (counts * dim)) : 0)
p_by_counts(data::Vector{vdp_t}, N::Int64) = [d.n / N for d in data]
p_by_paper(data::Vector{vdp_t}, N::Int64)  = [fx(d.n, N, length(data)) for d in data]
function p_by_decay(data::Vector{vdp_t}, N::Int64)
  N = size(data)[1]
  n = sum([d.n for d in data])
  p = ones(N) ./ N
  i = 0
  index = 0
  for d in data
    index = index + 1
    for points in d.points
      i = i + 1
      diff = (1 - 1.0 / (1.0 + i)) * p[index]
      p[index] = p[index] - diff
      for j=1:N
        if j != index
          p[j] = p[j] + diff / (N-1)
        end
      end
    end
  end
  p
end

function get_avg(dimension::Int64, nr_of_data_points::Int64,
                             nr_of_samples::Int64, repeats::Int64)
  diffs = zeros(nr_of_samples, repeats)
  for i=1:repeats
    data = draw_data_points_uniform(nr_of_data_points, dimension)
    q = [1.0/length(data) for d in data]
    for j = 1:nr_of_samples
      point = rand(dimension)
      add_sample_to_data!(point , data)
      p = p_by_counts(data, j)
      diffs[j,i] = KL(p,q)
    end
  end
  println("Done with $dimension, $nr_of_data_points $nr_of_samples")
  mean(diffs,2)
end

function get_nr_of_required_samples(
  index::Int64, dimension::Int64, nr_of_data_points::Int64,
  nr_of_samples::Int64, repeats::Int64, limit::Float64)
  q = [1.0/length(data) for d in data]

  s = @parallel (+) for i=1:repeats
    data = draw_data_points_uniform(nr_of_data_points, dimension)
    r = nr_of_samples
    for j = 1:nr_of_samples
      point = rand(dimension)
      add_sample_to_data!(point , data)
      p = p_by_counts(data, j)
      diffs = KL(p,q)
      if j > 100
        if diff < limit
          r = j
          break
        end
      end
    end
    r
  end
  s = s / repeats
  writedlm("result_file_$index.txt", [dimension nr_of_data_points s])
  s
end

function calculate_avg_data()
  avg_data = []

  dimensions        = [50:10:200]
  nr_of_data_points = [200:100:8000]
  repeats           = 10
  sample_sizes      = [10000]

  n = length(dimensions) * length(nr_of_data_points) * length(sample_sizes)
  m = n * repeats

  println("Running $m experiments in total.")
  #= pm = Progress(n, 1) =#

  s = []
  for dim in dimensions
    for i in sample_sizes
      for j in nr_of_data_points
        s = [s, @spawn get_avg(dim, j, i, repeats)]
      end
    end
  end
  v = []
  for r in s
    d = fetch(r)
    #= next!(pm) =#
    if v == []
      v = d
    else
      v = hcat(v, d)
    end
  end

  writedlm("data/results_dim_$dim\_sample_sizes_$i.txt",v,',')
end

function calculate_avg_nr_of_required_samples(max::Int64, limit::Float64,
dimensions::Vector{Int64}, nr_of_data_points::Vector{Int64}, repeats::Int64)
  avg_data = []
  m = 0
  index = 0
  for j = 1:length(nr_of_data_points)
    for i = 1:length(dimensions)
      index = index + 1
      if isfile("result_file_$index.txt") == false
        m = m + 1
      end
    end
  end

  n = length(dimensions) * length(nr_of_data_points) - m
  println("Running $m experiments in total, skipped $n.")
  pm = Progress(m, 1)

  results = zeros(length(dimensions), length(nr_of_data_points))
  indices = zeros(length(dimensions) * length(nr_of_data_points), 2)
  pointers = []
  index = 0
  for j = 1:length(nr_of_data_points)
    for i = 1:length(dimensions)
      index = index + 1
      if isfile("result_file_$index.txt") == false
        dim = dimensions[i]
        nd = nr_of_data_points[j]
        r = get_nr_of_required_samples(index, dim, nd, max_sample_sizes, repeats, limit)
        results[i, j] = r
        next!(pm)
      end
    end
  end
  writedlm("required_samples.txt", results, ',')
end

function uniform_sampling!(
  data::Vector{vdp_t},
  N::Int64)
  dim = length(data[1].point)
  for i=1:N
    p = rand(dim)
    add_sample_to_data!(p, data)
  end
end

end # module
