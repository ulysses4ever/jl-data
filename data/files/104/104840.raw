using Base.Test
require("Diff")

test_type = length(ARGS) == 1 ? ARGS[1] : "ALL"

s1 = "bjuclgiah iks apwecsogmbe ahndk fapst."
s2 = "qjurlviax iyszz zaweqsormev axndy fzaqstr."

if test_type == "ALL" || test_type == "TEST" || test_type == "INSTALL"
  @test Diff.one_of_the_lcs(s1, s2) ==  "julia is awesome and fast."
  @test Diff.one_of_the_lcs([0:7:500],[0:11:500]) == [0:7*11:500]
end

if test_type == "ALL" || test_type == "PERF"
  x = ''
  @time for rep = 1:70
    s1l = repeat(s1,rep)
    s2l = repeat(s2,rep)
    x = Diff.edit_distance(s1,s2)
  end
end
