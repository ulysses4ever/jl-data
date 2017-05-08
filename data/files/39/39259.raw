using Clustering
using DataFrames
using BioFeatures
using Distances

function clusters_by_size_order_permutation(cluster_object)
    cluster_assignments =  assignments(cluster_object)
    cluster_counts      =  counts(cluster_object)
    println("CLUSTER COUNTS: ", cluster_counts)

    cluster_size = {i => cluster_counts[i] for i in cluster_assignments}
    cluster_assignments_size_labels = Int64[]

    for c in cluster_assignments
         c_size = cluster_size[c]
         push!( cluster_assignments_size_labels, c_size )
    end
    #sort_order = sortperm(cluster_assignments_size_labels)
  println("finished cluster_assignments_size_labels")
  return cluster_assignments_size_labels
end
#=
function clusters_by_size_order_permutation(cluster_assignments)
    clusters = unique(cluster_assignments)
    println(clusters)
    num_clusters = length(clusters)

    # obtain counts in each cluster label
    h = hist(cluster_assignments, [i for i=0:num_clusters])
    println(h)
    h = h[2]
    println("Got these clusters $h")
    # now make dictionary mapping the current labels (1 to n )
    # to a label that is the size of how many are in the cluster
    cluster_size = {i => h[i] for i = 1:num_clusters}
    println("cluster size: $cluster_size")
    cluster_assignments_size_labels = Int64[]
    println("do for loop btw: cluster_assignments_size_labels")
    for c in cluster_assignments
         c_size = cluster_size[c]
         push!( cluster_assignments_size_labels, c_size )
    end
    # println("pushed on to $cluster_assignments_size_labels")
  #sort_order = sortperm(cluster_assignments_size_labels)
  return cluster_assignments_size_labels
end
function order_vector(vector,cluster_assignments)
    #sort_order = sortperm(cluster_assignments)
    cluster_assignments_size_labels = clusters_by_size_order_permutation(cluster_assignments)
    sort_order = sortperm(cluster_assignments_size_labels)
    sort!(cluster_assignments_size_labels)
    return ( vector[sort_order], cluster_assignments_size_labels)
end
=#
function order_vector(vector,cluster_object)
    #sort_order = sortperm(cluster_assignments)
    cluster_assignments_size_labels = clusters_by_size_order_permutation(cluster_object)
    sort_order = sortperm(cluster_assignments_size_labels)
    sort!(cluster_assignments_size_labels)
    return ( vector[sort_order], cluster_assignments_size_labels)
end

function order_matrix(tiles_matrix,cluster_object)
    #cluster_assignments =  assignments(cluster_object)
    #cluster_counts      =  counts(cluster_object)
    #cluster_size = {i => cluster_counts[i] for i in cluster_assignments}
    #cluster_assignments_size_labels = Int64[]
    #println("do for loop btw: cluster_assignments_size_labels")
    #for c in cluster_assignments
    #     c_size = cluster_size[c]
    #     push!( cluster_assignments_size_labels, c_size )
    #end
    #sort_order = sortperm(cluster_assignments_size_labels)
   cluster_assignments_size_labels = clusters_by_size_order_permutation(cluster_object)
   sort_order = sortperm(cluster_assignments_size_labels)
   return tiles_matrix[ sort_order,:]
end

#=
function order_matrix( tiles_matrix, cluster_assignments)

    # we want each row to be together with its other cluster members
    # AND we want those groups to be sorted by the number that are in each cluster
    # This means changing the number of the cluster (e.g. 1,2,3 and 4) to the amount
    # that are in the cluster (e.g. 13,445,34 and 67) and sorting on that .

    clusters = unique(cluster_assignments)
    println("CLUSTERS: $clusters")
    num_clusters = length(clusters)

    # obtain counts in each cluster label
    #h = hist(cluster_assignments, [i for i=0:num_clusters])
    h = Dict()
    for cl in cluster_assignments
        if haskey(h,cl)
            h[cl]+=1
        else
           h[cl] = 1
       end
    end
    println("COUNTS PER CLUSTER: $h")
    #h = h[2]
    println("Got these clusters $h")
    # now make dictionary mapping the current labels (1 to n )
    # to a label that is the size of how many are in the cluster
    cluster_size = {i => h[i] for i in cluster_assignments}
    println("cluster size: $cluster_size")
    cluster_assignments_size_labels = Int64[]
    println("do for loop btw: cluster_assignments_size_labels")
    for c in cluster_assignments
         c_size = cluster_size[c]
         push!( cluster_assignments_size_labels, c_size )
    end
    # println("pushed on to $cluster_assignments_size_labels")
    sort_order = sortperm(cluster_assignments_size_labels)
    return tiles_matrix[ sort_order,:] #this doesn't work
end
=#

function cluster_tiles(tiles_matrix;method="kmeans", num_clusters_range=5:5, kmeans_repeats=1,  num_clusters=5,eps=5,minpts=100)

   cluster_assignments = nothing
   tiles_matrix_transpose = tiles_matrix'
   sil_vals = nothing
   if (method == "kmeans")
      #cluster_object = kmeans_cluster_tiles(tiles_matrix_transpose,num_clusters)
      (cluster_object, sil_vals) = kmeans_cluster_tiles(tiles_matrix_transpose,kmeans_repeats, num_clusters_range)
   elseif( method == "affprop"  )
      cluster_object = aff_prop_cluster_tiles(tiles_matrix)
   elseif(method == "dbscan")
     cluster_object = dbscan_hammings(tiles_matrix_transpose,eps,minpts)
     cluster_object.assignments =cluster_object.assignments + 1
     cluster_counts = sum(cluster_object.counts)
     count_label_one = length(cluster_object.assignments) - cluster_counts
     unshift!(cluster_object.counts,count_label_one)
   end

   cluster_assignments = assignments(cluster_object)
   println("CLUSTER ASSIGNMENTS: ", cluster_assignments)

   #tiles_matrix_ordered_by_cluster = order_matrix(tiles_matrix_transpose, cluster_assignments)
   tiles_matrix_ordered_by_cluster = order_matrix(tiles_matrix, cluster_object)

   return (tiles_matrix_ordered_by_cluster, cluster_object,sil_vals)
end

function kmeans_cluster_tiles(tiles_matrix,num_clusters)
    println("kmeans ready")
    tiles_matrix_FLOAT = convert(Array{Float64,2},tiles_matrix)
    kmeans_cluster_object = kmeans(tiles_matrix_FLOAT, num_clusters)
    #cluster_assignments = kmeans_cluster_object.assignments
    #return cluster_assignments
    return kmeans_cluster_object
end

# THIS DOES LOTS MORE THAN THE ABOVE
function kmeans_cluster_tiles(tiles_matrix, num_repetitions, cluster_range)
   println("kmeans (ADVANCED) ready")
    tiles_matrix_FLOAT = convert(Array{Float64,2},tiles_matrix)
  current_mean_sil_val = 0
  current_kmeans_cluster_object = nothing
  #sil_dict = Dict{Int64, Array{Float64}}()
  k_array = Int64[]
  mean_sil_array=Float64[]
  rep_array = Int64[]
  cost_array=Float64[]
  for k in cluster_range
      for r =1:num_repetitions
           println("cluster k $k, repetition $r")
           kmeans_cluster_object = kmeans(tiles_matrix_FLOAT, k)
           distance_matrix = pairwise(SqEuclidean(),tiles_matrix)
           sil_val = silhouettes(kmeans_cluster_object,distance_matrix)
           mean_sil_val = mean(sil_val)
           if mean_sil_val > current_mean_sil_val
               current_kmeans_cluster_object = kmeans_cluster_object
               current_mean_sil_val = mean_sil_val
           end
           println("mean sil val: ", mean_sil_val)
           push!(k_array,k)
           push!(mean_sil_array, mean_sil_val)
           push!(rep_array, r)
           push!(cost_array,kmeans_cluster_object.totalcost)
           println("mean cost: ", kmeans_cluster_object.totalcost)
           println("current sil val: ", current_mean_sil_val )
      end
  end
  sil_df = DataFrame(k=k_array,r=rep_array,ave_sil=mean_sil_array,cost=cost_array)
  return (current_kmeans_cluster_object,sil_df)
end


function dbscan_hammings(tiles_matrix, eps=5,minpts=10)
    println("dbscan ready")
      distance_matrix = pairwise(Hamming(),tiles_matrix)
    ds = dbscan(distance_matrix,eps,minpts)
    return ds #.assignments
end

function aff_prop_cluster_tiles(tiles_matrix)
    println("affinity propogation ready")
    #similarity_matrix = -pairwise(Hamming(),tiles_matrix)
    similarity_matrix = -pairwise(Euclidean(),tiles_matrix)
    af=affinityprop(similarity_matrix)
    return af
end

function cluster_tiles_plot()
end

function cluster_tiles_barplot()
end
