jClass = @jimport "java.lang.Class";
jMethod = @jimport "java.lang.reflect.Method";
jConstructor = @jimport "java.lang.reflect.Constructor";

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



function getMethod{T}(typ::Type{JavaObject{T}}, name::ASCIIString = "")
	obj = typ((),);
	myClass   = jcall(obj, "getClass", (jClass), (),);
	myMethods = jcall(myClass, "getMethods", (Array{jMethod,1}), (),);
	for i= 1:size(myMethods,1)	
		s = jcall(myMethods[i], "toString", (JString), (),);
		if (name!="") && (match(Regex(name), s) != nothing)
			print(s);
			print("\n");
		end
	end
	print("\n");
end

function getMethod(obj::JavaObject, name::ASCIIString = "")
	myClass   = jcall(obj, "getClass", (jClass), (),);
	myMethods = jcall(myClass, "getMethods", (Array{jMethod,1}), (),);
	for i= 1:size(myMethods,1)	
		s = jcall(myMethods[i], "toString", (JString), (),);
		if (name!="") && (match(Regex(name), s) != nothing)
			print(s);
			print("\n");
		end
	end
	print("\n");
end


function getConstructor{T}(typ::Type{JavaObject{T}}, name::ASCIIString = "")
	obj = typ((),);
	myClass   = jcall(obj, "getClass", (jClass), (),);
	myConstructors = jcall(myClass, "getConstructors", (Array{jConstructor,1}), (),);
	for i= 1:size(myConstructors,1)	
		s = jcall(myConstructors[i], "toString", (JString), (),);
		if (name!="") && (match(Regex(name), s) != nothing)
			print(s);
			print("\n");
		end
	end
	print("\n");
end

function getConstructor(obj::JavaObject, name::ASCIIString = "")
	myClass   = jcall(obj, "getClass", (jClass), (),);
		myConstructors = jcall(myClass, "getConstructors", (Array{jConstructor,1}), (),);
	for i= 1:size(myConstructors,1)	
		s = jcall(myConstructors[i], "toString", (JString), (),);
		if (name!="") && (match(Regex(name), s) != nothing)
			print(s);
			print("\n");
		end
	end
	print("\n");
end

