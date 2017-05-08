using Gadfly

function plot_belief(b::Belief; nsamples = 1000)
  samples = [rand(b) for i = 1:nsamples]
  samplesx = [s[1] for s in samples]
  samplesa = [s[2] for s in samples]
  plot(x = samplesx, y = samplesa, Geom.histogram2d)
end

## Visualisation
function vis(b::SampleableBelief, nsamples::Int64)
  data = [rand(b) for i = 1:nsamples]
  Xs = [d[1] for d in data]
  As = [d[2] for d in data]
  Gadfly.plot(x=Xs, y=As,Gadfly.Geom.histogram2d)
end
