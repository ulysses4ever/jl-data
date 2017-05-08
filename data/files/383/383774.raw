using DBI
using PostgreSQL
using PyPlot
using DataFrames

function getPatientIDs(conn)
	println("gathering patient IDs")
	patientsWBloodWork = Int32[]
	querryBloodWork = "SELECT subject_id FROM MIMICIII.LABEVENTS WHERE ITEMID BETWEEN 51202 and 51211 OR ITEMID BETWEEN 51270 AND 51273 OR ITEMID = '51140' OR ITEMID ='51141' OR ITEMID = '51149' OR ITEMID BETWEEN 51213 AND 51214 OR ITEMID BETWEEN 51228 AND 51229 OR ITEMID BETWEEN 51264 AND 51266 OR ITEMID BETWEEN 51270 AND 51275 OR ITEMID BETWEEN 51297 AND 51299;"
	stmt = prepare(conn, querryBloodWork)
	result = execute(stmt)
	for row in result
		#println(row)
		currPatient = row[1]
		if(!in(currPatient, patientsWBloodWork))
			#println(currPatient)
			push!(patientsWBloodWork, currPatient)
		end
	
	end
	finish(stmt)
	return patientsWBloodWork;
end

function getPatientsWClottingTime(conn)
	println("getting patients with clotting time measurement")
	patientsWCT = Int32[]
	querryCT = "SELECT DISTINCT subject_id FROM MIMICIII.LABEVENTS WHERE ITEMID = 51141 OR ITEMID BETWEEN 51274 AND 51275;"
	stmt = prepare(conn,querryCT)
	res = execute(stmt)
	for row in res
		currPatient = row[1]
		push!(patientsWCT, currPatient)
	end
	finish(stmt)
	return patientsWCT
	
end

function getAdultPatientsWClottingTime(conn)
	println("getting adult patients with clotting time")
	patientsWCT = Int32[]
	querryCT = 
"WITH first_admission_time AS
(
  SELECT
      p.subject_id, p.dob, p.gender
      , MIN (a.admittime) AS first_admittime
      , MIN( ROUND( (cast(admittime as date) - cast(dob as date)) / 365.242,2) )
          AS first_admit_age
  FROM MIMICIII.patients p
  INNER JOIN MIMICIII.admissions a
  ON p.subject_id = a.subject_id
  GROUP BY p.subject_id, p.dob, p.gender
  ORDER BY p.subject_id
)
, age as
(
  SELECT
      subject_id, dob, gender
      , first_admittime, first_admit_age
      , CASE
          -- all ages > 89 in the database were replaced with 300
          -- we check using > 100 as a conservative threshold to ensure we capture all these patients
          WHEN first_admit_age > 100
              then '>89'
          WHEN first_admit_age >= 14
              THEN 'adult'
          WHEN first_admit_age <= 1
              THEN 'neonate'
          ELSE 'middle'
          END AS age_group
  FROM first_admission_time
)
select DISTINCT subject_id FROM age where age_group='adult' INTERSECT
SELECT DISTINCT subject_id FROM MIMICIII.LABEVENTS WHERE ITEMID = 51141 OR ITEMID BETWEEN 51274 AND 51275; "
	

	stmt = prepare(conn,querryCT)
	res = execute(stmt)
	for row in res
		currPatient = row[1]
		push!(patientsWCT, currPatient)
	end
	finish(stmt)
	return patientsWCT
end

function getTestInfo(conn,test,patient, testDic)
	#println("getting test info")
	times = DateTime[]
	hasLotsOfValues = false;
	conversionStr = "y-m-d HH:MM:SS"
	values = Float64[]
	querryTest = string("SELECT valuenum, charttime FROM MIMICIII.LABEVENTS WHERE ITEMID = ",test," AND subject_id = ", patient, ";")
	#println(querryTest)
	stmt = prepare(conn, querryTest)
	result = execute(stmt)
	#println(result)
	for row in result
		#println(row)
		timeStr = row[2]
		time = DateTime(timeStr, conversionStr)
		val = row[1]
		if(typeof(val)!=Union)
			push!(values, val)
			push!(times, time)	
		end	
	end
	if(length(values)>20)
		#plotResults(times, values, test, patient,testDic)
		hasLotsOfValues = true;
	end
	finish(stmt)
	df = DataFrame()
	df[:values] = values
	df[:datetimes] = times
	
	givenunits = getUnits(conn,test)
	#println(fill(givenunits,length(values),1))
	#df[:units] = fill(givenunits,length(values),1)
	
	return df;
end

function getUnits(conn,test)
	units = AbstractString[]
	querryUnits = string("select unitname from MIMICIII.d_items where itemid =", test, ";")
	#println(querryUnits)
	stmt = prepare(conn,querryUnits)
	result = execute(stmt)
	for row in result
		push!(units, row[1])
	end
	
	finish(stmt)

	if(length(units) ==0)
		push!(units, "unknown")
	end
	#println(units[1])
	return units[1]

end

function plotResults(times, values, test, patient,testDic)
	figure()
	plot(times, values, "kx")
	xlabel("Time")
	ylabel("values")
	title(string("For measurement ", testDic[test], " for patient number ", patient))
	#only create a new folder if neccessary
	currDirs = readdir()
	if(!in(string(patient), currDirs))
		mkdir(string(patient))
	end
	savefig(string(patient,"/For measurement ", testDic[test], " for patient number ", patient, ".png"))
		
end

function createItemDic(conn)
	testDic = Dict()
	querryDict = "SELECT itemid, label FROM MIMICIII.D_LABITEMS UNION SELECT itemid, label FROM MIMICIII.D_ITEMS;"
	stmt = prepare(conn, querryDict)
	result = execute(stmt)
	for row in result
		itemid = row[1]
		label = row[2]
		testDic[itemid] = label
	end
	
	finish(stmt)
	return testDic
end


function createICD9Dict(conn)
	ICD9Dic = Dict()
	querryDict = "SELECT ICD9_CODE,long_title from MIMICIII.D_ICD_DIAGNOSES;"
	stmt = prepare(conn,querryDict)
	result = execute(stmt)
	for row in result
		icd9code = row[1]
		name = row[2]
		ICD9Dic[icd9code] = name
	end
	finish(stmt)
	return ICD9Dic
end

function getEthnicity(conn,patient)
	querryEthnicity = string("SELECT ethnicity FROM MIMICIII.ADMISSIONS WHERE subject_id =", patient,";")
	stmt = prepare(conn, querryEthnicity)
	result = execute(stmt)
	ethn = ""
	for row in result
		#println(row)
		ethn= row[1]
	end
	finish(stmt)
	return ethn
end

function getDiagnosis(conn,patient)
	diagnoses = AbstractString[]
	querryDiagnosis = string("SELECT ICD9_CODE FROM MIMICIII.DIAGNOSES_ICD WHERE subject_id =", patient,";")
	stmt = prepare(conn, querryDiagnosis)
	result = execute(stmt)
	for row in result
		diagnosis= row[1]
		push!(diagnoses, diagnosis)
	end
	finish(stmt)
	return diagnoses
end

function getVisits(conn,patient)
	visits = Int32[]
	querryVisits = string("SELECT hadm_id FROM MIMICIII.ADMISSIONS WHERE subject_id =", patient,";")
	stmt = prepare(conn, querryVisits)
	result = execute(stmt)
	for row in result
		visit = row[1]
		push!(visits,visit)
	end
	finish(stmt)
	return visits
end

function getTestsRun(conn,patient,testsOfInterest)
	testsRun = Int32[]
	querryTests = string("SELECT itemid FROM MIMICIII.LABEVENTS WHERE subject_id= ", patient, ";")
	stmt = prepare(conn, querryTests)
	result = execute(stmt)
	for row in result
		currTest = row[1]
		if(!in(currTest, testsRun) && in(currTest, testsOfInterest))
			push!(testsRun, currTest)
		end
	end
	finish(stmt)
	return testsRun
end

function getGender(conn,patient)
	gender = ""
	querryGender = string("SELECT gender FROM MIMICIII.PATIENTS WHERE subject_id = ", patient, ";")
	stmt = prepare(conn,querryGender)
	result = execute(stmt)
	for row in result
		gender = row[1]
	end
	return gender
end

function getAgeAtFirstAdmit(conn,patient)
	querryDOB = string("SELECT dob FROM MIMICIII.PATIENTS WHERE subject_id = ", patient, ";")
	querryDateAdmit	= string("SELECT MIN(admittime) FROM MIMICIII.ADMISSIONS WHERE subject_id = ", patient, ";") #get first date admitted
	conversionStr = "y-m-d HH:MM:SS"
	numberOfMSinYear = 3.154E10
	stmt = prepare(conn, querryDOB)
	resDOB = execute(stmt)
	DOBstr = ""
	DateAdmitStr=""
	for row in resDOB
		DOBstr = row[1]
	end
	stmt = prepare(conn, querryDateAdmit)
	resAdmit = execute(stmt)
	for row in resAdmit
		DateAdmitStr = row[1]
	end
	DOB = DateTime(DOBstr, conversionStr)
	DateAdmit = DateTime(DateAdmitStr, conversionStr)
	age = Float64(DateAdmit-DOB)/numberOfMSinYear

	return age
end

function getDied(conn,patient)
	#if expire_flag = 1, they died in the hospital
	querryDied = string("SELECT expire_flag FROM MIMICIII.PATIENTS WHERE subject_id = ", patient, ";")
	stmt = prepare(conn, querryDied)
	res = execute(stmt)
	died=""
	for row in res
		died = row[1]
	end
	finish(stmt)
	return died
end

function getHeartrate(conn,patient)
	#units are in BPM
	println("getting heart rate")
	conversionStr = "y-m-d HH:MM:SS"
	querryHeartrate=string("SELECT valuenum, charttime FROM MIMICIII.CHARTEVENTS where (itemid = 211 OR itemid=220045) AND subject_id =", patient,";")
	stmt = prepare(conn,querryHeartrate)
	res = execute(stmt)
	times =DateTime[]
	rates = Float64[]
	for row in res
		rate = row[1]
		time = row[2]
		if(typeof(rate)!=Union)
			push!(rates,rate)
			push!(times,DateTime(time,conversionStr))
		end
	end
	df = DataFrame()
	df[:values] = rates
	df[:datetimes] = times

	finish(stmt)
	return df
end

function getMeanBloodPressure(conn,patient)
	#units are mmHg
	conversionStr = "y-m-d HH:MM:SS"
	println("getting BP")
	querryBP = string("SELECT valuenum, charttime FROM MIMICIII.CHARTEVENTS where (itemid = 220181 OR itemid=220052) AND subject_id = ", patient, ";")
	stmt = prepare(conn,querryBP)
	res = execute(stmt)
	times =DateTime[]
	BPs = Float64[]
	for row in res
		for k in 1:length(row)
			if (typeof(row[k])==Union)
				row[k]=-1
			end
		end
		if(length(row)>0)
			value = row[1]
			time = row[2]
			if(typeof(value)!=Union)
				push!(BPs, value)
				push!(times,DateTime(time,conversionStr))
			end
		end
	end
	df = DataFrame()
	df[:values] = BPs
	df[:datetimes] = times
	finish(stmt)
	return df
end

function getHeight(conn,patient)
	#returned value will be in cm
	println("getting height")
	height = 0.0
	querryInches = string("SELECT valuenum FROM MIMICIII.CHARTEVENTS where (itemid = 1394 OR itemid = 226707) AND subject_id = ", patient, ";")
	querryCm = string("SELECT valuenum FROM MIMICIII.CHARTEVENTS where (itemid = 226730) AND subject_id = ", patient, ";")
	inches_to_cm = 2.54

	stmt = prepare(conn,querryInches)
	res = execute(stmt)

	#if we don't have a measurement in inches, try cm
	if(length(res)==0)
		stmt = prepare(conn,querryCm)
		res = execute(stmt)
		for row in res
			height = row[1]
		end
	else
		for row in res
			height=row[1]*inches_to_cm
		end
	end
	finish(stmt)
	return height

end

function getWeight(conn,patient)
	#returned value will be in kg
	println("getting weight")
	weight = 0.0
	querrykg = string("SELECT valuenum FROM MIMICIII.CHARTEVENTS where (itemid = 3580 OR itemid = 226512) AND subject_id = ", patient, ";")
	querrylbs = string("SELECT valuenum FROM MIMICIII.CHARTEVENTS where (itemid = 3581 OR itemid = 226531) AND subject_id = ", patient, ";")
	lbs_to_kg = .4356

	stmt = prepare(conn,querrykg)
	res = execute(stmt)
	if(length(res)!=0)
		for row in res
			weight=row[1]
		end
	else
		stmt = prepare(conn,querrylbs)
		res = execute(stmt)
		for row in res
			weight = row[1]*lbs_to_kg
		end
	end
	finish(stmt)
	return weight
end

function getDrugs(conn,patient,itemDic)
	println("getting drugs")
	conversionStr = "y-m-d HH:MM:SS"
	times = DateTime[]
	items = AbstractString[]
	values = Float64[]
	units = AbstractString[]
	rates = []
	rateUnits = AbstractString[]
	routes = AbstractString[]
	querryCV = string("SELECT charttime, itemid, amount, amountuom, rate, rateuom, originalroute FROM MIMICIII.INPUTEVENTS_CV where subject_id = ", patient, ";")
	stmt = prepare(conn,querryCV)
	res = execute(stmt)
	for row in res
		#clean up unions
		for k in 1:length(row)
			if (typeof(row[k])==Union)
				row[k]=-1
			end
		end
		charttime = DateTime(row[1],conversionStr)
		push!(times, charttime)
		itemid = row[2]
		push!(items, itemDic[itemid])
		amount = row[3]
		push!(values, amount)
		unit = row[4]
		push!(units, unit)
		rate = row[5]
		if(typeof(rate)==Union)
			push!(rates, -1.0)
		else		
			push!(rates, rate)
		end
		rateUnit = row[6]
		push!(rateUnits, rateUnit)
		route = row[7]
		push!(routes,route)
	end

	querryMV= string("SELECT starttime, itemid,amount,amountuom,rate,rateuom FROM MIMICIII.INPUTEVENTS_MV where subject_id", patient, ";")
	stmt = prepare(conn, querryMV)
	res = execute(stmt)
	for row in res
		#clean up unions
		for k in 1:length(row)
			if (typeof(row[k])==Union)
				row[k]=-1
			end
		end
		charttimes = DateTime(row[1], conversionStr)
		push!(times, charttime)
		itemid = row[2]
		push!(items, itemDic[itemid])
		amount = row[3]
		push!(values, amount)
		unit = row[4]
		push!(units, unit)
		rate = row[5]
		if(typeof(rate)==Union)
			push!(rates, -1.0)
		else		
			push!(rates, rate)
		end
		rateUnits = row[6]
		push!(rateUnits, rateUnits)
	end
	df = DataFrame()
	df[:item]=items
	df[:times] = times
	df[:values] = values
	df[:units] = units
	df[:rates] = rates
	df[:rateUnits]=rateUnits

	return df
end

function plotfromDF(df, savestr)
	plotTimes = [];
	times = df[:datetimes]
	values = df[:values]
	#may need to convert strings to date times
	conversionStr = "y-m-d HH:MM:SS"
	if(contains(string(typeof(values)), "String"))
		for time in times
			push!(plotTimes, DateTime(time, conversionStr))
		end
	
	else
		plotTimes = times	
	end
	PyPlot.plot(plotTimes, values, "kx")
	savefig(savestr)
	close("all")
end

function plotDrugs(df, savestr,patient)
	uniqueDrugs = AbstractString[]

	for drug in df[1]
		if(!in(drug,uniqueDrugs))
			push!(uniqueDrugs,drug)
		end
	end
	println(uniqueDrugs)
	
	 fig = figure(figsize=(25,25))
	#fig.subplots_adjust(bottom=.2)
	plt[:hold] = true
	 #plt[:tight_layout]() 
	plt[:subplots_adjust](top=2.5)
	
	counter = 1
	for drug in uniqueDrugs
		ax = plt[:subplot](length(uniqueDrugs),1,counter)
		
		plt[:tick_params](axis="both", which="major", labelsize=7)
	 	plt[:tick_params](axis="both", which="minor", labelsize=7)
		#ax[:yaxis][:set_ylim]([0, 500])
		PyPlot.plot(df[:times], df[:values], "k." )
		ax[:set_ylim]([0,500])
		title(drug)
		counter=counter+1
	end
	
	savefig(savestr)
	close("all")
	
end

function buildProfile(conn,patient,testDic, ICD9Dic,testsOfInterest)
	println(string("bulding profile for patient ", patient))
	currDirs = readdir("output")
	if(!in(string(patient), currDirs))
		mkdir("output/"string(patient))
	end
	#ethnicity = getEthnicity(conn,patient)
	@time diagnoses = getDiagnosis(conn,patient)
	#visits = getVisits(conn,patient)
	#gender = getGender(conn,patient)
	@time testsRun = getTestsRun(conn,patient,testsOfInterest)
	#ageAtFirstAdmit = getAgeAtFirstAdmit(conn,patient)
	#died = getDied(conn,patient)
	#height = getHeight(conn,patient)
	#weight = getWeight(conn,patient)
	@time dfHeartrate = getHeartrate(conn,patient)
	#println(dfHeartrate)
	@time dfMeanBP = getMeanBloodPressure(conn, patient)
	#println(dfMeanBP)
	@time dfDrugs = getDrugs(conn,patient,testDic)
	println(dfDrugs)

	#println(string("Patient ", patient, " is ethnicity ", ethnicity, " gender ",  gender ," is ", height, " cm tall ", " weighs ", weight, " kg ", "and had ", length(visits), " vists."))
	#println(string("They were ", ageAtFirstAdmit, "when first admitted."))
	println("They had the following tests run:")
	for test in testsRun
		timeStrs = String[]
		println(testDic[test])
		dfTests =getTestInfo(conn,test,patient, testDic)
		if(length(dfTests)>1)
			plotfromDF(dfTests, string("output/",patient,"/", testDic[test], ".png"))
			#println(dfTests)
			writetable(string("output/",patient,"/", testDic[test], ".csv"),dfTests)
		end
	end
	println("They had the following diagnoses")
	for dia in diagnoses
		if(haskey(ICD9Dic,dia))
			println(ICD9Dic[dia])
		else
			println(dia)
		end
	end
	if(length(dfHeartrate)>0)
		writetable(string("output/",patient,"/", "HeartRate", ".csv"), dfHeartrate)
		plotfromDF(dfHeartrate, string("output/", patient,"/", "HeartRate", ".png"))
	end
	
	if(length(dfMeanBP)>0)
		writetable(string("output/", patient,"/","MeanBP", ".csv"), dfMeanBP)
		plotfromDF(dfMeanBP, string("output/", patient,"/","MeanBP", ".png"))
	end

	if(length(dfDrugs)>0)
		writetable(string("output/", patient,"/","Drugs", ".csv"), dfMeanBP)
		plotDrugs(dfDrugs, string("output/", patient,"/","Drugs", ".png"), patient)
	end

	println()

end

function main()
	conn = connect(Postgres, "localhost", "postgres", "totesSecure", "mimic", 5432)
	testsOfInterest = [51202:51211, 51270:51273, 51140:51141, 51149, 51213,51214,51228,51229,51264:51266,51270:51275,51296,51299]
	
	#@time patientsWBloodWork = getPatientIDs(conn)
	#for testing purposes, make things go faster
	patientsWBloodWork=Int32[12,13,17,18,19,20,21,38,41,22,23,37,43,44,42,45,36,35]
	#patientsWMultipleTests = Int32[]
	#patientsWClottingTime = getPatientsWClottingTime(conn)
	@time AdultPatientsWClottingTime = getAdultPatientsWClottingTime(conn)
	itemDic = createItemDic(conn)
	ICD9Dic = createICD9Dict(conn)
	#println(testDic)
	for patient in AdultPatientsWClottingTime
		if (mod(patient,100) ==0)
			println(string("on patient "), patient)
		end
#		numTestsRun = 0
#		for test in testsOfInterest
#			dfTests = getTestInfo(conn, test,patient,itemDic)
#			if(length(dfTests[:datetimes])>0)
#				numTestsRun = numTestsRun+1;
#			end
#		end
#		if(numTestsRun>1)
#			push!(patientsWMultipleTests, patient)
#		end
		#println(string("patient ", patient, " had ", numTestsRun, " tests of interest run."))
		buildProfile(conn,patient,itemDic,ICD9Dic,testsOfInterest)
	end
	
#	println("number of patients with more than 1 test run")
#	println(length(patientsWMultipleTests))	
#	#println(patientsWMultipleTests)
#	writedlm("patientsWMultipleTests.txt", patientsWMultipleTests)
	
	println("number of Adult patients with a clotting time measured")
	println(length(AdultPatientsWClottingTime))
	#println(patientsWClottingTime)
	writedlm("AdultpatientsWClottingTime.txt", AdultPatientsWClottingTime)
	PostgreSQL.disconnect(conn)
end

main()
