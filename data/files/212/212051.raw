macro c(ret_type, func, arg_types, lib)
    local args_in = Any[ symbol(string('a',x)) for x in 1:length(arg_types.args) ]
    quote
        $(esc(func))($(args_in...)) = ccall( ($(string(func)), $(Expr(:quote, lib)) ), $ret_type, $arg_types, $(args_in...) )
    end
end


# Skipping MacroDefinition: AV_GCC_VERSION_AT_LEAST(x,y)(__GNUC__>x||__GNUC__==x&&__GNUC_MINOR__>=y)
const av_always_inline = 
const av_extern_inline = 
const av_noinline = 
const av_pure = 
const av_const = 
const av_flatten = 
const attribute_deprecated = 
# Skipping MacroDefinition: AV_NOWARN_DEPRECATED(code)code
const av_unused = 
const av_used = 
const av_alias = 
# Skipping MacroDefinition: av_uninit(x)x
const av_builtin_constant_p = 
# Skipping MacroDefinition: av_printf_format(fmtpos,attrpos)__attribute__((__format__(__printf__,fmtpos,attrpos)))
const av_noreturn = 
# Skipping MacroDefinition: av_assert0(cond)do{if(!(cond)){av_log(NULL,AV_LOG_PANIC,"Assertion %s failed at %s:%d\n",AV_STRINGIFY(cond),__FILE__,__LINE__);abort();}\
# Skipping MacroDefinition: av_assert1(cond)((void)0)
# Skipping MacroDefinition: av_assert2(cond)((void)0)
const AV_HAVE_BIGENDIAN = 0
const AV_HAVE_FAST_UNALIGNED = 1
const AV_HAVE_INCOMPATIBLE_LIBAV_ABI = 0
const AV_HAVE_INCOMPATIBLE_FORK_ABI = 0
const AV_ESCAPE_FLAG_WHITESPACE = 0x01
const AV_ESCAPE_FLAG_STRICT = 0x02
# begin enum ANONYMOUS_10
typealias ANONYMOUS_10 Uint32
const AV_ESCAPE_MODE_AUTO = 0
const AV_ESCAPE_MODE_BACKSLASH = 1
const AV_ESCAPE_MODE_QUOTE = 2
# end enum ANONYMOUS_10
const FF_LAMBDA_SHIFT = 7
# Skipping MacroDefinition: FF_LAMBDA_SCALE(1<<FF_LAMBDA_SHIFT)
const FF_QP2LAMBDA = 118
# Skipping MacroDefinition: FF_LAMBDA_MAX(256*128-1)
const FF_QUALITY_SCALE = 
# Skipping MacroDefinition: AV_NOPTS_VALUE((int64_t)UINT64_C(0x8000000000000000))
const AV_TIME_BASE = 1000000
# Skipping MacroDefinition: AV_TIME_BASE_Q(AVRational){1,AV_TIME_BASE}
# Skipping MacroDefinition: av_int_list_length(list,term)av_int_list_length_for_size(sizeof(*(list)),list,term)
# begin enum ANONYMOUS_11
const AVMEDIA_TYPE_UNKNOWN = -1
const AVMEDIA_TYPE_VIDEO = 0
const AVMEDIA_TYPE_AUDIO = 1
const AVMEDIA_TYPE_DATA = 2
const AVMEDIA_TYPE_SUBTITLE = 3
const AVMEDIA_TYPE_ATTACHMENT = 4
const AVMEDIA_TYPE_NB = 5
# end enum ANONYMOUS_11
# begin enum ANONYMOUS_12
const AV_PICTURE_TYPE_NONE = 0
const AV_PICTURE_TYPE_I = 1
const AV_PICTURE_TYPE_P = 2
const AV_PICTURE_TYPE_B = 3
const AV_PICTURE_TYPE_S = 4
const AV_PICTURE_TYPE_SI = 5
const AV_PICTURE_TYPE_SP = 6
const AV_PICTURE_TYPE_BI = 7
# end enum ANONYMOUS_12
# Skipping MacroDefinition: AV_BASE64_SIZE(x)(((x)+2)/3*4+1)
const AV_BF_ROUNDS = 16
# Skipping MacroDefinition: FF_PAD_STRUCTURE(size,...)__VA_ARGS__charreserved_padding[size-sizeof(struct{__VA_ARGS__})];
# Skipping MacroDefinition: AV_BPRINT_SIZE_UNLIMITED((unsigned)-1)
const AV_BPRINT_SIZE_AUTOMATIC = 1
const AV_BPRINT_SIZE_COUNT_ONLY = 0
# Skipping MacroDefinition: AV_BSWAP16C(x)(((x)<<8&0xff00)|((x)>>8&0x00ff))
# Skipping MacroDefinition: AV_BSWAP32C(x)(AV_BSWAP16C(x)<<16|AV_BSWAP16C((x)>>16))
# Skipping MacroDefinition: AV_BSWAP64C(x)(AV_BSWAP32C(x)<<32|AV_BSWAP32C((x)>>32))
# Skipping MacroDefinition: AV_BSWAPC(s,x)AV_BSWAP##s##C(x)
# Skipping MacroDefinition: av_be2ne16(x)av_bswap16(x)
# Skipping MacroDefinition: av_be2ne32(x)av_bswap32(x)
# Skipping MacroDefinition: av_be2ne64(x)av_bswap64(x)
# Skipping MacroDefinition: av_le2ne16(x)(x)
# Skipping MacroDefinition: av_le2ne32(x)(x)
# Skipping MacroDefinition: av_le2ne64(x)(x)
# Skipping MacroDefinition: AV_BE2NEC(s,x)AV_BSWAPC(s,x)
# Skipping MacroDefinition: AV_LE2NEC(s,x)(x)
# Skipping MacroDefinition: AV_BE2NE16C(x)AV_BE2NEC(16,x)
# Skipping MacroDefinition: AV_BE2NE32C(x)AV_BE2NEC(32,x)
# Skipping MacroDefinition: AV_BE2NE64C(x)AV_BE2NEC(64,x)
# Skipping MacroDefinition: AV_LE2NE16C(x)AV_LE2NEC(16,x)
# Skipping MacroDefinition: AV_LE2NE32C(x)AV_LE2NEC(32,x)
# Skipping MacroDefinition: AV_LE2NE64C(x)AV_LE2NEC(64,x)
const AV_BUFFER_FLAG_READONLY = (1<<0)
const AV_CH_FRONT_LEFT = 0x00000001
const AV_CH_FRONT_RIGHT = 0x00000002
const AV_CH_FRONT_CENTER = 0x00000004
const AV_CH_LOW_FREQUENCY = 0x00000008
const AV_CH_BACK_LEFT = 0x00000010
const AV_CH_BACK_RIGHT = 0x00000020
const AV_CH_FRONT_LEFT_OF_CENTER = 0x00000040
const AV_CH_FRONT_RIGHT_OF_CENTER = 0x00000080
const AV_CH_BACK_CENTER = 0x00000100
const AV_CH_SIDE_LEFT = 0x00000200
const AV_CH_SIDE_RIGHT = 0x00000400
const AV_CH_TOP_CENTER = 0x00000800
const AV_CH_TOP_FRONT_LEFT = 0x00001000
const AV_CH_TOP_FRONT_CENTER = 0x00002000
const AV_CH_TOP_FRONT_RIGHT = 0x00004000
const AV_CH_TOP_BACK_LEFT = 0x00008000
const AV_CH_TOP_BACK_CENTER = 0x00010000
const AV_CH_TOP_BACK_RIGHT = 0x00020000
const AV_CH_STEREO_LEFT = 0x20000000
const AV_CH_STEREO_RIGHT = 0x40000000
const AV_CH_WIDE_LEFT = uint64(0x0000000080000000)
const AV_CH_WIDE_RIGHT = uint64(0x0000000100000000)
const AV_CH_SURROUND_DIRECT_LEFT = uint64(0x0000000200000000)
const AV_CH_SURROUND_DIRECT_RIGHT = uint64(0x0000000400000000)
const AV_CH_LOW_FREQUENCY_2 = uint64(0x0000000800000000)
const AV_CH_LAYOUT_NATIVE = uint64(0x8000000000000000)
# Skipping MacroDefinition: AV_CH_LAYOUT_MONO(AV_CH_FRONT_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_STEREO(AV_CH_FRONT_LEFT|AV_CH_FRONT_RIGHT)
# Skipping MacroDefinition: AV_CH_LAYOUT_2POINT1(AV_CH_LAYOUT_STEREO|AV_CH_LOW_FREQUENCY)
# Skipping MacroDefinition: AV_CH_LAYOUT_2_1(AV_CH_LAYOUT_STEREO|AV_CH_BACK_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_SURROUND(AV_CH_LAYOUT_STEREO|AV_CH_FRONT_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_3POINT1(AV_CH_LAYOUT_SURROUND|AV_CH_LOW_FREQUENCY)
# Skipping MacroDefinition: AV_CH_LAYOUT_4POINT0(AV_CH_LAYOUT_SURROUND|AV_CH_BACK_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_4POINT1(AV_CH_LAYOUT_4POINT0|AV_CH_LOW_FREQUENCY)
# Skipping MacroDefinition: AV_CH_LAYOUT_2_2(AV_CH_LAYOUT_STEREO|AV_CH_SIDE_LEFT|AV_CH_SIDE_RIGHT)
# Skipping MacroDefinition: AV_CH_LAYOUT_QUAD(AV_CH_LAYOUT_STEREO|AV_CH_BACK_LEFT|AV_CH_BACK_RIGHT)
# Skipping MacroDefinition: AV_CH_LAYOUT_5POINT0(AV_CH_LAYOUT_SURROUND|AV_CH_SIDE_LEFT|AV_CH_SIDE_RIGHT)
# Skipping MacroDefinition: AV_CH_LAYOUT_5POINT1(AV_CH_LAYOUT_5POINT0|AV_CH_LOW_FREQUENCY)
# Skipping MacroDefinition: AV_CH_LAYOUT_5POINT0_BACK(AV_CH_LAYOUT_SURROUND|AV_CH_BACK_LEFT|AV_CH_BACK_RIGHT)
# Skipping MacroDefinition: AV_CH_LAYOUT_5POINT1_BACK(AV_CH_LAYOUT_5POINT0_BACK|AV_CH_LOW_FREQUENCY)
# Skipping MacroDefinition: AV_CH_LAYOUT_6POINT0(AV_CH_LAYOUT_5POINT0|AV_CH_BACK_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_6POINT0_FRONT(AV_CH_LAYOUT_2_2|AV_CH_FRONT_LEFT_OF_CENTER|AV_CH_FRONT_RIGHT_OF_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_HEXAGONAL(AV_CH_LAYOUT_5POINT0_BACK|AV_CH_BACK_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_6POINT1(AV_CH_LAYOUT_5POINT1|AV_CH_BACK_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_6POINT1_BACK(AV_CH_LAYOUT_5POINT1_BACK|AV_CH_BACK_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_6POINT1_FRONT(AV_CH_LAYOUT_6POINT0_FRONT|AV_CH_LOW_FREQUENCY)
# Skipping MacroDefinition: AV_CH_LAYOUT_7POINT0(AV_CH_LAYOUT_5POINT0|AV_CH_BACK_LEFT|AV_CH_BACK_RIGHT)
# Skipping MacroDefinition: AV_CH_LAYOUT_7POINT0_FRONT(AV_CH_LAYOUT_5POINT0|AV_CH_FRONT_LEFT_OF_CENTER|AV_CH_FRONT_RIGHT_OF_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_7POINT1(AV_CH_LAYOUT_5POINT1|AV_CH_BACK_LEFT|AV_CH_BACK_RIGHT)
# Skipping MacroDefinition: AV_CH_LAYOUT_7POINT1_WIDE(AV_CH_LAYOUT_5POINT1|AV_CH_FRONT_LEFT_OF_CENTER|AV_CH_FRONT_RIGHT_OF_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_7POINT1_WIDE_BACK(AV_CH_LAYOUT_5POINT1_BACK|AV_CH_FRONT_LEFT_OF_CENTER|AV_CH_FRONT_RIGHT_OF_CENTER)
# Skipping MacroDefinition: AV_CH_LAYOUT_OCTAGONAL(AV_CH_LAYOUT_5POINT0|AV_CH_BACK_LEFT|AV_CH_BACK_CENTER|AV_CH_BACK_RIGHT)
# Skipping MacroDefinition: AV_CH_LAYOUT_STEREO_DOWNMIX(AV_CH_STEREO_LEFT|AV_CH_STEREO_RIGHT)
# begin enum ANONYMOUS_13
typealias ANONYMOUS_13 Uint32
const AV_MATRIX_ENCODING_NONE = 0
const AV_MATRIX_ENCODING_DOLBY = 1
const AV_MATRIX_ENCODING_DPLII = 2
const AV_MATRIX_ENCODING_NB = 3
# end enum ANONYMOUS_13
# Skipping MacroDefinition: AV_NE(be,le)(le)
# Skipping MacroDefinition: RSHIFT(a,b)((a)>0?((a)+((1<<(b))>>1))>>(b):((a)+((1<<(b))>>1)-1)>>(b))
# Skipping MacroDefinition: ROUNDED_DIV(a,b)(((a)>0?(a)+((b)>>1):(a)-((b)>>1))/(b))
# Skipping MacroDefinition: FF_CEIL_RSHIFT(a,b)(!av_builtin_constant_p(b)?-((-(a))>>(b)):((a)+(1<<(b))-1)>>(b))
# Skipping MacroDefinition: FFUDIV(a,b)(((a)>0?(a):(a)-(b)+1)/(b))
# Skipping MacroDefinition: FFUMOD(a,b)((a)-(b)*FFUDIV(a,b))
# Skipping MacroDefinition: FFABS(a)((a)>=0?(a):(-(a)))
# Skipping MacroDefinition: FFSIGN(a)((a)>0?1:-1)
# Skipping MacroDefinition: FFMAX(a,b)((a)>(b)?(a):(b))
# Skipping MacroDefinition: FFMAX3(a,b,c)FFMAX(FFMAX(a,b),c)
# Skipping MacroDefinition: FFMIN(a,b)((a)>(b)?(b):(a))
# Skipping MacroDefinition: FFMIN3(a,b,c)FFMIN(FFMIN(a,b),c)
# Skipping MacroDefinition: FFSWAP(type,a,b)do{typeSWAP_tmp=b;b=a;a=SWAP_tmp;}while(0)
# Skipping MacroDefinition: FF_ARRAY_ELEMS(a)(sizeof(a)/sizeof((a)[0]))
# Skipping MacroDefinition: FFALIGN(x,a)(((x)+(a)-1)&~((a)-1))
const av_ceil_log2 = 
const av_clip = 
const av_clip64 = 
const av_clip_uint8 = 
const av_clip_int8 = 
const av_clip_uint16 = 
const av_clip_int16 = 
const av_clipl_int32 = 
const av_clip_uintp2 = 
const av_sat_add32 = 
const av_sat_dadd32 = 
const av_clipf = 
const av_clipd = 
const av_popcount = 
const av_popcount64 = 
# Skipping MacroDefinition: MKTAG(a,b,c,d)((a)|((b)<<8)|((c)<<16)|((unsigned)(d)<<24))
# Skipping MacroDefinition: MKBETAG(a,b,c,d)((d)|((c)<<8)|((b)<<16)|((unsigned)(a)<<24))
# Skipping MacroDefinition: GET_UTF8(val,GET_BYTE,ERROR)val=GET_BYTE;{uint32_ttop=(val&128)>>1;if((val&0xc0)==0x80||val>=0xFE)ERRORwhile(val&top){inttmp=GET_BYTE-128;if(tmp>>6)ERRORval=(val<<6)+tmp;top<<=5;}val&=(top<<1)-1;}
# Skipping MacroDefinition: GET_UTF16(val,GET_16BIT,ERROR)val=GET_16BIT;{unsignedinthi=val-0xD800;if(hi<0x800){val=GET_16BIT-0xDC00;if(val>0x3FFU||hi>0x3FFU)ERRORval+=(hi<<10)+0x10000;}}
# Skipping MacroDefinition: PUT_UTF8(val,tmp,PUT_BYTE){intbytes,shift;uint32_tin=val;if(in<0x80){tmp=in;PUT_BYTE}else{bytes=(av_log2(in)+4)/5;shift=(bytes-1)*6;tmp=(256-(256>>bytes))|(in>>shift);PUT_BYTEwhile(shift>=6){shift-=6;tmp=0x80|((in>>shift)&0x3f);PUT_BYTE}}}
# Skipping MacroDefinition: PUT_UTF16(val,tmp,PUT_16BIT){uint32_tin=val;if(in<0x10000){tmp=in;PUT_16BIT}else{tmp=0xD800|((in-0x10000)>>10);PUT_16BITtmp=0xDC00|((in-0x10000)&0x3FF);PUT_16BIT}}
const AV_CPU_FLAG_FORCE = 0x80000000
const AV_CPU_FLAG_MMX = 0x0001
const AV_CPU_FLAG_MMXEXT = 0x0002
const AV_CPU_FLAG_MMX2 = 0x0002
const AV_CPU_FLAG_3DNOW = 0x0004
const AV_CPU_FLAG_SSE = 0x0008
const AV_CPU_FLAG_SSE2 = 0x0010
const AV_CPU_FLAG_SSE2SLOW = 0x40000000
const AV_CPU_FLAG_3DNOWEXT = 0x0020
const AV_CPU_FLAG_SSE3 = 0x0040
const AV_CPU_FLAG_SSE3SLOW = 0x20000000
const AV_CPU_FLAG_SSSE3 = 0x0080
const AV_CPU_FLAG_ATOM = 0x10000000
const AV_CPU_FLAG_SSE4 = 0x0100
const AV_CPU_FLAG_SSE42 = 0x0200
const AV_CPU_FLAG_AVX = 0x4000
const AV_CPU_FLAG_XOP = 0x0400
const AV_CPU_FLAG_FMA4 = 0x0800
const AV_CPU_FLAG_CMOV = 0x1001000
const AV_CPU_FLAG_AVX2 = 0x8000
const AV_CPU_FLAG_ALTIVEC = 0x0001
const AV_CPU_FLAG_ARMV5TE = (1<<0)
const AV_CPU_FLAG_ARMV6 = (1<<1)
const AV_CPU_FLAG_ARMV6T2 = (1<<2)
const AV_CPU_FLAG_VFP = (1<<3)
const AV_CPU_FLAG_VFPV3 = (1<<4)
const AV_CPU_FLAG_NEON = (1<<5)
# begin enum ANONYMOUS_14
typealias ANONYMOUS_14 Uint32
const AV_CRC_8_ATM = 0
const AV_CRC_16_ANSI = 1
const AV_CRC_16_CCITT = 2
const AV_CRC_32_IEEE = 3
const AV_CRC_32_IEEE_LE = 4
const AV_CRC_24_IEEE = 12
const AV_CRC_MAX = 13
# end enum ANONYMOUS_14
# begin enum AVCRCId
typealias AVCRCId Uint32
const AV_CRC_8_ATM = 0
const AV_CRC_16_ANSI = 1
const AV_CRC_16_CCITT = 2
const AV_CRC_32_IEEE = 3
const AV_CRC_32_IEEE_LE = 4
const AV_CRC_24_IEEE = 12
const AV_CRC_MAX = 13
# end enum AVCRCId
const AV_DICT_MATCH_CASE = 1
const AV_DICT_IGNORE_SUFFIX = 2
const AV_DICT_DONT_STRDUP_KEY = 4
const AV_DICT_DONT_STRDUP_VAL = 8
const AV_DICT_DONT_OVERWRITE = 16
const AV_DICT_APPEND = 32
# Skipping MacroDefinition: AVERROR(e)(-(e))
# Skipping MacroDefinition: AVUNERROR(e)(-(e))
# Skipping MacroDefinition: FFERRTAG(a,b,c,d)(-(int)MKTAG(a,b,c,d))
const AVERROR_EXPERIMENTAL = (-0x2bb2afa8)
const AV_ERROR_MAX_STRING_SIZE = 64
# Skipping MacroDefinition: av_err2str(errnum)av_make_error_string((char[AV_ERROR_MAX_STRING_SIZE]){0},AV_ERROR_MAX_STRING_SIZE,errnum)
const AVCOL_SPC_YCGCO = 
const AV_NUM_DATA_POINTERS = 8
const FF_DECODE_ERROR_INVALID_BITSTREAM = 1
const FF_DECODE_ERROR_MISSING_REFERENCE = 2
# begin enum ANONYMOUS_15
typealias ANONYMOUS_15 Uint32
const AVCOL_SPC_RGB = 0
const AVCOL_SPC_BT709 = 1
const AVCOL_SPC_UNSPECIFIED = 2
const AVCOL_SPC_FCC = 4
const AVCOL_SPC_BT470BG = 5
const AVCOL_SPC_SMPTE170M = 6
const AVCOL_SPC_SMPTE240M = 7
const AVCOL_SPC_YCOCG = 8
const AVCOL_SPC_NB = 9
# end enum ANONYMOUS_15
# begin enum ANONYMOUS_16
typealias ANONYMOUS_16 Uint32
const AVCOL_RANGE_UNSPECIFIED = 0
const AVCOL_RANGE_MPEG = 1
const AVCOL_RANGE_JPEG = 2
const AVCOL_RANGE_NB = 3
# end enum ANONYMOUS_16
# begin enum ANONYMOUS_17
typealias ANONYMOUS_17 Uint32
const AV_FRAME_DATA_PANSCAN = 0
# end enum ANONYMOUS_17
# begin enum ANONYMOUS_18
typealias ANONYMOUS_18 Uint32
const AV_HMAC_MD5 = 0
const AV_HMAC_SHA1 = 1
const AV_HMAC_SHA224 = 10
const AV_HMAC_SHA256 = 11
const AV_HMAC_SHA384 = 12
const AV_HMAC_SHA512 = 13
# end enum ANONYMOUS_18
const AV_LOG_QUIET = -8
const AV_LOG_PANIC = 0
const AV_LOG_FATAL = 8
const AV_LOG_ERROR = 16
const AV_LOG_WARNING = 24
const AV_LOG_INFO = 32
const AV_LOG_VERBOSE = 40
const AV_LOG_DEBUG = 48
# Skipping MacroDefinition: AV_LOG_MAX_OFFSET(AV_LOG_DEBUG-AV_LOG_QUIET)
# Skipping MacroDefinition: av_dlog(pctx,...)do{if(0)av_log(pctx,AV_LOG_DEBUG,__VA_ARGS__);}while(0)
const AV_LOG_SKIP_REPEATED = 1
# begin enum ANONYMOUS_19
typealias ANONYMOUS_19 Uint32
const AV_CLASS_CATEGORY_NA = 0
const AV_CLASS_CATEGORY_INPUT = 1
const AV_CLASS_CATEGORY_OUTPUT = 2
const AV_CLASS_CATEGORY_MUXER = 3
const AV_CLASS_CATEGORY_DEMUXER = 4
const AV_CLASS_CATEGORY_ENCODER = 5
const AV_CLASS_CATEGORY_DECODER = 6
const AV_CLASS_CATEGORY_FILTER = 7
const AV_CLASS_CATEGORY_BITSTREAM_FILTER = 8
const AV_CLASS_CATEGORY_SWSCALER = 9
const AV_CLASS_CATEGORY_SWRESAMPLER = 10
const AV_CLASS_CATEGORY_NB = 11
# end enum ANONYMOUS_19
# begin enum AVClassCategory
typealias AVClassCategory Uint32
const AV_CLASS_CATEGORY_NA = 0
const AV_CLASS_CATEGORY_INPUT = 1
const AV_CLASS_CATEGORY_OUTPUT = 2
const AV_CLASS_CATEGORY_MUXER = 3
const AV_CLASS_CATEGORY_DEMUXER = 4
const AV_CLASS_CATEGORY_ENCODER = 5
const AV_CLASS_CATEGORY_DECODER = 6
const AV_CLASS_CATEGORY_FILTER = 7
const AV_CLASS_CATEGORY_BITSTREAM_FILTER = 8
const AV_CLASS_CATEGORY_SWSCALER = 9
const AV_CLASS_CATEGORY_SWRESAMPLER = 10
const AV_CLASS_CATEGORY_NB = 11
# end enum AVClassCategory
const AV_LZO_INPUT_DEPLETED = 1
const AV_LZO_OUTPUT_FULL = 2
const AV_LZO_INVALID_BACKPTR = 4
const AV_LZO_ERROR = 8
const AV_LZO_INPUT_PADDING = 8
const AV_LZO_OUTPUT_PADDING = 12
const M_LOG2_10 = 3.32192809488736234787
const M_PHI = 1.61803398874989484820
# begin enum ANONYMOUS_20
typealias ANONYMOUS_20 Uint32
const AV_ROUND_ZERO = 0
const AV_ROUND_INF = 1
const AV_ROUND_DOWN = 2
const AV_ROUND_UP = 3
const AV_ROUND_NEAR_INF = 5
const AV_ROUND_PASS_MINMAX = 8192
# end enum ANONYMOUS_20
# Skipping MacroDefinition: DECLARE_ALIGNED(n,t,v)t__attribute__((aligned(n)))v
# Skipping MacroDefinition: DECLARE_ASM_CONST(n,t,v)staticconsttav_used__attribute__((aligned(n)))v
const av_malloc_attrib = 
# Skipping MacroDefinition: av_alloc_size(...)
const AV_OPT_FLAG_ENCODING_PARAM = 1
const AV_OPT_FLAG_DECODING_PARAM = 2
const AV_OPT_FLAG_METADATA = 4
const AV_OPT_FLAG_AUDIO_PARAM = 8
const AV_OPT_FLAG_VIDEO_PARAM = 16
const AV_OPT_FLAG_SUBTITLE_PARAM = 32
const AV_OPT_FLAG_FILTERING_PARAM = (1<<16)
const AV_OPT_SEARCH_CHILDREN = 0x0001
const AV_OPT_SEARCH_FAKE_OBJ = 0x0002
# Skipping MacroDefinition: av_opt_set_int_list(obj,name,val,term,flags)(av_int_list_length(val,term)>INT_MAX/sizeof(*(val))?AVERROR(EINVAL):av_opt_set_bin(obj,name,(constuint8_t*)(val),av_int_list_length(val,term)*sizeof(*(val)),flags))
# begin enum ANONYMOUS_21
typealias ANONYMOUS_21 Uint32
const AV_OPT_TYPE_FLAGS = 0
const AV_OPT_TYPE_INT = 1
const AV_OPT_TYPE_INT64 = 2
const AV_OPT_TYPE_DOUBLE = 3
const AV_OPT_TYPE_FLOAT = 4
const AV_OPT_TYPE_STRING = 5
const AV_OPT_TYPE_RATIONAL = 6
const AV_OPT_TYPE_BINARY = 7
const AV_OPT_TYPE_CONST = 128
const AV_OPT_TYPE_IMAGE_SIZE = 1397316165
const AV_OPT_TYPE_PIXEL_FMT = 1346784596
const AV_OPT_TYPE_SAMPLE_FMT = 1397116244
const AV_OPT_TYPE_VIDEO_RATE = 1448231252
const AV_OPT_TYPE_DURATION = 1146442272
const AV_OPT_TYPE_COLOR = 1129270354
const AV_OPT_TYPE_CHANNEL_LAYOUT = 1128811585
const FF_OPT_TYPE_FLAGS = 0
const FF_OPT_TYPE_INT = 1
const FF_OPT_TYPE_INT64 = 2
const FF_OPT_TYPE_DOUBLE = 3
const FF_OPT_TYPE_FLOAT = 4
const FF_OPT_TYPE_STRING = 5
const FF_OPT_TYPE_RATIONAL = 6
const FF_OPT_TYPE_BINARY = 7
const FF_OPT_TYPE_CONST = 128
# end enum ANONYMOUS_21
# begin enum ANONYMOUS_22
typealias ANONYMOUS_22 Uint32
const AV_OPT_FLAG_IMPLICIT_KEY = 1
# end enum ANONYMOUS_22
# Skipping MacroDefinition: av_parse_ratio_quiet(rate,str,max)av_parse_ratio(rate,str,max,AV_LOG_MAX_OFFSET,NULL)
const AV_PIX_FMT_FLAG_BE = (1<<0)
const AV_PIX_FMT_FLAG_PAL = (1<<1)
const AV_PIX_FMT_FLAG_BITSTREAM = (1<<2)
const AV_PIX_FMT_FLAG_HWACCEL = (1<<3)
const AV_PIX_FMT_FLAG_PLANAR = (1<<4)
const AV_PIX_FMT_FLAG_RGB = (1<<5)
const AV_PIX_FMT_FLAG_PSEUDOPAL = (1<<6)
const AV_PIX_FMT_FLAG_ALPHA = (1<<7)
const PIX_FMT_BE = 
const PIX_FMT_PAL = 
const PIX_FMT_BITSTREAM = 
const PIX_FMT_HWACCEL = 
const PIX_FMT_PLANAR = 
const PIX_FMT_RGB = 
const PIX_FMT_PSEUDOPAL = 
const PIX_FMT_ALPHA = 
const AVPALETTE_SIZE = 1024
const AVPALETTE_COUNT = 256
const AV_PIX_FMT_Y400A = 
const AV_PIX_FMT_GBR24P = 
# Skipping MacroDefinition: AV_PIX_FMT_NE(be,le)AV_PIX_FMT_##le
const AV_PIX_FMT_RGB32 = 
const AV_PIX_FMT_RGB32_1 = 
const AV_PIX_FMT_BGR32 = 
const AV_PIX_FMT_BGR32_1 = 
const AV_PIX_FMT_0RGB32 = 
const AV_PIX_FMT_0BGR32 = 
const AV_PIX_FMT_GRAY16 = 
const AV_PIX_FMT_RGB48 = 
const AV_PIX_FMT_RGB565 = 
const AV_PIX_FMT_RGB555 = 
const AV_PIX_FMT_RGB444 = 
const AV_PIX_FMT_BGR48 = 
const AV_PIX_FMT_BGR565 = 
const AV_PIX_FMT_BGR555 = 
const AV_PIX_FMT_BGR444 = 
const AV_PIX_FMT_YUV420P9 = 
const AV_PIX_FMT_YUV422P9 = 
const AV_PIX_FMT_YUV444P9 = 
const AV_PIX_FMT_YUV420P10 = 
const AV_PIX_FMT_YUV422P10 = 
const AV_PIX_FMT_YUV444P10 = 
const AV_PIX_FMT_YUV420P12 = 
const AV_PIX_FMT_YUV422P12 = 
const AV_PIX_FMT_YUV444P12 = 
const AV_PIX_FMT_YUV420P14 = 
const AV_PIX_FMT_YUV422P14 = 
const AV_PIX_FMT_YUV444P14 = 
const AV_PIX_FMT_YUV420P16 = 
const AV_PIX_FMT_YUV422P16 = 
const AV_PIX_FMT_YUV444P16 = 
const AV_PIX_FMT_RGBA64 = 
const AV_PIX_FMT_BGRA64 = 
const AV_PIX_FMT_GBRP9 = 
const AV_PIX_FMT_GBRP10 = 
const AV_PIX_FMT_GBRP12 = 
const AV_PIX_FMT_GBRP14 = 
const AV_PIX_FMT_GBRP16 = 
const AV_PIX_FMT_GBRAP16 = 
const AV_PIX_FMT_BAYER_BGGR16 = 
const AV_PIX_FMT_BAYER_RGGB16 = 
const AV_PIX_FMT_BAYER_GBRG16 = 
const AV_PIX_FMT_BAYER_GRBG16 = 
const AV_PIX_FMT_YUVA420P9 = 
const AV_PIX_FMT_YUVA422P9 = 
const AV_PIX_FMT_YUVA444P9 = 
const AV_PIX_FMT_YUVA420P10 = 
const AV_PIX_FMT_YUVA422P10 = 
const AV_PIX_FMT_YUVA444P10 = 
const AV_PIX_FMT_YUVA420P16 = 
const AV_PIX_FMT_YUVA422P16 = 
const AV_PIX_FMT_YUVA444P16 = 
const AV_PIX_FMT_XYZ12 = 
const AV_PIX_FMT_NV20 = 
const PixelFormat = 
const PIX_FMT_Y400A = 
const PIX_FMT_GBR24P = 
# Skipping MacroDefinition: PIX_FMT_NE(be,le)AV_PIX_FMT_NE(be,le)
const PIX_FMT_RGB32 = 
const PIX_FMT_RGB32_1 = 
const PIX_FMT_BGR32 = 
const PIX_FMT_BGR32_1 = 
const PIX_FMT_0RGB32 = 
const PIX_FMT_0BGR32 = 
const PIX_FMT_GRAY16 = 
const PIX_FMT_RGB48 = 
const PIX_FMT_RGB565 = 
const PIX_FMT_RGB555 = 
const PIX_FMT_RGB444 = 
const PIX_FMT_BGR48 = 
const PIX_FMT_BGR565 = 
const PIX_FMT_BGR555 = 
const PIX_FMT_BGR444 = 
const PIX_FMT_YUV420P9 = 
const PIX_FMT_YUV422P9 = 
const PIX_FMT_YUV444P9 = 
const PIX_FMT_YUV420P10 = 
const PIX_FMT_YUV422P10 = 
const PIX_FMT_YUV444P10 = 
const PIX_FMT_YUV420P12 = 
const PIX_FMT_YUV422P12 = 
const PIX_FMT_YUV444P12 = 
const PIX_FMT_YUV420P14 = 
const PIX_FMT_YUV422P14 = 
const PIX_FMT_YUV444P14 = 
const PIX_FMT_YUV420P16 = 
const PIX_FMT_YUV422P16 = 
const PIX_FMT_YUV444P16 = 
const PIX_FMT_RGBA64 = 
const PIX_FMT_BGRA64 = 
const PIX_FMT_GBRP9 = 
const PIX_FMT_GBRP10 = 
const PIX_FMT_GBRP12 = 
const PIX_FMT_GBRP14 = 
const PIX_FMT_GBRP16 = 
# begin enum ANONYMOUS_23
typealias ANONYMOUS_23 Cint
const AV_PIX_FMT_NONE = -1
const AV_PIX_FMT_YUV420P = 0
const AV_PIX_FMT_YUYV422 = 1
const AV_PIX_FMT_RGB24 = 2
const AV_PIX_FMT_BGR24 = 3
const AV_PIX_FMT_YUV422P = 4
const AV_PIX_FMT_YUV444P = 5
const AV_PIX_FMT_YUV410P = 6
const AV_PIX_FMT_YUV411P = 7
const AV_PIX_FMT_GRAY8 = 8
const AV_PIX_FMT_MONOWHITE = 9
const AV_PIX_FMT_MONOBLACK = 10
const AV_PIX_FMT_PAL8 = 11
const AV_PIX_FMT_YUVJ420P = 12
const AV_PIX_FMT_YUVJ422P = 13
const AV_PIX_FMT_YUVJ444P = 14
const AV_PIX_FMT_XVMC_MPEG2_MC = 15
const AV_PIX_FMT_XVMC_MPEG2_IDCT = 16
const AV_PIX_FMT_UYVY422 = 17
const AV_PIX_FMT_UYYVYY411 = 18
const AV_PIX_FMT_BGR8 = 19
const AV_PIX_FMT_BGR4 = 20
const AV_PIX_FMT_BGR4_BYTE = 21
const AV_PIX_FMT_RGB8 = 22
const AV_PIX_FMT_RGB4 = 23
const AV_PIX_FMT_RGB4_BYTE = 24
const AV_PIX_FMT_NV12 = 25
const AV_PIX_FMT_NV21 = 26
const AV_PIX_FMT_ARGB = 27
const AV_PIX_FMT_RGBA = 28
const AV_PIX_FMT_ABGR = 29
const AV_PIX_FMT_BGRA = 30
const AV_PIX_FMT_GRAY16BE = 31
const AV_PIX_FMT_GRAY16LE = 32
const AV_PIX_FMT_YUV440P = 33
const AV_PIX_FMT_YUVJ440P = 34
const AV_PIX_FMT_YUVA420P = 35
const AV_PIX_FMT_VDPAU_H264 = 36
const AV_PIX_FMT_VDPAU_MPEG1 = 37
const AV_PIX_FMT_VDPAU_MPEG2 = 38
const AV_PIX_FMT_VDPAU_WMV3 = 39
const AV_PIX_FMT_VDPAU_VC1 = 40
const AV_PIX_FMT_RGB48BE = 41
const AV_PIX_FMT_RGB48LE = 42
const AV_PIX_FMT_RGB565BE = 43
const AV_PIX_FMT_RGB565LE = 44
const AV_PIX_FMT_RGB555BE = 45
const AV_PIX_FMT_RGB555LE = 46
const AV_PIX_FMT_BGR565BE = 47
const AV_PIX_FMT_BGR565LE = 48
const AV_PIX_FMT_BGR555BE = 49
const AV_PIX_FMT_BGR555LE = 50
const AV_PIX_FMT_VAAPI_MOCO = 51
const AV_PIX_FMT_VAAPI_IDCT = 52
const AV_PIX_FMT_VAAPI_VLD = 53
const AV_PIX_FMT_YUV420P16LE = 54
const AV_PIX_FMT_YUV420P16BE = 55
const AV_PIX_FMT_YUV422P16LE = 56
const AV_PIX_FMT_YUV422P16BE = 57
const AV_PIX_FMT_YUV444P16LE = 58
const AV_PIX_FMT_YUV444P16BE = 59
const AV_PIX_FMT_VDPAU_MPEG4 = 60
const AV_PIX_FMT_DXVA2_VLD = 61
const AV_PIX_FMT_RGB444LE = 62
const AV_PIX_FMT_RGB444BE = 63
const AV_PIX_FMT_BGR444LE = 64
const AV_PIX_FMT_BGR444BE = 65
const AV_PIX_FMT_GRAY8A = 66
const AV_PIX_FMT_BGR48BE = 67
const AV_PIX_FMT_BGR48LE = 68
const AV_PIX_FMT_YUV420P9BE = 69
const AV_PIX_FMT_YUV420P9LE = 70
const AV_PIX_FMT_YUV420P10BE = 71
const AV_PIX_FMT_YUV420P10LE = 72
const AV_PIX_FMT_YUV422P10BE = 73
const AV_PIX_FMT_YUV422P10LE = 74
const AV_PIX_FMT_YUV444P9BE = 75
const AV_PIX_FMT_YUV444P9LE = 76
const AV_PIX_FMT_YUV444P10BE = 77
const AV_PIX_FMT_YUV444P10LE = 78
const AV_PIX_FMT_YUV422P9BE = 79
const AV_PIX_FMT_YUV422P9LE = 80
const AV_PIX_FMT_VDA_VLD = 81
const AV_PIX_FMT_GBRP = 82
const AV_PIX_FMT_GBRP9BE = 83
const AV_PIX_FMT_GBRP9LE = 84
const AV_PIX_FMT_GBRP10BE = 85
const AV_PIX_FMT_GBRP10LE = 86
const AV_PIX_FMT_GBRP16BE = 87
const AV_PIX_FMT_GBRP16LE = 88
const AV_PIX_FMT_YUVA422P_LIBAV = 89
const AV_PIX_FMT_YUVA444P_LIBAV = 90
const AV_PIX_FMT_YUVA420P9BE = 91
const AV_PIX_FMT_YUVA420P9LE = 92
const AV_PIX_FMT_YUVA422P9BE = 93
const AV_PIX_FMT_YUVA422P9LE = 94
const AV_PIX_FMT_YUVA444P9BE = 95
const AV_PIX_FMT_YUVA444P9LE = 96
const AV_PIX_FMT_YUVA420P10BE = 97
const AV_PIX_FMT_YUVA420P10LE = 98
const AV_PIX_FMT_YUVA422P10BE = 99
const AV_PIX_FMT_YUVA422P10LE = 100
const AV_PIX_FMT_YUVA444P10BE = 101
const AV_PIX_FMT_YUVA444P10LE = 102
const AV_PIX_FMT_YUVA420P16BE = 103
const AV_PIX_FMT_YUVA420P16LE = 104
const AV_PIX_FMT_YUVA422P16BE = 105
const AV_PIX_FMT_YUVA422P16LE = 106
const AV_PIX_FMT_YUVA444P16BE = 107
const AV_PIX_FMT_YUVA444P16LE = 108
const AV_PIX_FMT_VDPAU = 109
const AV_PIX_FMT_XYZ12LE = 110
const AV_PIX_FMT_XYZ12BE = 111
const AV_PIX_FMT_NV16 = 112
const AV_PIX_FMT_NV20LE = 113
const AV_PIX_FMT_NV20BE = 114
const AV_PIX_FMT_RGBA64BE = 291
const AV_PIX_FMT_RGBA64LE = 292
const AV_PIX_FMT_BGRA64BE = 293
const AV_PIX_FMT_BGRA64LE = 294
const AV_PIX_FMT_0RGB = 295
const AV_PIX_FMT_RGB0 = 296
const AV_PIX_FMT_0BGR = 297
const AV_PIX_FMT_BGR0 = 298
const AV_PIX_FMT_YUVA444P = 299
const AV_PIX_FMT_YUVA422P = 300
const AV_PIX_FMT_YUV420P12BE = 301
const AV_PIX_FMT_YUV420P12LE = 302
const AV_PIX_FMT_YUV420P14BE = 303
const AV_PIX_FMT_YUV420P14LE = 304
const AV_PIX_FMT_YUV422P12BE = 305
const AV_PIX_FMT_YUV422P12LE = 306
const AV_PIX_FMT_YUV422P14BE = 307
const AV_PIX_FMT_YUV422P14LE = 308
const AV_PIX_FMT_YUV444P12BE = 309
const AV_PIX_FMT_YUV444P12LE = 310
const AV_PIX_FMT_YUV444P14BE = 311
const AV_PIX_FMT_YUV444P14LE = 312
const AV_PIX_FMT_GBRP12BE = 313
const AV_PIX_FMT_GBRP12LE = 314
const AV_PIX_FMT_GBRP14BE = 315
const AV_PIX_FMT_GBRP14LE = 316
const AV_PIX_FMT_GBRAP = 317
const AV_PIX_FMT_GBRAP16BE = 318
const AV_PIX_FMT_GBRAP16LE = 319
const AV_PIX_FMT_YUVJ411P = 320
const AV_PIX_FMT_BAYER_BGGR8 = 321
const AV_PIX_FMT_BAYER_RGGB8 = 322
const AV_PIX_FMT_BAYER_GBRG8 = 323
const AV_PIX_FMT_BAYER_GRBG8 = 324
const AV_PIX_FMT_BAYER_BGGR16LE = 325
const AV_PIX_FMT_BAYER_BGGR16BE = 326
const AV_PIX_FMT_BAYER_RGGB16LE = 327
const AV_PIX_FMT_BAYER_RGGB16BE = 328
const AV_PIX_FMT_BAYER_GBRG16LE = 329
const AV_PIX_FMT_BAYER_GBRG16BE = 330
const AV_PIX_FMT_BAYER_GRBG16LE = 331
const AV_PIX_FMT_BAYER_GRBG16BE = 332
const AV_PIX_FMT_NB = 333
const PIX_FMT_NONE = -1
const PIX_FMT_YUV420P = 0
const PIX_FMT_YUYV422 = 1
const PIX_FMT_RGB24 = 2
const PIX_FMT_BGR24 = 3
const PIX_FMT_YUV422P = 4
const PIX_FMT_YUV444P = 5
const PIX_FMT_YUV410P = 6
const PIX_FMT_YUV411P = 7
const PIX_FMT_GRAY8 = 8
const PIX_FMT_MONOWHITE = 9
const PIX_FMT_MONOBLACK = 10
const PIX_FMT_PAL8 = 11
const PIX_FMT_YUVJ420P = 12
const PIX_FMT_YUVJ422P = 13
const PIX_FMT_YUVJ444P = 14
const PIX_FMT_XVMC_MPEG2_MC = 15
const PIX_FMT_XVMC_MPEG2_IDCT = 16
const PIX_FMT_UYVY422 = 17
const PIX_FMT_UYYVYY411 = 18
const PIX_FMT_BGR8 = 19
const PIX_FMT_BGR4 = 20
const PIX_FMT_BGR4_BYTE = 21
const PIX_FMT_RGB8 = 22
const PIX_FMT_RGB4 = 23
const PIX_FMT_RGB4_BYTE = 24
const PIX_FMT_NV12 = 25
const PIX_FMT_NV21 = 26
const PIX_FMT_ARGB = 27
const PIX_FMT_RGBA = 28
const PIX_FMT_ABGR = 29
const PIX_FMT_BGRA = 30
const PIX_FMT_GRAY16BE = 31
const PIX_FMT_GRAY16LE = 32
const PIX_FMT_YUV440P = 33
const PIX_FMT_YUVJ440P = 34
const PIX_FMT_YUVA420P = 35
const PIX_FMT_VDPAU_H264 = 36
const PIX_FMT_VDPAU_MPEG1 = 37
const PIX_FMT_VDPAU_MPEG2 = 38
const PIX_FMT_VDPAU_WMV3 = 39
const PIX_FMT_VDPAU_VC1 = 40
const PIX_FMT_RGB48BE = 41
const PIX_FMT_RGB48LE = 42
const PIX_FMT_RGB565BE = 43
const PIX_FMT_RGB565LE = 44
const PIX_FMT_RGB555BE = 45
const PIX_FMT_RGB555LE = 46
const PIX_FMT_BGR565BE = 47
const PIX_FMT_BGR565LE = 48
const PIX_FMT_BGR555BE = 49
const PIX_FMT_BGR555LE = 50
const PIX_FMT_VAAPI_MOCO = 51
const PIX_FMT_VAAPI_IDCT = 52
const PIX_FMT_VAAPI_VLD = 53
const PIX_FMT_YUV420P16LE = 54
const PIX_FMT_YUV420P16BE = 55
const PIX_FMT_YUV422P16LE = 56
const PIX_FMT_YUV422P16BE = 57
const PIX_FMT_YUV444P16LE = 58
const PIX_FMT_YUV444P16BE = 59
const PIX_FMT_VDPAU_MPEG4 = 60
const PIX_FMT_DXVA2_VLD = 61
const PIX_FMT_RGB444LE = 62
const PIX_FMT_RGB444BE = 63
const PIX_FMT_BGR444LE = 64
const PIX_FMT_BGR444BE = 65
const PIX_FMT_GRAY8A = 66
const PIX_FMT_BGR48BE = 67
const PIX_FMT_BGR48LE = 68
const PIX_FMT_YUV420P9BE = 69
const PIX_FMT_YUV420P9LE = 70
const PIX_FMT_YUV420P10BE = 71
const PIX_FMT_YUV420P10LE = 72
const PIX_FMT_YUV422P10BE = 73
const PIX_FMT_YUV422P10LE = 74
const PIX_FMT_YUV444P9BE = 75
const PIX_FMT_YUV444P9LE = 76
const PIX_FMT_YUV444P10BE = 77
const PIX_FMT_YUV444P10LE = 78
const PIX_FMT_YUV422P9BE = 79
const PIX_FMT_YUV422P9LE = 80
const PIX_FMT_VDA_VLD = 81
const PIX_FMT_GBRP = 82
const PIX_FMT_GBRP9BE = 83
const PIX_FMT_GBRP9LE = 84
const PIX_FMT_GBRP10BE = 85
const PIX_FMT_GBRP10LE = 86
const PIX_FMT_GBRP16BE = 87
const PIX_FMT_GBRP16LE = 88
const PIX_FMT_RGBA64BE = 291
const PIX_FMT_RGBA64LE = 292
const PIX_FMT_BGRA64BE = 293
const PIX_FMT_BGRA64LE = 294
const PIX_FMT_0RGB = 295
const PIX_FMT_RGB0 = 296
const PIX_FMT_0BGR = 297
const PIX_FMT_BGR0 = 298
const PIX_FMT_YUVA444P = 299
const PIX_FMT_YUVA422P = 300
const PIX_FMT_YUV420P12BE = 301
const PIX_FMT_YUV420P12LE = 302
const PIX_FMT_YUV420P14BE = 303
const PIX_FMT_YUV420P14LE = 304
const PIX_FMT_YUV422P12BE = 305
const PIX_FMT_YUV422P12LE = 306
const PIX_FMT_YUV422P14BE = 307
const PIX_FMT_YUV422P14LE = 308
const PIX_FMT_YUV444P12BE = 309
const PIX_FMT_YUV444P12LE = 310
const PIX_FMT_YUV444P14BE = 311
const PIX_FMT_YUV444P14LE = 312
const PIX_FMT_GBRP12BE = 313
const PIX_FMT_GBRP12LE = 314
const PIX_FMT_GBRP14BE = 315
const PIX_FMT_GBRP14LE = 316
const PIX_FMT_NB = 317
# end enum ANONYMOUS_23
# begin enum ANONYMOUS_24
typealias ANONYMOUS_24 Cint
const AV_SAMPLE_FMT_NONE = -1
const AV_SAMPLE_FMT_U8 = 0
const AV_SAMPLE_FMT_S16 = 1
const AV_SAMPLE_FMT_S32 = 2
const AV_SAMPLE_FMT_FLT = 3
const AV_SAMPLE_FMT_DBL = 4
const AV_SAMPLE_FMT_U8P = 5
const AV_SAMPLE_FMT_S16P = 6
const AV_SAMPLE_FMT_S32P = 7
const AV_SAMPLE_FMT_FLTP = 8
const AV_SAMPLE_FMT_DBLP = 9
const AV_SAMPLE_FMT_NB = 10
# end enum ANONYMOUS_24
const AV_TIMECODE_STR_SIZE = 16
# begin enum ANONYMOUS_25
typealias ANONYMOUS_25 Uint32
const AV_TIMECODE_FLAG_DROPFRAME = 1
const AV_TIMECODE_FLAG_24HOURSMAX = 2
const AV_TIMECODE_FLAG_ALLOWNEGATIVE = 4
# end enum ANONYMOUS_25
const AV_TS_MAX_STRING_SIZE = 32
# Skipping MacroDefinition: av_ts2str(ts)av_ts_make_string((char[AV_TS_MAX_STRING_SIZE]){0},ts)
# Skipping MacroDefinition: av_ts2timestr(ts,tb)av_ts_make_time_string((char[AV_TS_MAX_STRING_SIZE]){0},ts,tb)
# Skipping MacroDefinition: AV_STRINGIFY(s)AV_TOSTRING(s)
# Skipping MacroDefinition: AV_TOSTRING(s)#s
# Skipping MacroDefinition: AV_GLUE(a,b)a##b
# Skipping MacroDefinition: AV_JOIN(a,b)AV_GLUE(a,b)
# Skipping MacroDefinition: AV_PRAGMA(s)_Pragma(#s)
# Skipping MacroDefinition: AV_VERSION_INT(a,b,c)(a<<16|b<<8|c)
# Skipping MacroDefinition: AV_VERSION_DOT(a,b,c)a##.##b##.##c
# Skipping MacroDefinition: AV_VERSION(a,b,c)AV_VERSION_DOT(a,b,c)
const LIBAVUTIL_VERSION_MAJOR = 52
const LIBAVUTIL_VERSION_MINOR = 48
const LIBAVUTIL_VERSION_MICRO = 101
const LIBAVUTIL_VERSION_INT = 
const LIBAVUTIL_VERSION = 
const LIBAVUTIL_BUILD = 
const LIBAVUTIL_IDENT = "Lavu"
# Skipping MacroDefinition: FF_API_GET_BITS_PER_SAMPLE_FMT(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_FIND_OPT(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_OLD_AVOPTIONS(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_PIX_FMT(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_CONTEXT_SIZE(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_PIX_FMT_DESC(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_AV_REVERSE(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_AUDIOCONVERT(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_CPU_FLAG_MMX2(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_SAMPLES_UTILS_RETURN_ZERO(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_LLS_PRIVATE(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_LLS1(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_AVFRAME_LAVC(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_VDPAU(LIBAVUTIL_VERSION_MAJOR<53)
# Skipping MacroDefinition: FF_API_GET_CHANNEL_LAYOUT_COMPAT(LIBAVUTIL_VERSION_MAJOR<53)
