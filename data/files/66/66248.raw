importall Bukdu

type WelcomeController <: ApplicationController
end

global counter = 0

function index(::WelcomeController)
    commit = Bukdu.Server.commit_short
    text = """
# Bukdu 🌌

[Bukdu](https://github.com/wookay/Bukdu.jl) is a web development framework for [Julia](http://julialang.org).

It's influenced by [Phoenix framework](http://phoenixframework.org).


# Bukdu on Heroku

You can run Bukdu on [Heroku](https://www.heroku.com/).

 * Heroku: Create new app like this.

   - [heroku-bukdu](https://github.com/wookay/heroku-bukdu)

 * Heroku: Add two buildpacks on **Settings** -> **Add buildpack**

   - [https://github.com/wookay/heroku-buildpack-cmake](https://github.com/wookay/heroku-buildpack-cmake)

   - [https://github.com/wookay/heroku-buildpack-julia](https://github.com/wookay/heroku-buildpack-julia)

  ```sh
λ ~/work/heroku-bukdu \$ heroku buildpacks
=== bukdu Buildpack URLs
1. https://github.com/wookay/heroku-buildpack-cmake
2. https://github.com/wookay/heroku-buildpack-julia
```

 * Get more information: [https://devcenter.heroku.com/categories/deployment](https://devcenter.heroku.com/categories/deployment)


# Working with params

Put `conn::Conn` to the controller. Now, `params` could be accessed by indexing the controller. For example,

```julia
type CalculateController <: ApplicationController
    conn::Conn
end

function my_fn(c::CalculateController)
    q = c[:params]
    x, y = map(v -> parse(Int, v), (q[:x], q[:y]))
    render(JSON, x + 2y)
end

Router() do
    get("/my_fn", CalculateController, my_fn)
end
```

Check it by querying with parameters.

Get `x + 2y` for x = 2, y = 3 [/my_fn?x=2&y=3](/my_fn?x=2&y=3)

Get `x + 2y` for x = 5, y = 6 [/my_fn?x=5&y=6](/my_fn?x=5&y=6)


# Welcome

This page is running in the Bukdu commit [$commit](https://github.com/wookay/Bukdu.jl/commit/$commit) with Juila $(VERSION)

See the full code of [welcome.jl](https://github.com/wookay/heroku-bukdu/blob/master/welcome.jl).


$counter
"""
    global counter += 1
    render(Markdown/Layout, text)
end

function layout(::Layout, body)
    """
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0"/>
    <title>Bukdu 🌌 </title>
    <link rel="stylesheet" href="/css/default.min.css" />
    <link rel="stylesheet" href="/css/style.css" />
    <script src="/js/jquery-3.2.1.slim.min.js"></script>
    <script src="/js/highlight.min.js"></script>
    <script src="/js/julia.min.js"></script>
    <script>
  (function(i,s,o,g,r,a,m){i['GoogleAnalyticsObject']=r;i[r]=i[r]||function(){
  (i[r].q=i[r].q||[]).push(arguments)},i[r].l=1*new Date();a=s.createElement(o),
  m=s.getElementsByTagName(o)[0];a.async=1;a.src=g;m.parentNode.insertBefore(a,m)
  })(window,document,'script','https://www.google-analytics.com/analytics.js','ga');

  ga('create', 'UA-96334728-1', 'auto');
  ga('send', 'pageview');

  \$(document).ready(function() {
     hljs.initHighlighting();
  });
    </script>
</head>
<body>
$body
</body>
</html>
"""
end


type CalculateController <: ApplicationController
    conn::Conn
end

function my_fn(c::CalculateController)
    q = c[:params]
    x, y = map(v -> parse(Int, v), (q[:x], q[:y]))
    render(JSON, x + 2*y)
end

Router() do
    get("/", WelcomeController, index)
    get("/my_fn", CalculateController, my_fn)
end

Endpoint() do
    plug(Plug.Static, at= "/", from= "public")
    plug(Router)
end

Bukdu.start(parse(Int,ENV["PORT"]); host=ip"0.0.0.0")

(Endpoint)("/")
Base.JLOptions().isinteractive==0 && wait()

Bukdu.stop()
