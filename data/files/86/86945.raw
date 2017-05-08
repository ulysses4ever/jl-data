using DataFrames
using DSP
using HDF5
using Iterators
using MachineLearning

include("helpers.jl")

hdf5_data_file  = ARGS[1]
train_labels    = ARGS[2]

labels = readtable(train_labels)

h5open(hdf5_data_file, "r") do h5_file
	subject_sessions = Iterators.groupby(names(h5_file["train"]), subject_id)
	for sessions in subject_sessions
		println("Training on session ", sessions[1])
        data = read(h5_file["train"][sessions[1]])
        features = extract_features(data)
        targets = Int[get_label(labels, subject_id(sessions[1]), session_id(sessions[1]), i) for i=1:size(features,1)]
		imp = univariate_gaussian_importance(features, targets)
        sel_fea = sortperm(imp, rev=true)[1:20]
        #weights = lda(features[:, sel_fea], targets)
		model = fit(features[:, sel_fea], targets, classification_forest_options())
		for session in sessions[2:end]
			data = read(h5_file["train"][session])
        	features = extract_features(data)
			targets = Int[get_label(labels, subject_id(session), session_id(session), i) for i=1:size(features,1)]
			preds = vec(predict_probs(model, features[:, sel_fea])[:,2])
			println("Session ", session, " results: ", auc(targets, preds))
		end
	end
end
