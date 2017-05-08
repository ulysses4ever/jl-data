using Goose,
      FactCheck

using Goose: jl2bson

module People
  using LibBSON
  export Person, Dog
  type Person
    _id::BSONOID
    name::AbstractString
    age::Int64
  end
  Person(name, age) = Person(BSONOID(), name, age)
  type Dog
    _id::BSONOID
    name::AbstractString
    master::Person
  end
  Dog(name, master) = Dog(BSONOID(), name, master)
end

type NoID
  foo::Int64
end

using People

# db = GooseDB(MongoClient(), "pdb")
#
# facts("Goose") do
#   people = GooseCollection(db, Person, "people")
#   dogs = GooseCollection(db, Dog, "dogs")
#
#   context("Builds the DB map") do
#     @fact haskey(Goose.dbmap, "pdb") --> true
#     @fact Goose.dbmap["pdb"][1] --> people
#     @fact Goose.dbmap["pdb"][2] --> dogs
#   end
#
#   context("Serializes models") do
#     tim = Person("Tim", 25)
#     bso = jl2bson(tim)
#     @fact typeof(bso) --> BSONObject
#     @fact bso["name"] --> "Tim"
#     @fact bso["age"] --> 25
#
#     bso = jl2bson(Dog("Rover", tim))
#     @fact bso["master"]["\$id"] --> tim._id
#   end
#
#   context("Inserts some models") do
#     tim = Person("Tim", 25)
#     rover = Dog("Rover", tim)
#     @fact insert(people, tim) --> tim._id
#     @fact insert(dogs, rover) --> rover._id
#   end
#
#   context("Requires that model has _id field") do
#     @fact_throws GooseCollection(db, NoID, "noids")
#   end
#
#   context("Only inserts correct type") do
#     @fact_throws insert(people, Dog("Rover", Person("Tim", 25)))
#     @fact_throws insert(dogs, Person("Tim", 25))
#   end
#
#   context("Queries the collection") do
#     @fact typeof(first(find(people, ("age" => 25)))) --> Person
#     @fact first(find(people, ("age" => 25))).name --> "Tim"
#   end
#
#   context("Fetches DBRef") do
#     rover = first(find(dogs, ("name" => "Rover")))
#     @show rover
#   end
# end

type Birthday
  day::Date
  exact::DateTime
end

facts("JSON Serialization") do
  tim = Person("Tim", 25)
  js = Goose.jl2json(tim)
  @fact js[:name] --> "Tim"
  @fact js[:age] --> 25
  @fact typeof(js[:_id]) <: AbstractString --> true

  bday = Birthday(Dates.today(), now())
  b = Goose.jl2json(bday)
  @fact typeof(b[:day]) <: AbstractString --> true
  @fact typeof(b[:exact]) <: AbstractString --> true
end
