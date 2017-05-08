export HTTPRequest,
    HTTPResponse,
    HTTP_1_1

function preparehttpresponseheaders(r::Response)
    h_chunk, h_chunk_value = r.protocol.header_msg_chunk

    if chunked(r)
        if haskey(r.headers, r.protocol.header_msg_size)
            throw(ResponseException("invalid_header",
                str("The '", r.protocol.header_msg_size,
                    "' header doesn't valid on chunked data.");
                header=r.protocol.header_msg_size)
            )
        end
    end

    if r.status in r.protocol.status_wo_msg
        h = chunked(r) ? h_chunk : r.protocol.header_msg_size
        if haskey(r.headers, h)
            throw(ResponseException("status_not_accept_msg_body",
                str("The Response status ", r.status,
                    "' doesn't accept response body.");
                header=h, status=r.status))
        end
    end
end

const HTTP_1_1 = Protocol(
    "HTTP",
    "1.1",
    STATUS_CODES,
    sort(filter(x -> (x > 90 && x < 200) || x in (204, 304),
        [_ for _ in keys(STATUS_CODES)]
    )),
    String[],
    preparehttpresponseheaders,
    DefaultStatus(200, 400, 404, 500),
    ("Transfer-Encoding", "chunked"),
    "Content-Type",
    "Content-Length",
    (req) -> N,
    (res) -> N
)

protocol!(HTTP_1_1)
protocol!(("HTTP", "1.0"), HTTP_1_1)

HTTPRequest(io::AbstractIOSocket) = Request(io, HTTP_1_1)
HTTPResponse(io::AbstractIOSocket) = Response(io, HTTP_1_1)
