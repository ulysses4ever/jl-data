using Connect
using JSON
using HTTPClient.HTTPC
using Base.Test

# write your own tests here
connect = ConnectClient("55b078611f2ddd01a84c28db", "82B8B12421E674E10309A2B926BCFEB2-9F2ECFA4B7353269DE3BB515DFB8E3A4A754B4D36145CA2EB3554C9BF985C45C204736841691A9138D00CA88FE15A165")
temp = JSON.parse(bytestring(HTTPC.get("api.openweathermap.org/data/2.5/weather?id=7839562&units=metric").body))["main"]["temp"]
testdata = {"client" => "Julia", "temp" => temp}

r = push(connect, "tests", testdata)
@test r.http_code == 200
