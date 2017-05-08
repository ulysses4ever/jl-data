using Cairo

# Command-line program that draws a Koch snowflake. Usage:
#     julia snowflake.jl n sx sy
# Generates the n'th iteration of the fractal and saves it as a PNG of size
# sx by sy pixels.

# Get the n'th iteration of the Koch snowflake as a list of coordinates.
function snowflake(n)
	# initial triangle
	l = [(-1.0,0.0), (0.0,sqrt(3.0)), (1.0,0.0)]

	# n iterations
	for i=1:n
		next = Array((Float64, Float64), 3*4^i)
		k = 1
		for ((x1,y1), (x2,y2)) in @task pairsw(l)
			next[k]   = (x1, y1)
			next[k+1] = ((2x1 + x2)/3, (2y1 + y2)/3)
			next[k+2] = ((x1+x2)/2 + (y1-y2)/3, (y1+y2)/2 + (x2-x1)/3)
			next[k+3] = ((x1 + 2x2)/3, (y1 + 2y2)/3)
			k += 4
		end
		l = next
	end

	return l
end

# Produce pairs of elements from l, including a final pair of the last and
# first element.
function pairsw(l)
	for i=1:(length(l)-1)
		produce(l[i], l[i+1])
	end
	produce(l[end], l[1])
end

# Draw snowflake and save to file.
function draw(coordinates, sx, sy)
	c = CairoRGBSurface(sx,sy)
	cr = CairoContext(c)

	s = min(sx, sy)
	translate(cr, 0.5sx, 0.35sy)
	# we're drawing it upside-down -- uncomment to get it right-side up
	# translate(cr, 0.0sx, 0.35sy)
	# rotate(cr, pi)
	scale(cr, 0.3s, 0.3s)

	x,y = coordinates[1]
	move_to(cr, x,y)
	for (x,y) in coordinates[2:end]
		line_to(cr, x,y)
	end
	close_path(cr)

	set_source_rgb(cr, 0.39, 0.70, 0.87)
	fill(cr)

	write_to_png(c, "snowflake$n.png")
end

n = length(ARGS) < 1 ? 1 : int(ARGS[1])
sx = length(ARGS) < 2 ? 600 : int(ARGS[2])
sy = length(ARGS) < 3 ? 600 : int(ARGS[3])

draw(snowflake(n), sx, sy)
