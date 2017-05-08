using ArgMinimist
using Base.Test

function checkPositional()
  pos, kw = parse_args(["hello","world"])
  return pos == ["hello","world"] && length(kw)==0
end

function checkKeyword()

  expKW = Dict{Symbol,Any}()
  expKW[:jam] = false
  expKW[:honey] = true
  expKW[:cafe] = true

  expKW[:a] = true
  expKW[:b] = true
  expKW[:c] = true

  pos, kw = parse_args(["hello","world",
                          "--no-jam",
                          "--with-honey",
                          "-abc",
                          "--cafe"])

  return pos == ["hello","world"] && kw == expKW
end

function checkNamed()

  expKW = Dict{Symbol,Any}()
  expKW[:jam] = "yes"
  expKW[:honey] = "no"
  expKW[:cafe] = "ok"

  args = ["yes","no","--cafe=ok"]

  pos, kw = parse_named_args(["jam","honey","cafe"], args)
  return length(pos)==0 && kw == expKW
end
# write your own tests here
@test checkPositional()
@test checkKeyword()
@test checkNamed()
