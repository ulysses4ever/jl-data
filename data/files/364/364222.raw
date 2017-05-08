function get_index(quad::Rectangle, shape::Shape)
  x_max = maximum(shape.bounds[:,1])
  y_max = maximum(shape.bounds[:,2])
  x_min = minimum(shape.bounds[:,1])
  y_min = minimum(shape.bounds[:,2])

  left_quadrants = x_min > quad.x0 && x_max < (quad.x1 + quad.x0)/2
  right_quadrants = x_min > (quad.x1 + quad.x0)/2 && x_max < quad.x1

  top_quadrants = y_min > quad.y0 && y_max < (quad.y1 + quad.y0)/2
  bottom_quadrants = y_min > (quad.y1 + quad.y0)/2 && y_max < quad.y1


  if(right_quadrants && top_quadrants)
    return 1
  end

  if(left_quadrants && top_quadrants)
    return 2
  end

  if(left_quadrants && bottom_quadrants)
    return 3
  end

  if(right_quadrants && bottom_quadrants)
    return 4
  end

  return -1
end
