using HttpServer: HttpServer, HttpHandler, Request, Response

include("Template.jl")

templ = open(readall, "example.html")
println(Template.template(templ, Dict("name"=>"Alex", "names"=>["John", "Robert"], "i"=>"4")))

# http = HttpHandler() do req::Request, res::Response
#     templ = open(readall, "example.html")
#     ready = Template.template(templ, Dict("name"=>"Alex"))
#     resp = Response(ready)
# end
#
# run(Server(http), host=IPv4(127, 0, 0, 1), port=8000)
