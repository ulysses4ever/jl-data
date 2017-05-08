module RoesserModels

VERSION < v"0.4-" && using Docile

@doc doc"""
The Roesser model is a 2D state-space model, useful for 2D spatial dynamics
or a combination of 1D spatial dynamics and time.

References:
  \cite{Roesser:1975}
"""->
type RoesserModel
  A1::Array{Float64}
  A2::Array{Float64}
  A3::Array{Float64}
  A4::Array{Float64}
  B1::Array{Float64}
  B2::Array{Float64}
  C1::Array{Float64}
  C2::Array{Float64}
  D::Array{Float64}
  in_dim::Int
  out_dim::Int
  x_h_dim::Int
  x_v_dim::Int
  function RoesserModel(A1, A2, A3, A4, B1, B2, C1, C2, D)
    x_h_dim = size(A1, 1)
    x_v_dim = size(A4, 1)
    out_dim = size(C1, 1)
    in_dim = size(B1, 2)

    if ((size(A1, 2) != x_h_dim) || (size(A3,2) != x_h_dim)
        || (size(B1,1) != x_h_dim) || (size(C1,2) != x_h_dim)
        || (size(A2,1) != x_h_dim))
      error("Matrix dimensions for Horizontal states do not agree");
    end
    if  ((size(A2,2) != x_v_dim) || (size(A4,1) != x_v_dim)
         || (size(A4,2) != x_v_dim) || (size(B2,1) != x_v_dim)
         || (size(C2,2) != x_v_dim))
      error("Matrix dimensions for Vertical states do not agree");
    end
    if ((size(C2,1) != out_dim) || (size(D,1) != out_dim)
        || (size(B2,2) != in_dim) || (size(D,2) != in_dim))
      error("Matrix dimensions for Input/Output do not agree")
    end
    new(A1, A2, A3, A4, B1, B2, C1, C2, D, in_dim, out_dim, x_h_dim, x_v_dim)
  end
end

@doc doc"""
The CRSD (Causal Recursive Separable in Denominator) model is a specific type
of Roesser Models.

References:
  \cite{Roesser:1975}
"""->
function CrsdRoesserModel(A1, A2, A4, B1, B2, C1, C2, D)
  x_h_dim = size(A1, 1)
  x_v_dim = size(A3, 1)
  out_dim = size(C1, 1)
  in_dim = size(B1, 2)
  A3 = zeros(x_v_dim, x_h_dim);
  return RoesserModel(A1, A2, A3, A4, B1, B2, C1, C2, D, in_dim, out_dim, x_h_dim, x_v_dim)
end

@doc doc"""
Simulates the Roesser model in an iterative approach.

"""->
function simulate(system::RoesserModel, input)
  if system.in_dim > 1 && size(inputs,3) != system.in_dim
    error("Input dimension mismatch")
  end

  M = size(inputs,1)
  N = size(inputs,2)
  output = zeros(M, N, system.out_dim)
  x_h = zeros(size(inputs,1)+1, size(inputs,2)+1, system.x_h_dim)
  x_v = zeros(size(inputs,1)+1, size(inputs,2)+1, system.x_v_dim)

  A1 = system.A1
  A2 = system.A2
  A3 = system.A3
  A4 = system.A4
  B1 = system.B1
  B2 = system.B2
  C1 = system.C1
  C2 = system.C2
  D = system.D
  for i = 1:M
    for j = 1:N
      x_h[i+1,j, 1:end] = A1*vec(x_h[i,j, 1:end]) + A2*vec(x_v[i,j,1:end]) + B1 * vec(inputs[i,j,1:end])
      x_v[i,j+1, 1:end] = A3*vec(x_h[i,j, 1:end]) + A4*vec(x_v[i,j,1:end]) + B2 * vec(inputs[i,j,1:end])
      output[i,j, 1:end] = C1 * vec(x_h[i,j, 1:end]) + C2 * vec(x_v[i,j,1:end]) + D * vec(inputs[i,j,1:end])
    end
  end
  return output
end

@doc doc"""
Generate a completely random system. No check is performed for observability
or controllability.

"""->
function randomsystem(nh::Integer, nv::Integer, ouputs::Integer, inputs::Integer)
  A1 = randn(nh, nh);
  A2 = randn(nh, nv);
  A3 = randn(nv, nh);
  A4 = randn(nv, nv);
  C1 = randn(outputs, nh);
  C2 = randn(outputs, nv);
  B1 = randn(nh, inputs);
  B2 = randn(nv, inputs);
  D = randn(outputs, inputs);

  return RoesserModel(A1, A2, A3, A4, B1, B2, C1, C2, D);
end

@doc doc"""
Tests the model for global controllability, according to the criteria
formulated by Kung in 1976.

References:
  \cite{Kung:1976}
"""->
function is_global_controllable(system::RoesserModel, M::Integer, N::Integer)

end

@doc doc"""
Tests the model for global controllability, according to the criteria
formulated by Kung in 1976.

References:
  \cite{Kung:1976}
"""->
function is_global_observable(system::RoesserModel, M::Integer, N::Integer)

end

@doc doc"""
Tests the model for local controllability, according to the criteria
formulated by Roesser in 1975.

References:
  \cite{Roesser:1975}
  \cite{Kung:1976}
"""->
function is_local_controllable(system::RoesserModel)

end

@doc doc"""
Tests the model for local observability, according to the criteria
formulated by Roesser in 1975.

References:
  \cite{Roesser:1975}
  \cite{Kung:1976}
"""->
function is_local_observable(system::RoesserModel)

end

@doc doc"""
Tests the model for modal controllability, according to the criteria
formulated by Kung in 1976.

References:
  \cite{Kung:1976}
"""->
function is_modal_controllable(system::RoesserModel)

end

@doc doc"""
Tests the model for modal observability, according to the criteria
formulated by Kung in 1976.

References:
  \cite{Kung:1976}
"""->
function is_modal_observable(system::RoesserModel)

end

end # module
