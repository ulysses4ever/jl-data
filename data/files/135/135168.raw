using Base.Test
using NLP

@test tokenize("cat and dog")==["cat","and","dog"]
@test tokenize("c1at and dog")==["cat","and","dog"]
@test tokenize(" cat  and dog ")==["cat","and","dog"]
@test tokenize(" dog's and  \r\n     c1a@t#s  \r\n")==["dogs","and","cats"]
@test tokenize("a12409A322!@#%%@a\t\r\r\n")==["aaa"]
