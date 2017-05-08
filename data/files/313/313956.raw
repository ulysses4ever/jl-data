using Gadfly
using Dates
using Cairo

function main(filename)
	#filename = ARGS[1]
	#@show ARGS
	a = readdlm(filename, ' ', skipstart = 15, comments = false)
	col = 5
	col2 = 0
	title = a[1,col] 
	title2 = ""
	if contains(filename, "mem")
		col = 4
		title = a[1,col]
	elseif contains(filename, "disk")
		col = 7
		title = a[1,col]
		col2 = 4
		title2 = a[1,col2]
	end 	
	
	#Prepare Date-Time
	c = [SubString(string(int(a[i,1])), 1, 4) * "-" * SubString(string(int(a[i,1])), 5, 6) * "-" * SubString(string(int(a[i,1])), 7, 8) for i = 2:size(a,1)]

	#println(" c is $c")
	d1 = [ c[i - 1 ] * "T" * a[i,2] for i = 2:size(a,1) ]
	d = [DateTime(d1[i]) for i = 1:size(d1,1) ]

	if col2 == 0
		plot1 = plot(x = d, y = a[2:end,col], Geom.line, Guide.title(title));
		draw(PDF(title*".pdf", 6inch, 6inch), plot1)
	else
		plot1 = plot(x = d, y = a[2:end,col], Geom.line, Guide.title(title)); 
		plot2 = plot(x = d, y = a[2:end,col2], Geom.line, Guide.title(title2));
		draw(PDF(title*"&"*title2*".pdf", 6inch, 6inch), vstack(plot1, plot2))
	end

end
