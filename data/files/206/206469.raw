#random funciton I created that performs many operations 
function my_function(x::Float64)
    sum = 0.0; 
    n = 1000; 
    dx = x/n; 
    for i in 1:n
        sum += dx*sin(cos(x)-4.0)*exp(-x*x/0.5); 
    end
    
    sum
end

function plot_error()
	 error = y - lookup_y; 
	 plot(x,error); 
	 title("Error Between function evaluation and Lookup Table")
end

function plot_my_function()
	plot(x,y); 
end

#calculates the performance time for generating an array evaluating my function 
#or simply generating a lookup table
function compare_performance()
	 lookup_time = 0.0; 
	 linear_table = make_table_linear(my_function,a,b,n); 
	 lookup_time = @elapsed(make_table_linear(my_function,a,b,n)); 
	 this_x = linspace(0,1,100000); 
	 function_time = @elapsed map(my_function,this_x); 
	 lookup_time += @elapsed lookup(linear_table,this_x); 

	 this_y = map(my_function,this_x); 
	 this_lookup_y = lookup(linear_table,this_x); 

	 this_error = maximum(abs(this_y - this_lookup_y)); 

	 println("The time to use the function evaluation is ",function_time," and the time to use the lookup table is ",lookup_time); 
	 println("The maximum absolute error between the output of both methods is ", this_error); 
end


function compare_ecc_anom()
	 plot(mean_anom,my_ecc_anom); 
	 looked_up_ecc_anom = lookup(ecc_anom_table,mean_anom); 
	 plot(mean_anom,looked_up_ecc_anom,"o"); 
	 axis([0,2pi,0,8])
	 max_data = findmax(looked_up_ecc_anom); 
	 min_data = findmin(looked_up_ecc_anom); 
	 println("The max of lookup table is ",max_data[1]," located at ",mean_anom[max_data[2]] ); 
	 println("The min of lookup table is ",min_data[1]," located at ",mean_anom[min_data[2]]);  
end

function plot_ecc_deriv()
	 mean_anom = linspace(0,2pi,length(ecc_anom_table.dy)); 
	 plot(mean_anom,ecc_anom_table.dy); 
	 title("Eccentric Anaomaly Derivative"); 
	 xlabel("Mean anomaly");
end




a = 0.0; 
b = 1.0; 
n = 100; 

lookup_table = make_table_linear(my_function,a,b,n); 

x = linspace(a,b,1000); 
y = map(my_function,x); 

lookup_y = lookup(lookup_table,x); 

ecc_anom_table = make_table_linear(x -> ecc_anom(x,0.25),0.0,2pi,128);

mean_anom = linspace(0.0,2pi,1000); 
my_ecc_anom = ecc_anom(mean_anom,0.25); 
