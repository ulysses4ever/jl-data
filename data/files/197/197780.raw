
export 关键词引擎
export 混合引擎
export hmm引擎
export simhash引擎
export 标记引擎
export 概率引擎
export 索引引擎

function 关键词引擎(dict = DICTPATH,hmm = HMMPATH,stop_words = STOPPATH,idf = IDFPATH, topn = 5)
    分词初始化("关键词",dict,hmm,USERPATH,20,stop_words,idf)
end

function 混合引擎(dict = DICTPATH,hmm = HMMPATH,user = USERPATH)
    分词初始化("混合",dict,hmm,user)
end

function hmm引擎(hmm = HMMPATH)
    分词初始化("hmm",DICTPATH,hmm)
end

function simhash引擎(dict = DICTPATH,hmm = HMMPATH,stop_words = STOPPATH,idf = IDFPATH, topn = 5)
    分词初始化("simhash",dict,hmm,USERPATH,20,stop_words,idf)
end

function 标记引擎(dict = DICTPATH,hmm = HMMPATH,user = USERPATH)
    分词初始化("标记",dict,hmm,user)
end

function 概率引擎(dict = DICTPATH,user = USERPATH)
    分词初始化("概率",dict,HMMPATH,user)
end

function 索引引擎(dict = DICTPATH,hmm = HMMPATH,qmax = 20)
    分词初始化("索引",dict,hmm,USERPATH,qmax)
end
