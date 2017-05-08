module Slide

"Slide"
Slide

using Base.Markdown
export pages

pages = [

  md"""
  # module JuliaIntro
  """

  md"""
  # Julia
    $(Dates.today())
  """

    md"""
    # Julia
     - http://julialang.org/
     - 짤 logo_hires.png
    """

  md"""
  # JuliaCon
   - http://juliacon.org/
  """

    md"""
    # JuliaCon 2014
     - http://juliacon.org/2014/
    """

    md"""
    # JuliaCon 2015
     - http://juliacon.org/2015/
    """

  md"""
  # 개발
  """

    md"""
    # JuliaBox
     - https://juliabox.org/
    """

    md"""
    # REPL
    ```
    $ julia
    ```
    """

    md"""
    # IJulia
     - https://github.com/JuliaLang/IJulia.jl
    """

    md"""
    # Juno
     - http://junolab.org/
    """

  md"""
  # 문서
  """

    md"""
    # 책, 튜토리얼, 영상
     - http://julialang.org/learning/
     - 짤 books.png
    """

    md"""
    # 한글 문서
     - https://juliakorea.github.io/latest/
     - 줄리아 언어를 소개합니다 (The Julia Language) BY 권창현 http://thoughts.chkwon.net/the-julia-language/
    """

    md"""
    # 코드
     - https://github.com/JuliaLang/julia

    ```shell
    ~/head/julia master$ git log -p
    ```
    """

  md"""
  # 한국 커뮤니티
  """

    md"""
    # 페이스북
     - https://www.facebook.com/groups/juliakorea
    """

    md"""
    # 슬랙
     - https://juliakorea.slack.com
    """

  md"""
  # 번역 프로세스
  """

    md"""
    # 한글 문서
     - https://juliakorea.github.io/latest/
    """

    md"""
    # doc
     - https://github.com/juliakorea/doc
     - https://github.com/juliakorea/doc/graphs/contributors
    """

    md"""
    # git 도우미
     - https://github.com/juliakorea/doc/wiki/git
    """

    md"""
    # doc 이슈
     - https://github.com/juliakorea/doc/issues
    """

    md"""
    # doc 풀 리퀘스트
     - https://github.com/juliakorea/doc/pulls
    """

    md"""
    # slack 로그
     - https://juliakorea.slack.com/messages/translate/
     - https://juliakorea.slack.com/messages/log/
    """

  md"""
  # 꾸준한 코드 관리, 커버리지
  """

    md"""
    # Travis CI
     - https://travis-ci.org/juliakorea/doc
    """

    md"""
    # AppVeyor
     - https://ci.appveyor.com/project/wookay/doc
    """

    md"""
    # Coveralls
     - https://coveralls.io/github/juliakorea/doc?branch=master
    """

  md"""
  # 실무용 언어
  """

    md"""
    # julia-jobs 메일링
     - https://groups.google.com/forum/#!forum/julia-jobs
    """

    md"""
    # Julia Computing
     - http://juliacomputing.com/
     - http://venturebeat.com/2015/05/18/why-the-creators-of-the-julia-programming-language-just-launched-a-startup/
     - 짤 jcl-logo.png
     - 짤 creators.png
    """

  md"""
  # 연구용 언어
  """

    md"""
    # teaching
     - http://julialang.org/teaching/
    """

    md"""
    # 논문들
     - http://julialang.org/publications/
    """

    md"""
    # Julia Summer of Code 2015
     - http://julialang.org/jsoc
    """

  md"""
  # 과학
  """

    md"""
    # 커뮤니티
     - http://julialang.org/community/

    * JuliaLang – The language
    * JuliaStats – Statistics
    * JuliaOpt – Optimization
    * JuliaParallel – Parallel programming in Julia
    * BioJulia - Biology
    * JuliaAstro – Astronomy
    * JuliaQuant – Finance
    * JuliaQuantum – Julia libraries for quantum science and technology
    * JuliaSparse – Sparse matrix solvers
    * JuliaDiff – Differentiation tools
    * JuliaGPU – GPU computing
    * JuliaWeb – Web stack
    * JuliaCI – Continuous Integration Support for Julia packages
    * JuliaDSP – Digital signal processing
    * JuliaGraphs – Graph Theory and Implementation
    * JuliaLangEs – Julia resources in the Spanish language
    """

  md"""
  # 패키지
   - http://pkg.julialang.org/
  """

    md"""
    # Cxx.jl
     - https://github.com/Keno/Cxx.jl
     - https://github.com/juliakorea/OpenCV.jl/wiki/using-Cxx.jl
    """

    md"""
    ```julia
    using Cxx

    cxx\"\"\"
    // http://todayhumor.com/?programmer_12824
    void navs() {
      int i, j;
      printf("-----\n");
      for (i = 0x00477dc4, j = 0x01084210; i; i >>= 1, j >>= 1) {
        printf("%c%c", (i&1)*('*'-32) + 32, (j&1)*10);
      }
      printf("\n");
      printf("-----\n");
    }
    \"\"\"

    @cxx navs()
    ```
    """

    md"""
    # 유용한 패키지들
     - https://github.com/JuliaOpt/Convex.jl
     - https://github.com/JuliaOpt/JuMP.jl
    """

  md"""
  # 특징.jl
  """

    md"""
    # PARAMETRIC TYPES
    ```julia
    type 만세{짱짱<:Int}
    end

    만세{Int}
    # 만세{String}
    # 만세{Any}

    만세{Int} <: 만세
    # false == (만세{Int} <: Int)
    ```
    """

    md"""
    # PARAMETRIC TYPES - Array
    ```julia
    Array{Int}([1 2 3;4 5 6])
    Array{String}(["밥" "벌이"])
    Array{Any}([1 2 "밥"])
    # Array{Int}(["밥"])
    ```
    """

    md"""
    # PARAMETRIC TYPES - Dict
    ```julia
    Dict{Int,Int}(1=>2, 2=>3)
    Dict{Any,Int}(1=>2, "밥"=>3)
    # Dict{Int,Int}(1=>2, "밥"=>3)
    ```
    """

    md"""
    # PARAMETRIC TYPES - Union
    ```julia
    Union{Int,String}("밥")
    Union{Int,String}(1)
    ```
    """

    md"""
    # MULTIPLE DISPATCH
    ```julia
    멀() = 1
    멀(::Int) = 2
    멀(::Function) = 3

    멀() + 멀(0) + 멀(멀)
    # 멀("")

    methods(멀)
    Base.return_types(멀, (Any,))
    Base.return_types(멀, ())
    ```
    """

    md"""
    # MACROS
    ```julia
    macro 매크로()
      println("안녕")
    end

    @매크로
    ```
    """

    md"""
    # MACROS - PREFIXED STRING LITERALS
    ```julia
    macro 세번_str(a)
      [a,a,a]
    end

    세번"굳"

    v"1.2.3"
    v"1.2.3".major
    v"1.2.3".minor
    v"1.2.3".patch
    ```
    """

    md"""
    # 유용한 개념들
     - type inference
     - type safety
     - abstract, concrete
     - mutable, immutable
     - Any, Base.Bottom
     - linear algebra
       - matrix, vector, scalar
       - range, interval
       - dense, sparse
     - meta programming
     - staged programming
    """
    # - invariant, covariant
    # - parallel tasks, distributed arrays
    # - stream, pipe, async, sync

  md"""
  # 소소한 프로그래머
  """

    md"""
    # 줄리아로 짜본거
     - https://github.com/wookay/journal/wiki/줄리아로짠거
    """
    
    md"""
    # 줄리아는 뭐다
     - 새로 나온 게임
     - 정원 가꾸기
     - 설계자들 놀이터
     - 청년 혁명
    """

  #= md"""
  # 프로그래밍 스타일
   - 고민하는 지점
  """

    md"""
    # 자유도
     - 표현력
     - 재미
    """

    md"""
    # 팀
     - 줄리아 짱짱맨들
    """

    md"""
    # 패러다임
     - 변화와 수용
     - 생각의 틀
     - 생각의 한계
    """

    md"""
    # 권력과 현실
     - 자본
     - 주인
     - 자주성

       - 만들어야 할 가치
       - 지켜야 할 가치
    """

    md"""
    # 機械時代
     - 학습과 공유
     - 통섭과 환원
     - 성장과 생존
    """
  =#

  md"""
  # 커밍순
  """

    md"""
    # 마일스톤
     - https://github.com/julialang/julia/milestones
    """

    md"""
    # JuliaCon 2016
     - http://juliacon.org/
    """

  md"""
  # 사진 출처
   - Julia
     - logo_hires.png from https://github.com/JuliaLang/julialang.github.com/tree/master/images

   - Julia Computing
     - jcl-logo.png from http://juliacomputing.com/
     - creators.png from http://venturebeat.com/2015/05/18/why-the-creators-of-the-julia-programming-language-just-launched-a-startup/

   - books.png
     - https://www.packtpub.com/application-development/getting-started-julia-programming/
     - https://pragprog.com/book/7lang/seven-more-languages-in-seven-weeks
     - http://www.manning.com/voncsefalvay/
  """

  md"""
  # (╯°□°）╯  ┻━┻
  """

  md"""
  # end
  """
]

end
