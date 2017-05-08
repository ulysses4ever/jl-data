module SpatialCorrelation

export exponential!, exponential, matern!, matern, spherical!, spherical

# Σ: covariance matrix
# D: matrix of distances
# σ²: partial sill
# ϕ: spatial range
function exponential!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T)
  @assert σ² > 0.0
  @assert ϕ > 0.0
  if issym(D)
    fillexponentialsym!(Σ, D, σ², ϕ)
  else
    fillexponentialasym!(Σ, D, σ², ϕ)
  end
end # exponential!

function exponential{T <: FloatingPoint}(D::Matrix{T}, σ²::T, ϕ::T)
  Σ = fill(0.0, size(D))
  exponential!(Σ, D, σ², ϕ)
  return Σ
end  # exponential

function fillexponentialsym!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T)
  n = size(D, 1)
  for j = 1:n, i = 1:j
    if i == j
      Σ[i, j] = σ²
    else
      Σ[i, j] = σ² * exp(-D[i, j] / ϕ)
      Σ[j, i] = Σ[i, j]
    end
  end
end  # fillexponentialsym!

function fillexponentialasym!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T)
  n, m = size(D)
  for j = 1:m, i = 1:n
    d_ij = D[i, j]
    if d_ij == 0.0
      Σ[i, j] = σ²
    else
      Σ[i, j] = σ² * exp(-d_ij / ϕ)
    end
  end
end  # fillexponentialasym!

# Σ: covariance matrix
# D: matrix of distances
# σ²: partial sill
# ϕ: spatial range
# ν: smoothness (if 0.5, uses exponential functions)
function matern!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T, ν::T)
  @assert σ² > 0.0
  @assert ϕ > 0.0
  @assert ν > 0.0
  if issym(D)
    if ν == 0.5
      fillexponentialsym!(Σ, D, σ², ϕ)
    else
      fillmaternsym!(Σ, D, σ², ϕ, ν)
    end
  else
    if ν == 0.5
      fillexponentialasym!(Σ, D, σ², ϕ)
    else
      fillmaternasym!(Σ, D, σ², ϕ, ν)
    end
  end
end  # matern!

function matern{T <: FloatingPoint}(D::Matrix{T}, σ²::T, ϕ::T, ν::T)
  Σ = fill(0.0, size(D))
  matern!(Σ, D, σ², ϕ, ν)
  return Σ
end  # matern

function fillmaternsym!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T, ν::T)
  n = size(D, 1)
  for j = 1:n, i = 1:j
    if i == j
      Σ[i, j] = σ²
    else
      z = D[i, j] / ϕ
      Σ[i, j] = σ² * 2.0^(1.0 - ν) / gamma(ν) * (z)^ν * besselk(ν, z)
      Σ[j, i] = Σ[i, j]
    end
  end
end  # fillmaternsym!

function fillmaternasym!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T, ν::T)
  n, m = size(D)
  for j = 1:m, i = 1:n
    d_ij = D[i, j]
    if d_ij == 0.0
      Σ[i, j] = σ²
    else
      z = d_ij / ϕ
      Σ[i, j] = σ² * 2.0^(1.0 - ν) / gamma(ν) * (z)^ν * besselk(ν, z)
    end
  end
end  # fillmaternasym!

# Σ: covariance matrix
# D: matrix of distances
# σ²: partial sill
# ϕ: spatial range
function spherical!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T)
  @assert σ² > 0.0
  @assert ϕ > 0.0
  if issym(D)
    fillsphericalsym!(Σ, D, σ², ϕ)
  else
    fillsphericalasym!(Σ, D, σ², ϕ)
  end
end  # spherical!

function spherical{T <: FloatingPoint}(D::Matrix{T}, σ²::T, ϕ::T)
  Σ = fill(0.0, size(D))
  spherical!(Σ, D, σ², ϕ)
  return Σ
end  # spherical

function fillsphericalsym!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T)
  n = size(D, 1)
  for j = 1:n, i = 1:j
    if i == j
      Σ[i, j] = σ²
    else
      d_ij = D[i, j]
      if d_ij < ϕ
        z = d_ij / ϕ
        Σ[i, j] = σ² * (1.0 - 1.5 * z + 0.5 * z^3)
      else
        Σ[i, j] = 0.0
      end
      Σ[j, i] = Σ[i, j]
    end
  end
end  # fillsphericalsym!

function fillsphericalasym!{T <: FloatingPoint}(Σ::Matrix{T}, D::Matrix{T}, σ²::T, ϕ::T)
  n, m = size(D)
  for j = 1:m, i = 1:n
    d_ij = D[i, j]
    if d_ij == 0.0
      Σ[i, j] = σ²
    elseif d_ij < ϕ
      z = d_ij / ϕ
      Σ[i, j] = σ² * (1.0 - 1.5 * z + 0.5 * z^3)
    else
      Σ[i, j] = 0.0
    end
  end
end  # fillsphericalasym!

end # module
