using HttpServer
using Jolt

app = jolt()

app.use() do req, res, ctx
	url = req.resource
	println("start $url")
	produce()
	println("end $url")
end

app.get("/") do req, res, ctx
	"hello world"
end

app.get("/hello/:name") do req, res, ctx
	name = ctx.params[:name]
	"hello $name"
end

http = HttpHandler(app.dispatch) 
server = Server(http)
run(server, 8080)

