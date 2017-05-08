using JSON

function formatSolveBioResponse(res, raw=false)
    body = res.data
    if raw
        return body
    else
        res = JSON.parse(body)
        return res
    end
end
