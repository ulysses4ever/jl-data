##### TODO
# plug into http server
# server side templating
# json response
# body parser
# middleware
# serve files
# splat on url matching
# ...

module Jolt

using RouteParser

export jolt

immutable Route
	path::String
	method::Symbol
	handler::Function
end

type App
	routes::Array{Route,1} 
	get::Function
	selectRoute::Function

	function App()
		instance = new()
		instance.routes = Route[]
		
		# add a route to the routing table
		instance.get = function(handler::Function, path::String)
			push!(instance.routes, Route(path, :get, handler))
		end

		# select a route from a routing table based on a URL and method
		instance.selectRoute = function(path::String, method::Symbol)
			for route in filter((route) -> route.method == method || route.method == :any, instance.routes)
				params = isMatch(path, route.path)
				if (nothing != params)
					return (route,params)
				end
			end
		end

		# return the instance
		instance
	end

end

function jolt()
	App()
end

end #module