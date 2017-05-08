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

