using Requests
using JSON
using PyCall

# get a temporary token to access the cloud
gcloudCurrentToken = {
	"access_token" => "",
	"token_type"   => "Bearer",
	"expires_in"   => 3600
}
gcloudLastTokenFetch = 0
function gcloud_token(scope="https://www.googleapis.com/auth/devstorage.read_write")
	global gcloudCurrentToken, gcloudLastTokenFetch

	# fetch a new token if our current token will expire in less than 10 minutes
	if time() - gcloudLastTokenFetch > gcloudCurrentToken["expires_in"] - 600

		# if we are in the compute cloud then we can just ask for the token
	    try
	        @assert get("http://metadata.google.internal").status == 200
			gcloudCurrentToken = JSON.parse(get(
			    "http://metadata/computeMetadata/v1/instance/service-accounts/default/token",
			    headers={"X-Google-Metadata-Request"  => "True"}
			).data)

		# otherwise we have to prove our identity with a private key
	    catch
			@pyimport oauth2client.client as oauth 

			data = open(JSON.parse, ENV["HOME"]*"/.ssh/Link-c1ddd63b941b.json")
			assertion = oauth.SignedJwtAssertionCredentials(
			    data["client_email"],
			    data["private_key"],
			    scope=scope
			)[:_generate_assertion]()
	        
			gcloudCurrentToken = JSON.parse(post("https://accounts.google.com/o/oauth2/token",
			    data = "grant_type=urn%3Aietf%3Aparams%3Aoauth%3Agrant-type%3Ajwt-bearer&assertion=$assertion",
			    headers = {"Content-Type" => "application/x-www-form-urlencoded"},
			).data)
		end

		gcloudLastTokenFetch = time()
	end

	gcloudCurrentToken
end

# this is the text for the Authorization header
function gcloud_authorization()
	token = gcloud_token()
	token["token_type"]*" "token["access_token"]
end