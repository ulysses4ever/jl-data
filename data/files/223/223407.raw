########
#
#
#
########

using Requests

include("_00_includes.jl")

# Download data file
download_response = get("$base_url/gd80to84.txt")

# What's in the response from the server?
names(download_response)

# Make sure we actually got some data
dump(download_response.data)
print(download_response.data)

# Keep only the data part of the response
data = download_response.data

# Write the string to a local file - we'll use this from now on.
data_file = open("$base_folder/Data/gd80to84.txt", "w+")
write(data_file, data)
close(data_file)
