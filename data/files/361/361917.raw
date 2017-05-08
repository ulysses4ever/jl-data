#using HDF5, JLD
using MsgPack
# using PyCall
# using PyPlot
using Gadfly
using DataFrames
using SQLite

blas_set_num_threads(1)

function load_data(conn, job)
    job = "job_"*job
    res = query(conn, "select dims,numdata,map_energy,map_kld,post_kld from $job")
    blobs = map(x->MsgPack.unpack(x), query(conn, "select data from $job")[1])
    return res,blobs
end

conn = SQLiteDB(expanduser("~/largeresearch/results.db"))

#=res,blobs = load_data(conn, "1238af45d12f650387dbb7899950901c26cb6f6b")=#
res,blobs = load_data(conn, "ca2cb624c23a64289f728570fa6c77108de40669")

y = DataFrame(res.values)
names!(y, map(symbol, res.colnames))
y[:diff] = y[:map_kld] - y[:post_kld]

myp = plot(y, x=:numdata, y=:diff, 
  yintercept=[0.0], 
  Geom.point, 
  Geom.smooth, 
  Guide.xlabel("Number of training samples"),
  Guide.ylabel("MAP KLD - Posterior KLD"),
  Geom.hline(color="gray", size=1mm), 
  Theme(default_point_size=0.3mm, highlight_width=0.0mm, line_width=0.8mm))

draw(PDF("map_vs_post_kld2.pdf", 12cm, 8cm), myp)


#=ymean = aggregate(y, :numdata, x->mean(convert(Vector{Float64},x)))=#
#=ystd = aggregate(y, :numdata, x->std(convert(Vector{Float64},x)))=#

function filterNull(df, col)
  da = DataArray(df)
  res = DataFrame()
  for (i,name) in enumerate(names(df))
    res[name] = Array(eltypes(df)[i],0)
  end
  for i in 1:size(df,1)
    if df[col][i] != NULL
      push!(res, da[i,:])
    end
  end
  res
end

function process2D(res)
  resdf = DataFrame()
  resdf[:ss] = Int[x["stepscale"] for x in res[2]]
  resdf[:beta] = Float64[x["beta"] for x in res[2]]
  resdf[:post_kld] = res[1][3]
  resdf = filterNull(resdf, :post_kld)
  resdf
end

function make_image(df, col1, col2, f)
  pts1 = df[col1] |> unique |> sort
  pts2 = df[col2] |> unique |> sort
  m,n = map(length, (pts1,pts2))
  img = zeros(m,n)
  dict = Dict{Any,Float64}()
  for i=1:m, j=1:n
    img[i,j] = f(df[(df[col1].==pts1[i]) & (df[col2].==pts2[j]),:])
    dict[pts1[i],pts2[j]] = img[i,j]
  end
  img,dict
end

# res2df = process2D(res2d)
#
# mimg,mdict = make_image(res2df, :ss, :beta, x->mean(x[:post_kld]))
# simg,sdict = make_image(res2df, :ss, :beta, x->std(x[:post_kld]))
# figure()
# imshow(img, interpolation="None", origin="lower")
# xlabel("Beta")
# ylabel("Stepscale")
# colorbar()

function plot_cum(blobs, crit)
  for blob in blobs
    if crit(blob)
      plot(blob["cum_kld"])
    end
  end
end

function plot_thetas(blobs, crit)
  for blob in blobs
    if crit(blob)
      plot(blob["grid"], blob["thetas"])
    end
  end
end

function show_exp(res)
  x = res[1]
  y = DataFrame(x.values)
  names!(y, map(symbol,x.colnames))
  @show aggregate(y,:dims,x->mean_and_std(convert(Vector{Float64},x)))
  @show aggregate(y,:dims,x->sem(convert(Vector{Float64},x)))
  @show aggregate(y,:dims,x->variation(convert(Vector{Float64},x)))
end

#=show_exp(res_mh_fix)=#
#=show_exp(res_mhc_fix)=#
