# Examples of connectivity to Quandl and mysql from within Julia.
#   I'd suggest executing line-by-line rather than as a script.

# Pkg.add("Quandl")
# Pkg.add("ODBC")

# retrieve some data from quandl
# PRECONDITION:  setup a free quandl account and retrieve your API key
using Quandl

set_auth_token(my_quandl_api_key)

# I find it's way easier to search the quandl website for codes,
# but the package offers another way to search for timeseries
interactivequandl("Nikkei")

# download the Stevens Continuous Futures Nikkei series
ticker = "SCF/CME_NK1_FN";
data = quandl(ticker)
# data = quandl("SCF/CME_NK1_FN",format="DataFrame")# if a dataframe is preferred

# PRECONDITION:  install mysql and setup a user for the purpose of testing, this one's username is "julia"
using ODBC

ODBC.connect("mysql_db_julia",usr="julia",pwd="julia123")

# start a fresh table
query("drop table if exists mktdb.quandl_prices")
sql_create_table = "create table mktdb.quandl_prices";
sql_create_table = sql_create_table * "(Ticker varchar(20),priceDate Date,";
sql_create_table = sql_create_table * " Open Double unsigned, High Double unsigned, Low Double unsigned, Close Double unsigned, Volume Bigint unsigned,";
sql_create_table = sql_create_table * " PRIMARY KEY(Ticker,priceDate))"
query(sql_create_table)

# the table will be initially empty
query("describe mktdb.quandl_prices")
query("select * from mktdb.quandl_prices")


nRecords = length(data);
for rr = 1:nRecords
    effectiveDate = data.timestamp[rr];
    open = data.values[rr,1];
    high = data.values[rr,2];
    low = data.values[rr,3];
    close = data.values[rr,4];
    volume = data.values[rr,5];
    sql_insert = "insert into mktdb.quandl_prices (Ticker,priceDate,Open,High,Low,Close,Volume)";
    sql_insert = sql_insert * " values ('$ticker','$effectiveDate',$open,$high,$low,$close,$volume)";
    query(sql_insert);
end


# the table now contains some data
query("select * from mktdb.quandl_prices")

