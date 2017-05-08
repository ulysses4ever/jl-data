Pkg.add("Distributions")

using Distributions

function dropoutVec(d_percent,len)
  d = Binomial(1,d_percent)
  return rand(d,len)
end

X = [0 0 1;
     0 1 1;
     1 0 1;
     1 1 1];

y = [0;
     1;
     1;
     0];

#Setting network parameters
(alpha,hidden_dim) = (0.5,4);

(dropout, dropout_percent) = (true,0.5)

synapse_0 = 2*randn(3,hidden_dim) - 1;
synapse_1 = 2*randn(hidden_dim,1) - 1;

layer_1 = [];
layer_2 = [];

for j in 1:60000
  layer_1 = 1./(1+exp(-X*synapse_0));

  if(dropout)
    layer_1 *= reshape(dropoutVec(dropout_percent,length(layer_1)),size(layer_1))
  end

  layer_2 = 1./(1+exp(layer_1*synapse_1));

  layer_2_delta = (layer_2 - y).*(layer_2.*(1-layer_2));
  layer_1_delta = layer_2_delta*transpose(synapse_1) * layer_1*(1-layer_1);

  synapse_1 -= (alpha * layer_1*layer_2_delta);
  synapse_0 -= (alpha * transpose(X)*layer_1_delta);
end

display("Output after training:")
display(layer_1)
display(layer_2)