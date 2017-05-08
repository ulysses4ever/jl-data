using MexbtClient
using Base.Test

@test ticker("BTCMXN")["isAccepted"]
@test trades("BTCMXN")["isAccepted"]
@test tradesByDate("BTCMXN", 1416530012, 1416559390)["isAccepted"]
@test orderBook("BTCMXN")["isAccepted"]
@test productPairs()["isAccepted"]

account = Account("4b0911e93f372a401456061a70e4299a", "1831845ddae9cf45e57b851ff2ca0117", "ahimta@outlook.com", true)
order = createOrder(account, "BTCUSD", "buy", 0, 1.0, 342.99)
@test order["isAccepted"]
@test createMarketOrder(account, "BTCUSD", "buy", 1.0, 342.99)["isAccepted"]
@test createLimitOrder(account, "BTCUSD", "buy", 1.0, 342.99)["isAccepted"]
@test modifyOrder(account, "BTCUSD", order["serverOrderId"], 0)["isAccepted"]
@test moveOrderToTop(account, "BTCUSD", order["serverOrderId"])["isAccepted"]
@test executeOrder(account, "BTCUSD", order["serverOrderId"])["isAccepted"]
@test cancelOrder(account, "BTCUSD", order["serverOrderId"])["isAccepted"]
@test cancelAllOrders(account, "BTCUSD")["isAccepted"]
@test accountInfo(account)["isAccepted"]
@test balance(account)["isAccepted"]
@test accountTrades(account, "BTCUSD")["isAccepted"]
@test orders(account)["isAccepted"]
@test depositAddresses(account)["isAccepted"]
@test depositAddresses(account, "BTC")["isAccepted"]
# @test withdraw(account, "BTC", 1.2345678, "1yL8LFT5qqzPJY3hMRQCJd5CTs2F7SHjv")["isAccepted"]

