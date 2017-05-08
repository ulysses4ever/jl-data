import ANN;
import Boltzmann; #ML libraries
import DataFrames;
using HDF5;

include("params.jl");
include("loaddata.jl");
include("utils.jl");

X_train, X_test, y_train, y_test = load_train(TRAIN_PATH, valid_ratio);

# Scale values of to range [0;1] (Required by RBM)
X_train, norm = Scale!(X_train);
X_test = Scale!(X_test, norm);

# Initialize Restricted Boltzmann Machine
rbm = Boltzmann.BernoulliRBM(28*28, RBM_HIDDEN_LAYER);

#set size of training batches for RBM
bsize=size(X_train)[1]*batch_size;
# Train using constrastive divergence + gibbs sampling
Boltzmann.fit(rbm, X_train';lr=0.1, n_iter=RBM_ITER, batch_size=bsize, n_gibbs=3);
#Save trained RBM params
h5open(RBM_PARAMS_PATH, "w") do file
    Boltzmann.save_params(file, rbm, "rbm");
end

#train ANN using backprop from learnt features.
ann = ANN.ArtificialNeuralNetwork(ANN_HIDDEN_LAYER);

# Transform training data using learnt weights
# train neural net using backprop with input from RBM features
ANN.fit!(ann, Boltzmann.transform(rbm, X_train')', y_train;
    epochs=ANN_ITER, alpha=0.1, lambda=1e-5);

# Calculate training accuracy on validation set
y_proba = ANN.predict(ann, Boltzmann.transform(rbm, X_test')');
y_pred=getPredictions(ann, y_proba);
println("training accuracy: ",mean(y_pred .== y_test))
