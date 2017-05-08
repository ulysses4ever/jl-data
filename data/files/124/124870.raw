using HTTPClient.HTTPC
 
r = HTTPC.get("http://axe-level-1.herokuapp.com")
@assert r.http_code == 200
html = bytestring(r.body)
pattern = r"<tr>\s*<td>(.*)</td>\s*<td>(.*)</td>\s*<td>(.*)</td>\s*<td>(.*)</td>\s*<td>(.*)</td>\s*<td>(.*)</td>\s*</tr>"
substrings = matchall(pattern, html)
lines = String[]
for s in substrings[2:]
	c = match(pattern, s).captures
	push!(lines, "{\"name\": \"$(c[1])\", \"grades\": {\"國語\": $(c[2]), \"數學\": $(c[3]), \"自然\": $(c[4]), \"社會\": $(c[5]), \"健康教育\": $(c[6])}}")
end
 
f = open("test.txt", "w")
write(f, "[$(join(lines, ","))]")
close(f)
