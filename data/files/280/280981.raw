module logistic_sgd

export LogisticRegression,
       negative_log_likelihood,
       errors,
       sgd_optimization_mnist

using PyCall

@pyimport gzip
@pyimport os
@pyimport sys
@pyimport numpy
@pyimport theano
@pyimport theano.tensor as T
@pyimport urllib
@pyimport urllib.request as urlrequest
@pyimport pickle

include("pycommon.jl")

theanofunc = pyimport("theano")["function"][:__call__]

type LogisticRegression
  W
  b
  p_y_given_x
  y_pred
  params
  LogisticRegression(input, n_in, n_out) = begin
    self = new()
    self.W = theano.shared(
               value=numpy.zeros(
                 (n_in, n_out),
                 dtype=theano.config[:floatX]
               ),
               name="W",
               borrow=true
    )
    self.b = theano.shared(
               value=numpy.zeros(
                 (n_out,),
                 dtype=theano.config[:floatX]
               ),
               name="b",
               borrow=true
    )
    self.p_y_given_x = T.nnet[:softmax][:__call__](T.dot(input, self.W) + self.b)
    self.y_pred = T.argmax(self.p_y_given_x, axis=1)
    self.params = [self.W, self.b]
    self
  end
end


function negative_log_likelihood(logreg, y)
  """ Return the mean of the negative loglikelihood of the prediction
      of this model under a given target distribution."""
  println("type of y: $(typeof(y))")
  println("python type of y: $(y[:dtype])")
  println("type of y[:shape]: $(typeof(y[:shape]))")
  println("y[:shape]: $(y[:shape])")
  println("y[:shape][:__getitem__](1): $(y[:shape][:__getitem__](0))")
  order_index = T.arange(y[:shape][:__getitem__](0))
  println("order_index type $(typeof(order_index))")
  tlog = T.log[:__call__](logreg.p_y_given_x)[:__getitem__]((order_index, y))
  println("tlog type $(typeof(tlog))")
  tmean = T.mean(tlog)
  println("tmean type $(typeof(tmean))")
  println("-tmean type $(typeof(-tmean))")
  #-T.mean(T.log(logreg.p_y_given_x)[T.arange(y[:shape][1]), y])
  -tmean
end

function errors(logreg, y)
  """ Return a float representing the number of errors in the minibatch
      over the total number of examples of the minibatch ;
      zero one loss over the size of the minibatch. """
  println("y: $(y)")
  println("y[:ndim]: $(y[:ndim])")
  if y[:ndim] != logreg.y_pred[:ndim]
    error("y should have the same shape as self.y_pred")
  end
  println("y[:dtype]: $(y[:dtype])")
  if y[:dtype][1:3] == "int"
    T.mean(T.neq[:__call__](logreg.y_pred, y))
  else
    error("nyi")
  end
end

function load_data(dataset)
  """ Load the dataset """

  data_dir, data_file = dirname(dataset), basename(dataset)
  if data_dir == ""
    # Check if dataset is in the data directory.
    new_path = joinpath("..", "data", dataset)
    if isfile(new_path) || data_file == "mnist.pkl.gz"
      dataset = new_path
    end
  end

  if !isfile(dataset) && data_file == "mnist.pkl.gz"
    origin = "http://www.iro.umontreal.ca/~lisa/deep/data/mnist/mnist.pkl.gz"
    println("Downloading data from $(origin)")
    #urllib.urlretrieve(origin, dataset)
    urlrequest.urlretrieve(origin, dataset)
  end

  f = gzip.open(dataset, "rb")
  train_set, valid_set, test_set = pickle.load(f, encoding="latin1")
  f[:close]()

  function shared_dataset(data_xy, borrow=true)
    """ Function that laods the dataset into shared variable """
    data_x, data_y = data_xy
    shared_x = theano.shared(numpy.asarray(data_x, dtype=theano.config[:floatX]),
                             borrow=borrow)
    shared_y = theano.shared(numpy.asarray(data_y, dtype=theano.config[:floatX]),
                             borrow=borrow)
    shared_x, T.cast(shared_y, "int32")
  end

  test_set_x, test_set_y = shared_dataset(test_set)
  valid_set_x, valid_set_y = shared_dataset(valid_set)
  train_set_x, train_set_y = shared_dataset(train_set)

  rval = [(train_set_x, train_set_y), 
          (valid_set_x, valid_set_y),
          (test_set_x, test_set_y)]
  rval
end

function sgd_optimization_mnist(learning_rate=0.13, n_epochs=1000,
                                dataset="mnist.pkl.gz", batch_size=500)
  """ Demonstrate stochastic gradient descent optimization of a log-linear model """

  datasets = load_data(dataset)
  train_set_x, train_set_y = datasets[1]
  valid_set_x, valid_set_y = datasets[2]
  test_set_x, test_set_y = datasets[3]

  # compute number of minibatches for training, validation and testing.
  println("train set size type: $(typeof(train_set_x[:get_value](borrow=true)))")
  println("train set size $(size(train_set_x[:get_value](borrow=true), 1))")
  n_train_batches = size(train_set_x[:get_value](borrow=true), 1) / batch_size
  n_valid_batches = size(valid_set_x[:get_value](borrow=true), 1) / batch_size
  n_test_batches = size(test_set_x[:get_value](borrow=true), 1) / batch_size

  ######################
  # BUILD ACTUAL MODEL #
  ######################

  println("building the model...")

  # allocate symbolic variables for the data.
  index = T.lscalar[:__call__]()  # index to a [mini]batch

  # generate symbolic variables for input (x and y represent a minibach)
  x = T.matrix("x")   # data, presented as rasterized images.
  y = T.ivector[:__call__]("y")  # labels, presented as 1D vector of [int] labels.

  # construct the logistic regression class.
  # each MNIST image has size 28x28.
  classifier = LogisticRegression(x, 28*28, 10)
  println(typeof(classifier))
  println("negative_log_likelihood type: $(typeof(negative_log_likelihood))")
  println("classifier type: $(typeof(classifier))")
  println("y type: $(typeof(y))")
  cost = negative_log_likelihood(classifier, y)

  println("y: $(y)")
  println("y[:shape]: $(y[:shape])")

  println("errors: $(errors(classifier, y))")
  # compiling a theano function that computes the mistakes that are
  # made by the model on a minibatch.
  println(test_set_x[:__getitem__](pyslice(index*batch_size, (index+1)*batch_size)))
  test_model = theanofunc(
    inputs=[index],
    outputs=errors(classifier, y),
    givens={
      x => test_set_x[:__getitem__](pyslice(index*batch_size, (index + 1)*batch_size)),
      y => test_set_y[:__getitem__](pyslice(index*batch_size, (index + 1)*batch_size))
    }
  )[:__call__]

  validate_model = theanofunc(
    inputs=[index],
    outputs=errors(classifier, y),
    givens={
      x => valid_set_x[:__getitem__](pyslice(index*batch_size, (index + 1)*batch_size)),
      y => valid_set_y[:__getitem__](pyslice(index*batch_size, (index + 1)*batch_size))
    }
  )[:__call__]

  # compute the gradient of cost with respect to θ = (W, b)
  println("typeof(cost): $(typeof(cost))")
  g_W = T.grad(cost=cost, wrt=classifier.W)
  g_b = T.grad(cost=cost, wrt=classifier.b)

  # specify how to update the parameters of the model 
  # as a list of (variable, update expresion) pairs.
  updates = [(classifier.W, classifier.W - learning_rate * g_W),
             (classifier.b, classifier.b - learning_rate * g_b)]
  # compiling a theano function `train_model` that returns the cost, but in
  # the same time updates parameter of the model based on the rules
  # defined in `updates`.
  train_model = theanofunc(
    inputs=[index],
    outputs=cost,
    updates=updates,
    givens={
      x => train_set_x[:__getitem__](pyslice(index*batch_size, (index + 1)*batch_size)),
      y => train_set_y[:__getitem__](pyslice(index*batch_size, (index + 1)*batch_size))
    }
  )[:__call__]

  println("training the model...")
  # early-stopping parameters.
  patience = 5000 # look as this many examples regardles.
  patience_increase = 2 # wait this much longer when a new best is found.
  improvement_threshold = 0.995 # a relative improvement of this much is considered significant.
  validation_frequency = min(n_train_batches, patience / 2) # go throught this many
                                                            # minibaches before checking the network
                                                            # on the validation set; in this case
                                                            # we check every epoch.
  best_validation_loss = Inf
  println("validation frequency: $(validation_frequency)")
  test_score = 0.0
  @time begin
    done_looping = false
    epoch = 0
    while epoch < n_epochs && !done_looping
      epoch += 1
      for minibatch_index in 0:n_train_batches-1
        minibatch_avg_cost = train_model(minibatch_index)
        # iteration number.
        iter = (epoch - 1) * n_train_batches + minibatch_index
        if (iter+1) % validation_frequency == 0
          # compute zero-one loss on validation set
          validation_losses = [validate_model(i) for i in 0:n_valid_batches-1]
          this_validation_loss = numpy.mean(validation_losses)
          println("validation_losses type: $(typeof(this_validation_loss))")
          println("validation_losses: $(this_validation_loss)")
          println("this_validation_loss type: $(typeof(this_validation_loss))")
          println("this_validation_loss: $(this_validation_loss)")
          println("epoch $(epoch), minibatch $(minibatch_index+1)/$(n_train_batches), validation error $(this_validation_loss*100)%")

          # if we got the best validation score until now,
          if this_validation_loss < best_validation_loss
            # improve patience if loss improvement is good enough.
            if this_validation_loss < best_validation_loss * improvement_threshold
              patience = max(patience, iter * patience_increase)
            end
            best_validation_loss = this_validation_loss
            #test it on the test set.
            test_losses = [test_model(i) for i in 0:n_test_batches-1]
            test_score = numpy.mean(test_losses)
            print("    epoch $(epoch), minibatch $(minibatch_index+1)/$(n_train_batches), test error of best model $(test_score*100)%")
          end
        end
        if patience <= iter
          done_looping = true
          break
        end
      end
    end
  end
  println("Optimization complete with best validation score of $(best_validation_loss*100)% with test performance $(test_score*100)%")
end

end
