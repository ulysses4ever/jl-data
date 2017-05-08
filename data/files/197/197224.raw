type Request
	socket::TcpSocket
	size::Int
	headers::Dict{String, String}
	content::ASCIIString

	Request(socket::TcpSocket) = new(socket, 0, Dict{String, String}(), "")
end

function parserequest(sock::TcpSocket)
	req = Request(sock)
	readheaders!(req)

	read(req.socket, Char)

	req.content = readbytes(req.socket, int(req.headers["CONTENT_LENGTH"]))
	req
end

function readsize!(req::Request)
	req.size = int(readuntil(req.socket, ':')[1:end-1])
	return req.size
end

function readheaders!(req::Request)
	size = readsize!(req)
	header_data::ASCIIString = readbytes(req.socket, size)
	items = split(header_data, "\00")[1:end-1]

	i = 1
	while i <= length(items)
		#println("$(items[i])\t$(items[i+1])")
		req.headers[items[i]] = items[i+1]
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

function handlefunc(req::Request)
	println(req.socket, "Status: 200 OK")
	println(req.socket, "Content-Type: text/html")
	println(req.socket, "")
	println(req.socket, "<h2>Hello, $(req.headers["DOCUMENT_URI"][2:])</h2>")
	close(req.socket)
end

scgi(listen(9006), handlefunc)