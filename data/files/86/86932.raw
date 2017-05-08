using DataFrames
using DSP
using HDF5
using MachineLearning

function extract_features(data::Array{Float64, 2})
	# data is 59 columns wide
	# Col 1: Time
	# Col 2-57: 56 electrode features
	# Col 58: EOG channel
	# Col 59: Simulus channel
    filter = digitalfilter(Bandpass(0.5, 20, fs=200), Butterworth(10))

	events = find(data[:,59])
	zmuv = fit(data[:,2:58], ZmuvOptions())
	transformed = transform(zmuv, filt(filter, data[:,2:58]))
	#transformed = filt(filter, data[:,2:58])
	window = 10:10:400 # samples, at a 200 Hz sampling rate
	features = zeros(length(events), 57*length(window))
	for i=1:length(events)
		features[i,:] = transformed[events[i]+window, :]
	end
	features
end

function univariate_gaussian_importance(features::Array{Float64, 2}, target::Vector{Int})
	groups = sort(unique(target))
	@assert length(groups)==2

	features_0 = features[target.!=groups[2],:]
	features_1 = features[target.==groups[2],:]

	vec(abs(mean(features_1, 1)-mean(features_0, 1)) ./ sqrt(var(features_1, 1)+var(features_0, 1)))
end

function lda(features::Array{Float64, 2}, target::Vector{Int})
    groups = sort(unique(target))
    @assert length(groups)==2

    features_0 = features[target.!=groups[2],:]
    features_1 = features[target.==groups[2],:]
    s = cov(features_0)+cov(features_1)

    vec(inv(s)*transpose(mean(features_1, 1)-mean(features_0, 1)))
end

id_feed_back(subject::Int, session::Int, event::Int) = @sprintf("S%02d_Sess%02d_FB%03d", subject, session, event)
get_label(labels::DataFrame, subject::Int, session::Int, event::Int) = labels[labels[:IdFeedBack].==id_feed_back(subject, session, event), :Prediction][1]

function make_predictions(features, selected_features, w) 
    res = zeros(size(features, 1))
    for i=1:length(selected_features)
        m=vec(features[:,selected_features[i]]*w[i])
        m_ind = sortperm(m)
        m_t = zeros(length(m))
        m_t[m_ind] = [1:length(m_ind)]./length(m_ind)
        res += m_t./length(selected_features)
    end
    res
end

subject_id(session_name::String) = int(match(r"Data_S(\d+)_Sess(\d+)", session_name).captures[1])
session_id(session_name::String) = int(match(r"Data_S(\d+)_Sess(\d+)", session_name).captures[2])
