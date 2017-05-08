module mlp

using PyCall

@pyimport os
@pyimport sys
@pyimpor time
@pyimport numpy
@pyimport theano
@pyimport theano.tensor as T

import logistic_sgd: LogisticRegression, load_data

type HiddenLayer
  """
  Typical hidden layer of a MLP: units are fully-connected and have
  sigmoidal activation function. Weight matrix W is of shape (n_in, n_out)
  and the bias vector b is of shape(n_out,).

  NOTE: The nonlinearlity used here is tanh.

  Hidden unit activation is given by: tanh(input ⋅ W + b)
  """
  input
  output
  W
  b
  params
  HiddenLayer(input, output, W, b) = begin
    self = new(input, output, W, b)
    self.params = [W, b]
  end
end

# activation is e.g. T.tanh[:__call__]
HiddenLayer(rng, input, n_in, n_out, activation;
            W=None, b=None, activation=T.tanh[:__call__]) = begin
  if W == None
    W_values = numpy.asarray(
      rng.uniform(
        low=-numpy.sqrt(6.0 / (n_in + n_out)),
        high=numpy.sqrt(6.0 / (n_in + n_out)),
        size=(n_in, n_out)
      ),
      dtype=theano.config[:floatX]
    )
    if activation == T.nnet[:sigmoid]
      W_values = W_value * 4
    end
    W = theano.shared(value=W_values, name="W", borrow=true)
  end

  if b == None
    b_values = numpy.zeroes((n_out,), dtype=theano.config[:floatX])
    b = theano.shared(values=b_values, name="b", borrow=true)
  end

  lin_output = T.dot(input, W) + b
  output = if activatio == None
      lin_output
    else
      activation(lin_output)
    end
  HiddenLayer(input, output, W, b)
end

type MLP
  hidden_layer
  log_regression_layer
  norm_l1
  norm_l2
  negative_log_likelihood
  errors
  params
end

end
