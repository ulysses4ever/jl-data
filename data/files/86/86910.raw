include("helpers.jl")

hdf5_data_file = ARGS[1]
labels_file    = ARGS[2]

function fit_nn_model(h5_file, train_sessions, labels)
    println(train_sessions)
    train_fea     = Array(Array{Float64,2}, 0)
    train_targets = Array(Vector{Int},  0)
    for session in train_sessions
        println("Training on session ", session)
        data = read(h5_file["train"][session])
        features = extract_features(data)
        targets = Int[get_label(labels, subject_id(session), session_id(session), i) for i=1:size(features,1)]
        push!(train_fea, features)
        push!(train_targets, targets)
    end

    @time model = fit(vcat(train_fea...), vcat(train_targets...), classification_net_options(hidden_layers=[50], stop_criteria=StopAfterIteration(100)))
    @time preds = vec(predict_probs(model, vcat(train_fea...))[:,2])
    println("Train results: ", auc(vcat(train_targets...), preds), " Positive Targets: ", sum(vcat(train_targets...)), "/", length(vcat(train_targets...)))
    model
end

inter_subject_train_valid(hdf5_data_file, labels_file, fit_nn_model, extract_features)