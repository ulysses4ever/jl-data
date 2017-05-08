X = [0 0 1;
     0 1 1;
     1 0 1;
     1 1 1];

y = [0;
     1;
     1;
     0];

(alpha,hidden_dim) = (0.5,4);

synapse_0 = 2*randn(3,hidden_dim) - 1;
synapse_1 = 2*randn(hidden_dim,1) - 1;

layer_1 = [];
layer_2 = [];

for j in 1:60000
  layer_1 = 1./(1+exp(-X*synapse_0));
  layer_2 = 1./(1+exp(layer_1*synapse_1));

  layer_2_delta = (layer_2 - y).*(layer_2.*(1-layer_2));
  layer_1_delta = layer_2_delta*transpose(synapse_1) * layer_1*(1-layer_1);

  synapse_1 -= (alpha * layer_1*layer_2_delta);
  synapse_0 -= (alpha * transpose(X)*layer_1_delta);
end

display("Output after training:")
display(layer_1)
display(layer_2)