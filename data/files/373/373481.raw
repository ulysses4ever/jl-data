using HttpServer
using Jolt
using JoltView

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

app.get("/view/:name") do req, res, ctx
	View("test", {"Name" => ctx.params[:name]})
end

http = HttpHandler(app.dispatch) 
server = Server(http)
run(server, 8080)

