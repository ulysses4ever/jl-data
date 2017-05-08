module Kmeans

using Distances # for pairwise()
using StatsBase # for sample()

export kmeans, loss

# Cluster a dataset using the k-means algorithm. The k-means algorithm is covered in the
# book in section 2.4 , but generally does the following:
# 
# repeat until convergence:
#   assign data points to closest centroid (the assign_labels function)
#   set centroids to be mean of their assigned data points (the calculate_centroids function)
# 
# This implementation of k-means runs for 100 iterations instead of checking for convergence.
# It also picks the starting centroids using the initialize_centroids function instead of randomly 
# initializing them. Picking starting centroids is beyond the scope of this class, so you don't 
# need to worry about understanding the functions initialize_centroids() or kmeans_pp().
#
# Parameters: 
#   data - The datset to cluster, represented as a list of N m-vectors 
#          (column vectors of length m).
#   k    - The number of clusters in the data.
# 
# Returns:
#   centroids - The cluster centroids represented as a list of k column vectors.
#   labels    - A list of N cluster assignments, represented as integers so that
#               labels[labels .== i] returns the indices of all data points assigned
#               to cluster i, and data[labels[labels .== 1]] returns all data points
#               assigned to cluster i.
# Usage:
#   using Kmeans
#   k = 5; N=200; n=10
#   # generate a list of 200 random 10-vectors
#   data = { rand(n) for x in 1:N }
#   centroids, labels = kmeans(data,k)
#   # print the loss (J) for the clustering
#   print(loss(data,centroids,labels))
#   # print the vectors assigned to each cluster
#   for i=1:k
#     print(data[labels .== i])
#   end
function kmeans(data, k; iters=100)
  # determine the size of the data
  n,m = size(data)
  # intialize the centroids
  centroids = initialize_centroids(data, k)
  labels = zeros(Int, m)
  iter = 0
  while iter < iters
    # assign data points to nearest centroid
    labels = assign_labels(data, centroids)
    # calculate new centroids from data points
    centroids = calculate_centroids(data, labels, k, centroids)
    iter += 1
  end
  return centroids, labels
end

# Assigns each data point in 'data' to the closest centroid in 'centroids'
function assign_labels(data, centroids)
  # initialize an n-vector to store labels
  labels = zeros(Int, size(data,2))
  for i in 1:size(data, 2) # for each data point
    # calculate the euclidean distance from the ith data point to each centroid
    centroid_distances = pairwise(Euclidean(), data[:,i]'', centroids)
    # find the centroid closest to the ith data point
    distance, centroid = findmin(centroid_distances)
    labels[i] = centroid
  end
  return labels 
end

# Calculates each centroid's position as the mean of the data points assigned to it
function calculate_centroids(data, labels, k, old_centroids)
  n = size(data,1)
  centroids = zeros(n,k)
  for i = 1:k # for each centroid
    # get the data points assigned to the centroid
    centroid_data = data[:, labels .== i]
    # if the centroid has assigned data points, set it to be their mean
    if size(centroid_data, 2) > 0
      centroids[:,i] = sum(centroid_data, 2)/size(centroid_data,2)
    else # otherwise, leave it alone
      centroids[:,i] = old_centroids[:,i]
    end
  end
  return centroids
end

# Calculates the loss (J) of the given clustering
function loss(data, centroids, labels)
  sos_dist = 0.0
  _,m = size(data)
  for i = 1:m
    sos_dist += norm(data[:,i] - centroids[:,labels[i]])^2
  end
  return sos_dist*(1/m)
end

# Picks the starting centroids
# You DO NOT need to understand this function
function initialize_centroids(data, k; num_inits=4)
  losses = zeros(num_inits)
  choices = {}
  for i=1:num_inits
    centroids = kmeans_pp(data,k)
    push!(choices,centroids)
    labels = assign_labels(data,centroids)
    losses[i] = loss(data,centroids,labels)
  end
  val,ind = findmin(losses)
  return choices[ind]
end

# Helper function for picking the starting centroids
# You DO NOT need to understand this function
function kmeans_pp(data,k)
  n,num_obs = size(data)
  centroids = zeros(n,k)
  centroids[:,1] = data[:,rand(1:num_obs)]
  for i = 2:k
    dists = minimum(pairwise(Euclidean(), centroids[:,1:i-1]'',data),1).^2
    cind = sample(WeightVec(vec(dists./sum(dists))))
    centroids[:,i] = data[:,cind]
  end
  return centroids 
end

end
