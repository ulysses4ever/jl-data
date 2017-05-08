# ViewDBI

module ViewDBI

import Base: show, contains, hash
import Base.Meta.isexpr
import ODBC
import DataFrames

export ViewODBC, View, has_one, has_many, many_to_many, contains, resolve

abstract ViewDB

type ViewODBC <: ViewDB
    db::ODBC.Connection
    schema::Symbol
end

show(io::IO, kodbc::ViewODBC) = print(io, "ViewODBC(",kodbc.schema,")")

ViewODBC(dsn::String) = (ODBC.connect(dsn); ViewODBC(ODBC.conn, symbol(ODBC.conn.dsn)))
disconnect(vdb::ViewODBC) = ODBC.disconnect(vdb.db)

function table_info(vdb::ViewODBC, table)
    colnames = ODBC.query("""select COLUMN_NAME,COLUMN_TYPE,IS_NULLABLE,COLUMN_DEFAULT
                             from INFORMATION_SCHEMA.COLUMNS ISC 
                            where TABLE_SCHEMA=\"$(vdb.schema)\" and TABLE_NAME=\"$table\"
                         """, vdb.db)

    colnames[1] = [symbol(x)::Symbol for x in colnames[1]]

    keyinfo = ODBC.query("""select TABLE_SCHEMA,TABLE_NAME,CONSTRAINT_NAME,COLUMN_NAME,REFERENCED_TABLE_SCHEMA,REFERENCED_TABLE_NAME,REFERENCED_COLUMN_NAME
                            from INFORMATION_SCHEMA.KEY_COLUMN_USAGE ISC
                            where (TABLE_SCHEMA=\"$(vdb.schema)\" and TABLE_NAME=\"$table\")
                         """, vdb.db)

    for i = 1:DataFrames.ncol(keyinfo)
        keyinfo[i] = [symbol(x)::Symbol for x in keyinfo[i]]
    end

    return (colnames, keyinfo)
    # rkeyinfo = ODBC.query("""select TABLE_SCHEMA,TABLE_NAME,CONSTRAINT_NAME,COLUMN_NAME,REFERENCED_TABLE_SCHEMA,REFERENCED_TABLE_NAME,REFERENCED_COLUMN_NAME
    #                          from INFORMATION_SCHEMA.KEY_COLUMN_USAGE ISC
    #                          where (REFERENCED_TABLE_SCHEMA=\"$(vdb.schema)\" and REFERENCED_TABLE_NAME=\"$table\")
    #                       """, vdb.db)
    # return(colnames, keyinfo, rkeyinfo)
    
end

typealias Key Union(Symbol, Vector{Symbol})
contains(s::Vector{Symbol}, k::Vector{Symbol}) = issubset(k, s)

abstract DbView

type TableView <: DbView
    name::Symbol
    database::ViewDB
    schema::Symbol
    table::Symbol
    fields::Vector{Symbol}
    pk::Key
    prepare_fn#::Function
    transform_fn#::Function
    has_one::Dict{TableView,(Key,Key)}
    has_many::Dict{TableView,(Key,Key)}
    belongs_to::Dict{TableView,(Key,Key)}
    many_to_many::Dict{TableView,(TableView,Key,Key,Key,Key)}

    cols
    keyinfo
    #rkeyinfo
end

const VIEW_HASH=hash(TableView)

hash(en::TableView) = bitmix(VIEW_HASH, hash(en.name))

typealias ViewRelation Dict{TableView,(Key,Key)}

function TableView(name::Symbol, vdb::ViewDB; schema=vdb.schema, table=name, fields=Symbol[], args...)
    table = symbol(table)

    # TODO: handle case where db doesn't yet exist in vdb

    cols, keyinfo = table_info(vdb, table)

    if isempty(fields)
        fields = [symbol(x)::Symbol for x in cols["COLUMN_NAME"]]
    end

    pk = [symbol(x)::Symbol for x in keyinfo[keyinfo["CONSTRAINT_NAME"] .== :PRIMARY, "COLUMN_NAME"]]

    TableView(name, vdb, schema, table, fields, pk, 
           nothing, nothing, 
           (TableView=>(Key,Key))[], 
           (TableView=>(Key,Key))[], 
           (TableView=>(Key,Key))[], 
           (TableView=>(TableView,Key,Key,Key,Key))[],
           cols, keyinfo)
end

function show(io::IO, v::TableView)
    print(io, "TableView(")
    print(io, v.name)
    print(io, ", ", v.database)
    print(io, ", ", v.table)
    print(io, ", ", "fields=", v.fields)
    print(io, ", ", "pk=", v.pk) 
    print(io, ", ", "prepare_fn=", v.prepare_fn == nothing ? "nothing" : v.prepare_fn.env.name)
    print(io, ", ", "transform_fn=", v.transform_fn == nothing ? "nothing" : v.transform_fn.env.name)
    print(io, ", ", "has_one=",{x.name for x in keys(v.has_one)})
    print(io, ", ", "has_many=",{x.name for x in keys(v.has_many)})
    print(io, ", ", "belongs_to=",{x.name for x in keys(v.belongs_to)})
    print(io, ", ", "many_to_many=",{x.name for x in keys(v.many_to_many)}, ")")
end

function get_joinkey(main::TableView, other::TableView, mainkey::Key=main.pk)
    if contains(other.fields, mainkey);  return mainkey;  end
    for testkey in [join([main.table, :id], ""), join([main.table, :id], "_")]
        if contains(other.fields, testkey)
            return testkey
        end
    end
    error("get_joinkey: no key found to join Entities")
end

function linkup(main::TableView, relmain::ViewRelation, 
                sub::TableView, relsub::ViewRelation; 
                mainkey=main.pk, kwargs...)
    k = find(x->x[1] == :key, kwargs)
    key = isempty(k) ? get_joinkey(main, sub, mainkey) : kwargs[k[1]][2]

    @assert(contains(main.fields, mainkey))
    @assert(contains(sub.fields, key))
    @assert(typeof(mainkey) == typeof(key))
    @assert(!isa(mainkey, Vector) || length(mainkey) == length(key))

    relmain[sub] = (mainkey, key)
    relsub[main] = (key, mainkey)

    nothing
end

has_one(main::TableView, sub::TableView; mainkey=main.pk, kwargs...) = 
    linkup(main, main.has_one, sub, sub.belongs_to; mainkey=mainkey, kwargs...)

has_many(main::TableView, sub::TableView; mainkey=main.pk, kwargs...) = 
    linkup(main, main.has_many, sub, sub.belongs_to; mainkey=mainkey, kwargs...)

function many_to_many(ent1::TableView, ent2::TableView, joinent::TableView; entkey1=ent1.pk, entkey2=ent2.pk, kwargs...)
    k = find(x->x[1] == :joinkey1, kwargs)
    joinkey1 = isempty(k) ? get_joinkey(ent1, joinent, entkey1) : kwargs[k[1]][2]
    k = find(x->x[1] == :joinkey2, kwargs)
    joinkey2 = isempty(k) ? get_joinkey(ent2, joinent, entkey2) : kwargs[k[1]][2]

    @assert(contains(ent1.fields, entkey1))
    @assert(contains(ent2.fields, entkey2))
    @assert(contains(joinent.fields, joinkey1))
    @assert(contains(joinent.fields, joinkey2))
    @assert(!isa(entkey1, Vector) || length(entkey1) == length(joinkey1))
    @assert(!isa(entkey2, Vector) || length(entkey2) == length(joinkey2))

    ent1.many_to_many[entkey1] = (joinent, joinkey1, joinkey2, ent2, entkey2)
    ent2.many_to_many[entkey2] = (joinent, joinkey2, joinkey1, ent1, entkey1)

    nothing
end

function resolve(ent1::TableView, ent2::TableView)
    ref1 = ent1.keyinfo[((ent1.keyinfo["REFERENCED_TABLE_SCHEMA"] .== ent2.schema) &
                         (ent1.keyinfo["REFERENCED_TABLE_NAME"] .== ent2.table)),:]

    for r in DataFrames.EachRow(ref1)
        ent1.belongs_to[ent2] = (r[1,"COLUMN_NAME"], r[1,"REFERENCED_COLUMN_NAME"])
        ent2.has_many[ent1] = (r[1,"REFERENCED_COLUMN_NAME"], r[1,"COLUMN_NAME"])
    end

    ref2 = ent2.keyinfo[((ent2.keyinfo["REFERENCED_TABLE_SCHEMA"] .== ent1.schema) &
                         (ent2.keyinfo["REFERENCED_TABLE_NAME"] .== ent1.table)),:]

    for r in DataFrames.EachRow(ref2)
        ent2.belongs_to[ent1] = (r[1,"COLUMN_NAME"], r[1,"REFERENCED_COLUMN_NAME"])
        ent1.has_many[ent2] = (r[1,"REFERENCED_COLUMN_NAME"], r[1,"COLUMN_NAME"])
    end

    nothing
end

end

