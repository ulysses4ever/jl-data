using MixtureModels

# 1-Dimensional case
mu = [0.0 10.0]
sigma = Array(Float64, 1, 1, 2)
sigma[:, :, 1] = [1.0]''
sigma[:, :, 2] = [1.0]''
p = [0.9, 0.1]

distr = MixtureMultivariateNormals(mu, sigma, p)

X = rand(distr, 100_000)

k = 2
model = fit(MixtureMultivariateNormals, X, k)

# Force ordering by p?

# 2-Dimensional case w/ Diagonal Covariances
mu = [0.0 10.0; 0.0 10.0]
sigma = Array(Float64, 2, 2, 2)
sigma[:, :, 1] = [1.0 0.0; 0.0 1.0]
sigma[:, :, 2] = [1.0 0.0; 0.0 1.0]
p = [0.9, 0.1]

distr = MixtureMultivariateNormals(mu, sigma, p)

X = rand(distr, 100_000)

k = 2
model = fit(MixtureMultivariateNormals, X, k)

# 2-Dimensional case w/ Non-Diagonal Covariances
mu = [0.0 10.0; 0.0 10.0]
sigma = Array(Float64, 2, 2, 2)
sigma[:, :, 1] = [1.0 0.9; 0.9 1.0]
sigma[:, :, 2] = [1.0 0.9; 0.9 1.0]
p = [0.9, 0.1]

distr = MixtureMultivariateNormals(mu, sigma, p)

X = rand(distr, 10_000)

k = 2
model = fit(MixtureMultivariateNormals, X, k)

# 2-Dimensional case w/ Non-Diagonal Covariances and Different Volumes
mu = [0.0 10.0; 0.0 10.0]
sigma = Array(Float64, 2, 2, 2)
sigma[:, :, 1] = [1.0 0.9; 0.9 1.0]
sigma[:, :, 2] = 5.0 * [1.0 0.0; 0.0 1.0]
p = [0.9, 0.1]

distr = MixtureMultivariateNormals(mu, sigma, p)

X = rand(distr, 10_000)

k = 2
model = fit(MixtureMultivariateNormals, X, k)

# Return point assignments?
