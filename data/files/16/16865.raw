function read_config(pathname::String)
  config = JSON.parse(readall(pathname))
  return config
end

function clean_variable_name(variable_name::String)
  variable_name = replace(variable_name, r"^[^a-zA-Z0-9]+", "")
  variable_name = replace(variable_name, r"[^a-zA-Z0-9]+$", "")
  variable_name = replace(variable_name, r"_+", "_")
  variable_name = replace(variable_name, r"-+", "_")
  variable_name = replace(variable_name, r"\\s+", "_")
  variable_name = replace(variable_name, r"\\.+", "_")
  variable_name = replace(variable_name, r"[\\\\/]+", "_")
  if ismatch(r"^\d", variable_name)
    variable_name = strcat("x", variable_name)
  end
  return variable_name
end
