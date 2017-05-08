using Gadfly

include("helpers.jl")

plots_dir      = ARGS[1]
hdf5_data_file = ARGS[2]
labels_file    = ARGS[3]

function fit_nn_model(h5_file, train_sessions, labels)
    train_fea     = Array(Array{Float64,2}, 0)
    train_targets = Array(Vector{Int},  0)
    for session in train_sessions
        data = read(h5_file["train"][session])
        features = extract_features(data)
        targets = Int[get_label(labels, subject_id(session), session_id(session), i) for i=1:size(features,1)]
        push!(train_fea, features)
        push!(train_targets, targets)
    end

    fea = vcat(train_fea...)
    tar = vcat(train_targets...)
    p = randperm(size(fea, 1))
    fea = fea[p, :]
    tar = tar[p]

    @time model = fit(fea, tar, classification_net_options(hidden_layers=[10], stop_criteria=StopAfterIteration(5)))
    @time preds = vec(predict_probs(model, fea)[:,2])
    println("Train results: ", auc(tar, preds), " Positive Targets: ", sum(tar), "/", length(tar))
    model
end

function fit_augmented_nn_model(h5_file, train_sessions, labels)
    train_fea     = Array(Array{Float64,2}, 0)
    train_targets = Array(Vector{Int},  0)
    for session in train_sessions
        data   = read(h5_file["train"][session])
        events = find(data[:,59])
        event_targets = Int[get_label(labels, subject_id(session), session_id(session), i) for i=1:length(events)]

        features, targets = extract_augmented_features(data, event_targets)
        push!(train_fea, features)
        push!(train_targets, targets)
    end

    fea = vcat(train_fea...)
    tar = vcat(train_targets...)
    p = randperm(size(fea, 1))
    fea = fea[p, :]
    tar = tar[p]

    @time model = fit(fea, tar, classification_net_options(hidden_layers=[10], stop_criteria=StopAfterIteration(5)))
    @time preds = vec(predict_probs(model, fea)[:,2])
    println("Train results: ", auc(tar, preds), " Positive Targets: ", sum(tar), "/", length(tar))
    model
end

score1 = inter_subject_train_valid(hdf5_data_file, labels_file, fit_nn_model, extract_features)
rename!(score1, :AUC, :Score1)
score2 = inter_subject_train_valid(hdf5_data_file, labels_file, fit_augmented_nn_model, extract_features)
rename!(score2, :AUC, :Score2)

scores = join(score1, score2, on=:Subject)
println(scores)

layer1 = layer(scores, x=:Score1, y=:Score2, color=:Subject, Geom.point)
layer2 = layer(x=0:0.1:1, y=0:0.1:1, Geom.line)

draw(PNG(joinpath(plots_dir, "augmented2.png"), 8inch, 6inch), plot(layer1, layer2, Theme(panel_fill=color("white"), panel_opacity=1.0)))
