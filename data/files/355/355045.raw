import ANN;
import Boltzmann; #ML libraries
import DataFrames;
using HDF5;
using Gadfly; #Visualisation lib

include("params.jl");
include("loaddata.jl");
include("utils.jl");

X_test = load_test(TEST_PATH);

# Scale values of to range [0;1] (Required by RBM)
X_test = Scale!(X_test, norm);


# Initialize Restricted Boltzmann Machine
rbm = Boltzmann.BernoulliRBM(28*28, RBM_HIDDEN_LAYER);
#Save trained RBM params
h5open(RBM_PARAMS_PATH, "r") do file
    Boltzmann.load_params(file, rbm, "rbm");
end

# Calculate training accuracy on validation set
y_proba = ANN.predict(ann, Boltzmann.transform(rbm, X_test')');
y_pred = getPredictions(ann, y_proba);

dataframe = DataFrames.DataFrame(ImageId=1:size(y_pred)[1],Label=y_pred);
DataFrames.writetable("output/predictions.csv", dataframe);
println("prediction saved");
