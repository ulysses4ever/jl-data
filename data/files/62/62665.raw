
function setup_api_keys(keyfile = "api-keys.csv")
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
