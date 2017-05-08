using Gadfly

function plot_matrix( tiles_matrix, path )
     light_blue = color("blue")
     dark_blue  = color("red")
     sc = Scale.ContinuousColorScale(Scale.lab_gradient( dark_blue,
                                                         light_blue ) )
     num_rows = size(tiles_matrix,1)
     Gadfly.draw(PNG( path, 10inch, 10inch), spy2( tiles_matrix,  sc, Scale.y_continuous(maxvalue=num_rows) ) )
     # or call the R code, because the time this takes can be excessive??
end

function plot_matrix2(tiles_matrix,path; colour_scale =Scale.discrete_color_manual("black","red","green") )
    #border1 = color("blue")
    #border2 = color("green")
    num_rows = size(tiles_matrix,1)
    #sc = Scale.ContinuousColorScale(Scale.lab_gradient( border1,
    #                                                    border2 ) )
    #dc =Scale.discrete_color_manual("black","red","green")
    is, js, values = findnz(tiles_matrix)
    df = DataFrame(i=is, j=js, value=values)
    T = Theme(panel_fill=color("black"))
    p = Gadfly.plot(df, x="j", y="i", color="value",
        T,
        Coord.cartesian(yflip=true),
        #Scale.continuous_color,
        colour_scale,
        Scale.x_continuous,
        Scale.y_continuous(maxvalue=num_rows),
        Geom.rectbin,
        Stat.identity)

    Gadfly.draw(PNG( path, 10inch, 10inch), p )
end

# So you want to get the number of genes in each cluster and make a bar plot of those
# But the bar plot should be coloured by the average methylation level
# So we have to get a value for the average number of tiles methylated

# A. Get the number in each cluster
# B. Get the average methylation for each cluster

function plot_cluster_bar_chart(tiles_matrix, cluster_assignments,path,id=""; gadfly_theme = Theme(major_label_color = color("black"), minor_label_color=color("black")) )

    # GET NUMBERS OF REGIONS IN EACH CLUSTER
    # Make dictionary with keys as cluster_id
    # and value how many regions in each cluster
    cluster_counts = Dict{Int64,Int64}()
    for c in cluster_assignments
        if haskey( cluster_counts,c )
            cluster_counts[c] +=1
        else
            cluster_counts[c]=1
        end
     end

    # GET SUM OF TILES VALUES FOR EACH REGION
    i=1
    cluster_value_sum =Dict{Int64,Float64}()
    tiles_matrix_transpose = tiles_matrix
    for c in cluster_assignments
         sum_of_tiles = sum(tiles_matrix_transpose[i,:])
         if haskey(cluster_value_sum,c)
             cluster_value_sum[c] +=sum_of_tiles
         else
             cluster_value_sum[c] = sum_of_tiles
         end
         i +=1
     end

     # CALCULATE AVERAGE VALUE TILES FROM EACH REGION
     ave_cluster_value = Float64[]
     cluster_num = Int64[]
     for k in sort(collect(keys(cluster_value_sum)))
        println(cluster_value_sum[k])
        println(cluster_counts[k])
        ave_value_tiles = cluster_value_sum[k] / cluster_counts[k]
        push!(ave_cluster_value, ave_value_tiles)
        push!(cluster_num,cluster_counts[k])
     end

     # PLOT
     #sort_by_clusterN = sortperm(cluster_num,rev=true)
     df = DataFrame( average_cluster_value = ave_cluster_value, cluster_num = cluster_num)
     sort!(df, cols = [:cluster_num],rev=true)
     nrows = nrow(df)
     if nrows > 15
         nrows = 15
     end
     df = df[1:nrows,:]
     gp1 = plot(df, x=1:nrows, y="cluster_num", color="average_cluster_value",
         gadfly_theme,Geom.bar,
         Guide.title("Genes in Cluster $id"),
         Guide.xlabel("Cluster Number"),
         Guide.ylabel("Num of Regions"),
         Guide.colorkey("Avg Tiles Value"),
         Scale.y_continuous(format=:plain))
     Gadfly.draw(PNG(path,20cm, 15cm), gp1)
     return gp1
end
