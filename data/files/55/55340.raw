
include("util.jl")


# TODO: The fit_* and sample functions could be part of interfaces

abstract StateSpaceModel

log_likelihood(ssm::StateSpaceModel) = @NI
log_evidence(ssm::StateSpaceModel) = @NI
sample_date(ssm::StateSpaceModel) = @NI
sample_state_seq(ssm::StateSpaceModel) = @NI
map_state_seq(ssm::StateSpaceModel) = @NI
fit_mle(ssm::StateSpaceModel) = @NI
fit_map(ssm::StateSpaceModel) = @NI
sample(ssm::StateSpaceModel, n::Int=1) = @NI
predict(ssm::StateSpaceModel, h::Int) = @NI
filter(ssm::StateSpaceModel, h::Int) = @NI
filter(ssm::StateSpaceModel) = @NI
smooth(ssm::StateSpaceModel, h::Int) = @NI
smooth(ssm::StateSpaceModel) = @NI
