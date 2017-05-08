using HDFS

host = isempty(ARGS) ? "localhost" : ARGS[1]
port = isempty(ARGS) ? 9000 : int(ARGS[2])

# connect 
fs = hdfs_connect(host, port)
println("connected to hdfs:://$(host):$(port)")

const TEST_FILE = "/julia_test_file"
fileexist = hdfs_exists(fs, TEST_FILE) 
if !fileexist 
	println("Test file $TEST_FILE does not exist. Create it ...")
	ftemp = hdfs_open(fs, TEST_FILE, "w")  
	hdfs_write(ftemp, "Hello, HDFS with julia!\n")
	hdfs_flush(ftemp)  
	hdfs_close(ftemp)
	println("Test file $TEST_FILE created!")
end

@assert true == hdfs_exists(fs, TEST_FILE) 
ftemp = hdfs_open(fs, TEST_FILE, "r")
finfo = hdfs_get_path_info(fs, TEST_FILE)
szblock = finfo.block_sz
szread = finfo.size < 1024?finfo.size : 1024
opoffset = 0
hdfs_seek(ftemp, opoffset)
if szread == 0
	println("File length of $TEST_FILE equals zero!")
else
	println("Read first $szread of $(finfo.size) bytes from file $TEST_FILE ...")
	(buff, bytes) = hdfs_read(ftemp, szread)
	@assert bytes == szread
	strread = bytestring(buff[1:szread])
	print("Data readed: $strread");
end
hdfs_close(ftemp)

#cleanup 
#hdfs_delete(fs, TEST_FILE)

