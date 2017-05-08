
export keywords_worker
export mix_worker
export hmm_worker
export simhash_worker
export tag_worker
export mp_worker
export query_worker

function keywords_worker(dict = DICTPATH,hmm = HMMPATH,stop_words = STOPPATH,idf = IDFPATH, topn = 5)
    worker("keywords",dict,hmm,USERPATH,20,stop_words,idf)
end

function mix_worker(dict = DICTPATH,hmm = HMMPATH,user = USERPATH)
    worker("mix",dict,hmm,user)
end

function hmm_worker(hmm = HMMPATH)
    worker("hmm",DICTPATH,hmm)
end

function simhash_worker(dict = DICTPATH,hmm = HMMPATH,stop_words = STOPPATH,idf = IDFPATH, topn = 5)
    worker("simhash",dict,hmm,USERPATH,20,stop_words,idf)
end

function tag_worker(dict = DICTPATH,hmm = HMMPATH,user = USERPATH)
    worker("tag",dict,hmm,user)
end

function mp_worker(dict = DICTPATH,user = USERPATH)
    worker("mp",dict,HMMPATH,user)
end

function query_worker(dict = DICTPATH,hmm = HMMPATH,qmax = 20)
    worker("query",dict,hmm,USERPATH,qmax)
end
