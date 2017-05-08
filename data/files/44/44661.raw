# Author: Jeremy Werner
# Quick script to determine what proportion of my life I have lived in my current location
#  and on what date I will reach a given proportion. 

birth_date = Date(<YEAR>, <MONTH>, <DAY>)
moving_day = Date(<YEAR>, <MONTH>, <DAY>)

function today()
	Date(strftime("%F",time()))
end

function days_since(MovingDay::Date)
	today() - MovingDay 
end

function proportion_here(MovingDay::Date, BirthDate::Date)
	int(days_since(MovingDay)) / int(days_since(BirthDate))
end

function find_day(P::Number, MovingDay::Date, BirthDate::Date)
	if P >= 1 || P <= 0
		error("First argument P must be a number between 0 and 1")
	else
		days_from_now = -1 * int(today()) - int(MovingDay) / (P-1) +  int(BirthDate) * P / (P-1)
		return(today() + Dates.Day(int(days_from_now)))
	end
end
