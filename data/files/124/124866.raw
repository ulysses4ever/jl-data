using HTTPClient.HTTPC
lines = String[]
 
cookie = ""
url = "http://axe-level-4.herokuapp.com/lv4/"
last_url = url

for index = [1:24]
	the_url = index == 1 ? url : url * "?page=$(index)"
	options = RequestOptions(headers=[("Accept", "text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8"),
		("User-Agent", "Mozilla/5.0 (Macintosh; Intel Mac OS X 10_9_1) AppleWebKit/537.73.11 (KHTML, like Gecko) Version/7.0.1 Safari/537.73.11"),
		("Referer", last_url)])
	r = HTTPC.get(the_url, options)
	last_url = the_url
 
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
