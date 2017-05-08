module GoogleMaps

using Requests, JSON

export LatLng, geocode

type LatLng
    lat::Float64
    lng::Float64
end

function geocode(
    address::String)

    geocodeResponse = get("https://maps.googleapis.com/maps/api/geocode/json?address=$address&sensor=false&key=AIzaSyAEGq5zoIMANJa-5Q2Ux98rRjMx_ShlLtI")
    parsedResponse = JSON.parse(geocodeResponse.data)

    location = parsedResponse["results"][1]["geometry"]["location"]
    geocodeLatLng = LatLng(location["lat"], location["lng"])

    return(geocodeLatLng)
end

function getMap(
    center::LatLng,
    zoom::Int)

    urlBase = "http://maps.googleapis.com/maps/api/staticmap"

end

# package code goes here

end # module
