using DataFrames
using DSP
using HDF5
using Iterators
using MachineLearning

include("helpers.jl")

hdf5_data_file = ARGS[1]
labels_file    = ARGS[2]

labels = readtable(labels_file)

function fit_nn_model(h5_file)

end

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
	@time model = fit(vcat(train_fea...)[:,sel_fea], vcat(train_targets...), classification_net_options(stop_criteria=StopAfterIteration(100)))
	@time preds = vec(predict_probs(model, vcat(train_fea...)[:,sel_fea])[:,2])
	println("Train results: ", auc(vcat(train_targets...), preds), " Positive Targets: ", sum(vcat(train_targets...)), "/", length(vcat(train_targets...)))

	test_targets = Array(Vector{Int},  0)
	test_preds   = Array(Vector{Float64}, 0)

	for session in test_sessions
		data = read(h5_file["train"][session])
    	features = extract_features(data)[:, sel_fea]
		targets = Int[get_label(labels, subject_id(session), session_id(session), i) for i=1:size(features,1)]
		push!(test_targets, targets)
		preds = vec(predict_probs(model, features)[:,2])
		push!(test_preds, preds)
		println("Session ", session, " results: ", auc(targets, preds), " Positive Targets: ", sum(targets), "/", length(targets))
	end
	println("Test score: ", auc(vcat(test_targets...), vcat(test_preds...)))
end
