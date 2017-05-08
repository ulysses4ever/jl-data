module PageDown

export Page, next!, prev!, go!, first!, last!
export clear, proper
export @page, @current, @next, @prev, @go, @first, @last, @step, @open

__precompile__(true)

type Page
  pages::AbstractArray
  start::Int
  step::Int
  option::Dict
  count::Int
  Page(pages::AbstractArray) = new(pages, 1, 1, Dict(), length(pages))
  Page(pages::AbstractArray, start::Int, step::Int) = new(pages, start, step, Dict(), length(pages))
  Page(pages::AbstractArray, start::Int, step::Int, option::Dict) = new(pages, start, step, option, length(pages))
  Page(pages::AbstractArray, option::Pair...) = new(pages, 1, 1, Dict(option), length(pages))
end

function next!(page::Page)
  if (page.start + page.step) <= page.count
    page.start += page.step
  else
    #println("last page")
  end
  page
end

function prev!(page::Page)
  if page.start > page.step
    page.start -= page.step
  else
    #println("first page")
  end
  page
end

function go!(page::Page, number::Int)
  if number >= 1 && page.count >= number
    page.start = number
  else
    throw(ArgumentError("not found"))
  end
  page
end

function first!(page::Page)
  go!(page, 1)
end

function last!(page::Page)
  if page.count > page.step
    go!(page, page.count - (page.step - page.count % page.step - 1))
  else
    go!(page, page.count)
  end
end

function clear()
  @windows ? nothing : run(`clear`)
end

function proper(page::Page)
  if page.start + page.step <= page.count
    slides = page.pages[page.start:page.start+page.step-1]
  else
    slides = page.pages[page.start:end]
  end
  page,slides
end

function slides(tup::Tuple{Page,Array})
  page,slides = tup
  slides
end

function zzal(tup::Tuple{Page,Array})
  page,slides = tup
  img = haskey(page.option, "IMG") ? page.option["IMG"] : "IMG"
  imgcat = "../images/imgcat.go"
  ispath(imgcat) && for slide in slides
    isa(slide, Base.Markdown.MD) && for content in slide.content
      isa(content, Base.Markdown.List) && for item in content.items
        for el in item
          if startswith(el, img)
            zz,image = split(el, "$img ")
            run(`go run $imgcat ../images/$image`)
          end
        end
      end
    end
  end
  page,slides
end

function open(page::Page, site::Int)
  counter = 0
  for slide in page |> proper |> slides
    isa(slide, Base.Markdown.MD) && for content in slide.content
      isa(content, Base.Markdown.List) && for item in content.items
        for el in item
          m = match(r"http.*", el)
          if isa(m, RegexMatch)
            counter += 1
            if counter == site
              run(`open $(m.match)`)
              return
            end
          end
        end
      end
    end
  end
end


### macros

macro page()
  p = esc(:page)
  :( StepRange($p.start:$p.step:$p.count) )
end

macro current()
  :( $(esc(:page)) |> proper |> zzal |> slides )
end

macro next()
  clear()
  println()
  :( next!($(esc(:page))) |> proper |> zzal |> slides )
end

macro prev()
  :( prev!($(esc(:page))) |> proper |> slides )
end

macro go(number::Int)
  :( go!($(esc(:page)),$number) |> proper |> zzal |> slides )
end

macro first()
  :( first!($(esc(:page))) |> proper |> zzal |> slides )
end

macro last()
  :( last!($(esc(:page))) |> proper |> zzal |> slides )
end

macro step(pace::Int)
  :( $(esc(:page)).step = $pace )
end

macro open(site::Int)
  :( open($(esc(:page)),$site) )
end


# term
Base.Markdown.term(t::Union{Base.PipeEndpoint,Base.TTY}, a::Array{Base.Markdown.MD,1}) =
  [Base.Markdown.term(t, e) for e in a]
Base.Markdown.term(t::Union{Base.PipeEndpoint,Base.TTY}, a::Array{ASCIIString,1}) = a

end # module
