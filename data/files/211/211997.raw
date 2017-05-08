module Movies
include("avcodec_common.jl")
include("avcodec.jl")
include("avutil/avutil_common.jl")
include("avutil/mem.jl")
function ycbcr!(a::Array{Uint8,3},y::Array{Uint8,2},cb::Array{Uint8,2},cr::Array{Uint8,2})
    nc,width,height = size(a)
    for j=1:height,i=1:width y[i,j]=uint8(16+65.481*a[1,i,j]/256+128.553*a[2,i,j]/256+24.966*a[3,i,j]/256) end
    for j=1:ifloor(height/2),i=1:ifloor(width/2)
        r = mean(sub(a,1,(2*i-1):(2*i),(2*j-1):(2*j)))
        g = mean(sub(a,2,(2*i-1):(2*i),(2*j-1):(2*j)))
        b = mean(sub(a,3,(2*i-1):(2*i),(2*j-1):(2*j)))
        cb[i,j] = uint8(128-37.797*r/256-74.203*g/256+112.0*b/256)
        cr[i,j] = uint8(128+112.0*r/256-93.786*g/256-18.214*b/256)
    end
    return(y,cb,cr)
end

type MPEGVideo
    fps::Int64
    bit_rate::Int64
    width::Int64
    height::Int64
    buf_size::Int64
    buf::Array{Uint8,1}
    gop_size::Int64
    max_b_frames::Int64
    codec::Ptr{Void}
    context::Ptr{Void}
    picture::Ptr{Void}
    pic_buf::(Matrix{Uint8},Matrix{Uint8},Matrix{Uint8})
    f::IOStream
    frame_cnt::Int64
end
function MPEGVideo(;width=800,height=600,fps=25,f=open("out.mpg","w"))
    avcodec_register_all()
    codec = avcodec_find_encoder(AV_CODEC_ID_MPEG2VIDEO)
    picture = avcodec_alloc_frame()
    c= avcodec_alloc_context3(codec)
    bit_rate=4000000
    #Picture buffers
    y=Array(Uint8,width,height)
    cb=Array(Uint8,int(width/2),int(height/2))
    cr=Array(Uint8,int(width/2),int(height/2))
    time_base1=1
    time_base2=fps
    gop_size=10
    max_b_frames=1
    pix_fmt=PIX_FMT_YUV420P
    setCodecProps(c,bit_rate, width, height, time_base1, time_base2, gop_size, max_b_frames, pix_fmt)
    avcodec_open2(c, codec, C_NULL)
    outbuf_size = 4000000;
    outbuf = Array(Uint8,outbuf_size)
    setPictureProps(picture, y, cb, cr, width)
    return(MPEGVideo(fps,bit_rate,width,height,outbuf_size,outbuf,gop_size,max_b_frames,codec,c,picture,(y,cb,cr),f,0))
end
function pushframe(v::MPEGVideo,f::Array{Uint8,3})
    ycbcr!(f,v.pic_buf[1],v.pic_buf[2],v.pic_buf[3])
    out_size = avcodec_encode_video(v.context, v.buf, v.buf_size, v.picture);
    for i=1:out_size write(v.f,v.buf[i]) end
    v.frame_cnt=v.frame_cnt+1
end
function finalizeVideo(v::MPEGVideo)
    out_size=1
    while (out_size>0)  
        out_size = avcodec_encode_video(v.context, v.buf, v.buf_size, C_NULL);
        #println("encoding frame (size=$out_size)");
        for i=1:out_size write(v.f,v.buf[i]) end
    end
    write(v.f,0x00);write(v.f,0x00);write(v.f,0x01);write(v.f,0xb7)
    close(v.f)
    avcodec_close(v.context);
    av_free(v.context);
    av_free(v.picture);
end
export MPEGVideo, pushframe, finalizeVideo
end