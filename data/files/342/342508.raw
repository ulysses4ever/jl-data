using PyCall

+(x :: PyObject, y :: Any) = x[:__add__](y)
+(x :: Any, y :: PyObject) = y + x
-(x :: PyObject, y :: Any) = x[:__sub__](y)
-(x :: Any, y :: PyObject) = y - x
*(x :: PyObject, y :: Any) = x[:__mul__](y)
*(x :: Any, y :: PyObject) = y * x

function -(x :: PyObject)
  x[:__neg__]()
end

function pyslice(a, b)
  pybuiltin("slice")[:__call__](a, b)
end

pynone = pyeval("None")

