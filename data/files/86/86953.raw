using DataFrames
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

	events = find(data[:,59])
	zmuv = fit(data[:,2:58], ZmuvOptions())
	transformed = transform(zmuv, data[:,2:58])
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
    @assert length(groups)==2

    features_0 = features[target.!=groups[2],:]
    features_1 = features[target.==groups[2],:]
    s = cov(features_0)+cov(features_1)

    vec(inv(s)*transpose(mean(features_1, 1)-mean(features_0, 1)))
end

labels = readtable(train_labels)

id_feed_back(subject::Int, session::Int, event::Int) = @sprintf("S%02d_Sess%02d_FB%03d", subject, session, event)
get_label(labels::DataFrame, subject::Int, session::Int, event::Int) = labels[labels[:IdFeedBack].==id_feed_back(subject, session, event), :Prediction][1]

println("Subject 2, Session 1, Event 4: ", get_label(labels, 2, 1, 4))
println("Subject 2, Session 1, Event 5: ", get_label(labels, 2, 1, 5))

w = zeros(20)
selected_features = zeros(Int, 20)

h5open(hdf5_data_file, "r") do h5_file
    for session_name in names(h5_file["train"])[1:1]
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
        selected_features[:] = sortperm(imp, rev=true)[1:20]
        println("Seleected Feature Importance: ", imp[selected_features])

        w[:] = lda(features[:, selected_features], targets)
        println("w: ", w)
    end
    println("Selected Features: ", selected_features)
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
        features = extract_features(data)[:,selected_features]
        results = vec(features*w)
        submission = vcat(submission, DataFrame(IdFeedBack=[id_feed_back(subject, session, i) for i=1:length(results)], Prediction=results))
    end

    writetable(submission_file, submission)
end
