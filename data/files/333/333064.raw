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
  dogs = GooseCollection(Dog, MongoCollection(mcli, "pdb", "dogs"))

  context("Only inserts correct type") do
    @fact typeof(insert(people, Person("Tim", 25))) --> Mongo.BSONOID
    @fact_throws insert(people, Dog("Rover", Person("Tim", 25)))
    @fact_throws insert(dogs, Person("Tim", 25))
  end

  context("Queries the collection") do
    @fact typeof(first(find(people, ("age" => 25)))) --> Person
    @fact first(find(people, ("age" => 25))).name --> "Tim"
  end

end
