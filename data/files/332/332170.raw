using Taste
using FactCheck

facts("Have a beer") do
	todays_selection = [
	    Lambic = Bitter(rand(11:23))
	    Blonde = Bitter(rand(15:30))
	    Kölsch = Bitter(rand(18:25))
	    Märzen = Bitter(rand(18:25))
	    English = Bitter(rand(20:35))
	    Porter = Bitter(rand(20:40))
	    Brown = Bitter(rand(15:25))
	    NorthAmericanBrown = Bitter(rand(25:45))
	    Pilsener = Bitter(rand(30:45))
	    IPA = Bitter(rand(40:140))
	    IrishStout = Bitter(rand(25:60))
	]

	randbeer = rand(todays_selection)
    info(randbeer)

    istasty(beer::Bitter) = beer.IBU < 200
	@fact istasty(randbeer) => true
end


facts("Test Mac Tastebud Sensor") do
    if OS_NAME == :Darwin
        @fact measureumami() >= 0 => true
    else
        @fact_throws ErrorException measureumami()
    end
end
