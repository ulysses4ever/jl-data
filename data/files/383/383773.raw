using DBI
using PostgreSQL
using PyPlot
using DataFrames

function getPatientIDs(conn)
	println("gathering patient IDs")
	patientsWBloodWork = Int32[]
	querryBloodWork = "SELECT subject_id FROM MIMICIII.LABEVENTS WHERE ITEMID BETWEEN 51202 and 51211 OR ITEMID BETWEEN 51270 AND 51273 OR ITEMID = '51140' OR ITEMID ='51141' OR ITEMID = '51149' OR ITEMID BETWEEN 51213 AND 51214 OR ITEMID BETWEEN 51228 AND 51229 OR ITEMID BETWEEN 51264 AND 51266 OR ITEMID BETWEEN 51270 AND 51275 OR ITEMID BETWEEN 51297 AND 51299;"
	#stmt = prepare(conn, querryBloodWork)
	#result = execute(stmt)
	patientsWBloodWork = select(conn, querryBloodWork)
	finish(stmt)
	return patientsWBloodWork;
end

function main()
	conn = connect(Postgres, "localhost", "postgres", "totesSecure", "mimic", 5432)
	testsOfInterest = [51202:51211, 51270:51273, 51140:51141, 51149, 51213,51214,51228,51229,51264:51266,51270:51275,51296,51299]
	patient_ids= getPatientIDs(conn)
	println(patientids)
end

main()
