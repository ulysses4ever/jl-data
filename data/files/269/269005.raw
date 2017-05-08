"""Here are a collection of very simple functions that wrap around the python psycopg2 library. They are trivial to extend. Note also the attempt to avoid explicit side-effects in a function"""

using PyCall
@pyimport psycopg2
type PSQL_Connector
    connection
    cursor
end

function PSQL_Connector(dbname;user=user,password=password,hostname=hostname)
        #Returns a connection object, this function is meant to be invoked within a function needing connection objects 
        connection = psycopg2.connect("dbname="*dbname*" user="*user*" password="password" host="hostname)
        cursor = connection[:cursor]()
        return PSQL_Connector(connection,cursor)
end

function PSQL_Connector(dbname,username)
    #Returns a connection object when only the DBname and username need to be specified
    connection = psycopg2.connect("dbname="*dbname*" user="*user*)
    cursor = connection[:cursor]()
    return PSQL_Connector(connection,cursor)
end

function PSQL_Connector(dbname;user=username,password=password)
    #Returns a connection object when only the DBname, username and password need to be specified
    connection = psycopg2.connect("dbname="*dbname*" user="*user*" password="password)
    cursor = connection[:cursor]()
    return PSQL_Connector(connection,cursor)
end

function simplequery(connector::PSQL_Connector,querystring::String)
    """Send a simple query to a database. This is useful for queries extracting data from a database. The data is read all at once and returned as a string."""
    connector.cursor[:execute](querystring)
    data = connector.cursor[:fetchall]()
    connector.cursor[:close]()
    connector.connection[:close]()
    return data
 end
  
function insert_query(connector::PSQL_Connector,querystring)
    """Used for more complex queries where a commit is necessary, such as "INSERTS" or "CREATE" """
    connector.cursor[:execute](querystring)
    data = connector.cursor[:statusmessage]
    connector.connection[:commit]()
    connector.cursor[:close]()
    connector.connection[:close]()
    return data
end

#Example Function code written against the library:
const myconnector = psql_connector(mydb,username=myname,password=mypassword)


function insert_int_into_my_db(int::String,table::String,column="")
    if column != ""
        query = "INSERT INTO "*mytable*" ("column") ("*int*")"
        end
    if column == ""
        query = "INSERT INTO "*mytable" "*int
        end
    return insert_query(myconnector,query)
end
      
