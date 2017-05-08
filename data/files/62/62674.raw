
using MapLight


function catcodes_from_bill(bill)
    catcodes_from_orgs(bill["bill"]["organizations"])
end

function catcodes_from_orgs(orgs)
    (support, oppose) = (String[], String[])

    for org in orgs
        cohorts = org["disposition"] == "oppose" ? oppose : support
        push!(cohorts, org["catcode"])
    end

    (unique(support), unique(oppose))
end

function contributions_for_catcodes(contribs::DataFrame, codes::Array)
    contribs[Bool[ !DataFrames.isna(c) && c in codes for c in contribs[:RealCode] ], :]
end
