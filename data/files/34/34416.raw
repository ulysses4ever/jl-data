cd(string(dirname(@__FILE__)))

file = open("p102_triangles.txt")
triangles = readlines(file)
close(file)
triangles = [int(split(triangle,",")) for triangle in triangles]

function pe102(triangles)


  c = 0
  for triangle in triangles
    x1,y1,x2,y2,x3,y3 = triangle
    b1 = ((-x3)*(y2-y3) - (x2-x3)*(-y3)) < 0
    b2 = ((-x2)*(y1-y2) - (x1-x2)*(-y2)) < 0
    b3 = ((-x1)*(y3-y1) - (x3-x1)*(-y1)) < 0
    if ((b1 == b2) && (b2 == b3))
      c += 1
    end
  end

  return c
end

@time pe102(triangles)
