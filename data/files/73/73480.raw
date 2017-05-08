
module Bash
  import Base:
    keys

  export
    colors,
    clear,
    format

  #
  # Format given colors to a valid bash escape sequence
  #

  function format (color::String)
    "\e[" * color * "m"
  end

  function format (colors::Dict)
    for key in keys(colors)
      colors[key] = format(colors[key])
    end

    colors
  end

  #
  # Colors.
  #

  colors = [
    "black" => "0;30",
    "red" => "0;31"
  ]

  #
  # Background colors.
  #

  backgrounds = []

  #
  # Clear color to default.
  #

  clear = "0"

  #
  # Format all colors.
  #

  clear = format(clear)
  colors = format(colors)
end