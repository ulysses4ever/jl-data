using HTTPClient.HTTPC
lines = String[]
 
for index =[1:13]
	url = "http://axe-level-1.herokuapp.com/lv2"
	r = HTTPC.get(url, RequestOptions(query_params=collect({:page => index})))
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
