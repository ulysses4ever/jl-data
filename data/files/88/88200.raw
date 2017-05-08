importall Base;
using JavaCall;
JavaCall.init(["-verbose:jni", "-verbose:gc","-Djava.class.path=$(joinpath(Pkg.dir(), "View5D\\AllClasses"));$(joinpath(Pkg.dir(), "loci_tools.jar"))"]);

jMethod = @jimport "java.lang.reflect.Method";
jClass = @jimport "java.lang.Class";



# Call static methods
function mjcall{T}(typ::Type{JavaObject{T}}, method::String, rettype::Type, argtypes::Tuple, args... )
	try
		jcall(typ, method, rettype, argtypes, args );
	catch e
		getMethod(typ);
		error(e);	
	end
end

# Call instance methods
function mjcall(obj::JavaObject, method::String, rettype::Type, argtypes::Tuple, args... )
	try
		jcall(obj, method, rettype, argtypes, args );
	catch e
		getMethod(obj);
		error(e);
	end
end














function getMethod{T}(typ::Type{JavaObject{T}})
#function getMethod(typ)
	myClass   = jcall(typ, "getClass", (jClass), (),);
	#myName    = jcall(myClass, "getName", (JString), (),);
	myMethods = jcall(myClass, "getMethods", (Array{jMethod,1}), (),);
	for i= 1:size(myMethods,1)	
		s = jcall(myMethods[i], "toString", (JString), (),);
		print(s);
		print("\n");
	end
	print("\n");
end

function getMethod(obj::JavaObject)
#function getMethod(obj)
	myClass   = jcall(obj, "getClass", (jClass), (),);
	#myName    = jcall(myClass, "getName", (JString), (),);
	myMethods = jcall(myClass, "getMethods", (Array{jMethod,1}), (),);
	for i= 1:size(myMethods,1)	
		s = jcall(myMethods[i], "toString", (JString), (),);
		print(s);
		print("\n");
	end
	print("\n");
end

