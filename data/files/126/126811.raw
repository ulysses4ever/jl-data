module Parser

import JSON

export parseLine

true4x1 = ["1","1","1","1"]

keys = ["_id",
        "n_cn","n_ch","n_lc","n_mt",
        "r_cn","r_ch","r_lc","r_mt",
        "c_cn","c_ch","c_lc","c_mt",
        "t_le"]

function parseLine(line, resolve, reject)
    try
        @assert line[53:56] == true4x1
        resolve(JSON.json( Dict( zip(keys, [line[1]; line[57:69]]))))
    catch e
        reject(line)
    end
end

function wsMessage(header, msg)
    "{'header': '$header', 'msg': '$msg'}"
end

end
