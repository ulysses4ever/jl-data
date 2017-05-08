
# these tests will only run when a valid key file is present for a Google Cloud account
keyFile = ENV["HOME"]*"/.ssh/Link-c1ddd63b941b.json"

# make sure we got a valid token
token = gcloud_token(keyFile)
@assert length(token["access_token"]) > 0

# make sure we got didn't refresh the token but used the current one
tokenAgain = gcloud_token(keyFile)
@assert tokenAgain["access_token"] == token["access_token"]

@assert gcloud_authorization(keyFile) == token["token_type"]*" "token["access_token"]