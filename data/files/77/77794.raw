typealias Book Dict{UTF8String, ASCIIString}

funcs = Dict{UTF8String, Function}()

function openbook(f)
    isfile(f) || error("no such phonebook ('$f')")
    open(s -> deserialize(s), f, "r")
end
function savebook(book::Book, f)
    open(s -> serialize(s, book), f, "w")
end

pbcreate(args...) = error("create takes a one argument: phonebook")
function pbcreate(f)
    isfile(f) && error("file '$f' already exists, can't create a new phonebook there")
    savebook(Book(), f)
    ""
end
funcs["create"] = pbcreate

pblookup(args...) = error("lookup takes two arguments: name, phonebook")
function pblookup(name, f)
    book = openbook(f)
    haskey(book, name) ? "$name $(book[name])" : ""
end
funcs["lookup"] = pblookup

pbadd(args...) = error("add takes three arguments: name, number, phonebook")
function pbadd(name, number, f)
    book = openbook(f)
    haskey(book, name) && error("'$name' is already in phonebook '$f'")
    book[name] = number
    savebook(book, f)
    ""
end
funcs["add"] = pbadd

pbchange(args...) = error("change takes three arguments: name, number, phonebook")
function pbchange(name, number, f)
    book = openbook(f)
    haskey(book, name) || error("'$name' is not in phonebook '$f'")
    book[name] = number
    savebook(book, f)
    ""
end
funcs["change"] = pbchange

pbremove(args...) = error("remove takes two arguments: name, phonebook")
function pbremove(name, f)
    book = openbook(f)
    haskey(book, name) || error("'$name' is not in phonebook '$f'")
    delete!(book, name)
    savebook(book, f)
    ""
end
funcs["remove"] = pbremove

# const SECRET = randstring(20)
pbreverse(args...) = error("reverse takes two arguments: name, number, phonebook")
function pbreverse(number, f)
    book = openbook(f)
    # name = getkey(book, number, SECRET)
    inds = findin(collect(values(book)), [number])
    matches = collect(keys(book))[inds]
    join(matches, '\n')
end
funcs["reverse-lookup"] = pbreverse
