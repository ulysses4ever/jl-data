using HttpServer
using WebSockets


wsh = WebSocketHandler() do req, client
	while true
		cells = join(randColorField(360,180), ',');
		write(client, cells)

	end
end


function randColor()
	r = int(rand() * 255);
	g = int(rand() * 255);
	b = int(rand() * 255);

	c = hex((1 << 24) + (r << 16) + (g << 8) + b)[2:end];

	return "#$c";
end


function randColorField(x::Int64, y::Int64)
	map = String[];
	for i = 1:x
		for j = 1:y
			push!(map,string(randColor()));
		end
	end
	return map
end


server = Server(wsh)
run(server, 8080)