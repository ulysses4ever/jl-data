using HttpServer
using WebSockets


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

# y = randColorField(5,5);

# x = join(y, ',');

# println(y);
# println(x);

wsh = WebSocketHandler() do req, client
	while true
		cells = join(randColorField(100,100), ',');
		sleep(1);
		write(client, cells);
	end
end





server = Server(wsh)
run(server, 8080)