type NetString
	socket::TcpSocket
	size::Int
	headers::Dict{String, String}
	data::ASCIIString
	content::ASCIIString

	NetString(socket::TcpSocket) = new(socket, 0, Dict{String, String}(), "")
end

function parserequest(sock::TcpSocket)
	ns = NetString(sock)
	readenv!(ns)

	ns
end

function readsize(ns::NetString)
	ns.size = int(readuntil(ns.socket, ':')[1:end-1])
	return ns.size
end

function reads!(ns::NetString)
	size = readsize(ns)
	ns.data = readbytes(ns.socket, size)
	return ns.data
end

function readenv!(ns::NetString)
	headers = reads!(ns)
	items = split(headers, "\00")[1:end-1]

	i = 1
	while i <= length(items)
		println("$(items[i])\t$(items[i+1])")
		ns.headers[items[i]] = items[i+1]
		i += 2
	end
end

function scgi(server, handler)
	while true
		sock = accept(server)
		@async begin
			req = parserequest(sock)
			handler(req)
		end
	end
end

function handlefunc(ns::NetString)
	read(ns.socket, Char)
	ns.content = readbytes(ns.socket, int(ns.headers["CONTENT_LENGTH"]))
	println(ns.data)
	println("----")
	println(ns.content)
	println(ns.socket, "Status: 200 OK")
	println(ns.socket, "Content-Type: text/html")
	println(ns.socket, "")
	println(ns.socket, "<h2>Hello, $(ns.headers["DOCUMENT_URI"][2:])</h2>")
	close(ns.socket)
end

scgi(listen(9006), handlefunc)