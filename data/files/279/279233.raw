const loopbackip = IPv4(127,0,0,1)

function addloopback!(block_dist)
    localip = getipaddr()
    for iplist in block_dist
        # add loopback interface for localip
        (localip in iplist) && !(loopbackip in iplist) && push!(iplist, loopbackip)
    end
    block_dist
end

function Block(hfile::HDFSFile)
    isdir(hfile) && (return Block(hfile, true, 0))

    worker_ids = workers()
    localip = getipaddr()
    worker_ips = map(x->getaddrinfo(string(isa(x, LocalProcess)?localip:x.config.host.value)), map(x->Base.worker_from_id(x), worker_ids))

    blks = hdfs_blocks(hfile)
    #logmsg(blks)
    block_dist = [map(IPv4,x[2]) for x in blks]
    addloopback!(block_dist)
    block_wrkr_ids = map(ips->worker_ids[findin(worker_ips, ips)], block_dist)
    filestat = stat(hfile)
    block_sz = filestat.block_sz
    file_sz = filestat.size

    data = [(hfile, ((x-1)*block_sz+1):(min(file_sz,x*block_sz))) for x in 1:length(block_dist)]
    Block(hfile, data, block_wrkr_ids, as_it_is, as_it_is)
end
