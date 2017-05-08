function message{T <: String}(str::T)
  println(str)
end

function warning{T <: String}(str::T)
  println(str)
end

function read_config{T <: String}(pathname::T)
  config = JSON.parse(readall(pathname))
  return config
end

function clean_variable_name{T <: String}(variable_name::T)
  variable_name = replace(variable_name, r"^[^a-zA-Z0-9]+", "")
  variable_name = replace(variable_name, r"[^a-zA-Z0-9]+$", "")
  variable_name = replace(variable_name, r"_+", "_")
  variable_name = replace(variable_name, r"-+", "_")
  variable_name = replace(variable_name, r"\\s+", "_")
  variable_name = replace(variable_name, r"\\.+", "_")
  variable_name = replace(variable_name, r"[\\\\/]+", "_")
  return variable_name
end
