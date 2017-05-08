module Kmeans

using Gadfly

export kmeans, plot_j_vs_k, plot_j_hist

# Clusters a dataset using the k-means algorithm. The k-means algorithm is covered in the
# book in section 2.4, and does the following:
#
# repeat until convergence:
#   assign data points to closest centroid (the partition_data function)
#   set centroids to be mean of their assigned data points (the update_centroids function)
#
# Parameters:
#   data - The datset to cluster, represented as an Array of N n-vectors
#          (N column vectors of length n).
#   k    - The number of clusters in the data.
#
# Returns:
#   centroids - The cluster centroids represented as an array of k column vectors of length n.
#   labels    - An array of N cluster assignments in the same order as data, so that
#               the 1st data point's cluster assignment is labels[i]. The labels themselves
#               index into the centroids list, i.e. centroids[labels[1]] returns the
#               first data point's centroid.
#   losses    - An array containing the value of J at each iteration.
#
# Usage:
#   k = 5; N=200; n=10
#   # generate a list of 200 random 10-vectors
#   data = [ rand(n) for x in 1:N ]
#   centroids, labels, losses = kmeans(data,k)
#   # print the vectors assigned to each cluster
#   for i=1:k
#     print(data[labels .== i])
#   end
#
function kmeans(data, k)
  epsilon = 1e-6
  losses = Float64[]
  N = length(data)
  n = length(data[1])
  centroids, labels = initialize_centroids(data, k)
  while true
    labels = partition_data(data, centroids)
    centroids = update_centroids(data, labels, k, centroids)
    push!(losses, loss(data,centroids,labels))
    if length(losses) >= 2 && abs(losses[end] - losses[end-1]) <= epsilon
      break
    end
  end
  return centroids, labels, losses
end

# Assigns each data point to the closest centroid
function partition_data(data, centroids)
  labels = Int[]
  for i in 1:length(data)
    # calculate the euclidean distance from the ith data point to each centroid
    centroid_distances = pairwise_distance(data[i], centroids)
    # find the centroid closest to the ith data point
    distance, centroid_index = findmin(centroid_distances)
    push!(labels, centroid_index)
  end
  return labels
end

# Calculates each centroid as the mean of it's data points
function update_centroids(data, labels, k, old_centroids)
  centroids = Vector[]
  for i = 1:k
    # get the data points assigned to the centroid
    centroid_pts = data[labels .== i]
    # if the centroid has assigned data points, set it to be their mean
    if length(centroid_pts) > 0
      push!(centroids, mean(centroid_pts))
    else # otherwise, leave it alone
      push!(centroids, old_centroids[i])
    end
  end
  return centroids
end

# Calculates the loss (J) of the given clustering.
function loss(data, centroids, labels)
  N = length(data)
  sos_dist = 0.0
  for i = 1:N
    sos_dist += norm(data[i] - centroids[labels[i]])^2
  end
  return sos_dist*(1/N)
end

# Picks the starting centroids
# by randomly assigning data points to each centroid.
function initialize_centroids(data, k)
  N = length(data)
  n = length(data[1])
  labels = rand(1:k,N)
  centroids = update_centroids(data, labels, k, {zeros(n) for i=1:k})
  return centroids, labels
end

# Plots the values of J after each iteration for a run of k-means.
#
# Parameters:
#   j_hist - A vector of numbers representing J after each iteration. This vector is the third
#            value returned from the kmeans() function
# Output:
#   A properly formatted plot in your browser
#
function plot_j_hist(j_hist)
    plot(y=j_hist, x=1:length(j_hist), Geom.line,
      Guide.XLabel("Iteration"), Guide.YLabel("J"),
      Guide.xticks(ticks=[1:length(j_hist)]))
end

# Plots the values of J vs k for a series of runs of k-means.
#
# Parameters:
#   js - A 9-vector containing the value of J for k=2,...,10.
#
# Output:
#   A properly formatted plot in your browser.
#
function plot_j_vs_k(js)
    plot(y=js, x=2:10, Geom.line,
      Guide.XLabel("k"), Guide.YLabel("J"),
      Guide.xticks(ticks=[2:10]))
end

# Calculates the Eudclidean distance between vector and each vectors in 'vectors',
# returning an array.
function pairwise_distance(vector, vectors)
  return Float64[norm(vector - vectors[i]) for i=1:length(vectors)]
end

end
