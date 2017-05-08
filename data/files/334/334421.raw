module SpatialCorrelation

export exponential!, exponential, matern!, matern, spherical!, spherical
import Base.LinAlg.BLAS.gemm!

# d: matrix of distances
# σ²: partial sill
# ϕ: spatial range
# Σ: Matern covariance matrix
function exponential!(Σ::Matrix, d::Matrix, σ²::Real, ϕ::Real)
  if issym(d)
    fillexponentialsym!(Σ, d, σ², ϕ)
  else
    fillexponentialasym!(Σ, d, σ², ϕ)
  end
end # matern

function exponential(d::Matrix, σ²::Real, ϕ::Real)
  nrows, ncols = size(d)
  Σ = fill(0.0, nrows, ncols)
  exponential!(Σ, d, σ², ϕ)

  return Σ
end

function fillexponentialsym!(Σ::Matrix, d::Matrix, σ²::Real, ϕ::Real)
  n = size(d)[1]

  fill!(Σ, 0.0)
  for j = 1:n, i = 1:j
    if i == j
      Σ[i, j] = 0.5 * σ²  # when we add using gemm!, we get the correct diagonal
    else
      Σ[i, j] = σ² * exp(- d[i, j] / ϕ)
    end
  end

  gemm!('T', 'N', 1.0, Σ, eye(n), 1.0, Σ)
end

function fillexponentialasym!(Σ::Matrix, d::Matrix, σ²::Real, ϕ::Real)
  n = size(d)[1]

  for j = 1:n, i = 1:n
    d_ij = d[i, j]
    if d_ij == 0
      Σ[i, j] = σ²
    else
      Σ[i, j] = σ² * exp(- d[i, j] / ϕ)
    end
  end
end

# d: matrix of distances
# σ²: partial sill
# ν: smoothness (if 0.5, uses exponential functions)
# ϕ: spatial range
# Σ: Matern covariance matrix
function matern!(Σ::Matrix, d::Matrix, σ²::Real, ν::Real, ϕ::Real)
  if issym(d)
    if ν == 0.5
      fillexponentialsym!(Σ, d, σ², ϕ)
    else
      fillmaternsym!(Σ, d, σ², ν, ϕ)
    end
  else
    if ν == 0.5
      fillexponentialsym!(Σ, d, σ², ϕ)
    else
      fillmaternasym!(Σ, d, σ², ν, ϕ)
    end
  end
end # matern

function matern(d::Matrix, σ²::Real, ν::Real, ϕ::Real)
  nrows, ncols = size(d)
  Σ = fill(0.0, nrows, ncols)
  matern!(Σ, d, σ², ν, ϕ)

  return Σ
end

function fillmaternsym!(Σ::Matrix, d::Matrix, σ²::Real, ν::Real, ϕ::Real)
  n = size(d)[1]

  fill!(Σ, 0.0)
  for j = 1:n, i = 1:j
    if i == j
      Σ[i, j] = 0.5 * σ²  # when we add using gemm!, we get the correct diagonal
    else
      z = d[i, j] / ϕ
      Σ[i, j] = σ² * 2^(1 - ν) / gamma(ν) * (z)^ν * besselk(ν, z)
    end
  end
  gemm!('T', 'N', 1.0, Σ, eye(n), 1.0, Σ)
end

function fillmaternasym!(Σ::Matrix, d::Matrix, σ²::Real, ν::Real, ϕ::Real)
  n = size(d)[1]

  for j = 1:n, i = 1:n
    d_ij = d[i, j]
    if d_ij == 0
      Σ[i, j] = σ²
    else
      z = d[i, j] / ϕ
      Σ[i, j] = σ² * 2^(1 - ν) / gamma(ν) * (z)^ν * besselk(ν, z)
    end
  end
end

# d: matrix of distances
# σ²: partial sill
# ϕ: spatial range
# Σ: Matern covariance matrix
function spherical!(Σ::Matrix, d::Matrix, σ²::Real, ϕ::Real)
  if issym(d)
    fillsphericalsym!(Σ, d, σ², ϕ)
  else
    fillsphericalasym!(Σ, d, σ², ϕ)
  end
end # matern

function spherical(d::Matrix, σ²::Real, ϕ::Real)
  nrows, ncols = size(d)
  Σ = fill(0.0, nrows, ncols)
  spherical!(Σ, d, σ², ϕ)

  return Σ
end

function fillsphericalsym!(Σ::Matrix, d::Matrix, σ²::Real, ϕ::Real)
  n = size(d)[1]

  fill!(Σ, 0.0)
  for j = 1:n, i = 1:j
    if i == j
      Σ[i, j] = 0.5 * σ²  # when we add using gemm!, we get the correct diagonal
    else
      d_ij = d[i, j]
      if d_ij >= ϕ
        Σ[i, j] = 0
      else
        z = d[i, j] / ϕ
        Σ[i, j] = σ² * (1 - 1.5 * - z + 0.5 * z^3)
      end
    end
  end

  gemm!('T', 'N', 1.0, Σ, eye(n), 1.0, Σ)
end

function fillsphericalasym!(Σ::Matrix, d::Matrix, σ²::Real, ϕ::Real)
  n = size(d)[1]

  for j = 1:n, i = 1:n
    d_ij = d[i, j]
    if d_ij == 0
      Σ[i, j] = σ²
    elseif d_ij < ϕ
      z = d[i, j] / ϕ
      Σ[i, j] = σ² * (1 - 1.5 * - z + 0.5 * z^3)
    else
      Σ[i, j] = 0
    end
  end
end

end # module
