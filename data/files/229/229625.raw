export load_parameters
export parse_commandline

using ArgParse

function load_parameters(s::IO)
  params = Dict{Symbol,Any}()
  for line in readlines(s)
    line = strip(line)
    if ismatch(r"^(#|$)",line)
      continue
    end
    m = match(r"
    ^((?>[a-zA-Z_][0-9a-zA-Z_!]*))
    \s*=\s*
    (.*)
    "x,line)
    if m != nothing
      line |> parse |> eval
      key = symbol(m.captures[1])
      params[key] = eval(key)
    else
      error("パラメータファイル構文エラー: "*
            "'<識別子> = <式>' という形である必要があります"*
            "(特に、'=' が必要です)")
    end
  end
  return params
end
load_parameters(filename::String) = open(load_parameters,filename,"r")

function parse_commandline()
  settings = ArgParseSettings()
  settings.add_help = false
  @add_arg_table settings begin
    "--num", "-n"
      help = "ウォーカー数 NUM (>0) を指定します。"
      arg_type = Int
      default = 1024
      range_tester = n-> n>0
    "--steps", "-s"
      help = "実行ステップ数 STEPS (>0) を指定します。"
      arg_type = Int
      default = 1024
      range_tester = t-> t>0
    "--dim", "-d"
      help = "空間次元 DIM (0<DIM<4) を指定します。"
      arg_type = Int
      default = 1
      range_tester = d -> 0 < d < 4
    "--continuous", "-c"
      help = "連続空間上のランダムウォークを行います。" *
             "各ステップの差分は半径1 のd次元球面から一様ランダムに選ばれます。"
      action = :store_true
    "--output", "-o"
      help = "出力ファイル名を指定します。" *
             "空の場合、標準出力を使用します。"
      arg_type = String
      default = ""
    "--help", "-h"
      help = "このヘルプメッセージを表示して、終了します。"
      action = :show_help
  end
  return parse_args(settings)
end

