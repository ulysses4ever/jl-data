# These functions link to the LGPL 2.1 licensed MariaDB Connector/C library
# The documentation of the functions is derived from:
# https://mariadb.com/kb/en/mariadb/mariadb-connector-c
# The Julia wrapper functions are:
# Copyright (c) 2015 Dynactionize NV

"""
# Description

Returns the number of affected rows by the last operation associated with db, if the operation
was an "upsert" (INSERT, UPDATE, DELETE or REPLACE) statement, or -1 if the last query failed.

When using UPDATE, MariaDB will not update columns where the new value is the same as the old value.
This creates the possibility that affected_rows may not actually equal the number of rows
matched, only the number of rows that were literally affected by the query.
The REPLACE statement first deletes the record with the same primary key and then inserts the new
record. This function returns the number of deleted records in addition to the number of inserted
records.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
affected_rows(db::DB) =
    ccall( (:mysql_affected_rows, mariadb_lib), Culonglong, (Ptr{Void}, ), db.ptr)

"""
# Description

Toggles autocommit mode on or off for the current database connection. Autocommit mode will be set
if auto_mode=true or unset if auto_mode=false. Returns DB_OK on success, or nonzero if an error
occurred.

**Autocommit** mode only affects operations on transactional table types. To determine the current
state of autocommit mode use the SQL command SELECT @@autocommit. Be aware: the *rollback()*
function will not work if autocommit mode is switched on.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **auto_mode** whether to turn autocommit on or not.
"""
autocommit(db::DB, auto_mode::Bool) =
    ccall( (:mysql_autocommit, mariadb_lib), Cchar, (Ptr{Void}, Cchar),
           db.ptr, Int8(auto_mode)) != 0

"""
# Description

Changes the user and default database of the current connection.

In order to successfully change users a valid username and password parameters must be provided and
that user must have sufficient permissions to access the desired database. If for any reason
authorization fails, the current user authentication will remain.

Returns DB_OK on success, nonzero if an error occured.

**change_user** will always cause the current database connection to behave as if was a
completely new database connection, regardless of if the operation was completed successfully. This
reset includes performing a rollback on any active transactions, closing all temporary tables, and
unlocking all locked tables.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **user** the user name for server authentication
- **passwd** the password for server authentication
- **db** the default database. If desired, the empty string "" may be passed resulting in only
  changing the user and not selecting a database. To select a database in this case use the
  *select_db()* function.
"""
change_user(db::DB, user::AbstractString, passwd::AbstractString, dbname::AbstractString = "") =
    ccall((:mysql_change_user, mariadb_lib), Cchar, (Ptr{Void}, Cstring, Cstring, Cstring),
          db.ptr, user, passwd, (dbname == "" ? C_NULL : dbname))

"""
# Description

Returns the default client character set for the specified connection.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
character_set_name(db::DB) = bytestring(
    ccall( (:mysql_character_set_name, mariadb_lib), Cstring, (Ptr{Void},), db.ptr))

"""
# Description

Closes a previously opened connection.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
function close(db::DB)
    db.ptr == C_NULL && return
    ccall( (:mysql_close, mariadb_lib), Void, (Ptr{Void},), db.ptr)
    db.ptr = C_NULL
end

"""
# Description

Commits the current transaction for the specified database connection. Returns DB_OK on success,
nonzero if an error occurred.

Executing **commit()** will not affected the behaviour of *autocommit*. This means, any update
or insert statements following commit() will be rolled back when the connection gets closed.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
commit(db::DB) = ccall( (:mysql_commit, mariadb_lib), Cchar, (Ptr{Void},), db.ptr)

"""
# Description

The **data_seek()** function seeks to an arbitrary function result pointer specified by the
offset in the result set.

This function can only be used with buffered result sets obtained from the use of the
*store_result* function.

# Parameters

- **result** a result set identifier returned by *store_result()*.
- **offset** the field offset. Must be between 1 and the total number of rows.
"""
data_seek(result::DB_RES, offset::UInt64) =
    ccall( (:mysql_data_seek, mariadb_lib), Void, (Ptr{Void}, Culonglong), result.ptr, offset-1)

"""
# Description

This function is designed to be executed by an user with the SUPER privilege and is used to dump
server status information into the log for the MariaDB Server relating to the connection.

Returns DB_OK on success, nonzero if an error occurred.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
dump_debug_info(db::DB) =
    ccall( (:mysql_dump_debug_info, mariadb_lib), Cint, (Ptr{Void},), db.ptr)

"""
# Description

Returns the last error code for the most recent function call that can succeed or fail. Zero means
no error occurred.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
errno(db::DB) = ccall( (:mysql_errno, mariadb_lib), Cuint, (Ptr{Void},), db.ptr)

"""
# Description

Returns the last error message for the most recent function call that can succeed or fail. If no
error occurred an empty string is returned.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
last_error(db::DB) =
    bytestring(ccall( (:mysql_error, mariadb_lib), Cstring, (Ptr{Void},), db.ptr))

"""
# Description

Returns the definition of one column of a result set as a DB_FIELD type. Call this function
repeatedly to retrieve information about all columns in the result set.

The field order will be reset if you execute a new SELECT query.
In case only information for a specific field is required the field can be selected by using the
*field_seek()* function or obtained by *fetch_field_direct()* function.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
"""
fetch_field(result::DB_RES) =
    DB_FIELD(unsafe_load(ccall( (:mysql_fetch_field, mariadb_lib), Ptr{_DB_FIELD_},
                                (Ptr{Void},), result.ptr), 1))

"""
# Description

This function serves an identical purpose to the fetch_field() function with the single
difference that instead of returning one field at a time for each field, the fields are returned as
an array. Each field contains the definition for a column of the result set.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
"""
function fetch_fields(result::DB_RES)
    num_fields = ccall( (:mysql_num_fields, mariadb_lib), Cuint, (Ptr{Void},), result.ptr)
    fields = Vector{DB_FIELD}(num_fields)
    ptr = ccall( (:mysql_fetch_fields, mariadb_lib), Ptr{_DB_FIELD_}, (Ptr{Void},), result.ptr)
    for i in 1:num_fields
        fields[i] = DB_FIELD(unsafe_load(ptr,i))
    end
    fields
end

"""
# Description

Returns a pointer to a DB_FIELD structure which contains field information from the specified
result set.

The total number of fields can be obtained by *field_count()* or *num_fields()*.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
- **fieldnr** the field number. This value must be within the range from 1 to number of fields.
"""
fetch_field_direct(result::DB_RES, fieldnr::UInt) =
    DB_FIELD(unsafe_load(ccall( (:mysql_fetch_field_direct, mariadb_lib),
                                   Ptr{_DB_FIELD_}, (Ptr{Void}, Cuint),
                                   result.ptr, fieldnr-1), 1))

"""
# Description

The fetch_lengths() function returns an array containing the lengths of every column of the
current row within the result set (not including terminating zero character) or an empty array if an
error occurred.

**fetch_lengths()** is valid only for the current row of the result set. It returns an empty
array if you call it before calling *fetch_row()* or after retrieving all rows in the result.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
"""
function fetch_lengths(result::DB_RES)
    num_fields = ccall( (:mysql_num_fields, mariadb_lib), Cuint, (Ptr{Void},), result.ptr)
    ptr = ccall( (:mysql_fetch_lengths, mariadb_lib), Ptr{Culong}, (Ptr{Void},), result.ptr)
    ptr == C_NULL ? Culong[] : pointer_to_array(ptr, num_fields)
end

"""
# Description

Fetches one row of data from the result set and returns it as an array of ByteStrings (DB_ROW),
where each column is stored in an offset starting from 1 (one). Each subsequent call to this
function will return the next row within the result set, or an empty array if there are no more
rows.

If a column contains a NULL value the corresponding element will be set to Void().
Memory associated to DB_ROW will be freed when calling free_result() function.

Returns empty vector if no row is available.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
"""

function fetch_row(result::DB_RES)
    row = Vector{Any}()
    ptr = ccall( (:mysql_fetch_row, mariadb_lib), Ptr{Ptr{UInt8}}, (Ptr{Void},), result.ptr)
    ptr == C_NULL &&
        return row
    fields = fetch_fields(result)
    lengths = fetch_lengths(result)
    for i in 1:length(fields)
        # Get Ptr{UInt8}
        colptr = unsafe_load(ptr,i)
        push!(row,
              colptr == C_NULL
              ? Void()
              : dbparse(fields[i].julia_type, pointer_to_array(colptr, lengths[i])))
    end
    return row
end

"""
# Description

Returns the number of columns for the most recent query on the connection represented by the link
parameter as an unsigned integer. This function can be useful when using the *store_result()*
function to determine if the query should have produced a non-empty result set or not without
knowing the nature of the query.

The field_count() function should be used to determine if there is a result set available.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
field_count(db::DB) =
    ccall( (:mysql_field_count, mariadb_lib), Cuint, (Ptr{Void},), db.ptr)

"""
# Description

Sets the field cursor to the given offset. The next call to fetch_field() will retrieve the
field definition of the column associated with that offset.

Returns the previous value of the field cursor.

The number of fields can be obtained from *field_count()*.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
- **offset** the field number. This number must be in the range from 1..number of fields.
"""
field_seek(result::DB_RES, offset::DB_FIELD_OFFSET) =
    ccall( (:mysql_field_seek, mariadb_lib), Cuint, (ptr{Void}, Cuint),
           result.ptr, offset-1) + 1

"""
# Description

Return the offset of the field cursor used for the last *fetch_field()* call. This value can
be used as a parameter for the function *field_seek()*.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
"""
field_tell(result::DB_RES) =
    ccall( (:mysql_field_tell, mariadb_lib), Cuint, (Ptr{Void},), result.ptr) + 1

"""
# Description

Frees the memory associated with a result set.

You should always free your result set with **free_result()** as soon it's not needed anymore.
Row values obtained by a prior *fetch_row()* call will become invalid after calling
*free_result()*.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
"""
function free_result(result::DB_RES)
    result.ptr == C_NULL && return
    ccall( (:mysql_free_result, mariadb_lib), Void, (Ptr{Void},), result.ptr)
    result.ptr = C_NULL
end

"""
# Description

Returns information about the current default character set for the specified connection.

A complete list of supported character sets in the client library is listed in the function
description for *set_character_set_info()*.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
function get_character_set_info(db::DB)
    info = _MY_CHARSET_INFO_[_MY_CHARSET_INFO_()]
    ccall( (:mysql_get_character_set_info, mariadb_lib), Void, (Ptr{Void}, Ref{_MY_CHARSET_INFO_}),
            db.ptr, info)
    return MY_CHARSET_INFO(info[1])
end

"""
# Description

Returns a string representing the client library version.

To obtain the numeric value of the client library version use *get_client_version()*.
"""
get_client_info() =
    bytestring(ccall( (:mysql_get_client_info, mariadb_lib), Ptr{UInt8}, ()))

"""
# Description

Returns a number representing the client library version.

To obtain a string containing the client library version use the *get_client_info()* function.
"""
get_client_version() = ccall( (:mysql_get_client_version, mariadb_lib), Culong, ())

"""
# Description

Describes the type of connection in use for the connection, including the server host name. Returns
a string, or "" if the connection is not valid.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
    """

_wrap_null(ptr::Ptr{UInt8}) = (ptr == C_NULL) ? "" : bytestring(ptr)

get_host_info(db::DB) =
    _wrap_null(ccall( (:mysql_get_host_info, mariadb_lib), Ptr{UInt8}, (Ptr{Void},), db.ptr))

"""
# Description

Returns the protocol version number for the specified connection.

The client library doesn't support protocol version 9 and prior.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
get_proto_info(db::DB) =
    ccall( (:mysql_get_proto_info, mariadb_lib), Cuint, (Ptr{Void},), db.ptr)

"""
# Description

Returns the server version or "" on failure.

To obtain the numeric server version please use get_server_version().

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
get_server_info(db::DB) =
    _wrap_null(ccall( (:mysql_get_server_info, mariadb_lib), Ptr{UInt8}, (Ptr{Void},), db.ptr))

"""
# Description

Returns an integer representing the version of connected server.

The form of the version number is VERSION_MAJOR * 10000 + VERSION_MINOR * 100 + VERSION_PATCH.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
get_server_version(db::DB) =
    ccall( (:mysql_get_server_version, mariadb_lib), Culong, (Ptr{Void},), db.ptr)

"""
# Description

Returns the name of the currently used cipher of the ssl connection, or "" for non ssl connections.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
get_ssl_cipher(db::DB) =
    _wrap_null(ccall( (:mysql_get_ssl_cipher, mariadb_lib), Ptr{UInt8}, (Ptr{Void},), db.ptr))

"""
# Description

This function is used to create a hexadecimal string which can be used in SQL statements. e.g.
`INSERT INTO my_blob VALUES(X'A0E1CD')`.

Returns the hexadecimal encoded string.

# Parameters

- **from** the string which will be encoded
"""
function hex_string(from::AbstractString)
    num_bytes = sizeof(from)
    out = Vector{UInt8}(num_bytes * 2 + 1)
    len = ccall( (:mysql_hex_string, mariadb_lib), Culong, (Ptr{UInt8}, Ptr{UInt8}, Culong),
                  out, from, num_bytes)
    r = range(1, Int64(len))
    return (bytestring(getindex(out,r)), len)
end

"""
# Description

returns a string providing information about the last query executed. The nature of this string is
provided below:

| Query type                             | Example result string                        |
| -------------------------------------- | -------------------------------------------- |
| INSERT INTO ... SELECT ...             | Records: 100 Duplicates: 0 Warnings: 0       |
| INSERT INTO...VALUES (...),(...),(...) | Records: 3 Duplicates: 0 Warnings: 0         |
| LOAD DATA INFILE ...                   | Records: 1 Deleted: 0 Skipped: 0 Warnings: 0 |
| ALTER TABLE ...                        | Records: 3 Duplicates: 0 Warnings: 0         |
| UPDATE ...                             | Rows matched: 40 Changed: 40 Warnings: 0     |

Queries which do not fall into one of the preceding formats are not supported
(e.g. `SELECT ...`). In these situations info() will return an empty string.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
info(db::DB) =
    _wrap_null(ccall( (:mysql_info, mariadb_lib), Ptr{UInt8}, (Ptr{Void},), db.ptr))

"""
# Description

Prepares and initializes a DB structure to be used with real_connect().

If thread_init() was not called before, init() will also initialize the thread subsystem
for the current thread.

Any subsequent calls to any database function (except *options()*) will fail until
*real_connect()* was called.
Memory allocated by **init()** must be freed with *close()*.
"""
init() = DB(ccall( (:mysql_init, mariadb_lib), Ptr{Void}, (Ptr{Void},), C_NULL))

"""
# Descriiption

The **insert_id()** function returns the ID generated by a query on a table with a column
having the AUTO_INCREMENT attribute. If the last query wasn't an INSERT or UPDATE statement or if
the modified table does not have a column with the AUTO_INCREMENT attribute, this function will
return zero.

Performing an INSERT or UPDATE statement using the LAST_INSERT_ID() function will also modify the
value returned by the insert_id() function.
When performing a multi insert statement, insert_id() will return the value of the first row.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
insert_id(db::DB) =
    ccall( (:mysql_insert_id, mariadb_lib), Culonglong, (Ptr{UInt8},), db.ptr)

"""
# Description

This function is used to ask the server to kill a MariaDB thread specified by the processid
parameter. This value must be retrieved by SHOW PROCESSLIST. If trying to kill the own connection
thread_id() should be used.

Returns DB_OK on success, otherwise nonzero.

To stop a running command without killing the connection use KILL QUERY. The kill() function
only kills a connection, it doesn't free any memory - this must be done explicitly by calling
*close()*.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **pid** process id.
"""
kill(db::DB, pid::UInt) = call( (:mysql_kill, mariadb_lib), Cint, (PTr{UInt8}, Culong),
                                             db.ptr, pid)


"""
# Description

**server_end()** is an alias for *library_end()*.
"""
server_end() = ccall( (:mysql_server_end, mariadb_lib), Void, ())

"""
# Description

**server_init()** is an alias for *library_init()*.
"""
function server_init(argv::Vector{ByteString}, groups::Vector{ByteString})
    c_groups::Vector{Ptr{UInt8}}
    for s in groups
        push!(c_groups, pointer(s))
    end
    push!(c_groups, convert(Ptr{UInt8}, C_NULL))
    return ccall( (:mysql_server_init, mariadb_lib), Cint,
                   (Cint, Ptr{Ptr{UInt8}}, Ptr{Ptr{UInt8}}),
                   length(argv), argv, c_groups)
end

server_init(argv::Vector{ByteString}) =
    ccall( (:mysql_server_init, mariadb_lib), Cint,
           (Cint, Ptr{Ptr{UInt8}}, Ptr{Ptr{UInt8}}),
           length(argv), argv, C_NULL)

server_init() =
    ccall( (:mysql_server_init, mariadb_lib), Cint,
           (Cint, Ptr{Ptr{UInt8}}, Ptr{Ptr{UInt8}}),
           0, C_NULL, C_NULL)

"""
# Description

Call when finished using the library, such as after disconnecting from the server. In an embedded
server application, the embedded server is shut down and cleaned up. For a client program, only
cleans up by performing memory management tasks.

*server_end()* is an alias
"""
library_end() = server_end()

"""
# Description

Call to initialize the library before calling other functions, both for embedded servers and regular
clients. If used on an embedded server, the server is started and subsystems initialized. Returns
DB_OK for success, or nonzero if an error occurred.

Call *library_end()* to clean up after completion.

*server_init()* is an alias.

# Parameters
- **argv** The arguments to pass into the init function, If used, the first parameter should be the
    process name
- **groups** The groups to pass into the init function.
"""
library_init(argv::Vector{ByteString}, groups::Vector{ByteString}) = server_init(argv, groups)
library_init(argv::Vector{ByteString}) = server_init(argv)
library_init() = server_init()

"""
# Description

Indicates if one or more result sets are available from a previous call to *real_query()*.
Returns true if more result sets are available, otherwise false.

The function *set_server_option()* enables or disables multi statement support.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
more_results(db::DB) =
    ccall( (:mysql_more_results, mariadb_lib), Cchar, (Ptr{Void},), db.ptr) == 1

"""
# Description

Prepares next result set from a previous call to *real_query()* which can be retrieved by
*store_result()* or *use_result()*. Returns DB_OK on success, nonzero if an error
occurred.

If a multi query contains errors the return value of *errno/error()* might change and there
will be no result set available.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
next_result(db::DB) =
    ccall( (:mysql_next_result, mariadb_lib), Cint, (Ptr{Void},), db.ptr)

"""
# Description

Returns number of fields in a specified result set.

# Parameters

- **Result** A result set identifier returned by *store_result()* or *use_result()*.
"""
num_fields(result::DB_RES) =
    ccall( (:mysql_num_fields, mariadb_lib), Cuint, (Ptr{Void},), result.ptr)

"""
# Description

Returns number of rows in a result set.

The behaviour of num_rows() depends on whether buffered or unbuffered result sets are being
used. For unbuffered result sets, *num_rows()* will not return the correct number of rows
until all the rows in the result have been retrieved.

# Parameters

- **Result** A result set identifier returned by *store_result()* or *use_result()*.
"""
num_rows(result::DB_RES) =
    ccall( (:mysql_num_rows, mariadb_lib), Culonglong, (Ptr{Void},), result.ptr)

"""
# Description

Used to set extra connect options and affect behavior for a connection. This function may be called
multiple times to set several options. *options()* should be called after *init()* and
before *real_connect()*.

Returns DB_OK on success, non zero if an error occurred (invalid option or value).

## Options

- **INIT_COMMAND** Command(s) which will be executed when connecting and reconnecting to the
    server.
    ```
    options(db, INIT_COMMAND, "CREATE TABLE ...")
    ```

- **DB_OPT_COMPRESS** Use the compressed protocol for client server communication. If the server
    doesn't support compressed protocol, the default protocol will be used.
    ```
    options(db, OPT_COMPRESS)
    ```

- **OPT_CONNECT_TIMEOUT** Connect timeout in seconds. This value will be passed as an unsigned
    int parameter.
    ```
    options(db, OPT_CONNECT_TIMEOUT, 5)
    ```

- **OPT_LOCAL_INFILE** Enable or disable use of LOAD DATA LOCAL INFILE
    ```
    options(db, OPT_LOCAL_INFILE)        /* disable */
    options(db, OPT_LOCAL_INFILE, "1")   /* enable */
    ```

- **OPT_NAMED_PIPE** For Windows operating systems only: Use named pipes for client/server
    communication.
    ```
    options(db, OPT_NAMED_PIPE)
    ```

- **OPT_PROTOCOL** Specify the type of client/server protocol. Possible values are:
    - PROTOCOL_TCP
    - PROTOCOL_SOCKET
    - PROTOCOL_PIPE
    ```
    options(db, OPT_PROTOCOL, PROTOCOL_SOCKET)
    ```

- **OPT_RECONNECT** Enable or disable automatic reconnect.
    ```
    options(db, OPT_RECONNECT)       /* disable */
    options(db, OPT_RECONNECT, "1")  /* enable */
    ```

- **OPT_READ_TIMEOUT** Specifies the timeout in seconds for reading packets from server. This
    value will be passed as an unsigned int.
    ```
    options(db, OPT_READ_TIMEOUT, 5)
    ```

- **OPT_WRITE_TIMEOUT** Specifies the timeout in seconds for sending packets to server. This
    value will be passed as an unsigned int.
    ```
    options(db, OPT_WRITE_TIMEOUT, 5)
    ```

- **READ_DEFAULT_FILE** Read options from named option file instead of *my.cnf*
    ```
    options(db, READ_DEFAULT_FILE, "./my_conf.cnf")
    ```

- **READ_DEFAULT_GROUP** Read options from the named group from my.cnf or the file specified
    with *READ_DEFAULT_FILE*.
    ```
    options(db, READ_DEFAULT_GROUP, "my_section")
    ```

- **REPORT_DATA_TRUNCATION** Enable or disable reporting data truncation errors for prepared
    statement.
    ```
    options(db, REPORT_DATA_TRUNCATION)        /* disable */
    options(db, REPORT_DATA_TRUNCATION, "1")   /* enable */
    ```

- **SET_CHARSET_NAME** Specify the default character set for the connection.
    ```
    options(db, SET_CHARSET_NAME, "utf8")
    ```

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **option** the option you want to set. See description above.
- **arg** The value for the option.
"""
function _options(db::DB, option::OPTION, arg::Ptr{Void})
    option == PROGRESS_CALLBACK &&
        error("Unsupported option: PROGRESS_CALLBACK")
    ccall( (:mysql_options, mariadb_lib), Cint, (Ptr{Void}, Cint, Ptr{Void}),
           db.ptr, option, arg)
end

options(db::DB, option::OPTION) = _options(db, option, C_NULL)
options(db::DB, option::OPTION, arg::ByteString) = _options(db, option, @str_2_c_str(arg))
options(db::DB, option::OPTION, arg::Int) = _options(db, option, pointer(Cint[arg]))
options(db::DB, option::OPTION, arg::UInt) = _options(db, option, pointer(Cuint[arg]))
options(db::DB, option::OPTION, arg::PROTOCOL_TYPE) =  _options(db, option, convert(Int, arg))

"""
# Description

Checks whether the connection to the server is working. If it has gone down, and global option
reconnect is enabled an automatic reconnection is attempted.

Returns DB_OK on success, nonzero if an error occured.

This function can be used by clients that remain idle for a long while, to check whether the server
has closed the connection and reconnect if necessary.

If a reconnect occurred the thread_id will change. Also resources bundled to the connection
(prepared statements, locks, temporary tables, ...) will be released.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
ping(db::DB) = ccall( (:mysql_ping, mariadb_lib), Cint, (Ptr{Void},), db.ptr)

"""
# Description

Performs a statement pointed to by the null terminate string query against the database. Contrary to
*real_query()*, *query()* is not binary safe.

Returns DB_OK on success, non zero on failure.

For executing multi statements the statements within the null terminated string statements must be
separated by a semicolon.

If your statement contains binary data you should use *real_query()* or escape your data with
*hex_string()*.

To determine if a statement returned a result set use the function *num_fields()*.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **query** a string containing the statement to be performed.
"""
query(db::DB, query) =
    ccall( (:mysql_query, mariadb_lib), Cint, (Ptr{Void}, Cstring), db.ptr, query)

"""
# Description

Establishes a connection to a database server. Returns a database handle or C_NULL if an error
occurred.

The password doesn't need to be encrypted before executing real_connect(). This will be
handled in the client server protocol.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()*.
- **host** can be either a host name or an IP address. Passing the C_NULL value or the string "" or
    "localhost" to this parameter, the local host is assumed. When possible, pipes will be used
    instead of the TCP/IP protocol.
- **user** the user name
- **passwd** If "" provided or C_NULL, the server will attempt to authenticate the user against
    those user records which have no password only. This allows one username to be used with
    different permissions (depending on if a password as provided or not).
- **db** if provided will specify the default database to be used when performing queries.
- **port** specifies the port number to attempt to connect to the server.
- **unix_socket** specifies the socket or named pipe that should be used.
- **flags** the flags allows various connection options to be set:
    - **CLIENT_FOUND_ROWS** Return the number of matched rows instead of number of changed rows.
    - **CLIENT_NO_SCHEMA** Forbids the use of database.tablename.column syntax and forces the SQL
        parser to generate an error.
    - **CLIENT_COMPRESS** Use compression protocol
    - **CLIENT_IGNORE_SPACE** This option makes all function names reserved words.
    - **CLIENT_LOCAL_FILES** Use compression protocol
    - **CLIENT_MULTI_STATEMENTS** Allows the client to send multiple statements in one command.
        Statements will be divided by a semicolon.
    - **CLIENT_MULTI_RESULTS** Indicates that the client is able to handle multiple result sets from
        stored procedures or multi statements. This option will be automatically set if
        *CLIENT_MULTI_STATEMENTS* is set.
"""
_real_connect(dbptr::Ptr{Void},
              host::Ptr{UInt8} = C_NULL,
              user::Ptr{UInt8} = C_NULL,
              passwd::Ptr{UInt8} = C_NULL,
	      dbname::Ptr{UInt8} = C_NULL,
              port::UInt=UInt(0),
              unix_socket::Ptr{UInt8} = C_NULL,
              flags::UInt32=UInt32(0)) =
    ccall( (:mysql_real_connect, mariadb_lib), Ptr{Void},
	   (Ptr{Void}, Ptr{UInt8}, Ptr{UInt8}, Ptr{UInt8},
            Ptr{UInt8}, Cuint, Ptr{UInt8}, Culong),
           dbptr, host, user,passwd, dbname, port, unix_socket,flags)

function real_connect(db::DB, host::ByteString, user::ByteString;
                      passwd::ByteString = "",
		      dbname::ByteString = "",
                      port::UInt = UInt(0),
                      unix_socket::ByteString = "",
                      flags::UInt32 = UInt32(0))
    ret = _real_connect(db.ptr,
                        @str_2_c_str(host),
                        @str_2_c_str(user),
                        @str_2_c_str(passwd),
                        @str_2_c_str(dbname),
                        port,
                        @str_2_c_str(unix_socket),
    		        flags)
    db.ptr = ret
    db
end

"""
# Description

This function is used to create a legal SQL string that you can use in an SQL statement. The given
string is encoded to an escaped SQL string, taking into account the current character set of the connection.

Returns the escaped string.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **from** the string which will be escaped
"""
function real_escape_string(db::DB, from::AbstractString)
    num_bytes = length(from)
    out = Vector{UInt8}(num_bytes * 2 + 1)
    len = ccall( (:mysql_real_escape_string, mariadb_lib), Culong,
                  (Ptr{Void}, Ptr{UInt8}, Cstring, Culong),
                  db.ptr, out, from, num_bytes)
    r = range(1, Int64(len))
    return (bytestring(getindex(out,r)), len)
end

"""
**real_query()** is the binary safe function for performing a statement on the database
server.

Returns DB_OK on success, otherwise non zero

Contrary to the *query()* function, **real_query** is binary safe.

To determine if **real_query** returns a result set use the *num_fields()* function.

# Parameters
- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **query** a string containing the statement to be performed.
"""
real_query(db::DB, query::Vector{UInt8}) =
    ccall( (:mysql_real_query, mariadb_lib), Cint, (Ptr{Void}, Ptr{UInt8}, Culong),
           db.ptr, query, length(query))

real_query(db::DB, query::AbstractString) = real_query(db, bytestring(query).data)

"""
# Description

Flushes different types of information stored on the server. The bit-masked parameter options
specify which kind of information will be flushed. options can be any combinationation of the
following:

| Option            | Description                                         |
| ----------------- | --------------------------------------------------- |
| REFRESH_GRANT     | Refresh grant tables.                               |
| REFRESH_LOG       | Flush logs.                                         |
| REFRESH_TABLES    | Flush table cache.                                  |
| REFRESH_HOSTS     | Flush host cache.                                   |
| REFRESH_STATUS    | Reset status variable.                              |
| REFRESH_THREADS   | Flush thread chache.                                |
| REFRESH_SLAVE     | Reset master server information and restart slaves. |
| REFRESH_MASTER    | Remove binary log files.                            |
| REFRESH_READ_LOCK |                                                     |
| REFRESH_FAST      |                                                     |

Returns DB_OK on success, otherwise non zero.

To combine different values in the options parameter use the OR operator '|'. The function
*reload()* is an alias for *refresh()*.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **options**  a bit masked composed integer. See above.
"""
refresh(db::DB, options::UInt32) =
    ccall( (:mysql_refresh, mariadb_lib), Cchar, (Ptr{Void}, Cuint), db.ptr, options)

"""
# Description

Rolls back the current transaction for the database.

Returns DB_OK on success, nonzero if an error occurred.

**rollback()** will not work as expected if autocommit mode was set or the storage engine does
not support transactions.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
rollback(db::DB) =
    ccall( (:mysql_rollback, mariadb_lib), Cchar, (Ptr{Void},), db.ptr)

"""
# Description

Positions the row cursor to an aribtrary row in a result set which was obtained by
*store_result()*.

Returns the previous row offset.

This function will **not** work if the result set was obtained by *use_result()*.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
- **offset** row offset. This value can be obtained either by *row_seek()* or
    *row_tell()*
"""
row_seek(result::DB_RES, offset::DB_ROW_OFFSET) =
    DB_ROW_OFFSET(ccall( (:mysql_row_seek, mariadb_lib), Ptr{Void},
                            (Ptr{Void}, Ptr{Void}), result.ptr, offset.ptr))

"""
# Description

Returns the row offset of a result cursor. The returned offset value can be used to reposition the
result cursor by calling *row_seek()*.

This function will not work if the result set was obtained by *use_result()*.

# Parameters

- **result** a result set identifier returned by *store_result()* or *use_result()*.
"""
row_tell(result::DB_RES) =
    DB_ROW_OFFSET(ccall( (:mysql_row_tell, mariadb_lib), Ptr{Void}, (Ptr{Void},), result.ptr))

"""
# Description

Selects a database as default.

Returns DB_OK on success, non-zero on failure.

The SQL command SELECT DATABASE() will return the name of the default database.

The default database can also be set by the db parameter in real_connect().

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **db** the default database name.
"""
select_db(db::DB, dbname::AbstractString) =
    ccall( (:mysql_select_db, mariadb_lib), Cint, (Ptr{Void}, Cstring), db.ptr, dbname)

"""
# Description

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **query** the query
"""
send_query(db::DB, query::ByteString) =
    ccall( (:mysql_send_query, mariadb_lib),
           Cint, (Ptr{Void}, Cstring, Culong),
           db.ptr, query, sizeof(query))
send_query(db::DB, query::AbstractString) = send_query(db, bytestring(query))

"""
# Description

Sets the default character set for the current connection.

Returns DB_OK on success, non-zero on failure.

It's strongly recommended to use set_character_set() instead of SET NAMES ... since
*real_escape_string()* might fail or deliver unexpected results.

The client library supports the following character sets:

| Character set | Description                                                              |
| ------------- | ------------------------------------------------------------------------ |
| armscii8      | 8 bit character set for Armenian                                         |
| ascii	        | US ASCII character set                                                   |
| big5	        | 2 byte character set for traditional Chinese, Hongkong, Macau and Taiwan |
| binary        | 8 bit binary character set                                               |
| cp1250	| Windows code page 1250 character set                                     |
| cp1251	| Windows code page 1251 character set                                     |
| cp1256	| Windows code page 1256 character set                                     |
| cp1257	| Windows code page 1257 character set                                     |
| cp850	        | MS-DOS Codepage 850 (Western Europe)                                     |
| cp852	        | MS-DOS Codepage 852 (Middle Europe)                                      |
| cp866	        | MS-DOS Codepage 866 (Russian)                                            |
| cp932	        | Microsoft Codepage 932 (Extension to sjis)                               |
| dec8	        | DEC West European                                                        |
| eucjpms	| UJIS for Windows Japanese                                                |
| euckr	        | EUC KR-Korean                                                            |
| gb2312	| GB-2312 simplified Chinese                                               |
| gbk	        | GBK simplified Chinese                                                   |
| geostd8	| GEOSTD8 Georgian                                                         |
| greek	        | ISO 8859-7 Greek                                                         |
| hebrew	| ISO 8859-8 Hebrew                                                        |
| hp8	        | HP West European                                                         |
| keybcs2	| DOS Kamenicky Czech-Slovak                                               |
| koi8r	        | KOI8-R Relcom Russian                                                    |
| koi8u	        | KOI8-U Ukrainian                                                         |
| latin1	| CP1252 Western European                                                  |
| latin2	| ISO 8859-2 Central Europe                                                |
| latin5	| ISO 8859-9 Turkish                                                       |
| latin7	| ISO 8859-13 Baltic                                                       |
| macce	        | MAC Central European                                                     |
| macroman	| MAC Western European                                                     |
| sjis	        | SJIS for Windows Japanese                                                |
| swe7	        | 7-bit Swedish                                                            |
| tis620	| TIS620 Thai                                                              |
| ucs2	        | UCS-2 Unicode                                                            |
| ujis	        | EUC-JP Japanese                                                          |
| utf8	        | UTF-8 Unicode                                                            |
| utf16	        | UTF-16 Unicode                                                           |
| utf32	        | UTF-32 Unicode                                                           |

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **csname** character set name
"""
set_character_set(db::DB, csname::AbstractString) =
    ccall( (:mysql_set_character_set, mariadb_lib), Cint, (Ptr{Void}, Cstring),
           db.ptr, csname)

"""
# Description

Server option, which can be one of the following values:

| Option                            | Description                      |
| --------------------------------- | -------------------------------- |
| OPTION_MULTI_STATEMENTS_OFF | Disables multi statement support |
| OPTION_MULTI_STATEMENTS_ON  | Enable multi statement support   |

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **option** server option (see above)
"""
set_server_option(db::DB, option::SET_OPTION) =
    ccall( (:mysql_set_server_option, mariadb_lib), Cint, (Ptr{Void}, Cint), db.ptr, option)

"""
# Description

Sends a shutdown message to the server. To shutdown the database server, the user for the current
connection must have SHUTDOWN privileges.

Returns DB_OK on success, non-zero on failure.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **shutdown_level** currently only one shutdown level, **SHUTDOWN_DEFAULT** is supported.
"""
shutdown(db::DB, shutdown_level::SHUTDOWN_LEVEL) =
    ccall( (:mysql_shutdown, mariadb_lib), Cint, (Ptr{Void}, Cint), db.ptr, shutdown_level)

"""
# Description

Returns a string containing the SQLSTATE error code for the most recently invoked function that can
succeed or fail. The error code consists of five characters. '00000' means no error. The values are
specified by ANSI SQL and ODBC

Please note that not all client library error codes are mapped to SQLSTATE errors. Errors which
can't be mapped will returned as value HY000.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
sqlstate(db::DB) = bytestring(
    ccall( (:mysql_sqlstate, mariadb_lib), Ptr{UInt8}, (Ptr{Void},), db.ptr))

"""
# Description

Used for establishing a secure SSL connection. It must be called before attempting to use
*real_connect()*. SSL support must be enabled in the client library in order for the function
to have any effect.

"" or C_NULL can be used for an unused parameter.

*real_connect()* will return an error if attempting to connect and SSL is incorrectly set up.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
- **key** path to the key file.
- **cert** path to the certificate file.
- **ca** path to the certificate authority file.
- **capath** path to the directory containing the trusted SSL CA certificates in PEM format.
- **cipher** list of permitted ciphers to use for SSL encryption.
"""
_ssl_set(db::DB,
         key::Ptr{UInt8}=C_NULL,
         cert::Ptr{UInt8}=C_NULL,
	 ca::Ptr{UInt8}=C_NULL,
         capath::Ptr{UInt8}=C_NULL,
         cipher::Ptr{UInt8}=C_NULL) =
    ccall( (:mysql_ssl_set, mariadb_lib), Cchar,
	   (Ptr{Void}, Ptr{UInt8}, Ptr{UInt8}, Ptr{UInt8}, Ptr{UInt8}, Ptr{UInt8}),
           db.ptr, key, cert, ca, capath, cipher)

ssl_set(db::DB, key::ByteString, cert::ByteString, ca::ByteString, capath::ByteString,
        cipher::ByteString) =
    _ssl_set(db, @str_2_c_str(key), @str_2_c_str(cert), @str_2_c_str(ca), @str_2_c_str(capath),
             @str_2_c_str(cipher))

"""
# Description

**stat()** returns a string with the current server status for uptime, threads, queries, open
tables, flush tables and queries per second.

For a complete list of other status variables, you have to use the SHOW STATUS SQL command.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
stat(db::DB) = bytestring(
    ccall( (:mysql_stat, mariadb_lib), Ptr{UInt8}, (Ptr{Void},), db.ptr))

"""
# Description

Returns a buffered resultset from the last executed query.

**store_result()** returns C_NULL in case an error occured or if the query didn't return data
(e.g. when executing an INSERT or UPDATE query).

*field_count()* indicates if there will be a result set available.

The memory allocated by **store_result()** needs to be released by calling the function
*free_result()*.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
store_result(db::DB) =
    ccall( (:mysql_store_result, mariadb_lib), Ptr{Void}, (Ptr{Void},), db.ptr)

"""
# Description

The **thread_end()** function needs to be called before a client thread ends. It will release
thread specific memory, which was allocated by a previous thread_init() call.

Unlike *thread_init()* **thread_end()** will not be invoked automatically if the thread
ends. To avoid memory leaks *thread_end()* must be called explicitly.
"""
thread_end() = ccall( (:mysql_thread_end, mariadb_lib), Void, ())

"""
# Description

The thread_id() function returns the thread id for the current connection.

The current connection can be killed with *kill()*. If reconnect option is enabled the thread
id might change if the client reconnects to the server.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
thread_id(db::DB) =
    ccall( (:mysql_thread_id, mariadb_lib), Culong, (Ptr{Void},), db.ptr)

"""
# Description

Thread initialization for multi threaded clients. Multi threaded clients should call
**thread_init()** at the beginning of the thread initialization to initialize thread specific
client library variables. If **thread_init()** was not called explicitly, it will be called
automatically by *init()* or *real_connect()*.

Returns DB_OK if successful or 1 if an error occurred.

Before a client thread ends the *thread_end()* function must be called to release memory -
otherwise the client library will report an error.
"""
thread_init() = ccall( (:mysql_thread_init, mariadb_lib), Cchar, ())

"""
# Description

Indicates whether or not the client library is compiled as thread safe. Returns 1 if the client
library was compiled as thread safe otherwise zero.

By default the mariadb client library is compiled as thread safe.
"""
thread_safe() = ccall( (:mysql_thread_safe, mariadb_lib), Cint, ())

"""
# Description

Used to initiate the retrieval of a result set from the last query executed using the
*real_query()* function on the database connection. Either this or *the store_result()*
function must be called before the results of a query can be retrieved, and one or the other must be
called to prevent the next query on that database connection from failing.

Returns an unbuffered result set or C_NULL if an error occurred.

The **use_result()** function does not transfer the entire result set. Hence several functions
like *num_rows()* or *data_seek()* cannot be used. **use_result()** will block the
current connection until all result sets are retrieved or result set was released by
*free_result()*.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
use_result(db::DB) =
    DB_RES(ccall( (:mysql_use_result, mariadb_lib), Ptr{Void}, (Ptr{Void},), db.ptr))

"""
# Description

Returns the number of warnings from the last executed query, or zero if there are no warnings.

For retrieving warning messages you should use the SQL command SHOW WARNINGS. If
SQL_MODE TRADITIONAL is enabled an error instead of warning will be returned. For detailed
information check the server documentation.

# Parameters

- **db** a database handle, identifier, which was previously allocated by *init()* or
  *real_connect()*.
"""
warning_count(db::DB) =
    ccall( (:mysql_warning_count, mariadb_lib), Cuint, (Ptr{Void},), db.ptr)
