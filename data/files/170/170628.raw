module PageTest

using Base.Test

push!(LOAD_PATH, "src")

using PageDown

pages = ["1", "2", "3", "4", "5"]
page = Page(1, 1, pages)

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
page = Page(1, 10, pages, Dict())
@test_throws ArgumentError go!(page, 10)
last!(page)
@open 1
Base.Markdown.term(STDOUT, @first)

end
