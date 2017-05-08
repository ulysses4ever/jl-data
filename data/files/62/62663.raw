
include("api-keys.jl")
setup_api_keys()

using JSON
using Requests
using SunlightAPIs
using MapLight
using DataFrames
using OpenSecrets


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

function pac_contributions_for_crp_ids(contribs::DataFrame, crp_ids::Array)
    contribs[Bool[ !DataFrames.isna(c) && c in crp_ids for c in contribs[:CID] ], :]
end

function individual_contributions_for_crp_ids(contribs::DataFrame, crp_ids::Array)
    contribs[Bool[ !DataFrames.isna(c) && c in house_ids for c in contribs[:RecipID] ], :]
end

# this really needs to be brought into a NYT.jl
function congress_members(year, house; nyt_key = nyt_congress_key)
    NYT_API = URI("http://api.nytimes.com")
    congress_members = get(URI(NYT_API; path = "/svc/politics/v3/us/legislative/congress/$year/$house/members/current.json"); query = { "api-key" => nyt_key }).data
    JSON.parse(congress_members)["results"][1]["members"]
end

# this really needs to go into SunlightAPIs.jl
function sunlight_get_crpid(bioid; sunlight_key = sunlight_key)
    data = JSON.parse(get(URI(SUNLIGHT_CONGRESS_API; path = "/legislators"); query = {
        "bioguide_id" => bioid,
        "all_legislators" => true,
        "apikey" => sunlight_key
        }).data)

    data["results"][1]["crp_id"]
end

function congress_member_crp_ids(congress_members; sunlight_key = sunlight_key, max_tries = 10)
    member_bio_ids = [ m["id"] for m in congress_members ]
    member_crp_ids = String[]

    for bioid in member_bio_ids
        success = false
        num_tries = 1
        while !success && num_tries < max_tries
            try
                crp_id = sunlight_get_crpid(bioid; sunlight_key = sunlight_key)
                push!(member_crp_ids, crp_id)
                println(length(member_crp_ids), ": ", crp_id)
                success = true
            catch err
                println(err)
                num_tries += 1
            end
        end
    end

    member_crp_ids
end
