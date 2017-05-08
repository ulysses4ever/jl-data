Pkg.add("Quandl")
importall Quandl
set_auth_token("")
a = quandl("GOOG/NASDAQ_QQQ")
plot(x = [1:length(a.values[:,1])], y = a.values[:,1])
