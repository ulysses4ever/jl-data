function split!(quad::Rectangle, index::Int64)
  global level

  if(index == 1)
    rect = Rectangle((quad.x1 + quad.x0) / 2,
                     (quad.y0),
                     (quad.x1 - quad.x0) / 2,
                     (quad.y1 - quad.y0) / 2)
  end
  if(index == 2)
    rect = Rectangle((quad.x0),
                     (quad.y0),
                     (quad.x1 - quad.x0) / 2,
                     (quad.y1 - quad.y0) / 2)
  end
  if(index == 3)
    rect = Rectangle((quad.x0),
                     (quad.y1 + quad.y0) / 2,
                     (quad.x1 - quad.x0) / 2,
                     (quad.y1 - quad.y0) / 2)
  end
  if(index == 4)
    rect = Rectangle((quad.x1 + quad.x0) / 2,
                     (quad.y1 + quad.y0) / 2,
                     (quad.x1 - quad.x0) / 2,
                     (quad.y1 - quad.y0) / 2)
  end

  if(index == -1)
    #quad[1] = quad[2]
    return
  end

  return rect
end
