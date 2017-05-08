function plot_qubittimeevo(time_vec,excited_prob)
    p = scatter(;x=time_vec*1E9,y=excited_prob,mode="line")

    l = Layout(;title="Qubit Excited State Probability",
    xaxis=attr(title="Interaction Time (ns)", showgrid=false, zeroline=false),
    yaxis=attr(title="Excited Probability"))

    plot(p,l)
end


function plot_photonnumbers(photons)
    p = bar(;x=collect(0:length(photons)-1),y=photons)

    l = Layout(;title="Photon Number Population",
    xaxis=attr(title="n", showgrid=false, zeroline=false),
    yaxis=attr(title="Amplitude"))

    plot(p,l)
end


function plot_densitymatrix(densitymatrix)
    kets = 0
    for m = size(densitymatrix,1):-1:1
        if sum(abs(densitymatrix[m,:]))>0.00001
            kets = collect(0:m-1)
            break
        end
    end

    densitymatrix = densitymatrix[kets+1,kets+1]

    p = heatmap(;z=abs(densitymatrix),
    colorscale="Viridis")

    l = Layout(;title="Magnitude of Density Matrix Elements |ρ_{mn}|",
    xaxis_title="n",
    xaxis_ticktext=kets,
    xaxis_tickvals=kets,
    xaxis_side="top",
    yaxis_title="m",
    yaxis_ticktext=kets,
    yaxis_tickvals=kets,
    yaxis_autorange="reversed")

    plot(p,l)
end

function plot_wignerfunction(matrix)
    x = ((1:size(matrix,1))-size(matrix,1)/2)/10

    p = heatmap(;x=x,y=x,z=matrix,
    zsmooth="best",
    colorscale="Viridis")

    l = Layout(;title="Wigner Function")

    plot(p,l)
end
