using Jolt

app = jolt()

app.use() do req, res, ctx
	println("middleware running before controller")
	produce()
	println("middleware running after controller")
end

app.get("/") do req, res, ctx
  "hello world"
end

app.get("/hello/:name") do req, res, ctx
  name = ctx.params[:name]
  "hello $name"
end

start(app, 8000)