const default_server = "ceres.cepremap.org"

function list_categories(db; server = default_server)
    r = get("http://$(default_server)/$(db)/categories")
    JSON.parse(r.data)
end

function get_category(db, category_id; server = default_server)
    r = get("http://$(default_server)/$(db)/categories/$(category_id)")
    j = JSON.parse(r.data)
    j[1]
end

function list_series(db, category_id; server = default_server)
    r = get("http://$(default_server)/$(db)/categories/$(category_id)/series")
    JSON.parse(r.data)
end

function get_series(db, series_id, ::Type{Array}; server = default_server)
    r = get("http://$(default_server)/$(db)/series/$(series_id)")
    j = JSON.parse(r.data)
    j[1]
end
