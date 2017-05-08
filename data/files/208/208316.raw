using HttpServer: HttpServer, HttpHandler, Request, Response

include("Template.jl")

templ = open(readall, "example.html")
println(Template.template(templ,
	Dict(
		"name"=>"Alex",
		"names"=>["John", "Robert"],
		"help"=>["for help", " and for patience"]
	)
))

# http = HttpHandler() do req::Request, res::Response
#     templ = open(readall, "example.html")
#     ready = Template.template(templ, Dict("name"=>"Alex", "names"=>["John", "Robert"]))
#     resp = Response(ready)
# end
#
# run(Server(http), host=IPv4(127, 0, 0, 1), port=8000)
