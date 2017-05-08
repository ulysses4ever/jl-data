# These are used to link to the LGPL 2.1 licensed MariaDB Connector/C library
# They are derived from:
# https://mariadb.com/kb/en/mariadb/mariadb-connector-c
# The Julia wrapper types are:
# Copyright (c) 2015 Dynactionize NV

export DB, DB_ROW, DB_ROW_OFFSET, DB_FIELD_OFFSET, DB_FIELD, DB_CHARSET_INFO, DB_TIME, DB_RES
export DB_FIELD_TYPE, OPTION, PROTOCOL_TYPE, STATUS, SET_OPTION, SHUTDOWN_LEVEL
import Base: show

type DB
    ptr::Ptr{Void}
    DB(p) = (val = new(p) ; finalizer(val, close) ; val)
end

type DB_RES
    ptr::Ptr{Void}
    DB_RES(p) = (val = new(p) ; finalizer(val, free_result) ; val)
end

immutable DB_ROW_OFFSET
    ptr::Ptr{Void}
end

immutable DB_FIELD_OFFSET
    off::UInt32
end

@enum(DB_FIELD_TYPE,
    FT_DECIMAL,
    FT_TINY,
    FT_SHORT,
    FT_LONG,
    FT_FLOAT,
    FT_DOUBLE,
    FT_NULL,
    FT_TIMESTAMP,
    FT_LONGLONG,
    FT_INT24,
    FT_DATE,
    FT_TIME,
    FT_DATETIME,
    FT_YEAR,
    FT_NOWDATE,
    FT_VARCHAR,
    FT_BIT,
    FT_TIMESTAMP2,
    FT_DATETIME2,
    FT_TIME2,

    FT_NEWDECIMAL = 246,
    FT_ENUM,
    FT_SET,
    FT_TINY_BLOB,
    FT_MEDIUM_BLOB,
    FT_LONG_BLOB,
    FT_BLOB,
    FT_VAR_STRING,
    FT_STRING,
    FT_GEOMETRY)

immutable JT_ERROR ; end
    
for typ in (:DECIMAL, :TIMESTAMP, :DATE, :TIME, :DATETIME, :YEAR)
    nam = symbol("JT_", typ)
    @eval immutable $nam ; val::ByteString ; end
    @eval $(nam)(val::Vector{UInt8}) = $(nam)(bytestring(val))
    @eval show(io::IO, val::$nam) = show(io, val.val)
    @eval dbparse(::Type{$nam}, val::Vector{UInt8}) = $nam(bytestring(val))
end

for typ in (:VARCHAR, :CHAR, :BIT, :ENUM, :SET, :GEOMETRY)
    nam = symbol("JT_", typ)
    @eval immutable $nam ; val::ByteString ; end
    @eval show(io::IO, val::$nam) = show(io, val.val)
    @eval dbparse(::Type{$nam}, val::Vector{UInt8}) = $nam(bytestring(val))
end

for typ in (:TINY_TEXT, :MEDIUM_TEXT, :LONG_TEXT, :TEXT)
    nam = symbol("JT_", typ)
    # Shouldn't this be ByteString?
    @eval immutable $nam ; val::Vector{UInt8} ; end
    @eval show(io::IO, val::$nam) = show(io, bytestring(val.val))
    @eval dbparse(::Type{$nam}, val::Vector{UInt8}) = $nam(bytestring(val))
end
    
for typ in (:TINY_BLOB, :MEDIUM_BLOB, :LONG_BLOB, :VARBINARY, :BINARY, :BLOB)
    nam = symbol("JT_", typ)
    @eval type $nam ; val::Vector{UInt8} ; end
    @eval show(io::IO, val::$nam) = show(io, val.val)
    @eval dbparse(::Type{$nam}, val::Vector{UInt8}) = $nam(val)
end

export JT_TEXT_TYPES, JT_BINARY_TYPES
const JT_TEXT_TYPES = (JT_DECIMAL, JT_TIMESTAMP, JT_DATE, JT_TIME, JT_DATETIME, JT_YEAR,
                       JT_VARCHAR, JT_CHAR, JT_BIT, JT_ENUM, JT_SET, JT_GEOMETRY,
                       JT_TINY_TEXT, JT_MEDIUM_TEXT, JT_LONG_TEXT, JT_TEXT)
const JT_BINARY_TYPES = (JT_TINY_BLOB, JT_MEDIUM_BLOB, JT_LONG_BLOB,
                         JT_VARBINARY, JT_BINARY, JT_BLOB)
const JT_TYPES = Union{JT_TIMESTAMP, JT_VARCHAR, JT_CHAR, JT_BIT, JT_ENUM, JT_SET, JT_GEOMETRY,
                       JT_TINY_TEXT, JT_MEDIUM_TEXT, JT_LONG_TEXT, JT_TEXT,
		       JT_TINY_BLOB, JT_MEDIUM_BLOB, JT_LONG_BLOB,
		       JT_VARBINARY, JT_BINARY, JT_BLOB}

dbparse{T<:Number}(::Type{T}, val) = parse(T, bytestring(val))

"""Get small index, 1..maxindex, for MYSQL types"""
const offindex = -UInt(FT_NEWDECIMAL)+UInt(FT_TIME2)+2
const maxindex = UInt(FT_GEOMETRY)+offindex

function _typeindex(val::UInt32)
    val <= UInt32(FT_TIME2) && return val+1
    UInt32(FT_NEWDECIMAL) <= val <= UInt32(FT_GEOMETRY) && return val+offindex
    UInt32(0) # Invalid number
end

_typeindex(ft::DB_FIELD_TYPE) = _typeindex(UInt32(ft))

const typearray =
#                  Signed        Signed       Unsigned      Unsigned
#     Name         Text          Binary       Text          Binary
    [("DECIMAL",   JT_DECIMAL,   JT_ERROR,    JT_DECIMAL,   JT_ERROR),
     ("TINY",      Int8,         Int8,        UInt8,        UInt8),
     ("SHORT",     Int16,        Int16,       UInt16,       UInt8),
     ("LONG",      Int32,        Int32,       UInt32,       UInt32),
     ("FLOAT",     Float32,      Float32,     Float32,      Float32),
     ("DOUBLE",    Float64,      Float64,     Float64,      Float64),
     ("NULL",      Void,         Void,        Void,         Void),
     ("TIMESTAMP", JT_ERROR,     JT_ERROR,    JT_ERROR,     JT_TIMESTAMP),
     ("LONGLONG",  UInt64,       UInt64,      UInt64,       UInt64),
     ("INT24",     Int32,        Int32,       UInt32,       UInt32),
     ("DATE",      JT_DATE,      JT_ERROR,    JT_DATE,      JT_ERROR),
     ("TIME",      JT_TIME,      JT_ERROR,    JT_TIME,      JT_ERROR),
     ("DATETIME",  JT_DATETIME,  JT_ERROR,    JT_DATETIME,  JT_ERROR),
     ("YEAR",      JT_ERROR,	 JT_ERROR,    JT_YEAR,      JT_ERROR),
     ("NOWDATE",   JT_ERROR,     JT_ERROR,    JT_ERROR,     JT_DATETIME),
     ("VARCHAR",   JT_VARCHAR,   JT_VARBINARY,JT_VARCHAR,   JT_VARBINARY),
     ("BIT",       JT_BIT,       JT_ERROR,    JT_BIT,       JT_ERROR),
     ("TIMESTAMP2",JT_ERROR,     JT_ERROR,    JT_ERROR,     JT_TIMESTAMP),
     ("DATETIME2", JT_DATETIME,  JT_ERROR,    JT_DATETIME,  JT_ERROR),
     ("TIME2",     JT_TIME,      JT_ERROR,    JT_TIME,      JT_ERROR),
     ("NEWDECIMAL",JT_DECIMAL,   JT_ERROR,    JT_DECIMAL,   JT_ERROR),
     ("ENUM",      JT_ENUM,      JT_ERROR,    JT_ENUM,      JT_ERROR),
     ("SET",       JT_SET,       JT_ERROR,    JT_SET,       JT_ERROR),
     ("TINY_BLOB", JT_TINY_TEXT, JT_TINY_BLOB,JT_TINY_TEXT, JT_TINY_BLOB),
     ("MEDIUM_BLOB",JT_MEDIUM_TEXT,JT_MEDIUM_BLOB,JT_MEDIUM_TEXT,JT_MEDIUM_BLOB),
     ("LONG_BLOB", JT_LONG_TEXT, JT_LONG_BLOB,JT_LONG_TEXT, JT_LONG_BLOB),
     ("BLOB",      JT_TEXT,      JT_BLOB,     JT_TEXT,      JT_BLOB),
     ("VAR_STRING",JT_VARCHAR,   JT_VARBINARY,JT_VARCHAR,   JT_VARBINARY),
     ("STRING",    JT_CHAR,      JT_BINARY,   JT_CHAR,      JT_BINARY),
     ("GEOMETRY",  JT_GEOMETRY,  JT_ERROR,    JT_GEOMETRY,  JT_ERROR)]

const textarray =
    ["DECIMAL",
     "TINY",
     "SHORT",
     "LONG",
     "FLOAT",
     "DOUBLE",
     "NULL",
     "TIMESTAMP",
     "LONGLONG",
     "INT24",
     "DATE",
     "TIME",
     "DATETIME",
     "YEAR",
     "NOWDATE",
     "VARCHAR",
     "BIT",
     "TIMESTAMP2",
     "DATETIME2",
     "TIME2",
     "NEWDECIMAL",
     "ENUM",
     "SET",
     "TINY_TEXT",
     "MEDIUM_TEXT",
     "LONG_TEXT",
     "TEXT",
     "VARCHAR",
     "CHAR",
     "GEOMETRY"]

const CHAR_SET_BINARY    = 63

const TIMESTAMP_NONE     = -2
const TIMESTAMP_ERROR    = -1
const TIMESTAMP_DATE     =  0
const TIMESTAMP_DATETIME =  1
const TIMESTAMP_TIME     =  2

@enum(OPTION,
    CONNECT_TIMEOUT,
    OPT_COMPRESS,
    OPT_NAMED_PIPE,
    INIT_COMMAND,
    READ_DEFAULT_FILE,
    READ_DEFAULT_GROUP,
    SET_CHARSET_DIR,
    SET_CHARSET_NAME,
    OPT_LOCAL_INFILE,
    OPT_PROTOCOL,
    SHARED_MEMORY_BASE_NAME,
    OPT_READ_TIMEOUT,
    OPT_WRITE_TIMEOUT,
    OPT_USE_RESULT,
    OPT_USE_REMOTE_CONNECTION,
    OPT_USE_EMBEDDED_CONNECTION,
    OPT_GUESS_CONNECTION,
    SET_CLIENT_IP,
    SECURE_AUTH,
    REPORT_DATA_TRUNCATION,
    OPT_RECONNECT,
    OPT_SSL_VERIFY_SERVER_CERT,
    PLUGIN_DIR,
    DEFAULT_AUTH,
    ENABLE_CLEARTEXT_PLUGIN,
    PROGRESS_CALLBACK       = 5999,
    OPT_NONBLOCK            = 6000)

@enum(PROTOCOL_TYPE, DEFAULT, TCP, SOCKET, PIPE, MEMORY)

@enum(STATUS, READY, GET_RESULT, USE_RESULT, STATEMENT_GET_RESULT)

@enum(SET_OPTION, MULTI_STATEMENT_ON, OPTION_MULTI_STATEMENT_OFF)

const NO_MORE_RESULTS               = -1

const SHUTDOWN_KILLABLE_CONNECT     = 0x01
const SHUTDOWN_KILLABLE_TRANS       = 0x02
const SHUTDOWN_KILLABLE_LOCK_TABLE  = 0x04
const SHUTDOWN_KILLABLE_UPDATE      = 0x08

@enum(SHUTDOWN_LEVEL,
    WAIT_DEFAULT          = 0,
    WAIT_CONNECTIONS      = SHUTDOWN_KILLABLE_CONNECT,
    WAIT_TRANSACTIONS     = SHUTDOWN_KILLABLE_TRANS,
    WAIT_UPDATES          = SHUTDOWN_KILLABLE_UPDATE,
    WAIT_ALL_BUFFERS      = SHUTDOWN_KILLABLE_UPDATE<<1,
    WAIT_CRITICAL_BUFFERS = (SHUTDOWN_KILLABLE_UPDATE<<1)+1)

const NOT_NULL_FLAG                 = 0x00000001
const PRI_KEY_FLAG                  = 0x00000002
const UNIQUE_KEY_FLAG               = 0x00000004
const MULTIPLE_KEY_FLAG             = 0x00000008
const BLOB_FLAG                     = 0x00000010
const UNSIGNED_FLAG                 = 0x00000020
const ZEROFILL_FLAG                 = 0x00000040
const BINARY_FLAG                   = 0x00000080
const ENUM_FLAG                     = 0x00000100
const AUTO_INCREMENT_FLAG           = 0x00000200
const TIMESTAMP_FLAG                = 0x00000400
const SET_FLAG                      = 0x00000800
const NO_DEFAULT_VALUE_FLAG         = 0x00001000
const ON_UPDATE_NOW_FLAG            = 0x00002000
const NUM_FLAG                      = 0x00004000
const UNIQUE_FLAG                   = 0x00008000
const BINCP_FLAG                    = 0x00010000
const GET_FIXED_FIELDS_FLAG         = 0x00020000
const FIELD_IN_PART_FUNC_FLAG       = 0x00040000

const CLIENT_LONG_PASSWORD          = 0x00000001
const CLIENT_FOUND_ROWS             = 0x00000002
const CLIENT_LONG_FLAG              = 0x00000004
const CLIENT_CONNECT_WITH_DB        = 0x00000008
const CLIENT_NO_SCHEMA              = 0x00000010
const CLIENT_COMPRESS               = 0x00000020
const CLIENT_ODBC                   = 0x00000040
const CLIENT_LOCAL_FILES            = 0x00000080
const CLIENT_IGNORE_SPACE           = 0x00000100
const CLIENT_PROTOCOL_41            = 0x00000200
const CLIENT_INTERACTIVE            = 0x00000400
const CLIENT_SSL                    = 0x00000800
const CLIENT_IGNORE_SIGPIPE         = 0x00001000
const CLIENT_TRANSACTIONS           = 0x00002000
const CLIENT_RESERVED               = 0x00004000
const CLIENT_SECURE_CONNECTION      = 0x00008000
const CLIENT_MULTI_STATEMENTS       = 0x00010000
const CLIENT_MULTI_RESULTS          = 0x00020000
const CLIENT_PS_MULTI_RESULTS       = 0x00040000
const CLIENT_PLUGIN_AUTH            = 0x00080000
const CLIENT_PROGRESS               = 0x20000000
const CLIENT_SSL_VERIFY_SERVER_CERT = 0x40000000

const REFRESH_GRANT                 = 0x00000001
const REFRESH_LOG                   = 0x00000002
const REFRESH_TABLES                = 0x00000004
const REFRESH_HOSTS                 = 0x00000008
const REFRESH_STATUS                = 0x00000010
const REFRESH_THREADS               = 0x00000020
const REFRESH_SLAVE                 = 0x00000040
const REFRESH_MASTER                = 0x00000080
const REFRESH_ERROR_LOG             = 0x00000100
const REFRESH_ENGINE_LOG            = 0x00000200
const REFRESH_BINARY_LOG            = 0x00000400
const REFRESH_RELAY_LOG             = 0x00000800
const REFRESH_GENERAL_LOG           = 0x00001000
const REFRESH_SLOW_LOG              = 0x00002000
const REFRESH_READ_LOCK             = 0x00004000
const REFRESH_CHECKPOINT            = 0x00008000
const REFRESH_QUERY_CACHE           = 0x00010000
const REFRESH_QUERY_CACHE_FREE      = 0x00020000
const REFRESH_DES_KEY_FILE          = 0x00040000
const REFRESH_USER_RESOURCES        = 0x00080000
const REFRESH_TABLE_STATS           = 0x00100000
const REFRESH_INDEX_STATS           = 0x00200000
const REFRESH_USER_STATS            = 0x00400000
const REFRESH_FAST                  = 0x80000000

macro c_str_2_str(c_str)
    return :($c_str == C_NULL ? "" : bytestring($c_str))
end

macro str_2_c_str(str)
    return :($str == "" ? Base.convert(Ptr{UInt8}, C_NULL) : pointer($str))
end

type _DB_FIELD_
    name::Ptr{UInt8}
    org_name::Ptr{UInt8}
    table::Ptr{UInt8}
    org_table::Ptr{UInt8}
    db::Ptr{UInt8}
    catalog::Ptr{UInt8}
    def::Ptr{UInt8}
    @windows_only length::UInt32
    @windows_only max_length::UInt32
    @unix_only length::UInt
    @unix_only max_length::UInt
    name_length::UInt32
    org_name_length::UInt32
    table_length::UInt32
    org_table_length::UInt32
    db_length::UInt32
    catalog_length::UInt32
    def_length::UInt32
    flags::UInt32
    decimals::UInt32
    charsetnr::UInt32
    field_type::UInt32
    extension::Ptr{Void}
end
_DB_FIELD_() = _DB_FIELD_(C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL, C_NULL,
                          0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, C_NULL)

type DB_FIELD
    name::UTF8String
    org_name::UTF8String
    table::UTF8String
    org_table::UTF8String
    db::UTF8String
    catalog::UTF8String
    def::UTF8String
    length::UInt
    max_length::UInt
    flags::UInt32
    decimals::UInt32
    charsetnr::UInt32
    field_type::DB_FIELD_TYPE
    julia_type::DataType
    type_index::UInt8
end

map_sql_type(typ, csn, fla) =
    typearray[typ][(csn == CHAR_SET_BINARY ? 3 : 2) + ((fla & UNSIGNED_FLAG != 0) ? 2 : 0)]

function db_type_name(field::DB_FIELD)
    typ = typearray[field.type_index]
    if typ[2] != typ[4] && (field.flags & UNSIGNED_FLAG) != 0
        string(typ[1]," UNSIGNED")
    elseif field.charsetnr == CHAR_SET_BINARY
        typ[1]
    else
        textarray[field.type_index]
    end
end

DB_FIELD() = DB_FIELD("", "", "", "", "", 0, 0, 0, 0, 0, Void)
function DB_FIELD(c_db_field::_DB_FIELD_)
    index = _typeindex(c_db_field.field_type)
    DB_FIELD(@c_str_2_str(c_db_field.name),
             @c_str_2_str(c_db_field.org_name),
             @c_str_2_str(c_db_field.table),
             @c_str_2_str(c_db_field.org_table),
             @c_str_2_str(c_db_field.db),
             @c_str_2_str(c_db_field.catalog),
             @c_str_2_str(c_db_field.def),
             c_db_field.length,
             c_db_field.max_length,
             c_db_field.flags,
             c_db_field.decimals,
             c_db_field.charsetnr,
             DB_FIELD_TYPE(c_db_field.field_type),
    	     map_sql_type(index, c_db_field.charsetnr, c_db_field.flags),
    	     index)   
end

type _DB_CHARSET_INFO_
    number::UInt32
    state::UInt32
    csname::Ptr{UInt8}
    name::Ptr{UInt8}
    comment::Ptr{UInt8}
    dir::Ptr{UInt8}
    mbminlen::UInt32
    mbmaxlen::UInt32
end
_DB_CHARSET_INFO_() = _DB_CHARSET_INFO_(0, 0, C_NULL, C_NULL, C_NULL, C_NULL, 0, 0)

type DB_CHARSET_INFO
    number::UInt
    state::UInt
    csname::UTF8String
    name::UTF8String
    comment::UTF8String
    dir::UTF8String
    mbminlen::UInt
    mbmaxlen::UInt
end

DB_CHARSET_INFO() = DB_CHARSET_INFO(0, 0, "", "", "", "", 0, 0)
function DB_CHARSET_INFO(c_charset_info::_DB_CHARSET_INFO_)
    DB_CHARSET_INFO(
        c_charset_info.number,
        c_charset_info.state,
        @c_str_2_str(c_charset_info.csname),
        @c_str_2_str(c_charset_info.name),
        @c_str_2_str(c_charset_info.comment),
        @c_str_2_str(c_charset_info.dir),
        c_charset_info.mbminlen,
        c_charset_info.mbmaxlen
    )
end

type DB_TIME
    year::UInt32
    month::UInt32
    day::UInt32
    hour::UInt32
    minute::UInt32
    second::UInt32
    @windows_only second_part::UInt32
    @unix_only second_part::UInt
    neg::Int8
    time_type::Int8
end
