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
	 lookup_time += @elapsed lookup(linear_table,x); 

	 println("The time to use the function evaluation is ",function_time," and the time to use the lookup table is ",lookup_time); 
end



a = 0.0; 
b = 1.0; 
n = 100; 

lookup_table = make_table_linear(my_function,a,b,n); 

x = linspace(a,b,1000); 
y = map(my_function,x); 

lookup_y = lookup(lookup_table,x); 
