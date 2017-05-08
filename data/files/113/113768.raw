using Base.Test

push!(LOAD_PATH, "src")
push!(LOAD_PATH, "../src")

import JuliaIntro: page
@test 1 == page.start

import Slide: pages
for slide in pages
  @test isa(slide, Base.Markdown.MD)
end
