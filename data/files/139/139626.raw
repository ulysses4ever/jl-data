type FastCodingData{T}
  Dtx::Array{T, 2};
  DtD::Array{T, 2};
end
type FastCodingOpts{T}
  z::Array{T, 2};
  t::Array{T, 2};
  lambda_t::Array{T, 2};
  beta::T;       # 1
  mu_t::T;       # 1
  max_iter::Int; # 1000
  tol::T;        # 1e-10
  DEBUG::Bool;   # false
  debugData::Dict;
end
FastCodingOpts(T) = FastCodingOpts{T}(zeros(0, 0), zeros(0, 0), zeros(0, 0), 1, 1, 1000, 1e-10, false, Dict());


type LearningData{T}
  Ztx::Array{T, 2};
  ZtZ::Array{T, 2};
end
type LearningOpts{T}
  Dinit::Array{T, 2};
  s::Array{T, 2};
  lambda_s::Array{T, 2};
  mu_s::T;       # 1
  max_iter::Int; # 1000
  tol::T;        # 1e-10
  DEBUG::Bool;   # false
  debugData::Dict;
end
LearningOpts(T) = LearningOpts{T}(zeros(0, 0), zeros(0, 0), zeros(0, 0), 1., 1000, 1e-10, false, Dict());


type FSCOpts{T}
  Dinit::Array{T, 2};
  beta::T;       # 1
  mu_s::T;       # 1
  mu_t::T;       # 1
  max_iter::Int; # 1000
  tol::T;        # 1e-10
  FIXED_D::Bool; # false
  DEBUG::Bool;   # false
  debugData::Dict;
end
FSCOpts(T) = FSCOpts{T}(zeros(0, 0), 1., 1., 1., 1000, 1e-10, false, false, Dict());
