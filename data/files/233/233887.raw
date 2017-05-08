#number of subscribers when the subreddut is identified by its reddit id
#example: the "resumes" subreddit has id=t5_2r0bv
function idsubscribers(id::AbstractString)
	resp=Requests.get("https://www.reddit.com/api/info/.json?id="*id)
	resp=Requests.json(resp)
	resp["data"]["children"][1]["data"]["subscribers"]
end

#number of subscribers when the subreddut is identified by its name
function subscribers(sub::AbstractString)
	resp=Requests.get("https://www.reddit.com/r/"*sub*"/about.json")
	resp=Requests.json(resp)
	resp["data"]["subscribers"]
end

#convert datetime tuple to Unix time used in reddit timestamps
#timestamp intervals in cloudsearch searches is of the form 1420113600..1420200000
reddittime(yyyy,mm,dd,hh,min,sec)=Int(Dates.datetime2unix(DateTime(yyyy,mm,dd,hh,min,sec)))

#count the number of posts (top coded at 100) between two dates on a given subreddit
function countposts(subreddit::AbstractString,firstday::Tuple{Int64,Int64,Int64},lastday::Tuple{Int64,Int64,Int64})
	timestamp=string(reddittime(firstday[1],firstday[2],firstday[3],00,00,00))*".."*string(reddittime(lastday[1],lastday[2],lastday[3],00,00,00))
	url="https://www.reddit.com/r/"*subreddit*"/search.api?rank=title&limit=100&q=timestamp%3A"*timestamp*"&restrict_sr=on&syntax=cloudsearch"
	# println(url)
	resp=Requests.json(get("https://www.reddit.com/r/"*subreddit*"/search.api?rank=title&limit=200&q=timestamp%3A"*timestamp*"&restrict_sr=on&syntax=cloudsearch"));
	length(resp["data"]["children"])
end

#count the number of daily posts (top-coded at 100) for ndays days
function countdailyposts(subreddit::AbstractString,firstday::Date,ndays::Int64=3)
	dates=collect(firstday:firstday+Dates.Day(ndays-1))
	ts=TimeSeries.TimeArray(dates,zeros(length(dates)),["ts"])
	for i=1:ndays
		ts.values[i]=countposts(subreddit,Dates.yearmonthday(dates[i]),Dates.yearmonthday(dates[i]+Dates.Day(1)))
		sleep(.1)
	end
	ts
end

#parse the /about/traffic page of a subreddit
#2nd column is uniques and first columns is pageviews
function traffic(sub::AbstractString)
	resp=Requests.get("https://www.reddit.com/r/"*sub*"/about/traffic.json")
	resp=Requests.json(resp)
	n=length(resp["hour"])
	hourly=Array(Any,n,3)
	for i=1:n
		hourly[i,1]=Dates.unix2datetime(resp["hour"][i][1])
		hourly[i,2]=resp["hour"][i][2]
		hourly[i,3]=resp["hour"][i][3]
	end
	n=length(resp["day"])
	daily=Array(Any,n,3)
	for i=1:n
		daily[i,1]=Dates.Date(Dates.unix2datetime(resp["day"][i][1]))
		daily[i,2]=resp["day"][i][2]
		daily[i,3]=resp["day"][i][3]
	end
	n=length(resp["month"])
	monthly=Array(Any,n,3)
	for i=1:n
		dt=Dates.unix2datetime(resp["month"][i][1])
		monthly[i,1]=string(year(dt))*"-"*string(month(dt))
		monthly[i,2]=resp["month"][i][2]
		monthly[i,3]=resp["month"][i][3]
	end
	hourly,daily,monthly
end