using DataFrames
using Calendar

issues = readtable("issuedata.wsv",separator=' ')
issues[:Month] = map(s->month(Calendar.parse("yyyy-MM-dd",s)),issues[:Date])
issues[:Year] = map(s->year(Calendar.parse("yyyy-MM-dd",s)),issues[:Date])
issues[:Date] = map(s->Calendar.parse("yyyy-MM-dd",s),issues[:Date])

curdate = minimum(issues[:Date])

@printf "first issue was in %s\n" format("MMMM yyyy",curdate)
@printf "new users by month:\n"

seenusers = Dict()

while curdate < now() + months(1)
    # find all comments in this month
    subframe = sub(issues,(issues[:Month] .== month(curdate)) & (issues[:Year] .== year(curdate)))
    newusers = 0
    for i in 1:size(subframe,1)
        user = subframe[i,:User]
        if !haskey(seenusers,user)
            newusers += 1
            seenusers[user] = true
        end
    end
    @printf "%s: %d\n" format("MMMM yyyy",curdate) newusers
    curdate += months(1)
end

