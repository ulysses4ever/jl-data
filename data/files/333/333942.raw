
model = linear_train(labels[1:50:end], features[1:50:end, :]');

(predicted_labels, decision_values) = linear_predict(model, features[3:3:end, :]');

# Compute accuracy
@printf "Accuracy: %.2f%%\n" mean((predicted_labels .== labels[3:3:end]))*100
