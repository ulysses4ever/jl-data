using PyCall, PyPlot, Mamba

function chains2Ani(
  sim::Mamba.Chains,
  a::AbstractString="beta_spectrum.1",
  b::AbstractString="beta_spectrum.2",
  outfile::AbstractString="out.mp4"
)

  ind_a = findfirst(sim.names,a)
  ind_b = findfirst(sim.names,b)

  samps_a = sim[:,ind_a,1].value
  samps_b = sim[:,ind_b,1].value

  max_a = maximum(samps_a)
  min_a = minimum(samps_a)

  max_b = maximum(samps_b)
  min_b = minimum(samps_b)

  @pyimport matplotlib.animation as anim# First set up the figure, the axis, and the plot element we want to animate
  fig = figure()

  samples = size(sim)[1]

  global x_width = (min_a, max_a)
  global y_width = (min_b, max_b)
  samples_width = (0, samples)

  ax3 = fig[:add_subplot](223, xlim=x_width, ylim=y_width)
  ax1 = fig[:add_subplot](221, xlim=x_width, ylim=samples_width,sharex=ax3)
  ax2 = fig[:add_subplot](224, xlim=samples_width, ylim=y_width,sharey=ax3)

  subplots_adjust(hspace=0.0)

  line1, = ax1[:plot]([], [], lw=1)
  line2, = ax2[:plot]([], [], lw=1)
  line3, = ax3[:plot]([], [], "o", lw=2, alpha=.1)
  line4, = ax3[:plot]([], [], lw=1, alpha=.3)
  line5, = ax3[:plot]([], [], "k", lw=1)
  line6, = ax3[:plot]([], [], "k", lw=1)
  #ax1[:set_xticklabels]([])
  #ax2[:set_yticklabels]([])
  global lines = [line1, line2, line3, line4, line5, line6]

  function init()
    global lines
    for line in lines
      line[:set_data]([], [])
    end
    return lines
  end

  function animate(i)
      i = i+1

      global lines
      global x_width
      global y_width

      lines[1][:set_data](samps_a[1:i], 0:i-1)
      lines[2][:set_data](0:i-1,samps_b[1:i])
      lines[3][:set_data](samps_a[1:i], samps_b[1:i])
      lines[4][:set_data](samps_a[1:i], samps_b[1:i])
      x = samps_a[i]
      y = samps_b[i]
      lines[5][:set_data]([x, x], [y, y_width[2]])
      lines[6][:set_data]([x, x_width[2]], [y, y])
  return lines
  end

  @time myanim = anim.FuncAnimation(fig, animate, init_func=init,frames=size(samps_a)[1], interval=20, blit=false)

  @time myanim[:save](outfile, extra_args=["-vcodec", "libx264", "-pix_fmt", "yuv420p"])

end
