function haversine(lat1, lon1, lat2, lon2)
  # Haversine spherical distance calculations
  # This uses the haversine formula to calculate the great-circle
  # distance between two points on the earth's surface giving an
  # as-the-crow-flies distance between the points (ignoring any hills, of course!).

  # Convert all decimal degrees to radians
  lat1_rad = degrees2radians(lat1)
  lon1_rad = degrees2radians(lon1)
  lat2_rad = degrees2radians(lat2)
  lon2_rad = degrees2radians(lon2)

  R = 6371                              # Earth's radius in km
  delta_lat = abs(lat2_rad - lat1_rad)  # Abs. diff. in latitude
  delta_lon = abs(lon2_rad - lon1_rad)  # Abs. diff. in longitude

  # Haversine formula (http://www.movable-type.co.uk/scripts/latlong.html)
  a = sin(delta_lat/2)^2 + cos(lat1_rad) * cos(lat2_rad) * sin(delta_lon/2)^2
  c = 2 * atan2(sqrt(a), sqrt(1-a))

  # Return distance in kilometers
  return R * c
end


function buildDistanceMatrix(coords, miles=true)
  # Calculates a pair-wise distance matrix between a set of coordinates
  # Input:
  #  coords     Nx2 matrix of lat/lon coordinates in degrees
  #  miles      Whether to return distances in miles
  # Ouput:
  #  dmat       NxN matrix of distances in desired units
  
  n, _ = size(coords)
  dmat = zeros(n,n)

  for i = 1:n
    for j = (i+1):n
      dmat[i,j] = haversine(coords[i,1],coords[i,2],coords[j,1],coords[j,2])
      dmat[j,i] = dmat[i,j]
    end
  end

  # Convert to miles if desired
  if miles
    dmat .*= 0.621371
  end

  return dmat
end
