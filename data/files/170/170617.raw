module MacroTest

using Base.Test

push!(LOAD_PATH, "src")

using PageDown

pages = ["1", "2", "3", "4", "5"]
#page = Page(1, 1, pages)
page = Page(1, 1, pages, "IMG"=>"짤")

@test (page.start:page.step:page.count) == @page
@test ["1"] == @current

for n=1:2page.count
  println("n: $n")
  eval("@step $n")

  @go 1
  @test (1:page.step:page.count) == @page

  @next
  @test (1+page.step:page.step:page.count) == @page
  
  @prev
  @test (1:page.step:page.count) == @page
  
  @go 3
  @test (3:page.step:page.count) == @page
  
  @first
  @test (1:page.step:page.count) == @page
  
  @last
  @test (5:page.step:page.count) == @page
end

end
