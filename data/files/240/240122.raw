# Calculate distance between two latitude-longitude points
# Base unit definitions: Meter

Rx = 6378137.0 # Semi-mejor axis(WGS84)
Ry = 6356752.314245 # Semi-minor axis(WGS84)
E = sqrt((Rx^2 - Ry^2)/Rx^2) # eccentricity

function hubeny_distance(lat1, lng1, lat2, lng2)
  dx = (lng2 - lng1)*pi/180.0
  dy = (lat2 - lat1)*pi/180.0
  P = ((lat2 + lat1)/2.0)*pi/180.0
  W = sqrt(1 - E^2 * sin(P)^2)
  M = (Rx*(1 - E^2))/W^3 # Meridian radius of curvature
  N = Rx/W # Prime vertical radius of curvature
  return sqrt((dy * M)^2 + (dx * N * cos(P))^2)
end

