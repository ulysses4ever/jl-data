using Base.Test

push!(LOAD_PATH, "src")
push!(LOAD_PATH, "../src")

using JuliaIntro, Slide
@assert isdefined(:JuliaIntro)
@assert isdefined(:Slide)

@test 1 == 1
@test 1 == page.start

for slide in Slide.pages
  @test isa(slide, Base.Markdown.MD)
end
