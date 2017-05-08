using ConnectSDK
using JSON
using HTTPClient.HTTPC
using Base.Test

# write your own tests here
connect = ConnectClient("55b078611f2ddd01a84c28db", "15765BE8FF529140640431906EE1D749-79F100C25D90EB54EACE1376058FD10D32ABEEBE0C8353157C7708FD623EC5093BA915C70F4FE2B878C2DEAD3743E60A")
temp = JSON.parse(bytestring(HTTPC.get("api.openweathermap.org/data/2.5/weather?id=7839562&units=metric&APPID=159d95e992dd299342cd8190e6e1f964").body))["main"]["temp"]
testdata = {"client" => "Julia", "temp" => temp}

r = push(connect, "tests", testdata)
@test r.http_code == 200
