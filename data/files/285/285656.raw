using XmlToDict
using Base.Test, DataStructures

# write your own tests here
@test 1 == 1

xmltest = """
<?xml version="1.0" encoding="UTF-8"?>
<bookstore>
  <book category="COOKING" tag="first">
    <title lang="en">Everyday Italian</title>
    <author>Giada De Laurentiis</author>
    <year>2005</year>
    <price>30.00</price>
  </book>
  <book category="CHILDREN">
    <title lang="en">Harry Potter</title>
    <author>J K. Rowling</author>
    <year>2005</year>
    <price>29.99</price>
  </book>
  <newspaper>
    <name>The Times</name>
  </newspaper>
</bookstore>
"""

xt1 = xmlparse_string(xmltest)

@test xt1["bookstore"]["book"][1]["@category"] == "COOKING"
@test xt1["bookstore"]["book"][1]["@tag"] == "first"
@test xt1["bookstore"]["book"][1]["title"]["@lang"] == "en"
@test xt1["bookstore"]["book"][1]["title"]["#text"] == "Everyday Italian"
@test xt1["bookstore"]["book"][1]["author"]["#text"] == "Giada De Laurentiis"
@test xt1["bookstore"]["book"][1]["year"]["#text"] == "2005"
@test xt1["bookstore"]["book"][1]["price"]["#text"] == "30.00"


@test xt1["bookstore"]["book"][2]["@category"] == "CHILDREN"
@test xt1["bookstore"]["book"][2]["title"]["@lang"] == "en"
@test xt1["bookstore"]["book"][2]["title"]["#text"] == "Harry Potter"
@test xt1["bookstore"]["book"][2]["author"]["#text"] == "J K. Rowling"
@test xt1["bookstore"]["book"][2]["year"]["#text"] == "2005"
@test xt1["bookstore"]["book"][2]["price"]["#text"] == "29.99"

println("newspaper -> ", xt1["bookstore"][x2d"newspaper+"])

@test_throws KeyError xt1["bookstore"][x2d"magazines"]
@test xt1["bookstore"][x2d"magazines*"] == []

println("x2d'newspaper+' -> ", xt1["bookstore"][x2d"newspaper+"])
println("x2d'newspaper*' -> ", xt1["bookstore"][x2d"newspaper*"])
println("x2d'newspaper' -> ", [ xt1["bookstore"][x2d"newspaper"] ] )

@test isa(xt1["bookstore"]["newspaper"], Array) == false
@test xt1["bookstore"][x2d"newspaper+"] == [ xt1["bookstore"]["newspaper"] ]
@test xt1["bookstore"][x2d"newspaper*"] == [ xt1["bookstore"]["newspaper"] ]


