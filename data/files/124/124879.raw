using HTTPClient.HTTPC
lines = String[]
 
cookie = ""
url = "http://axe-level-1.herokuapp.com/lv3/"
 
for index = [1:76]
	if index == 1
		r = HTTPC.get(url)
		received_cookie = r.headers["Set-Cookie"]
		cookie = received_cookie[1:search(received_cookie, ';')]
	else
		r = HTTPC.get(url * "?page=next", RequestOptions(headers=[("Cookie", cookie)]))
	end
 
	@assert r.http_code == 200
	html = bytestring(r.body)
	pattern = r"<tr>\s*<td>(.*)</td>\s*<td>(.*)</td>\s*<td>(.*)</td>\s*</tr>"
	substrings = matchall(pattern, html)
	for s in substrings[2:]
		c = match(pattern, s).captures
		push!(lines, "{\"town\": \"$(c[1])\", \"village\": \"$(c[2])\", \"name\" : \"$(c[3])\"}")
	end
end
 
f = open("test.txt", "w")
write(f, "[$(join(lines, ","))]")
close(f)
