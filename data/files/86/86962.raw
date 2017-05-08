using DataFrames
using DSP
using HDF5
using MachineLearning

hdf5_data_file  = ARGS[1]
train_labels    = ARGS[2]
submission_file = ARGS[3]

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
	println("\tFound ", length(events), " events")
	window = 20:20:200 # samples, at a 200 Hz sampling rate
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
    println(groups)
    @assert length(groups)==2

    features_0 = features[target.!=groups[2],:]
    features_1 = features[target.==groups[2],:]
    s = cov(features_0)+cov(features_1)

    vec(inv(s)*transpose(mean(features_1, 1)-mean(features_0, 1)))
end

labels = readtable(train_labels)

id_feed_back(subject::Int, session::Int, event::Int) = @sprintf("S%02d_Sess%02d_FB%03d", subject, session, event)
get_label(labels::DataFrame, subject::Int, session::Int, event::Int) = labels[labels[:IdFeedBack].==id_feed_back(subject, session, event), :Prediction][1]

function make_predictions(features, selected_features, w) 
    res = zeros(size(features, 1))
    for i=1:length(selected_features)
        m=vec(features[:,selected_features[i]]*w[i])
        m_ind = sortperm(m)
        m_t = zeros(length(m))
        m_t[m_ind] = [1:length(m_ind)]./length(m_ind)

        println(m[1:10])
        res += m_t./length(selected_features)
    end
    res
end

w                 = Array(Vector{Float64}, 0)
selected_features = Array(Vector{Int}, 0)

h5open(hdf5_data_file, "r") do h5_file
    for session_name in names(h5_file["train"])
        println(session_name)
        m = match(r"Data_S(\d+)_Sess(\d+)", session_name)
        if typeof(m)==Void
            throw("Filename doesn't match pattern: " * session_name)
        end
        println("Subject: ", m.captures[1], "Session: ", m.captures[2])
        subject = int(m.captures[1])
        session = int(m.captures[2])
        data = read(h5_file["train"][session_name])
        println("Train size data: ", size(data))
        features = extract_features(data)
        targets = Int[get_label(labels, subject, session, i) for i=1:size(features,1)]
        imp = univariate_gaussian_importance(features, targets)
        sel_fea = sortperm(imp, rev=true)[1:20]
        weights = lda(features[:, sel_fea], targets)
        println("Selected Feature Importance: ", imp[sel_fea][1:4])
        if sum(isnan(weights))==0
            push!(selected_features, sel_fea)
            push!(w, weights)
        else
            println("NaN weights, subject ", subject, " session ", session)
        end
    end
    submission = DataFrame(IdFeedBack=ASCIIString[], Prediction=Float64[])

    for session_name in names(h5_file["test"])
        m = match(r"Data_S(\d+)_Sess(\d+)", session_name)
        if typeof(m)==Void
            throw("Filename doesn't match pattern: " * session_name)
        end
        println("Subject: ", m.captures[1], "Session: ", m.captures[2])
        subject = int(m.captures[1])
        session = int(m.captures[2])
        data = read(h5_file["test"][session_name])
        println("Test size data", size(data))
        features = extract_features(data)
        results = make_predictions(features, selected_features, w)
        println(results[1:10])

        submission = vcat(submission, DataFrame(IdFeedBack=[id_feed_back(subject, session, i) for i=1:length(results)], Prediction=results))
    end

    writetable(submission_file, submission)
end
