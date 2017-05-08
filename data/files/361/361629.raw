if !isfile("codes.json")
  import JSON.parsefile
  meta = download("http://registry.npmjs.org/statuses/1") |> parsefile
  pipeline(download(meta["dist"]["tarball"]),
           `tar --strip-components 1 -xmpf -`) |> run
end
