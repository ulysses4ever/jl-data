"""This collection of methods and definitions allow for easy location determination and comparison between differnt points on any sphere defined by their latitude and longitude."""
module EarthSphere
abstract Coordinate
#A coordinate describes a point in any coordinate system. 


abstract LatLong_Coord <: Coordinate
#This is a coordinate in a standard latitude-longitude coordinate system

type Degree
	#Abstraction for dealing with sexagesimal units of subtending the circle
	degree::Real
	minute::Real
	second::Real
end
export Degree


type Sphere_LatLong_Coord <: LatLong_Coord
	#Deals with a spherical latlong coordinate, similar to that used on good old planet earth
	latitude
	longitude
	#Example bearing: SW, NE
	bearing::String
	radius # 6371000 Meters for earth
end
function Earth_LatLong_Coord(latitude::Degree,longitude::Degree,bearing::String)
	latnumber = degree_to_decimal_degree(latitude)
	longnumber = degree_to_decimal_degree(longitude)
	Sphere_LatLong_Coord(latnumber,longnumber,bearing,6371)
end
export Earth_LatLong_Coord

Earth_LatLong_Coord(latitude::Real,longitude::Real,bearing::String) = Sphere_LatLong_Coord(latitude,longitude,bearing,6371)
function Earth_LatLong_Coord(latitude::Real,longitude::Real)
	if sign(latitude) == 1
		inclination = "N"
	elseif sign(latitude) == -1
		inclination = "S"
	else
		inclination = ""
	end
	if sign(longitude) == 1
		azimuth = "E"
	elseif sign(longitude) == -1
		azimuth = "W"
	else
		azimuth = ""
	end
	my_sphere = Sphere_LatLong_Coord(abs(latitude),abs(longitude),inclination*azimuth,6371)
	return my_sphere
end

	
		

type Spherical_Coord <: Coordinate
	#Mathematical formulation for a 3D spherical coordinate system
	radius::Real
	theta::Real
	phi::Real
end
export Spherical_Coord

function sign_lat_long(latitudeangle,longitudeangle,bearing)
	"""Returns a signed version of latitude and longitude based on the bearing given,
	uses a coordinate system where east is positive, west is negative, north is positive
	south is negative."""
	"""This will break if you feed it a bearing like "ES" or "WN", but such a case would be
	trivial to build up, build against, and is also not idiomatic"""
	"""UPDATE: This will no longer break if you do that thanks to a cheap and poorly executed hack. Please feel free to make this clean"""
	if length(bearing) == 1
		if bearing[1] == 'S'
			latitudeangle = (-1)*latitudeangle
		elseif bearing[1] == 'W'
			longitudeangle = (-1)*longitudeangle
		else
			return (latitudeangle,longitudeangle)
		end
	end
	if bearing[1] == 'E' | bearing[1] == 'W'
		bearing[1] = temp
		bearing[1] = bearing[2]
		bearing[2] = bearing[1]
	end

	if bearing[1] == 'S'
		latitudeangle = (-1)*latitudeangle
	end
	if bearing[2] == 'W'
		longitudeangle = (-1)*longitudeangle
	end
	return (latitudeangle,longitudeangle)
end

function sign_lat_long(latlong::LatLong_Coord)
	"Signs a latlong coord using the general sign_lat_long"
	(newlat,newlong) = sign_lat_long(latlong.latitude,latlong.longitude,latlong.bearing)
end




function degree_to_decimal_degree(degree::Degree)
	"Takes a degree in sextagesimal and returns a decimal degree"
	return degree.degree + degree.minute/60 + degree.second/(60^2)
end

function convert(Spherical_Coord,latlong::LatLong_Coord)
	(signedlat,signedlong) = sign_lat_long(latlong.latitude,latlong.longitude,latlong.bearing)
	phi = to_radians(signedlat)
	theta =  to_radians(signedlong)
	return Spherical_Coord(latlong.radius,theta,phi)
end
export convert
function latlongtotuple(s::Sphere_LatLong_Coord)
	#Takes a Spherical Coordinate and returns the signed latitude and longitude
	first = s.phi
	second = s.theta
	if ismatch(r"S",s.bearing)
		first = (-1)*first
	end
	if ismatch(r"W",s.bearing)
		second = (-1)*second
	end
	return (first,second)
end

function to_radians(degree::Real)
	"Takes a degree, returns radians"
	_sign = sign(degree)
	reduced_degree = mod(abs(degree),360)
	radians = reduced_degree*(pi/180)
	return radians*_sign
end

function get_distance(c1::Spherical_Coord,c2::Spherical_Coord)
	"Gets the distance between two different points on a sphere."
	if c1.radius != c2.radius
		error("These two points are not located on the same sphere")
	end
	#We're using the Vincenty formula, because it appears to be very computationally and algorithmically reasonable.
	#=central_angle = spherical_law_of_cosines(c1,c2)=#
	central_angle = vincenty(c1,c2)
	#=central_angle = haversine(c1,c2)=#
	#=central_angle = alternative_haversine(c1,c2)=#
	distance = c1.radius*central_angle

	return distance
end
function get_distance(c1::Sphere_LatLong_Coord,c2::Sphere_LatLong_Coord)
	c1s = convert(Spherical_Coord,c1)
	c2s = convert(Spherical_Coord,c2)
	return get_distance(c1s,c2s)
end

export get_distance

function vincenty(c1::Spherical_Coord,c2::Spherical_Coord)
	#An implementation of the Vincenty formula: http://en.wikipedia.org/wiki/Great-circle_distance
	longdiff = c1.theta-c2.theta
	#We could take absolute value of long (the difference of longitudes) but we only ever take the cosine of it, so we can just leave it (cosine is even, sign doesn't matter)
	vin_numerator = ( (cos(c2.phi)*sin(longdiff))^2 + ( cos(c1.phi)*sin(c2.phi) - sin(c1.phi)*cos(c2.phi)*cos(longdiff))^2 )^(1/2) 
	vin_denominator = sin(c1.phi)*sin(c2.phi)+cos(c1.phi)*cos(c2.phi)*cos(longdiff)
	central_angle = atan2(vin_numerator,vin_denominator)
	return central_angle
end
vincenty(c1,c2) = vincenty(convert(Spherical_Coord,c1),convert(Spherical_Coord,c2))
spherical_law_of_cosines(c1,c2) = spherical_law_of_cosines(convert(Spherical_Coord,c1),convert(Spherical_Coord,c2))
function spherical_law_of_cosines(c1::Spherical_Coord,c2::Spherical_Coord)
	#Implements Spherical Law of cosines, neither vincenty nor this are getting me close to google maps
	#UPDATE!: It's okay, I just accidentally had latitude for longitude and longitude for latitude, not really a big deal except it broke everything
	longdiff = abs(c1.theta-c2.theta)
	central_angle = acos(sin(c1.phi)*sin(c2.phi)+cos(c1.phi)*cos(c2.phi)*cos(longdiff))
	return central_angle
end
function haversine(c1::Spherical_Coord,c2::Spherical_Coord)
	longdiff = c1.theta-c2.theta
	latdiff = c1.phi-c2.phi
	a = (sin(latdiff/2))^2 + cos(c1.phi)*cos(c2.phi)*(sin(longdiff/2))^2
	central_angle = 2*atan2(sqrt(a),sqrt(1-a))
	return central_angle
end
function alternative_haversine(c1::Spherical_Coord,c2::Spherical_Coord)
	#This is another formulation of the haversine formula from wikipedia
	
	latdiff = abs(c1.phi-c2.phi)
	println(latdiff)
	longdiff = abs(c1.theta-c2.theta)
	println(longdiff)
	argument = sqrt(sin((latdiff)/2)*sin((latdiff)/2) - cos(c1.phi)*cos(c2.phi)*sin((longdiff)/2)*sin((longdiff)/2))
	central_angle = 2*asin(argument)
	return central_angle
end

alternative_haversine(c1,c2) =alternative_haversine(convert(Spherical_Coord,c1),convert(Spherical_Coord,c2))
haversine(c1,c2) = haversine(convert(Spherical_Coord,c1),convert(Spherical_Coord,c2))


	
end #End module 
