using JSON, Requests
include("apikey.jl")
#include("types.jl")

function callGeocodeAPI(
    url::String)
    # Sends get request to Google Maps, parses JSON response

    rawResponse = get(url)
    parsedResponseData = JSON.parse(rawResponse.data)

    return(parsedResponseData)
end

function changeSpaceToPlus!(
    str::String)
    # Changes spaces in a string to plus signs (+), used to replace spaces in addresses in URL

    str = replace(str, r" +", "+")
    return(str)
end

function extractGeocodeInfo(
    geocodeResponse::Dict{String, Any})
    # Pull center lat/lng and formatted name from the geocode JSON response.

    location = geocodeResponse["results"][1]["geometry"]["location"]
    center = LatLng(location["lat"], location["lng"])

    name = geocodeResponse["results"][1]["formatted_address"]

    info = Geocode(center, name)
    return(info)
end

function getGeocodeURL(
    address::String)
    # Inserts address and API key into URL template

    url = "https://maps.googleapis.com/maps/api/geocode/json?address=$address&sensor=false&key=$apikey"
    return(url)
end

function geocode(
    zip::Int)
    # Converts integer zip code into a string and calls geocode(String)

    zipString = string(zip)
    geocodeResults = geocode(zipString)
    return(geocodeResults)
end

function geocode(
    address::String)
    # Converts address spaces, gets geocode URL, then gets API response, then extracts lat/lng and formatted name.

    address = changeSpaceToPlus!(address)
    geocodeURL = getGeocodeURL(address)
    geocodeResponse = callGeocodeAPI(geocodeURL)
    geocodeResults = extractGeocodeInfo(geocodeResponse)
    return(geocodeResults)
end

function getMap(
    center::LatLng,
    zoom::Int)
    # Eventually this should make a call to the maps API and save an image.

end
