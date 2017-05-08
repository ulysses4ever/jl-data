using DataFrames
using DSP
using HDF5
using Iterators
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
	window = 0:10:200 # samples, at a 200 Hz sampling rate
	features = zeros(length(events), 57*length(window))
	for i=1:length(events)
		features[i,:] = transformed[events[i]+window, :]
	end
	features
end

function extract_augmented_features(data::Array{Float64, 2}, targets::Vector{Int}; augmented_class::Int=0, num_background::Int=100)
    filter = digitalfilter(Bandpass(0.5, 20, fs=200), Butterworth(10))

    events = find(data[:,59])

    background = ones(Int, size(data,1))
    background[1:1000] = 0
    background[end-1000:end] = 0
    for i=events
        background[i+(-100:100)]=0
    end

    background_sample_locs = find(background)
    background_sample_locs = background_sample_locs[randperm(length(background_sample_locs))][1:num_background]

    events  = vcat(events, background_sample_locs)
    targets = vcat(targets, augmented_class*ones(Int, num_background))

    zmuv = fit(data[:,2:58], ZmuvOptions())
    transformed = transform(zmuv, filt(filter, data[:,2:58]))
    #transformed = filt(filter, data[:,2:58])
    window = 0:10:200 # samples, at a 200 Hz sampling rate
    features = zeros(length(events), 57*length(window))
    for i=1:length(events)
        features[i,:] = transformed[events[i]+window, :]
    end
    features, targets
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

function inter_subject_train_valid(hdf5_data_file::String, labels_file::String, err_fit::Function, err_features::Function)
    labels = readtable(labels_file)
    scores = DataFrame(Subject=ASCIIString[], AUC=Float64[])
	h5open(hdf5_data_file, "r") do h5_file
		train_sessions = names(h5_file["train"])[1:40]
		valid_sessions = names(h5_file["train"])[41:end]

		model = err_fit(h5_file, train_sessions, labels)

		valid_targets = Vector{Int}[]
		valid_preds   = Vector{Float64}[]

		for subject_sessions in Iterators.groupby(valid_sessions, subject_id)
            push!(valid_targets, Int[])
            push!(valid_preds, Float64[])
			for session in subject_sessions
				data = read(h5_file["train"][session])
                features = err_features(data)
				targets = Int[get_label(labels, subject_id(session), session_id(session), i) for i=1:size(features,1)]
				push!(valid_targets[end], targets...)
				preds = vec(predict_probs(model, features)[:,2])
				push!(valid_preds[end], preds...)
			end
            score = auc(valid_targets[end], valid_preds[end])
            scores = vcat(scores, DataFrame(Subject=string(subject_id(subject_sessions[1])), AUC=[score]))
            println("Subject ", subject_id(subject_sessions[1]), " results: ", score, " Positive Targets: ", sum(valid_targets[end]), "/", length(valid_targets[end]))
		end
        score = auc(vcat(valid_targets...), vcat(valid_preds...))
        scores = vcat(scores, DataFrame(Subject=["All"], AUC=[score]))
		println("Test score: ", score)
	end
    scores
end
