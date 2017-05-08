# To test
# compile with ragel:
#   ~/Apps/ragel-julia/src/ragel -U ~/Dropbox/Workspace/julia/julia-ragel/test-ragel-moabs-2.rl
# the run the test-ragel-moabs-3 which calles the parse moabs function:
#   ~/Apps/julia-0.3/julia ~/Dropbox/Workspace/julia/julia-ragel/test-ragel-moabs-3.jl
#
module MOABSParserImpl

using Switch

type MOABSCoverage
    coverdict::Dict{ASCIIString,Int32}
    id::ASCIIString
    start_pos::ASCIIString
    stop_pos::ASCIIString
    score::ASCIIString
    c_count::Int32
    t_count::Int32
end



function parse_moabs(data::String, dict::Dict{ASCIIString,Int32})
    moabs_dict= MOABSCoverage( dict, "","","","",0,0)
    mark=0
    p=0
    pe=length(data)


_Test2_actions = Int8  [ 0, 1, 0, 1, 1, 1, 2, 1, 3, 1, 4, 1, 5, 1, 6, 1, 7, 1, 8, 1, 9, 1, 10, 1, 11, 1, 12, 0  ]
_Test2_key_offsets = Int8  [ 0, 0, 7, 9, 12, 14, 17, 22, 28, 30, 33, 35, 38, 46, 55, 0  ]
_Test2_trans_keys = Int8  [ 9, 48, 57, 65, 90, 97, 122, 48, 57, 9, 48, 57, 48, 57, 9, 48, 57, 46, 97, 110, 48, 57, 9, 46, 97, 110, 48, 57, 48, 57, 9, 48, 57, 48, 57, 9, 48, 57, 9, 43, 45, 46, 48, 57, 65, 90, 9, 10, 43, 45, 46, 48, 57, 65, 90, 48, 57, 65, 90, 97, 122, 0  ]
_Test2_single_lengths = Int8  [ 0, 1, 0, 1, 0, 1, 3, 4, 0, 1, 0, 1, 2, 3, 0, 0  ]
_Test2_range_lengths = Int8  [ 0, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 3, 3, 0  ]
_Test2_index_offsets = Int8  [ 0, 0, 5, 7, 10, 12, 15, 20, 26, 28, 31, 33, 36, 42, 49, 0  ]
_Test2_trans_cond_spaces = Int8  [ -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 0  ]
_Test2_trans_offsets = Int8  [ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 0  ]
_Test2_trans_lengths = Int8  [ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0  ]
_Test2_cond_keys = Int8  [ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0  ]
_Test2_cond_targs = Int8  [ 2, 1, 1, 1, 0, 3, 0, 4, 3, 0, 5, 0, 6, 5, 0, 7, 7, 7, 7, 0, 8, 7, 7, 7, 7, 0, 9, 0, 10, 9, 0, 11, 0, 12, 11, 0, 13, 13, 13, 13, 13, 0, 13, 14, 13, 13, 13, 13, 0, 1, 1, 1, 0, 0  ]
_Test2_cond_actions = Int8  [ 3, 0, 0, 0, 0, 5, 0, 7, 0, 0, 9, 0, 11, 0, 0, 13, 13, 13, 13, 0, 15, 0, 0, 0, 0, 0, 17, 0, 19, 0, 0, 21, 0, 23, 0, 0, 0, 0, 0, 0, 0, 0, 0, 25, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0  ]
Test2_start  :: Int  = 14
Test2_first_final  :: Int  = 14
Test2_error  :: Int  = 0
Test2_en_main  :: Int  = 14

begin
cs = Test2_start;
	end

begin
_acts = 0
_keys = 0
_ckeys = 0
if p == pe
    @goto _test_eof

end
if cs == 0
    @goto _out

end
@label _resume
_keys = int(_Test2_key_offsets[1 + cs] );
	_trans = convert(Uint ,_Test2_index_offsets[1 + cs]);

	_klen = convert(Int ,_Test2_single_lengths[1 + cs]);
	if _klen > 0
    begin
_lower = 0
_mid = 0
_upper = 0
_lower = _keys;
		_upper = _keys + _klen - 1;
		while ( true  )
    begin
if _upper < _lower
    break;


end
_mid = _lower + ((_upper-_lower) >> 1);
			if ( data[1 + p ]) < _Test2_trans_keys[1 + _mid ]
    _upper = _mid - 1;

elseif ( ( data[1 + p ]) > _Test2_trans_keys[1 + _mid ] )
    _lower = _mid + 1;

else
    begin
_trans += convert(Uint ,(_mid - _keys));
				@goto _match
end

end
end

end
_keys += _klen;
		_trans += convert(Uint ,_klen);
	end

end
_klen = convert(Int ,_Test2_range_lengths[1 + cs]);
	if _klen > 0
    begin
_lower = 0
_mid = 0
_upper = 0
_lower = _keys;
		_upper = _keys + (_klen<<1) - 2;
		while ( true  )
    begin
if _upper < _lower
    break;


end
_mid = _lower + (((_upper-_lower) >> 1) & ~1);
			if ( data[1 + p ]) < _Test2_trans_keys[1 + _mid ]
    _upper = _mid - 2;

elseif ( ( data[1 + p ]) > _Test2_trans_keys[1 + _mid + 1 ] )
    _lower = _mid + 2;

else
    begin
_trans += convert(Uint ,((_mid - _keys)>>1));
				@goto _match
end

end
end

end
_trans += convert(Uint ,_klen);
	end

end
@label _match
_ckeys = int(_Test2_trans_offsets[1 + _trans] );
	_klen = convert(Int ,_Test2_trans_lengths[1 + _trans]);
	_cond = convert(Uint ,_Test2_trans_offsets[1 + _trans]);

	_cpc = 0;
	@switch _Test2_trans_cond_spaces[1 + _trans]  begin
end
begin
_lower = 0
_mid = 0
_upper = 0
_lower = _ckeys;
		_upper = _ckeys + _klen - 1;
		while ( true  )
    begin
if _upper < _lower
    break;


end
_mid = _lower + ((_upper-_lower) >> 1);
			if _cpc < convert(Int ,_Test2_cond_keys[1 + _mid ])
    _upper = _mid - 1;

elseif ( _cpc > convert(Int ,_Test2_cond_keys[1 + _mid ]) )
    _lower = _mid + 1;

else
    begin
_cond += convert(Uint ,(_mid - _ckeys));
				@goto _match_cond
end

end
end

end
cs = 0;
		@goto _again
end
@label _match_cond
cs = convert(Int ,_Test2_cond_targs[1 + _cond]);

	if _Test2_cond_actions[1 + _cond] == 0
    @goto _again

end
_acts = int(_Test2_cond_actions[1 + _cond] );
	_nacts = convert(Uint ,_Test2_actions[1 + _acts ]); _acts += 1
;
	while ( _nacts > 0  )
    begin
@switch _Test2_actions[1 + _acts ] begin
@case 0
begin
mark=p
    end


	break;
	@case 1
begin
moabs_dict.id=data.data[mark+1:p]
    end


	break;
	@case 2
begin
mark=p
    end


	break;
	@case 3
begin
moabs_dict.start_pos= ASCIIString( data.data[mark+1:p])
    end


	break;
	@case 4
begin
mark=p
    end


	break;
	@case 5
begin
moabs_dict.stop_pos= ASCIIString( data.data[mark+1:p])
    end


	break;
	@case 6
begin
mark=p
    end


	break;
	@case 7
begin
moabs_dict.score=  ASCIIString( data.data[mark+1:p])
    end


	break;
	@case 8
begin
mark=p
    end


	break;
	@case 9
begin
moabs_dict.c_count=parseint( Int32, ASCIIString( data.data[mark+1:p]) )
    end


	break;
	@case 10
begin
mark=p
    end


	break;
	@case 11
begin
moabs_dict.t_count=parseint( Int32, ASCIIString( data.data[mark+1:p]) )
    end


	break;
	@case 12
begin
str=string( moabs_dict.id,".", moabs_dict.start_pos,".", moabs_dict.stop_pos )
       if !haskey( moabs_dict.coverdict, str)
           moabs_dict.coverdict[ str ] = moabs_dict.c_count + moabs_dict.t_count
       else
           moabs_dict.coverdict[ str ] += (moabs_dict.c_count + moabs_dict.t_count)
       end
    end


	break;
		end
_nacts -= 1
;
		_acts += 1
;
	end

end
@label _again
if cs == 0
    @goto _out

end
p += 1
;
	if p != pe
    @goto _resume

end
@label _test_eof
begin
end
@label _out
begin
end
end
return moabs_dict
end

end

