using Requests
using JSON

const fb_api_root = "http://www.deepspaceweb.com:80/fishbase/api/"

const species_id = [10, 11, 23]


for sp_idx in species_id
   request_url = string(fb_api_root, "species/id/", sp_idx)
   request = get(request_url)
   if request.status == 200
      request_content = request.data
      response = JSON.parse(request.data)
      println("#", sp_idx, "\t", response["Genus"], " ", response["Species"])
   end
end
