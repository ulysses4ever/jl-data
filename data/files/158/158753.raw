using PyCall
@pyimport matplotlib.pyplot as plt
include("../Utils.jl")
srand(123)

# Generate true logx values
logx = log(rand(100, 2))
for j in 1:size(logx)[2]
  for i in 2:size(logx)[1]
    logx[i, j] += logx[i-1, j]
  end
end

# Fake log likelihoods
logl = 10*sqrt(-logx)

# We won't have the true logx values, but here's a prior sample
logx = log(rand(100, 2))
for j in 1:size(logx)[2]
  for i in 2:size(logx)[1]
    logx[i, j] += logx[i-1, j]
  end
end

# Gibbs sample one value
function update!(logx::Array{Float64, 2})
  ii = rand(1:size(logx)[1])
  jj = rand(1:size(logx)[2])

  # Generate proposal
  proposal = 0.
  if ii == size(logx)[1]
    proposal = logx[ii-1, jj] + log(rand())
  elseif ii==1
    proposal = logx[ii+1, jj]*rand()
  else
    proposal = logx[ii+1, jj] + (logx[ii-1, jj] - logx[ii+1, jj])*rand()
  end

  # Measure inconsistency
  inconsistency_old = 0
  inconsistency_new = 0

  for j in 1:size(logx)[2]
    if j != jj
      for i in 1:size(logx)[1]


        if (logl[ii, jj] > logl[i, j]) && (logx[ii, jj] > logx[i, j])
          inconsistency_old += 1
        end
        if (logl[ii, jj] < logl[i, j]) && (logx[ii, jj] < logx[i, j])
          inconsistency_old += 1
        end

        if (logl[ii, jj] > logl[i, j]) && (proposal > logx[i, j])
          inconsistency_new += 1
        end
        if (logl[ii, jj] < logl[i, j]) && (proposal < logx[i, j])
          inconsistency_new += 1
        end

      end
    end
  end

  # Accept?
  accepted = false
  if inconsistency_new <= inconsistency_old
    logx[ii, jj] = proposal
    accepted = true
  end
  return accepted
end


plt.ion()
accepted = 0
for i in 1:1000000
  accepted += update!(logx)

  if rem(i, 100) == 0
    plt.hold(false)
    plt.plot(logx[:,1], logl[:,1], "bo-", alpha=0.4)
    plt.hold(true)
    plt.plot(logx[:,2], logl[:,2], "ro-", alpha=0.4)
    plt.title(i)
    plt.draw()
    println(accepted/i)
  end
end

plt.ioff()
plt.show()

