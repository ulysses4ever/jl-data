using Plotly
using Requests

function getInnerOrBoundaryMaximum(a)
  gotit = 0
  mx = Float64[]
  cfe1 = Dict()
  cfe2 = Dict()
  for i in 2:size(a,1)-1
    for j in 1:size(a,2)-1
      if (j>1 &&
            a[i,j] > a[i-1,j-1] &&
            a[i,j] > a[i  ,j-1] &&
            a[i,j] > a[i+1,j-1] &&
            a[i,j] > a[i-1,j  ] &&
            a[i,j] > a[i+1,j  ] &&
            a[i,j] > a[i-1,j+1] &&
            a[i,j] > a[i  ,j+1] &&
            a[i,j] > a[i+1,j+1]) ||
          (a[i,j] > a[i-1,j  ] &&
             a[i,j] > a[i+1,j  ] &&
             a[i,j] > a[i-1,j+1] &&
             a[i,j] > a[i  ,j+1] &&
             a[i,j] > a[i+1,j+1])
        push!(mx, a[i,j])
        cfe1[a[i,j]] = i/1000
        cfe2[a[i,j]] = j/1000
        #if gotit != 0
        #  print("Found multiple inner peaks!!!\n");
        #end
        gotit += 1
      end
    end
  end
  if gotit != 0
    m = maximum(mx)
    return (m, cfe1[m], cfe2[m])
  else
    return (NaN, NaN, NaN)
  end
end

function getInnerMaximum(a)
  gotit = 0
  mx = Float64[]
  cfe1 = Dict()
  cfe2 = Dict()
  for i in 2:size(a,1)-1
    for j in 2:size(a,2)-1
      if  a[i,j] > a[i-1,j-1] &&
          a[i,j] > a[i  ,j-1] &&
          a[i,j] > a[i+1,j-1] &&
          a[i,j] > a[i-1,j  ] &&
          a[i,j] > a[i+1,j  ] &&
          a[i,j] > a[i-1,j+1] &&
          a[i,j] > a[i  ,j+1] &&
          a[i,j] > a[i+1,j+1]
        push!(mx, a[i,j])
        cfe1[a[i,j]] = i/1000
        cfe2[a[i,j]] = j/1000
        #if gotit != 0
        #  print("Found multiple inner peaks!!!\n");
        #end
        gotit += 1
      end
    end
  end
  if gotit != 0
    m = maximum(mx)
    return (m, cfe1[m], cfe2[m])
  else
    return (NaN, NaN, NaN)
  end
end

Plotly.signin("arakitin", "j9zjom7mnc")

tri_meta = readcsv("/Users/arakitin/Downloads/v2_verification_sifs_w_results-1.csv")

v2ver_meta = readcsv("/Users/arakitin/Downloads/singleton_meta.csv")

v2ver = Int64[]
v2ver_data = readcsv("/Users/arakitin/Downloads/singleton_data.csv")
for i = 2:size(v2ver_data, 1)
  cfe13_2 = v2ver_data[i, find(v2ver_data[1,:] .== " cfe13_2 ")]
  cfe18_2 = v2ver_data[i, find(v2ver_data[1,:] .== " cfe18_2 ")]
  cfe21_2 = v2ver_data[i, find(v2ver_data[1,:] .== " cfe21_2 ")]
  #if max(cfe13_2, cfe18_2, cfe21_2) > 0.001
  push!(v2ver, v2ver_data[i, find(v2ver_data[1,:] .== "sif")][1])
  #end
end

twins_meta = readcsv("/Users/arakitin/Downloads/twins_meta.csv")

non_identical_twins = Int64[]
identical_twins = Int64[]
twins_data = readcsv("/Users/arakitin/Downloads/twins_data.csv")
for i = 2:size(twins_data, 1)
  cfe13_2 = twins_data[i, find(twins_data[1,:] .== " cfe13_2 ")]
  cfe18_2 = twins_data[i, find(twins_data[1,:] .== " cfe18_2 ")]
  cfe21_2 = twins_data[i, find(twins_data[1,:] .== " cfe21_2 ")]
  if max(cfe13_2[1], cfe18_2[1], cfe21_2[1]) > 0.001
    push!(non_identical_twins, twins_data[i, find(twins_data[1,:] .== "sif")][1])
  else
    push!(identical_twins, twins_data[i, find(twins_data[1,:] .== "sif")][1])
  end
end

for zzz in [1 2 3]

  if zzz==1
    list = non_identical_twins
    list_meta = twins_meta
    what = "non-identical-twins"
  elseif zzz==2
    list = identical_twins
    list_meta = twins_meta
    what = "identical-twins"
  elseif zzz==3
    list = v2ver
    list_meta = v2ver_meta
    what = "v2ver"
  end

  len = length(list)

  statCFE = fill(NaN, len)
  nocall  = fill(NaN, len)

  MaxLikeA13 = fill(NaN, len)
  MaxLikeB13 = fill(NaN, len)
  MaxLikeR13 = fill(NaN, len)
  MaxLikeD13 = fill(NaN, len)
  MaxLikeA18 = fill(NaN, len)
  MaxLikeB18 = fill(NaN, len)
  MaxLikeR18 = fill(NaN, len)
  MaxLikeD18 = fill(NaN, len)
  MaxLikeA21 = fill(NaN, len)
  MaxLikeB21 = fill(NaN, len)
  MaxLikeR21 = fill(NaN, len)
  MaxLikeD21 = fill(NaN, len)

  cfe1fromMaxLikeA13 = fill(NaN, len)
  cfe2fromMaxLikeA13 = fill(NaN, len)
  cfe1fromMaxLikeB13 = fill(NaN, len)
  cfe2fromMaxLikeB13 = fill(NaN, len)
  cfe1fromMaxLikeA18 = fill(NaN, len)
  cfe2fromMaxLikeA18 = fill(NaN, len)
  cfe1fromMaxLikeB18 = fill(NaN, len)
  cfe2fromMaxLikeB18 = fill(NaN, len)
  cfe1fromMaxLikeA21 = fill(NaN, len)
  cfe2fromMaxLikeA21 = fill(NaN, len)
  cfe1fromMaxLikeB21 = fill(NaN, len)
  cfe2fromMaxLikeB21 = fill(NaN, len)

  cc = 0
  for sif in list
    cc += 1

    print(string(sif)*"   "*string(cc/0.01/length(list))*" %\n");

    resp = Requests.get("http://stats-dev:8080/stats/rest//utility/"*string(sif)*"/cfe/likelihoods")

    if resp.data == ""
      println("Faulty sif "*string(sif))
      continue
    end

    str = resp.data
    str = replace(str, "<", "")
    str = replace(str, ">", "")
    str = replace(str, "/", "")
    str = replace(str, "html", "")
    str = replace(str, "head", "")
    str = replace(str, "body", "")
    str = replace(str,"nan", "-Inf")
    str = replace(str, "\n", " ")
    str = replace(str, ",", " ")
    eval(parse(str))

    statCFE[cc] = list_meta[find(list_meta[:,1] .== sif), find(list_meta[1,:] .== " statCFE")][1]

    (MaxLikeA13[cc], cfe1fromMaxLikeA13[cc], cfe2fromMaxLikeA13[cc]) = getInnerMaximum(chr13[:,3:end])
    (MaxLikeB13[cc], cfe1fromMaxLikeB13[cc], cfe2fromMaxLikeB13[cc]) = getInnerOrBoundaryMaximum(chr13[:,1:4])
    if maximum(chr13) != max(MaxLikeA13[cc], MaxLikeB13[cc])
      println("Chr13: Maximum mismatch ", maximum(chr13), " and ", max(MaxLikeA13[cc], MaxLikeB13[cc]))
    end
    #if ~isnan(MaxLikeA13[end]) && ~isnan(MaxLikeB13[end])
    #  print("Double-peak diff "*string(MaxLikeA13[end] - MaxLikeB13[end])*" in sif "*string(sif)*", chr13, ")
    #  println("CFE = ", statCFE[end])
    #end

    (MaxLikeA18[cc], cfe1fromMaxLikeA18[cc], cfe2fromMaxLikeA18[cc]) = getInnerMaximum(chr18[:,3:end])
    (MaxLikeB18[cc], cfe1fromMaxLikeB18[cc], cfe2fromMaxLikeB18[cc]) = getInnerOrBoundaryMaximum(chr18[:,1:4])
    if maximum(chr18) != max(MaxLikeA18[cc], MaxLikeB18[cc])
      println("Chr18: Maximum mismatch ", maximum(chr18), " and ", max(MaxLikeA18[cc], MaxLikeB18[cc]))
    end
    #if ~isnan(MaxLikeA18[end]) && ~isnan(MaxLikeB18[end])
    #  print("Double-peak diff "*string(MaxLikeA18[end] - MaxLikeB18[end])*" in sif "*string(sif)*", chr18, ")
    #  println("CFE = ", statCFE[end])
    #end

    (MaxLikeA21[cc], cfe1fromMaxLikeA21[cc], cfe2fromMaxLikeA21[cc]) = getInnerMaximum(chr21[:,3:end])
    (MaxLikeB21[cc], cfe1fromMaxLikeB21[cc], cfe2fromMaxLikeB21[cc]) = getInnerOrBoundaryMaximum(chr21[:,1:4])
    if maximum(chr21) != max(MaxLikeA21[cc], MaxLikeB21[cc])
      println("Chr21: Maximum mismatch ", maximum(chr21), " and ", max(MaxLikeA21[cc], MaxLikeB21[cc]))
    end
    #if ~isnan(MaxLikeA21[end]) && ~isnan(MaxLikeB21[end])
    #  print("Double-peak diff "*string(MaxLikeA21[end] - MaxLikeB21[end])*" in sif "*string(sif)*", chr21 ")
    #  println("CFE = ", statCFE[end])
    #end

    review = tri_meta[find(tri_meta[:,find(tri_meta[1,:] .== "sif_id")] .== sif), find(tri_meta[1,:] .== "review_result")]
    if (size(review,1)==1)
      nocall[cc] = (review[1][1:7] == "NO_CALL")
    else
      nocall[cc] = true # Assuming no-call if not-known
    end
  end

  for c in ["13" "18" "21"]

    MaxLikeA = [
      "13" => MaxLikeA13,
      "18" => MaxLikeA18,
      "21" => MaxLikeA21
      ]

    MaxLikeB = [
      "13" => MaxLikeB13,
      "18" => MaxLikeB18,
      "21" => MaxLikeB21
      ]

    layout = [
      "title" => "Chr. "*c*": Max. Lik. @ Area and Max. Lik. @ Boundary"
      ]

    data = [
      [
        "x" => MaxLikeA[c][~isnan(MaxLikeA[c])],
        "name" => "Max. Lik. @ Area",
        "opacity" => 0.75,
        "type" => "histogram"
        ],
      [
        "x" => MaxLikeB[c][~isnan(MaxLikeB[c])],
        "name" => "Max. Lik. @ Boundary",
        "opacity" => 0.75,
        "type" => "histogram"
        ]
      ]

    response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chr"*c, "fileopt" => "overwrite"])

    ratio = MaxLikeA[c] ./ MaxLikeB[c]

    MaxLikeRA = log10(-1 .+ ratio[ratio.>1])
    MaxLikeRB = log10( 1 .- ratio[ratio.<1])

    layout = [
      "title" => "Chr. "*c*": Max. Lik. @ Area and Max. Lik. @ Boundary" ,
      "xaxis" => [
        "title" => "log10(1 - A/B), if |A| < |B|, log10(A/B - 1) otherwise"
        ],
      "yaxis" => [
        "title" => "Frequency of occurrence"
        ]
      ]

    data = [
      [
        "x" => MaxLikeRA[~isnan(MaxLikeRA)],
        "name" => "Boundary peak dominates",
        "opacity" => 0.75,
        "type" => "histogram"
        ],
      [
        "x" => MaxLikeRB[~isnan(MaxLikeRB)],
        "name" => "Area peak dominates",
        "opacity" => 0.75,
        "type" => "histogram"
        ]
      ]

    response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chr"*c*"-ratio", "fileopt" => "overwrite"])

    MaxLikeD = MaxLikeA[c] .- MaxLikeB[c]
    #MaxLikeD13 = MaxLikeD13[MaxLikeD13.>0]
    #MaxLikeD13 = log10(MaxLikeD13)

    data = [
      [
        "x" => MaxLikeD[~isnan(MaxLikeD)],
        "name" => "Max. Lik. @ Area - Max. Lik. @ Boundary",
        "opacity" => 0.75,
        "type" => "histogram"
        ]
      ]

    layout = [
      "title" => "Chr. "*c*" Max. Lik. @ Area - Max. Lik. @ Boundary",
      "xaxis" => [
        "title" => "Max. Lik. @ Area - Max. Lik. @ Boundary"
        ],
      "yaxis" => [
        "title" => "Frequency of occurrence"
        ]
      ]

    response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chr"*c*"-diff", "fileopt" => "overwrite"])

    layout = [
      "title" => "Chr. "*c*" Max. Lik. @ Area vs Max. Lik. @ Boundary",
      "xaxis" => [
        "title" => "Max. Lik. @ Boundary"
        ],
      "yaxis" => [
        "title" => "Max. Lik. @ Area"
        ]
      ]
    data = [
      [
        "x" => MaxLikeB[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])],
        "y" => MaxLikeA[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])],
        "name" => "Max. Lik. @ Area vs Max. Lik. @ Boundary",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ]
      ]

    response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chr"*c*"-scat", "fileopt" => "overwrite"])

    layout = [
      "title" => "Chr. "*c*" (Max. Lik. @ Area - Max. Lik. @ Boundary) vs CFE",
      "xaxis" => [
        "title" => "StatCFE"
        ],
      "yaxis" => [
        "title" => "Max. Lik. @ Area - Max. Lik. @ Boundary"
        ]
      ]

    data = [
      [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])],
        "y" => MaxLikeA[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])] .- MaxLikeB[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])],
        "name" => "(Max. Lik. @ Area - Max. Lik. @ Boundary) vs statistics.CFE",
        "mode" => "markers",
        "marker" => [
          "size" => 12
          ],
        "type" => "scatter"
        ]
      ]
    response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chr"*c*"-diff-vsCFE", "fileopt" => "overwrite"])

# ======================

    cfe1fromMaxLikeA = [
      "13" => cfe1fromMaxLikeA13,
      "18" => cfe1fromMaxLikeA18,
      "21" => cfe1fromMaxLikeA21
      ]
    cfe2fromMaxLikeA = [
      "13" => cfe2fromMaxLikeA13,
      "18" => cfe2fromMaxLikeA18,
      "21" => cfe2fromMaxLikeA21
      ]
    cfe1fromMaxLikeB = [
      "13" => cfe1fromMaxLikeB13,
      "18" => cfe1fromMaxLikeB18,
      "21" => cfe1fromMaxLikeB21
      ]
    cfe2fromMaxLikeB = [
      "13" => cfe2fromMaxLikeB13,
      "18" => cfe2fromMaxLikeB18,
      "21" => cfe2fromMaxLikeB21
      ]

    layout = [
      "title" => "Chr. "*c*" (Max. Lik. @ Area OR Max. Lik. @ Boundary) vs CFE",
      "xaxis" => [
        "title" => "StatCFE"
        ],
      "yaxis" => [
        "title" => "CFE1 OR CFE2 from Max. Lik. @ Area OR from Max. Lik. @ Boundary"
        ]
      ]
    data = [
      [
        "x" => statCFE[~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])],
        "y" => cfe1fromMaxLikeA[c][~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])],
        "name" => "CFE1 from Max. Lik. @ Area (with no Boundary peak) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
      [
        "x" => statCFE[~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])],
        "y" => cfe2fromMaxLikeA[c][~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])],
        "name" => "CFE2 from Max. Lik. @ Area (with no Boundary peak) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
      [
        "x" => statCFE[isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])],
        "y" => cfe1fromMaxLikeB[c][isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])],
        "name" => "CFE1 from Max. Lik. @ Boundary (with no Area peak) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
      [
        "x" => statCFE[isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])],
        "y" => cfe2fromMaxLikeB[c][isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c])],
        "name" => "CFE2 from Max. Lik. @ Boundary (with no Area peak) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ]
      ]

    response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chr"*c*"-4CFEvsCFE", "fileopt" => "overwrite"])

# =====================

    data = [
       [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .> MaxLikeB[c])],
        "y" => cfe1fromMaxLikeA[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .> MaxLikeB[c])],
        "name" => "CFE1 from Max. Lik. @ Area (with existing B < A) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
       [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .> MaxLikeB[c])],
        "y" => cfe2fromMaxLikeA[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .> MaxLikeB[c])],
        "name" => "CFE2 from Max. Lik. @ Area (with existing B < A) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
       [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .< MaxLikeB[c])],
        "y" => cfe1fromMaxLikeB[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .< MaxLikeB[c])],
        "name" => "CFE1 from Max. Lik. @ Boundary (with existing A < B) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
       [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .< MaxLikeB[c])],
        "y" => cfe2fromMaxLikeB[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .< MaxLikeB[c])],
        "name" => "CFE2 from Max. Lik. @ Boundary (with existing A < B) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ]
      ]

    response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chr"*c*"-4CFEvsCFE-higher-peak", "fileopt" => "overwrite"])

# ====================

    data = [
       [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .< MaxLikeB[c])],
        "y" => cfe1fromMaxLikeA[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .< MaxLikeB[c])],
        "name" => "CFE1 from Max. Lik. @ Area (with existing B > A) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
       [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .< MaxLikeB[c])],
        "y" => cfe2fromMaxLikeA[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .< MaxLikeB[c])],
        "name" => "CFE2 from Max. Lik. @ Area (with existing B > A) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
       [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .> MaxLikeB[c])],
        "y" => cfe1fromMaxLikeB[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .> MaxLikeB[c])],
        "name" => "CFE1 from Max. Lik. @ Boundary (with existing A > B) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ],
       [
        "x" => statCFE[~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .> MaxLikeB[c])],
        "y" => cfe2fromMaxLikeB[c][~isnan(MaxLikeA[c]) & ~isnan(MaxLikeB[c]) & (MaxLikeA[c] .> MaxLikeB[c])],
        "name" => "CFE2 from Max. Lik. @ Boundary (with existing A > B) vs statCFE",
        "mode" => "markers",
        "marker" => [
          "size" => 6
          ],
        "type" => "scatter"
        ]
      ]

    response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chr"*c*"-4CFEvsCFE-lower-peak", "fileopt" => "overwrite"])

    fp = open("results.txt", "a") # Home directory
    write(fp, what*"-chr"*c*"\n")

    write(fp, string(size(MaxLikeA[c][isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])]))*"\n")
    write(fp, string(size(MaxLikeB[c][isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])]))*"\n")

    write(fp, string(size(~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])))*"\n")
    write(fp, string(statCFE[~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])].<0.15)*"\n")
    if(zzz==3)
      write(fp, string(!nocall[~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])])*"\n")
      write(fp, string(list[~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c]) & statCFE[~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])].<0.05 & !nocall[~isnan(MaxLikeA[c]) & isnan(MaxLikeB[c])]])*"\n")
    end
    close(fp)

  end

  # =====================

  layout = [
    "title" => "Chr. 13,18,21 (Max. Lik. @ Area - Max. Lik. @ Boundary) vs CFE",
    "xaxis" => [
      "title" => "StatCFE"
      ],
    "yaxis" => [
      "title" => "Max. Lik. @ Area - Max. Lik. @ Boundary"
      ]
    ]

  data = [
    [
      "x" => statCFE[~isnan(MaxLikeA13) & ~isnan(MaxLikeB13)],
      "y" => MaxLikeA13[~isnan(MaxLikeA13) & ~isnan(MaxLikeB13)] .- MaxLikeB13[~isnan(MaxLikeA13) & ~isnan(MaxLikeB13)],
      "name" => "Chr 13 (Max. Lik. @ Area - Max. Lik. @ Boundary) vs CFE",
      "mode" => "markers",
      "marker" => [
        "size" => 6
        ],
      "type" => "scatter"
      ],
    [
      "x" => statCFE[~isnan(MaxLikeA18) & ~isnan(MaxLikeB18)],
      "y" => MaxLikeA18[~isnan(MaxLikeA18) & ~isnan(MaxLikeB18)] .- MaxLikeB18[~isnan(MaxLikeA18) & ~isnan(MaxLikeB18)],
      "name" => "Chr 18 (Max. Lik. @ Area - Max. Lik. @ Boundary) vs CFE",
      "mode" => "markers",
      "marker" => [
        "size" => 6
        ],
      "type" => "scatter"
      ],
    [
      "x" => statCFE[~isnan(MaxLikeA21) & ~isnan(MaxLikeB21)],
      "y" => MaxLikeA21[~isnan(MaxLikeA21) & ~isnan(MaxLikeB21)] .- MaxLikeB21[~isnan(MaxLikeA21) & ~isnan(MaxLikeB21)],
      "name" => "Chr 21 (Max. Lik. @ Area - Max. Lik. @ Boundary) vs CFE",
      "mode" => "markers",
      "marker" => [
        "size" => 6
        ],
      "type" => "scatter"
      ]
    ]

  response = Plotly.plot(data, ["layout" => layout, "filename" => what*"-chrAll-diff-vsCFE", "fileopt" => "overwrite"])


end




