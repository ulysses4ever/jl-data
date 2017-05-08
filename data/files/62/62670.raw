
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

function contributions_for_catcodes(codes::Array, contrib_table::Array)
    contribs = Any[]

    for code in codes
        os_code = "|$code|"
        for i in 1:first(size(contrib_table))
            contrib_table[i, 7] == os_code && push!(contribs, contrib_table[i, 5])
       end
    end

    unique(contribs)
end
