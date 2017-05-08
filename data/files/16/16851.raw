function message{T <: String}(str::T)
  println(str)
end

function warning{T <: String}(str::T)
  println(str)
end

function read_config{T <: String}(str::T)
  config = {"cache_loading" => "on",
            "data_loading" => "on",
            "recursive_loading" => "on",
            "munging" => "on",
            "logging" => "off",
            "load_libraries" => "on",
            "libraries" => String[]}
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
