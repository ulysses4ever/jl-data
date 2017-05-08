const regex = Regex("([<>]=?)?$(Base.VERSION_REGEX.pattern[2:end-1])", "ix")

abstract VersionQuery

immutable VersionRestriction{operator} <: VersionQuery
  value::VersionNumber
end

immutable VersionGlob <: VersionQuery
  major::Int
  minor::Int
  patch::Int
  VersionGlob(a,b,c) = begin
    a ≡ nothing && return new(-1,-1,-1)
    b ≡ nothing && return new(int(a),-1,-1)
    c ≡ nothing && return new(int(a),int(b),-1)
    return new(int(a),int(b),int(c))
  end
end

immutable Conjunction <: VersionQuery
  queries::(VersionQuery...)
end

##
# Parse a SemverQuery from a string
#
function semver_query(s::String)
  s == "*" && return VersionGlob(-1,-1,-1)
  queries = map(eachmatch(regex, s)) do match
    op,major,minor,patch = match.captures
    op ≡ nothing && return VersionGlob(major,minor,patch)
    version = convert(VersionNumber, match.match[length(op) + 1:end])
    VersionRestriction{symbol(op)}(version)
  end
  @assert !isempty(queries) "\"$s\" is not a valid semver query"
  length(queries) > 1 ? Conjunction(tuple(queries...)) : queries[1]
end

macro semver_str(s) semver_query(s) end

test("parser") do
  @test semver">=3" == VersionRestriction{:>=}(v"3")
  @test semver"3.1" == VersionGlob(3,1,-1)
  @test semver"*" == VersionGlob(-1,-1,-1)
  @test semver"3" == VersionGlob(3,-1,-1)
  @test semver">2.1 <3.2" == Conjunction((semver">2.1",semver"<3.2"))
end

##
# Test if a version satisfies a SemverQuery
#
Base.ismatch(q::VersionRestriction{:<}, v::VersionNumber) = v < q.value
Base.ismatch(q::VersionRestriction{:>}, v::VersionNumber) = v > q.value
Base.ismatch(q::VersionRestriction{:>=}, v::VersionNumber) = v >= q.value
Base.ismatch(q::VersionRestriction{:<=}, v::VersionNumber) = v <= q.value

Base.ismatch(q::VersionGlob, v::VersionNumber) = begin
  q.patch ≡ -1 || q.patch ≡ v.patch || return false
  q.minor ≡ -1 || q.minor ≡ v.minor || return false
  q.major ≡ -1 || q.major ≡ v.major || return false
  return true
end

Base.ismatch(q::Conjunction, v::VersionNumber) = all(q-> ismatch(q, v), q.queries)

test("ismatch") do
  @test !ismatch(semver">=2.1", v"2")
  @test ismatch(semver"<2.1", v"2")
  @test ismatch(semver"1", v"1.2.3")
  @test !ismatch(semver"1.3", v"1.2.3")
  @test ismatch(semver">1 <2", v"1.2.3")
  @test !ismatch(semver">1.2.4 <2", v"1.2.3")
end

##
# Find the best match from a collection of versions
#
Base.findmax(q::VersionQuery, enumerable) = begin
  best_v = typemin(VersionNumber)
  for v in enumerable
    if ismatch(q, v) && v > best_v
      best_v = v
    end
  end
  return best_v
end

test("findmax") do
  @test findmax(semver"1", [v"1",v"1.1",v"1.1.1",v"1.1.2"]) == v"1.1.2"
  @test findmax(semver">1 <2", [v"1.1",v"1",v"2"]) == v"1.1"
end
