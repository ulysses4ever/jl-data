module PageTest

using Base.Test
using PageDown

pages = ["1", "2", "3", "4", "5"]
page = Page(pages)

@test 1 == page.start
@test 1 == page.step

next!(page)
@test 2 == page.start

prev!(page)
@test 1 == page.start

prev!(page)
@test 1 == page.start

last!(page)
@test page.count == page.start

first!(page)
@test 1 == page.start

@test (page,["1"]) == proper(page)


# coverage
page = Page(pages, 1, 10)
@test_throws ArgumentError go!(page, 10)
last!(page)
@open 1
Base.Markdown.term(STDOUT, @first)

pages = ["1", "2", "3", "4", "5"]
page = Page(pages, 1, 1, Dict())

option = Dict(:IMG=>"IMG", :imgcmd=>"ls", :imgcat=>"", :imgfolder=>"", :opencmd=>"echo")
using Base.Markdown
pages = [md"""
         # img
          - IMG sample.png
         """]
page = Page(pages, option)
@next

pages = [md"""
         # github
          - http://github.com
         """]
page = Page(pages, option)
@open 1

end
