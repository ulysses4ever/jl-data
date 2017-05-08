if !isfile("code.json")
  import JSON.parsefile
  meta = download("http://registry.npmjs.org/statuses/1") |> parsefile
  (download(meta["dist"]["tarball"])
    |> `gzip -cd`
    |> `tar --strip-components 1 -xmpf -`
    |> run)
end
