# artificial neural networks to model non-linear relationships

Pkg.clone("https://github.com/EricChiang/ANN.jl.git")
using ANN
ann = ArtificialNeuralNetwork(12)
ArtificialNeuralNetwork([],[12],[])

fit!(ann,X_train,y_train,epochs=30,alpha=0.1,lambda=1e-5)

y_proba = predict(ann,X_test)

y_pred = Array(Int64,length(y_test))

for i in 1:length(y_test)
    # must translate class index to label
    y_pred[i] = ann.classes[indmax(y_proba[i,:])]
end

println("Prediction accuracy: ",mean(y_pred .== y_test))

function confusion_matrix(y_true::Array{Int64,1},y_pred::Array{Int64,1})
    # Generate confusion matrix
    classes = sort(unique([unique(y_true),unique(y_pred)]))
    cm = zeros(Int64,length(classes),length(classes))
    
    for i in 1:length(y_test)
        # translate label to index
        true_class = findfirst(classes,y_test[i])
        pred_class = findfirst(classes,y_pred[i])
        # pred class is the row, true class is the column
        cm[pred_class,true_class] += 1
    end
    cm
end

confusion_matrix(y_test,y_pred)
