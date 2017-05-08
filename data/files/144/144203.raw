
function bulkCalc_evwVgl1(disc::DiscMethode)
	N = 400.0
	dt = 2e-6
	as = 1.0:0.1:2.0
	T = 10.0

	N = 500.0
	dt = 2e-6 / 1.4
	as = [1.3 1.5 1.7]
	as = [1.1 1.9]
	T = 4.0

	for a in as
		res = fractDeriv(dx=1.0/N, dt=dt, T=T, bwp=EvwVgl(b=0.1), disc=disc, a=a);
		RS_save(res, "evwVgl1_$(disc.toString)_$a")
	end
	
end


function bulkCalc_evwVgl2(disc::DiscMethode)
	dt = 2e-6
	T = 10.0
	
	params = [
		100 1.1
		200 1.1
	#	400 1.1
	##	800 1.1
	##	1600 1.1
	##	3200 1.1
		100 1.5
		200 1.5
	#	400 1.5
	##	800 1.5
	##	1600 1.5
	##	3200 1.5
		100 1.9
		200 1.9
	#	400 1.9
	##	800 1.9
	];

	for i = 1:length(params[:,1])
		res = fractDeriv(dx=1.0/params[i,1], dt=dt, T=T, bwp=EvwVgl(b=0.1), disc=disc, a=params[i,2]);
		RS_save(res, "evwVgl2_$(disc.toString)_$(params[i,1])_$(params[i,2])")
	end
	
end

function bulkCalc_evwVgl3(disc::DiscMethode)
	T = 10.0
	N = 400
	a = 1.5
	
	#dts = [2e-6 2e-5 2e-4 2e-3]
	dts = [2e-5 2e-4 2e-3]
	
	N = 800
	dts = [2e-4]/2.8

	for dt in dts
		res = fractDeriv(dx=1.0/N, dt=dt, T=T, bwp=EvwVgl(b=0.1), disc=disc, a=a);
		RS_save(res, "evwVgl3_$(disc.toString)_$dt")
		res = 0;
	end
	
end

function bulkCalc1()
	#bulkCalc_evwVgl1(L2("im"));
	bulkCalc_evwVgl2(L2("im"));
	bulkCalc_evwVgl3(L2("im"));
end

function bulkCalc2()
	#bulkCalc_evwVgl1(L2C("im"));
	bulkCalc_evwVgl2(L2C("im"));
	bulkCalc_evwVgl3(L2C("im"));
end

function GS_alphaMatrix()
	as1 = 1.0 : 0.1 : 2.0 ;
	as2 = as1;
	#dt = 0.1;
	dt = 0.005;

	#as1 = 1.5 : 0.1 : 2.0 ;
	#as2 = 1.0 : 0.1 : 1.5;
	#dt = 0.01;
	
	#as1 = 1.0 : 0.1 : 1.4 ;
	#as2 = 1.0 : 0.1 : 2.0;
	#dt = 0.01;
	
	#as1 = 1.5 : 0.1 : 2.0 ;
	#as2 = 1.6 : 0.1 : 2.0;
	#dt = 0.01;
	
	for a1 in as1, a2 in as2
		
		if(a1 <= 1.2 || (a1 == 1.3 && a2 <= 1.5))
			continue;
		end
		
		
		res_u, res_v = fractGrayScott(dx=0.0025, dt=dt, bwp=GrayScott(a1=a1,a2=a2),disc1=L2("im"),disc2=L2("im"),imgX=400,imgT=250);
		RS_save(res_u, "alphaMat/alphaMat_$(a1)_$(a2)_u")
		RS_save(res_v, "alphaMat/alphaMat_$(a1)_$(a2)_v")

		RS_makeMesh2(res_u);
		savefig("resultaten/alphaMat/alphaMat_$(a1)_$(a2)_u.png");
		close();

		RS_makePlot(res_u);
		savefig("resultaten/alphaMat/alphaMat_$(a1)_$(a2)_u_plot.png");
		close();

		RS_makeMesh2(res_v);
		savefig("resultaten/alphaMat/alphaMat_$(a1)_$(a2)_v.png");
		close();

		RS_makePlot(res_v);
		savefig("resultaten/alphaMat/alphaMat_$(a1)_$(a2)_v_plot.png");
		close();
		
		res_u = 0;
		res_v = 0;
	end
	
end

function GS_alphaMatrix_addPlots()
	as1 = 1.0 : 0.1 : 2.0 ;
	as2 = as1;
	dt = 0.01;
	
	for a1 in as1, a2 in as2
		result = RS_open("alphaMat_0.0025_$(dt)/alphaMat_$(a1)_$(a2)_u");
		RS_makePlot(result);
		savefig("resultaten/alphaMat_0.0025_$(dt)/alphaMat_$(a1)_$(a2)_u_plot.png");
		close();
		
		result = RS_open("alphaMat_0.0025_$(dt)/alphaMat_$(a1)_$(a2)_v");
		RS_makePlot(result);
		savefig("resultaten/alphaMat_0.0025_$(dt)/alphaMat_$(a1)_$(a2)_v_plot.png");
		close();
		RS_makeMesh(result);
		savefig("resultaten/alphaMat_0.0025_$(dt)/alphaMat_$(a1)_$(a2)_v.png");
		close();
		
		println("$(a1)_$(a2)");
	end
end

function GS_alphaMatrix_specificPlots()
	as = [
		(1.2, 1.8)
		(1.2, 1.7)
		(1.2, 1.0)
		(1.6, 1.5)
		(1.6, 2.0)
		(2.0, 2.0)
	]
	dt = 0.01;
	
	for (a1, a2) in as
		result = RS_open("alphaMat_0.0025_$(dt)/alphaMat_$(a1)_$(a2)_v");
		RS_makeMesh2(result);
		savefig("resultaten/alphaMat_0.0025_$(dt)/alphaMat_$(a1)_$(a2)_v_2.png");
		close();
		
		println("$(a1)_$(a2)");
	end
end