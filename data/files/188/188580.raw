module MexbtClient

using Requests
using Nettle
using JSON

export Account, MexbtException, UnknownCurrencyException, HttpException
export ticker, trades, tradesByDate, orderBook, productPairs
export createOrder, createMarketOrder, createLimitOrder, modifyOrder, moveOrderToTop, executeOrder, cancelOrder, cancelAllOrders
export accountInfo, balance, accountTrades, orders, depositAddresses, withdraw

abstract MexbtException <: Exception

type UnknownCurrencyException <: MexbtException end
type HttpException            <: MexbtException end

typealias JSONDocument Dict{String, Any}

function postRequest(url::String, params::JSONDocument = JSONDocument())
  res = post(url, json = params)

  if res.status != 200
    throw(HttpException(res.status))
  else
    JSON.parse(res.data)::JSONDocument
  end
end

function postPublicRequest(endpoint::String, params::JSONDocument = JSONDocument())
  postRequest("https://public-api.mexbt.com/v1/$(endpoint)", params)
end

function ticker(productPair::String)
  params::JSONDocument = ["productPair" => productPair]
  postPublicRequest("ticker", params)
end

function trades(ins::String, startIndex::Int = -1, count::Int = 20)
  params::JSONDocument = ["ins" => ins, "startIndex" => startIndex, "count" => count]
  postPublicRequest("trades", params)
end

function tradesByDate(ins::String, startDate::Int64, endDate::Int64)
  params::JSONDocument = ["ins" => ins, "startDate" => startDate, "endDate" => endDate]
  postPublicRequest("trades-by-date", params)
end

function orderBook(productPair::String)
  params::JSONDocument = ["productPair" => productPair]
  postPublicRequest("order-book", params)
end

function productPairs()
  postPublicRequest("product-pairs")
end

immutable Account
  publicKey::String
  privateKey::String
  userId::String
  isSandbox::Bool
end

function postPrivateRequest(account::Account, endpoint::String, params::JSONDocument = JSONDocument())
  nonce = int64(time() * 1000)
  message = "$(nonce)$(account.userId)$(account.publicKey)"
  signature = uppercase(bytes2hex(sha256_hmac(account.privateKey, message)))

  signedParams::JSONDocument = merge(params, ["apiNonce" => nonce, "apiKey" => account.publicKey, "apiSig" => signature])

  url = if account.isSandbox "https://private-api-sandbox.mexbt.com/v1/$(endpoint)" else "https://private-api.mexbt.com/v1/$(endpoint)" end
  postRequest(url, signedParams)
end

function createOrder(account::Account, ins::String, side::String, orderType::Int, qty::Float64, px::Float64)
  params::JSONDocument = ["ins" => ins, "side" => side, "orderType" => orderType, "qty" => qty, "px" => px]
  postPrivateRequest(account, "orders/create", params)
end

function createMarketOrder(account::Account, ins::String, side::String, qty::Float64, px::Float64)
  createOrder(account, ins, side, 1, qty, px)
end

function createLimitOrder(account::Account, ins::String, side::String, qty::Float64, px::Float64)
  createOrder(account, ins, side, 0, qty, px)
end

function modifyOrder(account::Account, ins::String, serverOrderId::Int, modifyAction::Int)
  params::JSONDocument = ["ins" => ins, "serverOrderId" => serverOrderId, "modifyAction" => modifyAction]
  postPrivateRequest(account, "orders/modify", params)
end

function moveOrderToTop(account::Account, ins::String, serverOrderId::Int)
  modifyOrder(account, ins, serverOrderId, 0)
end

function executeOrder(account::Account, ins::String, serverOrderId::Int)
  modifyOrder(account, ins, serverOrderId, 1)
end

function cancelOrder(account::Account, ins::String, serverOrderId::Int)
  params::JSONDocument = ["ins" => ins, "serverOrderId" => serverOrderId]
  postPrivateRequest(account, "orders/cancel", params)
end

function cancelAllOrders(account::Account, ins::String)
  params::JSONDocument = ["ins" => ins]
  postPrivateRequest(account, "orders/cancel-all", params)
end

function accountInfo(account::Account)
  postPrivateRequest(account, "me")
end

function balance(account::Account)
  postPrivateRequest(account, "balance")
end

function accountTrades(account::Account, ins::String, startIndex::Int = -1, count::Int = 20)
  params::JSONDocument = ["ins" => ins, "startIndex" => startIndex, "count" => count]
  postPrivateRequest(account, "trades", params)
end

function orders(account::Account)
  postPrivateRequest(account, "orders")
end

function depositAddresses(account::Account)
  postPrivateRequest(account, "deposit-addresses")
end

function depositAddresses(account::Account, ins::String)
  res = depositAddresses(account)
  if res["isAccepted"]
    nameAddressPairs = res["addresses"]
    pairIndex = findfirst(pair -> pair["name"] == ins, nameAddressPairs)
    if pairIndex == 0
      throw(UnknownCurrencyException(ins))
    else
      ["isAccepted" => true , "depsitAddress" => nameAddressPairs[pairIndex]["depositAddress"]]
    end
  else
    ["isAccepted" => false, "rejectReason" => res["rejectReason"]]
  end
end

function withdraw(account::Account, ins::String, amount::Float64, sendToAddress::String)
  formattedAmount = if account.isSandbox @sprintf("%.6f", amount) else @sprintf("%.8f", amount) end
  params::JSONDocument = ["ins" => ins, "amount" => formattedAmount, "sendToAddress" => sendToAddress]
  postPrivateRequest(account, "withdraw", params)
end

end
