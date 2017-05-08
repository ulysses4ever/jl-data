function fscore(clusters,assigned)
    results = zeros(length(clusters),4);
    for i=1:length(clusters)
        for j=1:length(clusters)
            c_r = [clusters[i]; clusters[j]]
            c_a = [assigned[i]; assigned[j]]
            if (c_r[1] == c_r[2])&(c_a[1] == c_a[2])
                results[i,1] += 1
            elseif (c_r[1] == c_r[2])&(c_a[1] != c_a[2])
                results[i,2] += 1
            elseif (c_r[1] != c_r[2])&(c_a[1] == c_a[2])
                results[i,3] += 1
            else
                results[i,4] += 1
            end
        end
    end
    results_sum = sum(results,1)/2;
    p = results_sum[1]/(results_sum[1]+results_sum[3])
    r = results_sum[1]/(results_sum[1]+results_sum[2])
    return 2*(p*r)/(p+r)
end