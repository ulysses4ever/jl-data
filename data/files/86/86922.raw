using DataFrames
using DSP
using HDF5
using Iterators
using MachineLearning

include("helpers.jl")

hdf5_data_file  = ARGS[1]
train_labels    = ARGS[2]
submission_file = ARGS[3]

labels = readtable(train_labels)

h5open(hdf5_data_file, "r") do h5_file
	train_sessions = names(h5_file["train"])
	test_sessions  = names(h5_file["test"])

	train_fea     = Array(Array{Float64,2}, 0)
	train_targets = Array(Vector{Int},  0)

	println(train_sessions)
	for session in train_sessions
		println("Training on session ", session)
        data = read(h5_file["train"][session])
        features = extract_features(data)
        targets = Int[get_label(labels, subject_id(session), session_id(session), i) for i=1:size(features,1)]
		push!(train_fea, features)
		push!(train_targets, targets)
        #weights = lda(features[:, sel_fea], targets)
	end

	imp = univariate_gaussian_importance(vcat(train_fea...), vcat(train_targets...))
    sel_fea = sortperm(imp, rev=true)[1:end]
	println("Fitting Model")
	@time model = fit(vcat(train_fea...)[:,sel_fea], vcat(train_targets...), classification_net_options(hidden_layers=[100], stop_criteria=StopAfterIteration(100)))
	@time preds = vec(predict_probs(model, vcat(train_fea...)[:,sel_fea])[:,2])
	println("Train results: ", auc(vcat(train_targets...), preds), " Positive Targets: ", sum(vcat(train_targets...)), "/", length(vcat(train_targets...)))

    submission = DataFrame(IdFeedBack=ASCIIString[], Prediction=Float64[])

	for session in test_sessions
		data = read(h5_file["test"][session])
    	features = extract_features(data)[:, sel_fea]
		preds = vec(predict_probs(model, features)[:,2])
		submission = vcat(submission, DataFrame(IdFeedBack=[id_feed_back(subject_id(session), session_id(session), i) for i=1:length(preds)], Prediction=preds))
    end
    writetable(submission_file, submission)
end
