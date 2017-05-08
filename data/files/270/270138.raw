using Goose,
      FactCheck

module People
  export Person, Dog
  type Person
    name::AbstractString
    age::Int64
  end
  type Dog
    name::AbstractString
    master::Person
  end
end

using People

mcli = MongoClient()

facts("Goose") do
  people = GooseCollection(Person, MongoCollection(mcli, "pdb", "people"))
  @fact typeof(insert(people, Person("Tim", 25))) --> Mongo.BSONOID
  @fact_throws insert(people, Dog("Rover", Person("Tim", 25)))
end
