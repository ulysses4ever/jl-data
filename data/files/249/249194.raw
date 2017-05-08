using InfluxDB
using Base.Test

# write your own tests here
influx = InfluxDBClient("http://localhost", 8086, "root", "root", "telegraf")
@test influx.baseurl == "http://localhost:8086"
@test influx.database == "telegraf"
