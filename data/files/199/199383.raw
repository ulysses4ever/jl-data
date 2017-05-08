function getLatLngFromGeocode(
    geocodeResponse::Dict{String, Any})

    location::Dict = geocodeResponse["results"][1]["geometry"]["location"]
    latLng::LatLng = LatLng(location["lat"], location["lng"])

    return(latLng)
end


function geocode(
    address::String)

    rawResponse = get("https://maps.googleapis.com/maps/api/geocode/json?address=$address&sensor=false&key=AIzaSyAEGq5zoIMANJa-5Q2Ux98rRjMx_ShlLtI")
    parsedResponseData = JSON.parse(rawResponse.data)

    return(parsedResponseData)
end

function getMap(
    center::LatLng,
    zoom::Int)

    urlBase = "http://maps.googleapis.com/maps/api/staticmap"

end
