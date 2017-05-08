# Create synonyms with the same names as the C MySQL/MariaDB client

export MYSQL, mysql_error, MY_CHARSET_INFO, MYSQL_OK
const MYSQL = DB
const MYSQL_OK = DB_OK
const mysql_error = last_error
const MY_CHARSET_INFO = DB_CHARSET_INFO

for fun in (:affected_rows, :autocommit, :change_user, :character_set_name, :close, :commit,
    	    :data_seek, :dump_debug_info, :errno, :escape_string, :fetch_field, :fetch_fields,
            :fetch_field_direct, :fetch_lengths, :fetch_row, :field_count, :field_seek,
    	    :field_tell, :free_result, :get_character_set_info, :get_client_info,
    	    :get_client_version, :get_host_info, :get_proto_info, :get_server_info,
	    :get_server_version, :get_ssl_cipher, :hex_string, :info, :init, :insert_id,
    	    :kill, :library_end, :library_init, :more_results, :next_result, :num_fields,
    	    :num_rows, :options, :ping, :query, :real_connect, :real_escape_string,
            :real_query, :refresh, :rollback, :row_seek, :row_tell, :select_db, :send_query,
            :server_end, :server_init, :set_character_set, :set_server_option, :shutdown,
            :sqlstate, :ssl_set, :stat, :store_result, :thread_end, :thread_id, :thread_init,
            :thread_safe, :use_result, :warning_count)
    sym = symbol(string("mysql_",fun))
    @eval $sym = $fun
    @eval export $sym
end

for typ in (:RES, :ROW, :FIELD_OFFSET, :ROW_OFFSET, :FIELD, :TIME)
    sym = symbol(string("MYSQL_",typ))
    @eval $sym = $(symbol(string("DB_",typ)))
    @eval export $sym
end

for typ in (:TIMESTAMP_NONE, :TIMESTAMP_ERROR, :TIMESTAMP_DATE, :TIMESTAMP_DATETIME,
    	    :TIMESTAMP_TIME, :OPTION, :OPT_CONNECT_TIMEOUT, :OPT_COMPRESS, :OPT_NAMED_PIPE,
            :INIT_COMMAND, :READ_DEFAULT_FILE, :READ_DEFAULT_GROUP, :SET_CHARSET_DIR,
            :SET_CHARSET_NAME, :OPT_LOCAL_INFILE, :OPT_PROTOCOL, :SHARED_MEMORY_BASE_NAME,
            :OPT_READ_TIMEOUT, :OPT_WRITE_TIMEOUT, :OPT_USE_RESULT, :OPT_USE_REMOTE_CONNECTION,
            :OPT_USE_EMBEDDED_CONNECTION, :OPT_GUESS_CONNECTION, :SET_CLIENT_IP, :SECURE_AUTH,
    	    :REPORT_DATA_TRUNCATION, :OPT_RECONNECT, :OPT_SSL_VERIFY_SERVER_CERT, :PLUGIN_DIR,
            :DEFAULT_AUTH, :ENABLE_CLEARTEXT_PLUGIN, :PROGRESS_CALLBACK, :OPT_NONBLOCK,
            :NO_MORE_RESULTS, :SHUTDOWN_KILLABLE_CONNECT, :SHUTDOWN_KILLABLE_TRANS,
    	    :SHUTDOWN_KILLABLE_LOCK_TABLE, :SHUTDOWN_KILLABLE_UPDATE, :SHUTDOWN_LEVEL)
    sym = symbol(string("MYSQL_",typ))
    @eval $sym = $typ
    @eval export $sym
end

for typ in (:DEFAULT, :TCP, :SOCKET, :PIPE, :MEMORY)
    sym = symbol(string("MYSQL_PROTOCOL_",typ))
    @eval $sym = $typ
    @eval export $sym
end

for typ in (:READY, :GET_RESULT, :USE_RESULT, :STATEMENT_GET_RESULT)
    sym = symbol(string("MYSQL_STATUS_",typ))
    @eval $sym = $typ
    @eval export $sym
end

export SHUTDOWN_DEFAULT
const  SHUTDOWN_DEFAULT = WAIT_DEFAULT
for typ in (:CONNECTIONS, :TRANSACTIONS, :UPDATES, :ALL_BUFFERS, :CRITICAL_BUFFERS)
    sym = symbol(string("SHUTDOWN_WAIT_",typ))
    @eval $sym = $(symbol(string("WAIT_",typ)))
    @eval export $sym
end

for sym in (:NOT_NULL, :PRI_KEY, :UNIQUE_KEY, :MULTIPLE_KEY, :BLOB, :UNSIGNED, :ZEROFILL,
            :BINARY, :ENUM, :AUTO_INCREMENT, :TIMESTAMP, :SET, :NO_DEFAULT_VALUE, :ON_UPDATE_NOW,
            :NUM, :UNIQUE, :BINCP, :GET_FIXED_FIELDS, :FIELD_IN_PART_FUNC)
    @eval export $(symbol(string(sym,"_FLAG")))
end

for sym in (:LONG_PASSWORD, :FOUND_ROWS, :LONG_FLAG, :CONNECT_WITH_DB, :NO_SCHEMA, :COMPRESS,
            :ODBC, :LOCAL_FILES, :IGNORE_SPACE, :PROTOCOL_41, :INTERACTIVE, :SSL, :IGNORE_SIGPIPE,
            :TRANSACTIONS, :RESERVED, :SECURE_CONNECTION, :MULTI_STATEMENTS, :MULTI_RESULTS,
            :PS_MULTI_RESULTS, :PLUGIN_AUTH, :PROGRESS, :SSL_VERIFY_SERVER_CERT)
    @eval export $(symbol(string("CLIENT_",sym)))
end

for sym in (:GRANT, :LOG, :TABLES, :HOSTS, :STATUS, :THREADS, :SLAVE, :MASTER, :ERROR_LOG,
            :ENGINE_LOG, :BINARY_LOG, :RELAY_LOG, :GENERAL_LOG, :SLOW_LOG, :READ_LOCK,
            :CHECKPOINT, :QUERY_CACHE, :QUERY_CACHE_FREE, :DES_KEY_FILE, :USER_RESOURCES,
            :TABLE_STATS, :INDEX_STATS, :USER_STATS, :FAST)
    @eval export $(symbol(string("REFRESH_",sym)))
end

export MYSQL_OPTION_MULTI_STATEMENT_ON, MYSQL_OPTION_MULTI_STATEMENT_OFF
const MYSQL_OPTION_MULTI_STATEMENT_ON  = MULTI_STATEMENT_ON
const MYSQL_OPTION_MULTI_STATEMENT_OFF = MULTI_STATEMENT_OFF
