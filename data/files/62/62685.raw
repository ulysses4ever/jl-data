
using JSON
using SunlightAPIs
using MapLight

function setup_global_keys(keyfile = "api-keys.csv")
    keys = readcsv(keyfile)

    for i in 1:first(size(keys))
        keyname = strip(keys[i, 1])
        key = strip(keys[i, 2])

        keyname == "maplight" && (global maplight_key = key)
        keyname == "sunlight" && (global sunlight_key = key)
        keyname == "nyt-campaign-finance" && (global nyt_cf_key = key)
        keyname == "nyt-congress" && (global nyt_congress_key = key)
        keyname == "nyt-districts" && (global nyt_districts_key = key)
    end
end

# -------

function catcodes_from_bill(bill)
    catcodes_from_orgs(bill["bill"]["organizations"])
end

function catcodes_from_orgs(orgs)
    [ org["catcode"] for org in orgs ]
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
