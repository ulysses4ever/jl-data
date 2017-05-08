export UNUR_DISTR, UNUR_PAR, UNUR_GEN, UNUR_URNG, UNUR_FUNCT_CONT
export unur_urng_gsl_new, unur_urng_gslptr_new, unur_urng_gslqrng_new
export unur_urng_prng_new, unur_urng_prngptr_new
export RngStream_SetPackageSeed, unur_urng_rngstream_new, unur_urng_rngstreamptr_new

# Provides typed opaque pointers.
type UNUR_DISTR
end

type UNUR_PAR
end

type UNUR_GEN
end

type UNUR_URNG
end

type UNUR_FUNCT_CONT
end

### GSL generators
function unur_urng_gsl_new(urngtype)
    ccall((:unur_urng_gsl_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{Void},), urngtype)
end

function unur_urng_gslptr_new(urngtype)
    ccall((:unur_urng_gslptr_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{Void},), urngtype)
end

function unur_urng_gslqrng_new(qrngtype, dim)
    ccall((:unur_urng_gslqrng_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{Void}, Cuint), qrngtype, dim)
end

### PRNG generators
function unur_urng_prng_new( prngstr )
    ccall((:unur_urng_prng_new, "libunuran"), Ptr{UNUR_URNG}, (Cstring,), prngstr)
end

function unur_urng_prngptr_new( prng_urng )
    ccall((:unur_urng_prngptr_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UInt8},), prng_urng)
end

### RngStreams
function RngStream_SetPackageSeed(seed)
  assert(length(seed)==6)
  assert(eltype(seed)==UInt64)
  ccall((:RngStream_SetPackageSeed, "librngstreams"), Void,
                (Ptr{UInt64},), seed)
end

function unur_urng_rngstream_new( urngstr )
    ccall((:unur_urng_rngstream_new, "libunuran"), Ptr{UNUR_URNG}, (Cstring,), urngstr)
end

function unur_urng_rngstreamptr_new( rngstream )
    ccall((:unur_urng_rngstream_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UInt8},), rngstream)
end

export unur_get_default_urng
function unur_get_default_urng()
    res=ccall((:unur_get_default_urng, "libunuran"), Ptr{UNUR_URNG}, () )
    res
end

export unur_set_default_urng
function unur_set_default_urng(urng_new)
    res=ccall((:unur_set_default_urng, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UNUR_URNG}, ), urng_new)
    res
end

export unur_set_default_urng_aux
function unur_set_default_urng_aux(urng_new)
    res=ccall((:unur_set_default_urng_aux, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UNUR_URNG}, ), urng_new)
    res
end

export unur_get_default_urng_aux
function unur_get_default_urng_aux()
    res=ccall((:unur_get_default_urng_aux, "libunuran"), Ptr{UNUR_URNG}, () )
    res
end

export unur_set_urng
function unur_set_urng(parameters, urng)
    res=ccall((:unur_set_urng, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{UNUR_URNG}, ), parameters, urng)
    res
end

export unur_chg_urng
function unur_chg_urng(generator, urng)
    res=ccall((:unur_chg_urng, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UNUR_GEN}, Ptr{UNUR_URNG}, ), generator, urng)
    res
end

export unur_get_urng
function unur_get_urng(generator)
    res=ccall((:unur_get_urng, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_set_urng_aux
function unur_set_urng_aux(parameters, urng_aux)
    res=ccall((:unur_set_urng_aux, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{UNUR_URNG}, ), parameters, urng_aux)
    res
end

export unur_use_urng_aux_default
function unur_use_urng_aux_default(parameters)
    res=ccall((:unur_use_urng_aux_default, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_chgto_urng_aux_default
function unur_chgto_urng_aux_default(generator)
    res=ccall((:unur_chgto_urng_aux_default, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_chg_urng_aux
function unur_chg_urng_aux(generator, urng_aux)
    res=ccall((:unur_chg_urng_aux, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UNUR_GEN}, Ptr{UNUR_URNG}, ), generator, urng_aux)
    res
end

export unur_get_urng_aux
function unur_get_urng_aux(generator)
    res=ccall((:unur_get_urng_aux, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_urng_sample
function unur_urng_sample(urng)
    res=ccall((:unur_urng_sample, "libunuran"), Cdouble, (Ptr{UNUR_URNG}, ), urng)
    res
end

export unur_sample_urng
function unur_sample_urng(gen)
    res=ccall((:unur_sample_urng, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), gen)
    res
end

export unur_urng_sample_array
function unur_urng_sample_array(urng, X, dim)
    res=ccall((:unur_urng_sample_array, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Cdouble}, Cint, ), urng, X, dim)
    res
end

export unur_urng_reset
function unur_urng_reset(urng)
    res=ccall((:unur_urng_reset, "libunuran"), Cint, (Ptr{UNUR_URNG}, ), urng)
    res
end

export unur_urng_sync
function unur_urng_sync(urng)
    res=ccall((:unur_urng_sync, "libunuran"), Cint, (Ptr{UNUR_URNG}, ), urng)
    res
end

export unur_urng_seed
function unur_urng_seed(urng, seed)
    res=ccall((:unur_urng_seed, "libunuran"), Cint, (Ptr{UNUR_URNG}, Cuint, ), urng, seed)
    res
end

export unur_urng_anti
function unur_urng_anti(urng, anti)
    res=ccall((:unur_urng_anti, "libunuran"), Cint, (Ptr{UNUR_URNG}, Cint, ), urng, anti)
    res
end

export unur_urng_nextsub
function unur_urng_nextsub(urng)
    res=ccall((:unur_urng_nextsub, "libunuran"), Cint, (Ptr{UNUR_URNG}, ), urng)
    res
end

export unur_urng_resetsub
function unur_urng_resetsub(urng)
    res=ccall((:unur_urng_resetsub, "libunuran"), Cint, (Ptr{UNUR_URNG}, ), urng)
    res
end

export unur_gen_sync
function unur_gen_sync(generator)
    res=ccall((:unur_gen_sync, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_gen_seed
function unur_gen_seed(generator, seed)
    res=ccall((:unur_gen_seed, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cuint, ), generator, seed)
    res
end

export unur_gen_anti
function unur_gen_anti(generator, anti)
    res=ccall((:unur_gen_anti, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, anti)
    res
end

export unur_gen_reset
function unur_gen_reset(generator)
    res=ccall((:unur_gen_reset, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_gen_nextsub
function unur_gen_nextsub(generator)
    res=ccall((:unur_gen_nextsub, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_gen_resetsub
function unur_gen_resetsub(generator)
    res=ccall((:unur_gen_resetsub, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_urng_new
function unur_urng_new(sampleunif, state)
    res=ccall((:unur_urng_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{Cdouble}, Ptr{Void}, ), sampleunif, state)
    res
end

export unur_urng_free
function unur_urng_free(urng)
    res=ccall((:unur_urng_free, "libunuran"), Void, (Ptr{UNUR_URNG}, ), urng)
    res
end

export unur_urng_set_sample_array
function unur_urng_set_sample_array(urng, samplearray)
    res=ccall((:unur_urng_set_sample_array, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Cdouble}, ), urng, samplearray)
    res
end

export unur_urng_set_sync
function unur_urng_set_sync(urng, sync)
    res=ccall((:unur_urng_set_sync, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Unexposed}, ), urng, sync)
    res
end

export unur_urng_set_seed
function unur_urng_set_seed(urng, setseed)
    res=ccall((:unur_urng_set_seed, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Unexposed}, ), urng, setseed)
    res
end

export unur_urng_set_anti
function unur_urng_set_anti(urng, setanti)
    res=ccall((:unur_urng_set_anti, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Unexposed}, ), urng, setanti)
    res
end

export unur_urng_set_reset
function unur_urng_set_reset(urng, reset)
    res=ccall((:unur_urng_set_reset, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Unexposed}, ), urng, reset)
    res
end

export unur_urng_set_nextsub
function unur_urng_set_nextsub(urng, nextsub)
    res=ccall((:unur_urng_set_nextsub, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Unexposed}, ), urng, nextsub)
    res
end

export unur_urng_set_resetsub
function unur_urng_set_resetsub(urng, resetsub)
    res=ccall((:unur_urng_set_resetsub, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Unexposed}, ), urng, resetsub)
    res
end

export unur_urng_set_delete
function unur_urng_set_delete(urng, fpdelete)
    res=ccall((:unur_urng_set_delete, "libunuran"), Cint, (Ptr{UNUR_URNG}, Ptr{Unexposed}, ), urng, fpdelete)
    res
end

export unur_urng_MRG31k3p
function unur_urng_MRG31k3p(dummy)
    res=ccall((:unur_urng_MRG31k3p, "libunuran"), Cdouble, (Ptr{Void}, ), dummy)
    res
end

export unur_urng_MRG31k3p_seed
function unur_urng_MRG31k3p_seed(dummy, seed)
    res=ccall((:unur_urng_MRG31k3p_seed, "libunuran"), Void, (Ptr{Void}, Cuint, ), dummy, seed)
    res
end

export unur_urng_MRG31k3p_reset
function unur_urng_MRG31k3p_reset(dummy)
    res=ccall((:unur_urng_MRG31k3p_reset, "libunuran"), Void, (Ptr{Void}, ), dummy)
    res
end

export unur_urng_fish
function unur_urng_fish(dummy)
    res=ccall((:unur_urng_fish, "libunuran"), Cdouble, (Ptr{Void}, ), dummy)
    res
end

export unur_urng_fish_seed
function unur_urng_fish_seed(dummy, seed)
    res=ccall((:unur_urng_fish_seed, "libunuran"), Void, (Ptr{Void}, Cuint, ), dummy, seed)
    res
end

export unur_urng_fish_reset
function unur_urng_fish_reset(dummy)
    res=ccall((:unur_urng_fish_reset, "libunuran"), Void, (Ptr{Void}, ), dummy)
    res
end

export unur_urng_mstd
function unur_urng_mstd(dummy)
    res=ccall((:unur_urng_mstd, "libunuran"), Cdouble, (Ptr{Void}, ), dummy)
    res
end

export unur_urng_mstd_seed
function unur_urng_mstd_seed(dummy, seed)
    res=ccall((:unur_urng_mstd_seed, "libunuran"), Void, (Ptr{Void}, Cuint, ), dummy, seed)
    res
end

export unur_urng_mstd_reset
function unur_urng_mstd_reset(dummy)
    res=ccall((:unur_urng_mstd_reset, "libunuran"), Void, (Ptr{Void}, ), dummy)
    res
end

export unur_urng_builtin
function unur_urng_builtin()
    res=ccall((:unur_urng_builtin, "libunuran"), Ptr{UNUR_URNG}, () )
    res
end

export unur_urng_builtin_aux
function unur_urng_builtin_aux()
    res=ccall((:unur_urng_builtin_aux, "libunuran"), Ptr{UNUR_URNG}, () )
    res
end

export unur_urng_fvoid_new
function unur_urng_fvoid_new(urand, reset)
    res=ccall((:unur_urng_fvoid_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{Void}, Ptr{Void}, ), urand, reset)
    res
end

export unur_urng_randomshift_new
function unur_urng_randomshift_new(qrng, srng, dim)
    res=ccall((:unur_urng_randomshift_new, "libunuran"), Ptr{UNUR_URNG}, (Ptr{UNUR_URNG}, Ptr{UNUR_URNG}, Cint, ), qrng, srng, dim)
    res
end

export unur_urng_randomshift_nextshift
function unur_urng_randomshift_nextshift(urng)
    res=ccall((:unur_urng_randomshift_nextshift, "libunuran"), Cint, (Ptr{UNUR_URNG}, ), urng)
    res
end

export unur_distr_free
function unur_distr_free(distribution)
    res=ccall((:unur_distr_free, "libunuran"), Void, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_set_name
function unur_distr_set_name(distribution, name)
    res=ccall((:unur_distr_set_name, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, name)
    res
end

export unur_distr_get_name
function unur_distr_get_name()
    res=ccall((:unur_distr_get_name, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_get_dim
function unur_distr_get_dim(distribution)
    res=ccall((:unur_distr_get_dim, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_get_type
function unur_distr_get_type(distribution)
    res=ccall((:unur_distr_get_type, "libunuran"), Cuint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_is_cont
function unur_distr_is_cont(distribution)
    res=ccall((:unur_distr_is_cont, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_is_cvec
function unur_distr_is_cvec(distribution)
    res=ccall((:unur_distr_is_cvec, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_is_cemp
function unur_distr_is_cemp(distribution)
    res=ccall((:unur_distr_is_cemp, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_is_cvemp
function unur_distr_is_cvemp(distribution)
    res=ccall((:unur_distr_is_cvemp, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_is_discr
function unur_distr_is_discr(distribution)
    res=ccall((:unur_distr_is_discr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_is_matr
function unur_distr_is_matr(distribution)
    res=ccall((:unur_distr_is_matr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_set_extobj
function unur_distr_set_extobj(distribution, extobj)
    res=ccall((:unur_distr_set_extobj, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, extobj)
    res
end

export unur_distr_get_extobj
function unur_distr_get_extobj()
    res=ccall((:unur_distr_get_extobj, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_clone
function unur_distr_clone(distr)
    res=ccall((:unur_distr_clone, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, ), distr)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_clone"))
    end
    res
end

export unur_distr_cemp_new
function unur_distr_cemp_new()
    res=ccall((:unur_distr_cemp_new, "libunuran"), Ptr{UNUR_DISTR}, () )
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cemp_new"))
    end
    res
end

export unur_distr_cemp_set_data
function unur_distr_cemp_set_data(distribution, sample, n_sample)
    res=ccall((:unur_distr_cemp_set_data, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, ), distribution, sample, n_sample)
    res
end

export unur_distr_cemp_read_data
function unur_distr_cemp_read_data(distribution, filename)
    res=ccall((:unur_distr_cemp_read_data, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, filename)
    res
end

export unur_distr_cemp_get_data
function unur_distr_cemp_get_data(distribution, sample)
    res=ccall((:unur_distr_cemp_get_data, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, sample)
    res
end

export unur_distr_cemp_set_hist
function unur_distr_cemp_set_hist(distribution, prob, n_prob, xmin, xmax)
    res=ccall((:unur_distr_cemp_set_hist, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, Cdouble, Cdouble, ), distribution, prob, n_prob, xmin, xmax)
    res
end

export unur_distr_cemp_set_hist_prob
function unur_distr_cemp_set_hist_prob(distribution, prob, n_prob)
    res=ccall((:unur_distr_cemp_set_hist_prob, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, ), distribution, prob, n_prob)
    res
end

export unur_distr_cemp_set_hist_domain
function unur_distr_cemp_set_hist_domain(distribution, xmin, xmax)
    res=ccall((:unur_distr_cemp_set_hist_domain, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, Cdouble, ), distribution, xmin, xmax)
    res
end

export unur_distr_cemp_set_hist_bins
function unur_distr_cemp_set_hist_bins(distribution, bins, n_bins)
    res=ccall((:unur_distr_cemp_set_hist_bins, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, ), distribution, bins, n_bins)
    res
end

export unur_distr_cont_new
function unur_distr_cont_new()
    res=ccall((:unur_distr_cont_new, "libunuran"), Ptr{UNUR_DISTR}, () )
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cont_new"))
    end
    res
end

export unur_distr_cont_set_pdf
function unur_distr_cont_set_pdf(distribution, pdf)
    res=ccall((:unur_distr_cont_set_pdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, pdf)
    res
end

export unur_distr_cont_set_dpdf
function unur_distr_cont_set_dpdf(distribution, dpdf)
    res=ccall((:unur_distr_cont_set_dpdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, dpdf)
    res
end

export unur_distr_cont_set_cdf
function unur_distr_cont_set_cdf(distribution, cdf)
    res=ccall((:unur_distr_cont_set_cdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, cdf)
    res
end

export unur_distr_cont_set_invcdf
function unur_distr_cont_set_invcdf(distribution, invcdf)
    res=ccall((:unur_distr_cont_set_invcdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, invcdf)
    res
end

export unur_distr_cont_get_pdf
function unur_distr_cont_get_pdf(distribution)
    res=ccall((:unur_distr_cont_get_pdf, "libunuran"), Ptr{UNUR_FUNCT_CONT}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_get_dpdf
function unur_distr_cont_get_dpdf(distribution)
    res=ccall((:unur_distr_cont_get_dpdf, "libunuran"), Ptr{UNUR_FUNCT_CONT}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_get_cdf
function unur_distr_cont_get_cdf(distribution)
    res=ccall((:unur_distr_cont_get_cdf, "libunuran"), Ptr{UNUR_FUNCT_CONT}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_get_invcdf
function unur_distr_cont_get_invcdf(distribution)
    res=ccall((:unur_distr_cont_get_invcdf, "libunuran"), Ptr{UNUR_FUNCT_CONT}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_eval_pdf
function unur_distr_cont_eval_pdf(x, distribution)
    res=ccall((:unur_distr_cont_eval_pdf, "libunuran"), Cdouble, (Cdouble, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cont_eval_dpdf
function unur_distr_cont_eval_dpdf(x, distribution)
    res=ccall((:unur_distr_cont_eval_dpdf, "libunuran"), Cdouble, (Cdouble, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cont_eval_cdf
function unur_distr_cont_eval_cdf(x, distribution)
    res=ccall((:unur_distr_cont_eval_cdf, "libunuran"), Cdouble, (Cdouble, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cont_eval_invcdf
function unur_distr_cont_eval_invcdf(u, distribution)
    res=ccall((:unur_distr_cont_eval_invcdf, "libunuran"), Cdouble, (Cdouble, Ptr{UNUR_DISTR}, ), u, distribution)
    res
end

export unur_distr_cont_set_logpdf
function unur_distr_cont_set_logpdf(distribution, logpdf)
    res=ccall((:unur_distr_cont_set_logpdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, logpdf)
    res
end

export unur_distr_cont_set_dlogpdf
function unur_distr_cont_set_dlogpdf(distribution, dlogpdf)
    res=ccall((:unur_distr_cont_set_dlogpdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, dlogpdf)
    res
end

export unur_distr_cont_set_logcdf
function unur_distr_cont_set_logcdf(distribution, logcdf)
    res=ccall((:unur_distr_cont_set_logcdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, logcdf)
    res
end

export unur_distr_cont_get_logpdf
function unur_distr_cont_get_logpdf(distribution)
    res=ccall((:unur_distr_cont_get_logpdf, "libunuran"), Ptr{UNUR_FUNCT_CONT}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_get_dlogpdf
function unur_distr_cont_get_dlogpdf(distribution)
    res=ccall((:unur_distr_cont_get_dlogpdf, "libunuran"), Ptr{UNUR_FUNCT_CONT}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_get_logcdf
function unur_distr_cont_get_logcdf(distribution)
    res=ccall((:unur_distr_cont_get_logcdf, "libunuran"), Ptr{UNUR_FUNCT_CONT}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_eval_logpdf
function unur_distr_cont_eval_logpdf(x, distribution)
    res=ccall((:unur_distr_cont_eval_logpdf, "libunuran"), Cdouble, (Cdouble, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cont_eval_dlogpdf
function unur_distr_cont_eval_dlogpdf(x, distribution)
    res=ccall((:unur_distr_cont_eval_dlogpdf, "libunuran"), Cdouble, (Cdouble, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cont_eval_logcdf
function unur_distr_cont_eval_logcdf(x, distribution)
    res=ccall((:unur_distr_cont_eval_logcdf, "libunuran"), Cdouble, (Cdouble, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cont_set_pdfstr
function unur_distr_cont_set_pdfstr(distribution, pdfstr)
    res=ccall((:unur_distr_cont_set_pdfstr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, pdfstr)
    res
end

export unur_distr_cont_set_cdfstr
function unur_distr_cont_set_cdfstr(distribution, cdfstr)
    res=ccall((:unur_distr_cont_set_cdfstr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, cdfstr)
    res
end

export unur_distr_cont_get_pdfstr
function unur_distr_cont_get_pdfstr()
    res=ccall((:unur_distr_cont_get_pdfstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cont_get_dpdfstr
function unur_distr_cont_get_dpdfstr()
    res=ccall((:unur_distr_cont_get_dpdfstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cont_get_cdfstr
function unur_distr_cont_get_cdfstr()
    res=ccall((:unur_distr_cont_get_cdfstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cont_set_pdfparams
function unur_distr_cont_set_pdfparams(distribution, params, n_params)
    res=ccall((:unur_distr_cont_set_pdfparams, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, ), distribution, params, n_params)
    res
end

export unur_distr_cont_get_pdfparams
function unur_distr_cont_get_pdfparams(distribution, params)
    res=ccall((:unur_distr_cont_get_pdfparams, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ref{Ptr{Cdouble}}, ), distribution, params)
    res
end

export unur_distr_cont_set_pdfparams_vec
function unur_distr_cont_set_pdfparams_vec(distribution, par, param_vec, n_param_vec)
    res=ccall((:unur_distr_cont_set_pdfparams_vec, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cint, Ptr{Cdouble}, Cint, ), distribution, par, param_vec, n_param_vec)
    res
end

export unur_distr_cont_get_pdfparams_vec
function unur_distr_cont_get_pdfparams_vec(distribution, par, param_vecs)
    res=ccall((:unur_distr_cont_get_pdfparams_vec, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cint, Ptr{Cdouble}, ), distribution, par, param_vecs)
    res
end

export unur_distr_cont_set_logpdfstr
function unur_distr_cont_set_logpdfstr(distribution, logpdfstr)
    res=ccall((:unur_distr_cont_set_logpdfstr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, logpdfstr)
    res
end

export unur_distr_cont_get_logpdfstr
function unur_distr_cont_get_logpdfstr()
    res=ccall((:unur_distr_cont_get_logpdfstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cont_get_dlogpdfstr
function unur_distr_cont_get_dlogpdfstr()
    res=ccall((:unur_distr_cont_get_dlogpdfstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cont_set_logcdfstr
function unur_distr_cont_set_logcdfstr(distribution, logcdfstr)
    res=ccall((:unur_distr_cont_set_logcdfstr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, logcdfstr)
    res
end

export unur_distr_cont_get_logcdfstr
function unur_distr_cont_get_logcdfstr()
    res=ccall((:unur_distr_cont_get_logcdfstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cont_set_domain
function unur_distr_cont_set_domain(distribution, left, right)
    res=ccall((:unur_distr_cont_set_domain, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, Cdouble, ), distribution, left, right)
    res
end

export unur_distr_cont_get_domain
function unur_distr_cont_get_domain(distribution, left, right)
    res=ccall((:unur_distr_cont_get_domain, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Ptr{Cdouble}, ), distribution, left, right)
    res
end

export unur_distr_cont_get_truncated
function unur_distr_cont_get_truncated(distribution, left, right)
    res=ccall((:unur_distr_cont_get_truncated, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Ptr{Cdouble}, ), distribution, left, right)
    res
end

export unur_distr_cont_set_hr
function unur_distr_cont_set_hr(distribution, hazard)
    res=ccall((:unur_distr_cont_set_hr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, hazard)
    res
end

export unur_distr_cont_get_hr
function unur_distr_cont_get_hr(distribution)
    res=ccall((:unur_distr_cont_get_hr, "libunuran"), Ptr{UNUR_FUNCT_CONT}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_eval_hr
function unur_distr_cont_eval_hr(x, distribution)
    res=ccall((:unur_distr_cont_eval_hr, "libunuran"), Cdouble, (Cdouble, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cont_set_hrstr
function unur_distr_cont_set_hrstr(distribution, hrstr)
    res=ccall((:unur_distr_cont_set_hrstr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, hrstr)
    res
end

export unur_distr_cont_get_hrstr
function unur_distr_cont_get_hrstr()
    res=ccall((:unur_distr_cont_get_hrstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cont_set_mode
function unur_distr_cont_set_mode(distribution, mode)
    res=ccall((:unur_distr_cont_set_mode, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, ), distribution, mode)
    res
end

export unur_distr_cont_upd_mode
function unur_distr_cont_upd_mode(distribution)
    res=ccall((:unur_distr_cont_upd_mode, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_get_mode
function unur_distr_cont_get_mode(distribution)
    res=ccall((:unur_distr_cont_get_mode, "libunuran"), Cdouble, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_set_center
function unur_distr_cont_set_center(distribution, center)
    res=ccall((:unur_distr_cont_set_center, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, ), distribution, center)
    res
end

export unur_distr_cont_get_center
function unur_distr_cont_get_center(distribution)
    res=ccall((:unur_distr_cont_get_center, "libunuran"), Cdouble, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_set_pdfarea
function unur_distr_cont_set_pdfarea(distribution, area)
    res=ccall((:unur_distr_cont_set_pdfarea, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, ), distribution, area)
    res
end

export unur_distr_cont_upd_pdfarea
function unur_distr_cont_upd_pdfarea(distribution)
    res=ccall((:unur_distr_cont_upd_pdfarea, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cont_get_pdfarea
function unur_distr_cont_get_pdfarea(distribution)
    res=ccall((:unur_distr_cont_get_pdfarea, "libunuran"), Cdouble, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cxtrans_new
function unur_distr_cxtrans_new(distribution)
    res=ccall((:unur_distr_cxtrans_new, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, ), distribution)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cxtrans_new"))
    end
    res
end

export unur_distr_cxtrans_get_distribution
function unur_distr_cxtrans_get_distribution(distribution)
    res=ccall((:unur_distr_cxtrans_get_distribution, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, ), distribution)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cxtrans_get_distribution"))
    end
    res
end

export unur_distr_cxtrans_set_alpha
function unur_distr_cxtrans_set_alpha(distribution, alpha)
    res=ccall((:unur_distr_cxtrans_set_alpha, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, ), distribution, alpha)
    res
end

export unur_distr_cxtrans_set_rescale
function unur_distr_cxtrans_set_rescale(distribution, mu, sigma)
    res=ccall((:unur_distr_cxtrans_set_rescale, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, Cdouble, ), distribution, mu, sigma)
    res
end

export unur_distr_cxtrans_get_alpha
function unur_distr_cxtrans_get_alpha(distribution)
    res=ccall((:unur_distr_cxtrans_get_alpha, "libunuran"), Cdouble, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cxtrans_get_mu
function unur_distr_cxtrans_get_mu(distribution)
    res=ccall((:unur_distr_cxtrans_get_mu, "libunuran"), Cdouble, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cxtrans_get_sigma
function unur_distr_cxtrans_get_sigma(distribution)
    res=ccall((:unur_distr_cxtrans_get_sigma, "libunuran"), Cdouble, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cxtrans_set_logpdfpole
function unur_distr_cxtrans_set_logpdfpole(distribution, logpdfpole, dlogpdfpole)
    res=ccall((:unur_distr_cxtrans_set_logpdfpole, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, Cdouble, ), distribution, logpdfpole, dlogpdfpole)
    res
end

export unur_distr_cxtrans_set_domain
function unur_distr_cxtrans_set_domain(distribution, left, right)
    res=ccall((:unur_distr_cxtrans_set_domain, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, Cdouble, ), distribution, left, right)
    res
end

export unur_distr_corder_new
function unur_distr_corder_new(distribution, n, k)
    res=ccall((:unur_distr_corder_new, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, Cint, Cint, ), distribution, n, k)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_corder_new"))
    end
    res
end

export unur_distr_corder_get_distribution
function unur_distr_corder_get_distribution(distribution)
    res=ccall((:unur_distr_corder_get_distribution, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, ), distribution)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_corder_get_distribution"))
    end
    res
end

export unur_distr_corder_set_rank
function unur_distr_corder_set_rank(distribution, n, k)
    res=ccall((:unur_distr_corder_set_rank, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cint, Cint, ), distribution, n, k)
    res
end

export unur_distr_corder_get_rank
function unur_distr_corder_get_rank(distribution, n, k)
    res=ccall((:unur_distr_corder_get_rank, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Int}, Ptr{Int}, ), distribution, n, k)
    res
end

export unur_distr_cvec_new
function unur_distr_cvec_new(dim)
    res=ccall((:unur_distr_cvec_new, "libunuran"), Ptr{UNUR_DISTR}, (Cint, ), dim)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cvec_new"))
    end
    res
end

export unur_distr_cvec_set_pdf
function unur_distr_cvec_set_pdf(distribution, pdf)
    res=ccall((:unur_distr_cvec_set_pdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, pdf)
    res
end

export unur_distr_cvec_set_dpdf
function unur_distr_cvec_set_dpdf(distribution, dpdf)
    res=ccall((:unur_distr_cvec_set_dpdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, dpdf)
    res
end

export unur_distr_cvec_set_pdpdf
function unur_distr_cvec_set_pdpdf(distribution, pdpdf)
    res=ccall((:unur_distr_cvec_set_pdpdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, pdpdf)
    res
end

export unur_distr_cvec_get_pdf
function unur_distr_cvec_get_pdf(distribution)
    res=ccall((:unur_distr_cvec_get_pdf, "libunuran"), Ptr{UNUR_FUNCT_CVEC}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_get_dpdf
function unur_distr_cvec_get_dpdf(distribution)
    res=ccall((:unur_distr_cvec_get_dpdf, "libunuran"), Ptr{UNUR_VFUNCT_CVEC}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_get_pdpdf
function unur_distr_cvec_get_pdpdf(distribution)
    res=ccall((:unur_distr_cvec_get_pdpdf, "libunuran"), Ptr{UNUR_FUNCTD_CVEC}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_eval_pdf
function unur_distr_cvec_eval_pdf(x, distribution)
    res=ccall((:unur_distr_cvec_eval_pdf, "libunuran"), Cdouble, (Ptr{Cdouble}, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cvec_eval_dpdf
function unur_distr_cvec_eval_dpdf(result, x, distribution)
    res=ccall((:unur_distr_cvec_eval_dpdf, "libunuran"), Cint, (Ptr{Cdouble}, Ptr{Cdouble}, Ptr{UNUR_DISTR}, ), result, x, distribution)
    res
end

export unur_distr_cvec_eval_pdpdf
function unur_distr_cvec_eval_pdpdf(x, coord, distribution)
    res=ccall((:unur_distr_cvec_eval_pdpdf, "libunuran"), Cdouble, (Ptr{Cdouble}, Cint, Ptr{UNUR_DISTR}, ), x, coord, distribution)
    res
end

export unur_distr_cvec_set_logpdf
function unur_distr_cvec_set_logpdf(distribution, logpdf)
    res=ccall((:unur_distr_cvec_set_logpdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, logpdf)
    res
end

export unur_distr_cvec_set_dlogpdf
function unur_distr_cvec_set_dlogpdf(distribution, dlogpdf)
    res=ccall((:unur_distr_cvec_set_dlogpdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, dlogpdf)
    res
end

export unur_distr_cvec_set_pdlogpdf
function unur_distr_cvec_set_pdlogpdf(distribution, pdlogpdf)
    res=ccall((:unur_distr_cvec_set_pdlogpdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, pdlogpdf)
    res
end

export unur_distr_cvec_get_logpdf
function unur_distr_cvec_get_logpdf(distribution)
    res=ccall((:unur_distr_cvec_get_logpdf, "libunuran"), Ptr{UNUR_FUNCT_CVEC}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_get_dlogpdf
function unur_distr_cvec_get_dlogpdf(distribution)
    res=ccall((:unur_distr_cvec_get_dlogpdf, "libunuran"), Ptr{UNUR_VFUNCT_CVEC}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_get_pdlogpdf
function unur_distr_cvec_get_pdlogpdf(distribution)
    res=ccall((:unur_distr_cvec_get_pdlogpdf, "libunuran"), Ptr{UNUR_FUNCTD_CVEC}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_eval_logpdf
function unur_distr_cvec_eval_logpdf(x, distribution)
    res=ccall((:unur_distr_cvec_eval_logpdf, "libunuran"), Cdouble, (Ptr{Cdouble}, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cvec_eval_dlogpdf
function unur_distr_cvec_eval_dlogpdf(result, x, distribution)
    res=ccall((:unur_distr_cvec_eval_dlogpdf, "libunuran"), Cint, (Ptr{Cdouble}, Ptr{Cdouble}, Ptr{UNUR_DISTR}, ), result, x, distribution)
    res
end

export unur_distr_cvec_eval_pdlogpdf
function unur_distr_cvec_eval_pdlogpdf(x, coord, distribution)
    res=ccall((:unur_distr_cvec_eval_pdlogpdf, "libunuran"), Cdouble, (Ptr{Cdouble}, Cint, Ptr{UNUR_DISTR}, ), x, coord, distribution)
    res
end

export unur_distr_cvec_set_mean
function unur_distr_cvec_set_mean(distribution, mean)
    res=ccall((:unur_distr_cvec_set_mean, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, mean)
    res
end

export unur_distr_cvec_get_mean
function unur_distr_cvec_get_mean()
    res=ccall((:unur_distr_cvec_get_mean, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cvec_set_covar
function unur_distr_cvec_set_covar(distribution, covar)
    res=ccall((:unur_distr_cvec_set_covar, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, covar)
    res
end

export unur_distr_cvec_set_covar_inv
function unur_distr_cvec_set_covar_inv(distribution, covar_inv)
    res=ccall((:unur_distr_cvec_set_covar_inv, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, covar_inv)
    res
end

export unur_distr_cvec_get_covar
function unur_distr_cvec_get_covar()
    res=ccall((:unur_distr_cvec_get_covar, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cvec_get_cholesky
function unur_distr_cvec_get_cholesky()
    res=ccall((:unur_distr_cvec_get_cholesky, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cvec_get_covar_inv
function unur_distr_cvec_get_covar_inv()
    res=ccall((:unur_distr_cvec_get_covar_inv, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cvec_set_rankcorr
function unur_distr_cvec_set_rankcorr(distribution, rankcorr)
    res=ccall((:unur_distr_cvec_set_rankcorr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, rankcorr)
    res
end

export unur_distr_cvec_get_rankcorr
function unur_distr_cvec_get_rankcorr()
    res=ccall((:unur_distr_cvec_get_rankcorr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cvec_get_rk_cholesky
function unur_distr_cvec_get_rk_cholesky()
    res=ccall((:unur_distr_cvec_get_rk_cholesky, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cvec_set_marginals
function unur_distr_cvec_set_marginals(distribution, marginal)
    res=ccall((:unur_distr_cvec_set_marginals, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{UNUR_DISTR}, ), distribution, marginal)
    res
end

export unur_distr_cvec_set_marginal_array
function unur_distr_cvec_set_marginal_array(distribution, marginals)
    res=ccall((:unur_distr_cvec_set_marginal_array, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{UNUR_DISTR}, ), distribution, marginals)
    res
end

export unur_distr_cvec_set_marginal_list
function unur_distr_cvec_set_marginal_list(distribution)
    res=ccall((:unur_distr_cvec_set_marginal_list, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_get_marginal
function unur_distr_cvec_get_marginal(distribution, n)
    res=ccall((:unur_distr_cvec_get_marginal, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, Cint, ), distribution, n)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cvec_get_marginal"))
    end
    res
end

export unur_distr_cvec_set_pdfparams
function unur_distr_cvec_set_pdfparams(distribution, params, n_params)
    res=ccall((:unur_distr_cvec_set_pdfparams, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, ), distribution, params, n_params)
    res
end

export unur_distr_cvec_get_pdfparams
function unur_distr_cvec_get_pdfparams(distribution, params)
    res=ccall((:unur_distr_cvec_get_pdfparams, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, params)
    res
end

export unur_distr_cvec_set_pdfparams_vec
function unur_distr_cvec_set_pdfparams_vec(distribution, par, param_vec, n_params)
    res=ccall((:unur_distr_cvec_set_pdfparams_vec, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cint, Ptr{Cdouble}, Cint, ), distribution, par, param_vec, n_params)
    res
end

export unur_distr_cvec_get_pdfparams_vec
function unur_distr_cvec_get_pdfparams_vec(distribution, par, param_vecs)
    res=ccall((:unur_distr_cvec_get_pdfparams_vec, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cint, Ptr{Cdouble}, ), distribution, par, param_vecs)
    res
end

export unur_distr_cvec_set_domain_rect
function unur_distr_cvec_set_domain_rect(distribution, lowerleft, upperright)
    res=ccall((:unur_distr_cvec_set_domain_rect, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Ptr{Cdouble}, ), distribution, lowerleft, upperright)
    res
end

export unur_distr_cvec_is_indomain
function unur_distr_cvec_is_indomain(x, distribution)
    res=ccall((:unur_distr_cvec_is_indomain, "libunuran"), Cint, (Ptr{Cdouble}, Ptr{UNUR_DISTR}, ), x, distribution)
    res
end

export unur_distr_cvec_set_mode
function unur_distr_cvec_set_mode(distribution, mode)
    res=ccall((:unur_distr_cvec_set_mode, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, mode)
    res
end

export unur_distr_cvec_upd_mode
function unur_distr_cvec_upd_mode(distribution)
    res=ccall((:unur_distr_cvec_upd_mode, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_get_mode
function unur_distr_cvec_get_mode()
    res=ccall((:unur_distr_cvec_get_mode, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cvec_set_center
function unur_distr_cvec_set_center(distribution, center)
    res=ccall((:unur_distr_cvec_set_center, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, center)
    res
end

export unur_distr_cvec_get_center
function unur_distr_cvec_get_center()
    res=ccall((:unur_distr_cvec_get_center, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_cvec_set_pdfvol
function unur_distr_cvec_set_pdfvol(distribution, volume)
    res=ccall((:unur_distr_cvec_set_pdfvol, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, ), distribution, volume)
    res
end

export unur_distr_cvec_upd_pdfvol
function unur_distr_cvec_upd_pdfvol(distribution)
    res=ccall((:unur_distr_cvec_upd_pdfvol, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_get_pdfvol
function unur_distr_cvec_get_pdfvol(distribution)
    res=ccall((:unur_distr_cvec_get_pdfvol, "libunuran"), Cdouble, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_condi_new
function unur_distr_condi_new(distribution, pos, dir, k)
    res=ccall((:unur_distr_condi_new, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Ptr{Cdouble}, Cint, ), distribution, pos, dir, k)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_condi_new"))
    end
    res
end

export unur_distr_condi_set_condition
function unur_distr_condi_set_condition(distribution, pos, dir, k)
    res=ccall((:unur_distr_condi_set_condition, "libunuran"), Cint, (Ptr{Unexposed}, Ptr{Cdouble}, Ptr{Cdouble}, Cint, ), distribution, pos, dir, k)
    res
end

export unur_distr_condi_get_condition
function unur_distr_condi_get_condition(distribution, pos, dir, k)
    res=ccall((:unur_distr_condi_get_condition, "libunuran"), Cint, (Ptr{Unexposed}, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Int}, ), distribution, pos, dir, k)
    res
end

export unur_distr_condi_get_distribution
function unur_distr_condi_get_distribution(distribution)
    res=ccall((:unur_distr_condi_get_distribution, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, ), distribution)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_condi_get_distribution"))
    end
    res
end

export unur_distr_cvemp_new
function unur_distr_cvemp_new(dim)
    res=ccall((:unur_distr_cvemp_new, "libunuran"), Ptr{UNUR_DISTR}, (Cint, ), dim)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cvemp_new"))
    end
    res
end

export unur_distr_cvemp_set_data
function unur_distr_cvemp_set_data(distribution, sample, n_sample)
    res=ccall((:unur_distr_cvemp_set_data, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, ), distribution, sample, n_sample)
    res
end

export unur_distr_cvemp_read_data
function unur_distr_cvemp_read_data(distribution, filename)
    res=ccall((:unur_distr_cvemp_read_data, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, filename)
    res
end

export unur_distr_cvemp_get_data
function unur_distr_cvemp_get_data(distribution, sample)
    res=ccall((:unur_distr_cvemp_get_data, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, sample)
    res
end

export unur_distr_discr_new
function unur_distr_discr_new()
    res=ccall((:unur_distr_discr_new, "libunuran"), Ptr{UNUR_DISTR}, () )
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_discr_new"))
    end
    res
end

export unur_distr_discr_set_pv
function unur_distr_discr_set_pv(distribution, pv, n_pv)
    res=ccall((:unur_distr_discr_set_pv, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, ), distribution, pv, n_pv)
    res
end

export unur_distr_discr_make_pv
function unur_distr_discr_make_pv(distribution)
    res=ccall((:unur_distr_discr_make_pv, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_discr_get_pv
function unur_distr_discr_get_pv(distribution, pv)
    res=ccall((:unur_distr_discr_get_pv, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, pv)
    res
end

export unur_distr_discr_set_pmf
function unur_distr_discr_set_pmf(distribution, pmf)
    res=ccall((:unur_distr_discr_set_pmf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, pmf)
    res
end

export unur_distr_discr_set_cdf
function unur_distr_discr_set_cdf(distribution, cdf)
    res=ccall((:unur_distr_discr_set_cdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, cdf)
    res
end

export unur_distr_discr_set_invcdf
function unur_distr_discr_set_invcdf(distribution, invcdf)
    res=ccall((:unur_distr_discr_set_invcdf, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Void}, ), distribution, invcdf)
    res
end

export unur_distr_discr_get_pmf
function unur_distr_discr_get_pmf(distribution)
    res=ccall((:unur_distr_discr_get_pmf, "libunuran"), Ptr{UNUR_FUNCT_DISCR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_discr_get_cdf
function unur_distr_discr_get_cdf(distribution)
    res=ccall((:unur_distr_discr_get_cdf, "libunuran"), Ptr{UNUR_FUNCT_DISCR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_discr_get_invcdf
function unur_distr_discr_get_invcdf(distribution)
    res=ccall((:unur_distr_discr_get_invcdf, "libunuran"), Ptr{UNUR_IFUNCT_DISCR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_discr_eval_pv
function unur_distr_discr_eval_pv(k, distribution)
    res=ccall((:unur_distr_discr_eval_pv, "libunuran"), Cdouble, (Cint, Ptr{UNUR_DISTR}, ), k, distribution)
    res
end

export unur_distr_discr_eval_pmf
function unur_distr_discr_eval_pmf(k, distribution)
    res=ccall((:unur_distr_discr_eval_pmf, "libunuran"), Cdouble, (Cint, Ptr{UNUR_DISTR}, ), k, distribution)
    res
end

export unur_distr_discr_eval_cdf
function unur_distr_discr_eval_cdf(k, distribution)
    res=ccall((:unur_distr_discr_eval_cdf, "libunuran"), Cdouble, (Cint, Ptr{UNUR_DISTR}, ), k, distribution)
    res
end

export unur_distr_discr_eval_invcdf
function unur_distr_discr_eval_invcdf(u, distribution)
    res=ccall((:unur_distr_discr_eval_invcdf, "libunuran"), Cint, (Cdouble, Ptr{UNUR_DISTR}, ), u, distribution)
    res
end

export unur_distr_discr_set_pmfstr
function unur_distr_discr_set_pmfstr(distribution, pmfstr)
    res=ccall((:unur_distr_discr_set_pmfstr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, pmfstr)
    res
end

export unur_distr_discr_set_cdfstr
function unur_distr_discr_set_cdfstr(distribution, cdfstr)
    res=ccall((:unur_distr_discr_set_cdfstr, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cstring, ), distribution, cdfstr)
    res
end

export unur_distr_discr_get_pmfstr
function unur_distr_discr_get_pmfstr()
    res=ccall((:unur_distr_discr_get_pmfstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_discr_get_cdfstr
function unur_distr_discr_get_cdfstr()
    res=ccall((:unur_distr_discr_get_cdfstr, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_distr_discr_set_pmfparams
function unur_distr_discr_set_pmfparams(distribution, params, n_params)
    res=ccall((:unur_distr_discr_set_pmfparams, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, Cint, ), distribution, params, n_params)
    res
end

export unur_distr_discr_get_pmfparams
function unur_distr_discr_get_pmfparams(distribution, params)
    res=ccall((:unur_distr_discr_get_pmfparams, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Cdouble}, ), distribution, params)
    res
end

export unur_distr_discr_set_domain
function unur_distr_discr_set_domain(distribution, left, right)
    res=ccall((:unur_distr_discr_set_domain, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cint, Cint, ), distribution, left, right)
    res
end

export unur_distr_discr_get_domain
function unur_distr_discr_get_domain(distribution, left, right)
    res=ccall((:unur_distr_discr_get_domain, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Int}, Ptr{Int}, ), distribution, left, right)
    res
end

export unur_distr_discr_set_mode
function unur_distr_discr_set_mode(distribution, mode)
    res=ccall((:unur_distr_discr_set_mode, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cint, ), distribution, mode)
    res
end

export unur_distr_discr_upd_mode
function unur_distr_discr_upd_mode(distribution)
    res=ccall((:unur_distr_discr_upd_mode, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_discr_get_mode
function unur_distr_discr_get_mode(distribution)
    res=ccall((:unur_distr_discr_get_mode, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_discr_set_pmfsum
function unur_distr_discr_set_pmfsum(distribution, sum)
    res=ccall((:unur_distr_discr_set_pmfsum, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Cdouble, ), distribution, sum)
    res
end

export unur_distr_discr_upd_pmfsum
function unur_distr_discr_upd_pmfsum(distribution)
    res=ccall((:unur_distr_discr_upd_pmfsum, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_discr_get_pmfsum
function unur_distr_discr_get_pmfsum(distribution)
    res=ccall((:unur_distr_discr_get_pmfsum, "libunuran"), Cdouble, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_matr_new
function unur_distr_matr_new(n_rows, n_cols)
    res=ccall((:unur_distr_matr_new, "libunuran"), Ptr{UNUR_DISTR}, (Cint, Cint, ), n_rows, n_cols)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_matr_new"))
    end
    res
end

export unur_distr_matr_get_dim
function unur_distr_matr_get_dim(distribution, n_rows, n_cols)
    res=ccall((:unur_distr_matr_get_dim, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{Int}, Ptr{Int}, ), distribution, n_rows, n_cols)
    res
end

export unur_auto_new
function unur_auto_new(distribution)
    res=ccall((:unur_auto_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_auto_set_logss
function unur_auto_set_logss(parameters, logss)
    res=ccall((:unur_auto_set_logss, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, logss)
    res
end

export unur_dari_new
function unur_dari_new(distribution)
    res=ccall((:unur_dari_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_dari_set_squeeze
function unur_dari_set_squeeze(parameters, squeeze)
    res=ccall((:unur_dari_set_squeeze, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, squeeze)
    res
end

export unur_dari_set_tablesize
function unur_dari_set_tablesize(parameters, size)
    res=ccall((:unur_dari_set_tablesize, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, size)
    res
end

export unur_dari_set_cpfactor
function unur_dari_set_cpfactor(parameters, cp_factor)
    res=ccall((:unur_dari_set_cpfactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, cp_factor)
    res
end

export unur_dari_set_verify
function unur_dari_set_verify(parameters, verify)
    res=ccall((:unur_dari_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_dari_chg_verify
function unur_dari_chg_verify(generator, verify)
    res=ccall((:unur_dari_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_dau_new
function unur_dau_new(distribution)
    res=ccall((:unur_dau_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_dau_set_urnfactor
function unur_dau_set_urnfactor(parameters, factor)
    res=ccall((:unur_dau_set_urnfactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_dgt_new
function unur_dgt_new(distribution)
    res=ccall((:unur_dgt_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_dgt_set_guidefactor
function unur_dgt_set_guidefactor(parameters, factor)
    res=ccall((:unur_dgt_set_guidefactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_dgt_set_variant
function unur_dgt_set_variant(parameters, variant)
    res=ccall((:unur_dgt_set_variant, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cuint, ), parameters, variant)
    res
end

export unur_dgt_eval_invcdf_recycle
function unur_dgt_eval_invcdf_recycle(generator, u, recycle)
    res=ccall((:unur_dgt_eval_invcdf_recycle, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Ptr{Cdouble}, ), generator, u, recycle)
    res
end

export unur_dgt_eval_invcdf
function unur_dgt_eval_invcdf(generator, u)
    res=ccall((:unur_dgt_eval_invcdf, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, u)
    res
end

export unur_dsrou_new
function unur_dsrou_new(distribution)
    res=ccall((:unur_dsrou_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_dsrou_set_cdfatmode
function unur_dsrou_set_cdfatmode(parameters, Fmode)
    res=ccall((:unur_dsrou_set_cdfatmode, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, Fmode)
    res
end

export unur_dsrou_set_verify
function unur_dsrou_set_verify(parameters, verify)
    res=ccall((:unur_dsrou_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_dsrou_chg_verify
function unur_dsrou_chg_verify(generator, verify)
    res=ccall((:unur_dsrou_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_dsrou_chg_cdfatmode
function unur_dsrou_chg_cdfatmode(generator, Fmode)
    res=ccall((:unur_dsrou_chg_cdfatmode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, Fmode)
    res
end

export unur_dss_new
function unur_dss_new(distribution)
    res=ccall((:unur_dss_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_arou_new
function unur_arou_new(distribution)
    res=ccall((:unur_arou_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_arou_set_usedars
function unur_arou_set_usedars(parameters, usedars)
    res=ccall((:unur_arou_set_usedars, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usedars)
    res
end

export unur_arou_set_darsfactor
function unur_arou_set_darsfactor(parameters, factor)
    res=ccall((:unur_arou_set_darsfactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_arou_set_max_sqhratio
function unur_arou_set_max_sqhratio(parameters, max_ratio)
    res=ccall((:unur_arou_set_max_sqhratio, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, max_ratio)
    res
end

export unur_arou_get_sqhratio
function unur_arou_get_sqhratio(generator)
    res=ccall((:unur_arou_get_sqhratio, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_arou_get_hatarea
function unur_arou_get_hatarea(generator)
    res=ccall((:unur_arou_get_hatarea, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_arou_get_squeezearea
function unur_arou_get_squeezearea(generator)
    res=ccall((:unur_arou_get_squeezearea, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_arou_set_max_segments
function unur_arou_set_max_segments(parameters, max_segs)
    res=ccall((:unur_arou_set_max_segments, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, max_segs)
    res
end

export unur_arou_set_cpoints
function unur_arou_set_cpoints(parameters, n_stp, stp)
    res=ccall((:unur_arou_set_cpoints, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, Ptr{Cdouble}, ), parameters, n_stp, stp)
    res
end

export unur_arou_set_usecenter
function unur_arou_set_usecenter(parameters, usecenter)
    res=ccall((:unur_arou_set_usecenter, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usecenter)
    res
end

export unur_arou_set_guidefactor
function unur_arou_set_guidefactor(parameters, factor)
    res=ccall((:unur_arou_set_guidefactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_arou_set_verify
function unur_arou_set_verify(parameters, verify)
    res=ccall((:unur_arou_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_arou_chg_verify
function unur_arou_chg_verify(generator, verify)
    res=ccall((:unur_arou_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_arou_set_pedantic
function unur_arou_set_pedantic(parameters, pedantic)
    res=ccall((:unur_arou_set_pedantic, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, pedantic)
    res
end

export unur_ars_new
function unur_ars_new(distribution)
    res=ccall((:unur_ars_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_ars_set_max_intervals
function unur_ars_set_max_intervals(parameters, max_ivs)
    res=ccall((:unur_ars_set_max_intervals, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, max_ivs)
    res
end

export unur_ars_set_cpoints
function unur_ars_set_cpoints(parameters, n_cpoints, cpoints)
    res=ccall((:unur_ars_set_cpoints, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, Ptr{Cdouble}, ), parameters, n_cpoints, cpoints)
    res
end

export unur_ars_set_reinit_percentiles
function unur_ars_set_reinit_percentiles(parameters, n_percentiles, percentiles)
    res=ccall((:unur_ars_set_reinit_percentiles, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, Ptr{Cdouble}, ), parameters, n_percentiles, percentiles)
    res
end

export unur_ars_chg_reinit_percentiles
function unur_ars_chg_reinit_percentiles(generator, n_percentiles, percentiles)
    res=ccall((:unur_ars_chg_reinit_percentiles, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, Ptr{Cdouble}, ), generator, n_percentiles, percentiles)
    res
end

export unur_ars_set_reinit_ncpoints
function unur_ars_set_reinit_ncpoints(parameters, ncpoints)
    res=ccall((:unur_ars_set_reinit_ncpoints, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, ncpoints)
    res
end

export unur_ars_chg_reinit_ncpoints
function unur_ars_chg_reinit_ncpoints(generator, ncpoints)
    res=ccall((:unur_ars_chg_reinit_ncpoints, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, ncpoints)
    res
end

export unur_ars_set_max_iter
function unur_ars_set_max_iter(parameters, max_iter)
    res=ccall((:unur_ars_set_max_iter, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, max_iter)
    res
end

export unur_ars_set_verify
function unur_ars_set_verify(parameters, verify)
    res=ccall((:unur_ars_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_ars_chg_verify
function unur_ars_chg_verify(generator, verify)
    res=ccall((:unur_ars_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_ars_set_pedantic
function unur_ars_set_pedantic(parameters, pedantic)
    res=ccall((:unur_ars_set_pedantic, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, pedantic)
    res
end

export unur_ars_get_loghatarea
function unur_ars_get_loghatarea(generator)
    res=ccall((:unur_ars_get_loghatarea, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_ars_eval_invcdfhat
function unur_ars_eval_invcdfhat(generator, u)
    res=ccall((:unur_ars_eval_invcdfhat, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, ), generator, u)
    res
end

export unur_hinv_new
function unur_hinv_new(distribution)
    res=ccall((:unur_hinv_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_hinv_set_order
function unur_hinv_set_order(parameters, order)
    res=ccall((:unur_hinv_set_order, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, order)
    res
end

export unur_hinv_set_u_resolution
function unur_hinv_set_u_resolution(parameters, u_resolution)
    res=ccall((:unur_hinv_set_u_resolution, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, u_resolution)
    res
end

export unur_hinv_set_cpoints
function unur_hinv_set_cpoints(parameters, stp, n_stp)
    res=ccall((:unur_hinv_set_cpoints, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{Cdouble}, Cint, ), parameters, stp, n_stp)
    res
end

export unur_hinv_set_boundary
function unur_hinv_set_boundary(parameters, left, right)
    res=ccall((:unur_hinv_set_boundary, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, Cdouble, ), parameters, left, right)
    res
end

export unur_hinv_set_guidefactor
function unur_hinv_set_guidefactor(parameters, factor)
    res=ccall((:unur_hinv_set_guidefactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_hinv_set_max_intervals
function unur_hinv_set_max_intervals(parameters, max_ivs)
    res=ccall((:unur_hinv_set_max_intervals, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, max_ivs)
    res
end

export unur_hinv_get_n_intervals
function unur_hinv_get_n_intervals(generator)
    res=ccall((:unur_hinv_get_n_intervals, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_hinv_eval_approxinvcdf
function unur_hinv_eval_approxinvcdf(generator, u)
    res=ccall((:unur_hinv_eval_approxinvcdf, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, ), generator, u)
    res
end

export unur_hinv_chg_truncated
function unur_hinv_chg_truncated(generator, left, right)
    res=ccall((:unur_hinv_chg_truncated, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), generator, left, right)
    res
end

export unur_hinv_estimate_error
function unur_hinv_estimate_error(generator, samplesize, max_error, MAE)
    res=ccall((:unur_hinv_estimate_error, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, Ptr{Cdouble}, Ptr{Cdouble}, ), generator, samplesize, max_error, MAE)
    res
end

export unur_hrb_new
function unur_hrb_new(distribution)
    res=ccall((:unur_hrb_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_hrb_set_upperbound
function unur_hrb_set_upperbound(parameters, upperbound)
    res=ccall((:unur_hrb_set_upperbound, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, upperbound)
    res
end

export unur_hrb_set_verify
function unur_hrb_set_verify(parameters, verify)
    res=ccall((:unur_hrb_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_hrb_chg_verify
function unur_hrb_chg_verify(generator, verify)
    res=ccall((:unur_hrb_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_hrd_new
function unur_hrd_new(distribution)
    res=ccall((:unur_hrd_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_hrd_set_verify
function unur_hrd_set_verify(parameters, verify)
    res=ccall((:unur_hrd_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_hrd_chg_verify
function unur_hrd_chg_verify(generator, verify)
    res=ccall((:unur_hrd_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_hri_new
function unur_hri_new(distribution)
    res=ccall((:unur_hri_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_hri_set_p0
function unur_hri_set_p0(parameters, p0)
    res=ccall((:unur_hri_set_p0, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, p0)
    res
end

export unur_hri_set_verify
function unur_hri_set_verify(parameters, verify)
    res=ccall((:unur_hri_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_hri_chg_verify
function unur_hri_chg_verify(generator, verify)
    res=ccall((:unur_hri_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_itdr_new
function unur_itdr_new(distribution)
    res=ccall((:unur_itdr_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_itdr_set_xi
function unur_itdr_set_xi(parameters, xi)
    res=ccall((:unur_itdr_set_xi, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, xi)
    res
end

export unur_itdr_set_cp
function unur_itdr_set_cp(parameters, cp)
    res=ccall((:unur_itdr_set_cp, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, cp)
    res
end

export unur_itdr_set_ct
function unur_itdr_set_ct(parameters, ct)
    res=ccall((:unur_itdr_set_ct, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, ct)
    res
end

export unur_itdr_get_xi
function unur_itdr_get_xi(generator)
    res=ccall((:unur_itdr_get_xi, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_itdr_get_cp
function unur_itdr_get_cp(generator)
    res=ccall((:unur_itdr_get_cp, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_itdr_get_ct
function unur_itdr_get_ct(generator)
    res=ccall((:unur_itdr_get_ct, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_itdr_get_area
function unur_itdr_get_area(generator)
    res=ccall((:unur_itdr_get_area, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_itdr_set_verify
function unur_itdr_set_verify(parameters, verify)
    res=ccall((:unur_itdr_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_itdr_chg_verify
function unur_itdr_chg_verify(generator, verify)
    res=ccall((:unur_itdr_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_mcorr_new
function unur_mcorr_new(distribution)
    res=ccall((:unur_mcorr_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_mcorr_set_eigenvalues
function unur_mcorr_set_eigenvalues(par, eigenvalues)
    res=ccall((:unur_mcorr_set_eigenvalues, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{Cdouble}, ), par, eigenvalues)
    res
end

export unur_mcorr_chg_eigenvalues
function unur_mcorr_chg_eigenvalues(gen, eigenvalues)
    res=ccall((:unur_mcorr_chg_eigenvalues, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, ), gen, eigenvalues)
    res
end

export unur_ninv_new
function unur_ninv_new(distribution)
    res=ccall((:unur_ninv_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_ninv_set_useregula
function unur_ninv_set_useregula(parameters)
    res=ccall((:unur_ninv_set_useregula, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_ninv_set_usenewton
function unur_ninv_set_usenewton(parameters)
    res=ccall((:unur_ninv_set_usenewton, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_ninv_set_usebisect
function unur_ninv_set_usebisect(parameters)
    res=ccall((:unur_ninv_set_usebisect, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_ninv_set_max_iter
function unur_ninv_set_max_iter(parameters, max_iter)
    res=ccall((:unur_ninv_set_max_iter, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, max_iter)
    res
end

export unur_ninv_chg_max_iter
function unur_ninv_chg_max_iter(generator, max_iter)
    res=ccall((:unur_ninv_chg_max_iter, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, max_iter)
    res
end

export unur_ninv_set_x_resolution
function unur_ninv_set_x_resolution(parameters, x_resolution)
    res=ccall((:unur_ninv_set_x_resolution, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, x_resolution)
    res
end

export unur_ninv_chg_x_resolution
function unur_ninv_chg_x_resolution(generator, x_resolution)
    res=ccall((:unur_ninv_chg_x_resolution, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, x_resolution)
    res
end

export unur_ninv_set_u_resolution
function unur_ninv_set_u_resolution(parameters, u_resolution)
    res=ccall((:unur_ninv_set_u_resolution, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, u_resolution)
    res
end

export unur_ninv_chg_u_resolution
function unur_ninv_chg_u_resolution(generator, u_resolution)
    res=ccall((:unur_ninv_chg_u_resolution, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, u_resolution)
    res
end

export unur_ninv_set_start
function unur_ninv_set_start(parameters, left, right)
    res=ccall((:unur_ninv_set_start, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, Cdouble, ), parameters, left, right)
    res
end

export unur_ninv_chg_start
function unur_ninv_chg_start(gen, left, right)
    res=ccall((:unur_ninv_chg_start, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), gen, left, right)
    res
end

export unur_ninv_set_table
function unur_ninv_set_table(parameters, no_of_points)
    res=ccall((:unur_ninv_set_table, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, no_of_points)
    res
end

export unur_ninv_chg_table
function unur_ninv_chg_table(gen, no_of_points)
    res=ccall((:unur_ninv_chg_table, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), gen, no_of_points)
    res
end

export unur_ninv_chg_truncated
function unur_ninv_chg_truncated(gen, left, right)
    res=ccall((:unur_ninv_chg_truncated, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), gen, left, right)
    res
end

export unur_ninv_eval_approxinvcdf
function unur_ninv_eval_approxinvcdf(generator, u)
    res=ccall((:unur_ninv_eval_approxinvcdf, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, ), generator, u)
    res
end

export unur_nrou_new
function unur_nrou_new(distribution)
    res=ccall((:unur_nrou_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_nrou_set_u
function unur_nrou_set_u(parameters, umin, umax)
    res=ccall((:unur_nrou_set_u, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, Cdouble, ), parameters, umin, umax)
    res
end

export unur_nrou_set_v
function unur_nrou_set_v(parameters, vmax)
    res=ccall((:unur_nrou_set_v, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, vmax)
    res
end

export unur_nrou_set_r
function unur_nrou_set_r(parameters, r)
    res=ccall((:unur_nrou_set_r, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, r)
    res
end

export unur_nrou_set_center
function unur_nrou_set_center(parameters, center)
    res=ccall((:unur_nrou_set_center, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, center)
    res
end

export unur_nrou_set_verify
function unur_nrou_set_verify(parameters, verify)
    res=ccall((:unur_nrou_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_nrou_chg_verify
function unur_nrou_chg_verify(generator, verify)
    res=ccall((:unur_nrou_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_pinv_new
function unur_pinv_new(distribution)
    res=ccall((:unur_pinv_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_pinv_set_order
function unur_pinv_set_order(parameters, order)
    res=ccall((:unur_pinv_set_order, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, order)
    res
end

export unur_pinv_set_smoothness
function unur_pinv_set_smoothness(parameters, smoothness)
    res=ccall((:unur_pinv_set_smoothness, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, smoothness)
    res
end

export unur_pinv_set_u_resolution
function unur_pinv_set_u_resolution(parameters, u_resolution)
    res=ccall((:unur_pinv_set_u_resolution, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, u_resolution)
    res
end

export unur_pinv_set_use_upoints
function unur_pinv_set_use_upoints(parameters, use_upoints)
    res=ccall((:unur_pinv_set_use_upoints, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, use_upoints)
    res
end

export unur_pinv_set_usepdf
function unur_pinv_set_usepdf(parameters)
    res=ccall((:unur_pinv_set_usepdf, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_pinv_set_usecdf
function unur_pinv_set_usecdf(parameters)
    res=ccall((:unur_pinv_set_usecdf, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_pinv_set_boundary
function unur_pinv_set_boundary(parameters, left, right)
    res=ccall((:unur_pinv_set_boundary, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, Cdouble, ), parameters, left, right)
    res
end

export unur_pinv_set_searchboundary
function unur_pinv_set_searchboundary(parameters, left, right)
    res=ccall((:unur_pinv_set_searchboundary, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, Cint, ), parameters, left, right)
    res
end

export unur_pinv_set_max_intervals
function unur_pinv_set_max_intervals(parameters, max_ivs)
    res=ccall((:unur_pinv_set_max_intervals, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, max_ivs)
    res
end

export unur_pinv_get_n_intervals
function unur_pinv_get_n_intervals(generator)
    res=ccall((:unur_pinv_get_n_intervals, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_pinv_set_keepcdf
function unur_pinv_set_keepcdf(parameters, keepcdf)
    res=ccall((:unur_pinv_set_keepcdf, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, keepcdf)
    res
end

export unur_pinv_eval_approxinvcdf
function unur_pinv_eval_approxinvcdf(generator, u)
    res=ccall((:unur_pinv_eval_approxinvcdf, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, ), generator, u)
    res
end

export unur_pinv_eval_approxcdf
function unur_pinv_eval_approxcdf(generator, x)
    res=ccall((:unur_pinv_eval_approxcdf, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, ), generator, x)
    res
end

export unur_pinv_estimate_error
function unur_pinv_estimate_error(generator, samplesize, max_error, MAE)
    res=ccall((:unur_pinv_estimate_error, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, Ptr{Cdouble}, Ptr{Cdouble}, ), generator, samplesize, max_error, MAE)
    res
end

export unur_srou_new
function unur_srou_new(distribution)
    res=ccall((:unur_srou_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_srou_set_r
function unur_srou_set_r(parameters, r)
    res=ccall((:unur_srou_set_r, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, r)
    res
end

export unur_srou_set_cdfatmode
function unur_srou_set_cdfatmode(parameters, Fmode)
    res=ccall((:unur_srou_set_cdfatmode, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, Fmode)
    res
end

export unur_srou_set_pdfatmode
function unur_srou_set_pdfatmode(parameters, fmode)
    res=ccall((:unur_srou_set_pdfatmode, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, fmode)
    res
end

export unur_srou_set_usesqueeze
function unur_srou_set_usesqueeze(parameters, usesqueeze)
    res=ccall((:unur_srou_set_usesqueeze, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usesqueeze)
    res
end

export unur_srou_set_usemirror
function unur_srou_set_usemirror(parameters, usemirror)
    res=ccall((:unur_srou_set_usemirror, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usemirror)
    res
end

export unur_srou_set_verify
function unur_srou_set_verify(parameters, verify)
    res=ccall((:unur_srou_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_srou_chg_verify
function unur_srou_chg_verify(generator, verify)
    res=ccall((:unur_srou_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_srou_chg_cdfatmode
function unur_srou_chg_cdfatmode(generator, Fmode)
    res=ccall((:unur_srou_chg_cdfatmode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, Fmode)
    res
end

export unur_srou_chg_pdfatmode
function unur_srou_chg_pdfatmode(generator, fmode)
    res=ccall((:unur_srou_chg_pdfatmode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, fmode)
    res
end

export unur_ssr_new
function unur_ssr_new(distribution)
    res=ccall((:unur_ssr_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_ssr_set_cdfatmode
function unur_ssr_set_cdfatmode(parameters, Fmode)
    res=ccall((:unur_ssr_set_cdfatmode, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, Fmode)
    res
end

export unur_ssr_set_pdfatmode
function unur_ssr_set_pdfatmode(parameters, fmode)
    res=ccall((:unur_ssr_set_pdfatmode, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, fmode)
    res
end

export unur_ssr_set_usesqueeze
function unur_ssr_set_usesqueeze(parameters, usesqueeze)
    res=ccall((:unur_ssr_set_usesqueeze, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usesqueeze)
    res
end

export unur_ssr_set_verify
function unur_ssr_set_verify(parameters, verify)
    res=ccall((:unur_ssr_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_ssr_chg_verify
function unur_ssr_chg_verify(generator, verify)
    res=ccall((:unur_ssr_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_ssr_chg_cdfatmode
function unur_ssr_chg_cdfatmode(generator, Fmode)
    res=ccall((:unur_ssr_chg_cdfatmode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, Fmode)
    res
end

export unur_ssr_chg_pdfatmode
function unur_ssr_chg_pdfatmode(generator, fmode)
    res=ccall((:unur_ssr_chg_pdfatmode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, fmode)
    res
end

export unur_tabl_new
function unur_tabl_new(distribution)
    res=ccall((:unur_tabl_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_tabl_set_variant_ia
function unur_tabl_set_variant_ia(parameters, use_ia)
    res=ccall((:unur_tabl_set_variant_ia, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, use_ia)
    res
end

export unur_tabl_set_cpoints
function unur_tabl_set_cpoints(parameters, n_cpoints, cpoints)
    res=ccall((:unur_tabl_set_cpoints, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, Ptr{Cdouble}, ), parameters, n_cpoints, cpoints)
    res
end

export unur_tabl_set_nstp
function unur_tabl_set_nstp(parameters, n_stp)
    res=ccall((:unur_tabl_set_nstp, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, n_stp)
    res
end

export unur_tabl_set_useear
function unur_tabl_set_useear(parameters, useear)
    res=ccall((:unur_tabl_set_useear, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, useear)
    res
end

export unur_tabl_set_areafraction
function unur_tabl_set_areafraction(parameters, fraction)
    res=ccall((:unur_tabl_set_areafraction, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, fraction)
    res
end

export unur_tabl_set_usedars
function unur_tabl_set_usedars(parameters, usedars)
    res=ccall((:unur_tabl_set_usedars, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usedars)
    res
end

export unur_tabl_set_darsfactor
function unur_tabl_set_darsfactor(parameters, factor)
    res=ccall((:unur_tabl_set_darsfactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_tabl_set_variant_splitmode
function unur_tabl_set_variant_splitmode(parameters, splitmode)
    res=ccall((:unur_tabl_set_variant_splitmode, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cuint, ), parameters, splitmode)
    res
end

export unur_tabl_set_max_sqhratio
function unur_tabl_set_max_sqhratio(parameters, max_ratio)
    res=ccall((:unur_tabl_set_max_sqhratio, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, max_ratio)
    res
end

export unur_tabl_get_sqhratio
function unur_tabl_get_sqhratio(generator)
    res=ccall((:unur_tabl_get_sqhratio, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tabl_get_hatarea
function unur_tabl_get_hatarea(generator)
    res=ccall((:unur_tabl_get_hatarea, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tabl_get_squeezearea
function unur_tabl_get_squeezearea(generator)
    res=ccall((:unur_tabl_get_squeezearea, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tabl_set_max_intervals
function unur_tabl_set_max_intervals(parameters, max_ivs)
    res=ccall((:unur_tabl_set_max_intervals, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, max_ivs)
    res
end

export unur_tabl_get_n_intervals
function unur_tabl_get_n_intervals(generator)
    res=ccall((:unur_tabl_get_n_intervals, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tabl_set_slopes
function unur_tabl_set_slopes(parameters, slopes, n_slopes)
    res=ccall((:unur_tabl_set_slopes, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{Cdouble}, Cint, ), parameters, slopes, n_slopes)
    res
end

export unur_tabl_set_guidefactor
function unur_tabl_set_guidefactor(parameters, factor)
    res=ccall((:unur_tabl_set_guidefactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_tabl_set_boundary
function unur_tabl_set_boundary(parameters, left, right)
    res=ccall((:unur_tabl_set_boundary, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, Cdouble, ), parameters, left, right)
    res
end

export unur_tabl_chg_truncated
function unur_tabl_chg_truncated(gen, left, right)
    res=ccall((:unur_tabl_chg_truncated, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), gen, left, right)
    res
end

export unur_tabl_set_verify
function unur_tabl_set_verify(parameters, verify)
    res=ccall((:unur_tabl_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_tabl_chg_verify
function unur_tabl_chg_verify(generator, verify)
    res=ccall((:unur_tabl_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_tabl_set_pedantic
function unur_tabl_set_pedantic(parameters, pedantic)
    res=ccall((:unur_tabl_set_pedantic, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, pedantic)
    res
end

export unur_tdr_new
function unur_tdr_new(distribution)
    res=ccall((:unur_tdr_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_tdr_set_c
function unur_tdr_set_c(parameters, c)
    res=ccall((:unur_tdr_set_c, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, c)
    res
end

export unur_tdr_set_variant_gw
function unur_tdr_set_variant_gw(parameters)
    res=ccall((:unur_tdr_set_variant_gw, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_tdr_set_variant_ps
function unur_tdr_set_variant_ps(parameters)
    res=ccall((:unur_tdr_set_variant_ps, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_tdr_set_variant_ia
function unur_tdr_set_variant_ia(parameters)
    res=ccall((:unur_tdr_set_variant_ia, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_tdr_set_usedars
function unur_tdr_set_usedars(parameters, usedars)
    res=ccall((:unur_tdr_set_usedars, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usedars)
    res
end

export unur_tdr_set_darsfactor
function unur_tdr_set_darsfactor(parameters, factor)
    res=ccall((:unur_tdr_set_darsfactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_tdr_set_cpoints
function unur_tdr_set_cpoints(parameters, n_stp, stp)
    res=ccall((:unur_tdr_set_cpoints, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, Ptr{Cdouble}, ), parameters, n_stp, stp)
    res
end

export unur_tdr_set_reinit_percentiles
function unur_tdr_set_reinit_percentiles(parameters, n_percentiles, percentiles)
    res=ccall((:unur_tdr_set_reinit_percentiles, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, Ptr{Cdouble}, ), parameters, n_percentiles, percentiles)
    res
end

export unur_tdr_chg_reinit_percentiles
function unur_tdr_chg_reinit_percentiles(generator, n_percentiles, percentiles)
    res=ccall((:unur_tdr_chg_reinit_percentiles, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, Ptr{Cdouble}, ), generator, n_percentiles, percentiles)
    res
end

export unur_tdr_set_reinit_ncpoints
function unur_tdr_set_reinit_ncpoints(parameters, ncpoints)
    res=ccall((:unur_tdr_set_reinit_ncpoints, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, ncpoints)
    res
end

export unur_tdr_chg_reinit_ncpoints
function unur_tdr_chg_reinit_ncpoints(generator, ncpoints)
    res=ccall((:unur_tdr_chg_reinit_ncpoints, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, ncpoints)
    res
end

export unur_tdr_chg_truncated
function unur_tdr_chg_truncated(gen, left, right)
    res=ccall((:unur_tdr_chg_truncated, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), gen, left, right)
    res
end

export unur_tdr_set_max_sqhratio
function unur_tdr_set_max_sqhratio(parameters, max_ratio)
    res=ccall((:unur_tdr_set_max_sqhratio, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, max_ratio)
    res
end

export unur_tdr_get_sqhratio
function unur_tdr_get_sqhratio(generator)
    res=ccall((:unur_tdr_get_sqhratio, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tdr_get_hatarea
function unur_tdr_get_hatarea(generator)
    res=ccall((:unur_tdr_get_hatarea, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tdr_get_squeezearea
function unur_tdr_get_squeezearea(generator)
    res=ccall((:unur_tdr_get_squeezearea, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tdr_set_max_intervals
function unur_tdr_set_max_intervals(parameters, max_ivs)
    res=ccall((:unur_tdr_set_max_intervals, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, max_ivs)
    res
end

export unur_tdr_set_usecenter
function unur_tdr_set_usecenter(parameters, usecenter)
    res=ccall((:unur_tdr_set_usecenter, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usecenter)
    res
end

export unur_tdr_set_usemode
function unur_tdr_set_usemode(parameters, usemode)
    res=ccall((:unur_tdr_set_usemode, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, usemode)
    res
end

export unur_tdr_set_guidefactor
function unur_tdr_set_guidefactor(parameters, factor)
    res=ccall((:unur_tdr_set_guidefactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_tdr_set_verify
function unur_tdr_set_verify(parameters, verify)
    res=ccall((:unur_tdr_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_tdr_chg_verify
function unur_tdr_chg_verify(generator, verify)
    res=ccall((:unur_tdr_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_tdr_set_pedantic
function unur_tdr_set_pedantic(parameters, pedantic)
    res=ccall((:unur_tdr_set_pedantic, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, pedantic)
    res
end

export unur_tdr_eval_invcdfhat
function unur_tdr_eval_invcdfhat(generator, u, hx, fx, sqx)
    res=ccall((:unur_tdr_eval_invcdfhat, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, Ptr{Cdouble}, Ptr{Cdouble}, Ptr{Cdouble}, ), generator, u, hx, fx, sqx)
    res
end

export unur_utdr_new
function unur_utdr_new(distribution)
    res=ccall((:unur_utdr_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_utdr_set_pdfatmode
function unur_utdr_set_pdfatmode(parameters, fmode)
    res=ccall((:unur_utdr_set_pdfatmode, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, fmode)
    res
end

export unur_utdr_set_cpfactor
function unur_utdr_set_cpfactor(parameters, cp_factor)
    res=ccall((:unur_utdr_set_cpfactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, cp_factor)
    res
end

export unur_utdr_set_deltafactor
function unur_utdr_set_deltafactor(parameters, delta)
    res=ccall((:unur_utdr_set_deltafactor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, delta)
    res
end

export unur_utdr_set_verify
function unur_utdr_set_verify(parameters, verify)
    res=ccall((:unur_utdr_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_utdr_chg_verify
function unur_utdr_chg_verify(generator, verify)
    res=ccall((:unur_utdr_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_utdr_chg_pdfatmode
function unur_utdr_chg_pdfatmode(generator, fmode)
    res=ccall((:unur_utdr_chg_pdfatmode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, fmode)
    res
end

export unur_empk_new
function unur_empk_new(distribution)
    res=ccall((:unur_empk_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_empk_set_kernel
function unur_empk_set_kernel(parameters, kernel)
    res=ccall((:unur_empk_set_kernel, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cuint, ), parameters, kernel)
    res
end

export unur_empk_set_kernelgen
function unur_empk_set_kernelgen(parameters, kernelgen, alpha, kernelvar)
    res=ccall((:unur_empk_set_kernelgen, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{UNUR_GEN}, Cdouble, Cdouble, ), parameters, kernelgen, alpha, kernelvar)
    res
end

export unur_empk_set_beta
function unur_empk_set_beta(parameters, beta)
    res=ccall((:unur_empk_set_beta, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, beta)
    res
end

export unur_empk_set_smoothing
function unur_empk_set_smoothing(parameters, smoothing)
    res=ccall((:unur_empk_set_smoothing, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, smoothing)
    res
end

export unur_empk_chg_smoothing
function unur_empk_chg_smoothing(generator, smoothing)
    res=ccall((:unur_empk_chg_smoothing, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, smoothing)
    res
end

export unur_empk_set_varcor
function unur_empk_set_varcor(parameters, varcor)
    res=ccall((:unur_empk_set_varcor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, varcor)
    res
end

export unur_empk_chg_varcor
function unur_empk_chg_varcor(generator, varcor)
    res=ccall((:unur_empk_chg_varcor, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, varcor)
    res
end

export unur_empk_set_positive
function unur_empk_set_positive(parameters, positive)
    res=ccall((:unur_empk_set_positive, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, positive)
    res
end

export unur_empl_new
function unur_empl_new(distribution)
    res=ccall((:unur_empl_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_hist_new
function unur_hist_new(distribution)
    res=ccall((:unur_hist_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_mvtdr_new
function unur_mvtdr_new(distribution)
    res=ccall((:unur_mvtdr_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_mvtdr_set_stepsmin
function unur_mvtdr_set_stepsmin(parameters, stepsmin)
    res=ccall((:unur_mvtdr_set_stepsmin, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, stepsmin)
    res
end

export unur_mvtdr_set_boundsplitting
function unur_mvtdr_set_boundsplitting(parameters, boundsplitting)
    res=ccall((:unur_mvtdr_set_boundsplitting, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, boundsplitting)
    res
end

export unur_mvtdr_set_maxcones
function unur_mvtdr_set_maxcones(parameters, maxcones)
    res=ccall((:unur_mvtdr_set_maxcones, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, maxcones)
    res
end

export unur_mvtdr_get_ncones
function unur_mvtdr_get_ncones(generator)
    res=ccall((:unur_mvtdr_get_ncones, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_mvtdr_get_hatvol
function unur_mvtdr_get_hatvol(generator)
    res=ccall((:unur_mvtdr_get_hatvol, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_mvtdr_set_verify
function unur_mvtdr_set_verify(parameters, verify)
    res=ccall((:unur_mvtdr_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_mvtdr_chg_verify
function unur_mvtdr_chg_verify(generator, verify)
    res=ccall((:unur_mvtdr_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_norta_new
function unur_norta_new(distribution)
    res=ccall((:unur_norta_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_vempk_new
function unur_vempk_new(distribution)
    res=ccall((:unur_vempk_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_vempk_set_smoothing
function unur_vempk_set_smoothing(parameters, smoothing)
    res=ccall((:unur_vempk_set_smoothing, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, smoothing)
    res
end

export unur_vempk_chg_smoothing
function unur_vempk_chg_smoothing(generator, smoothing)
    res=ccall((:unur_vempk_chg_smoothing, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, smoothing)
    res
end

export unur_vempk_set_varcor
function unur_vempk_set_varcor(parameters, varcor)
    res=ccall((:unur_vempk_set_varcor, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, varcor)
    res
end

export unur_vempk_chg_varcor
function unur_vempk_chg_varcor(generator, varcor)
    res=ccall((:unur_vempk_chg_varcor, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, varcor)
    res
end

export unur_vnrou_new
function unur_vnrou_new(distribution)
    res=ccall((:unur_vnrou_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_vnrou_set_u
function unur_vnrou_set_u(parameters, umin, umax)
    res=ccall((:unur_vnrou_set_u, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{Cdouble}, Ptr{Cdouble}, ), parameters, umin, umax)
    res
end

export unur_vnrou_chg_u
function unur_vnrou_chg_u(generator, umin, umax)
    res=ccall((:unur_vnrou_chg_u, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Ptr{Cdouble}, ), generator, umin, umax)
    res
end

export unur_vnrou_set_v
function unur_vnrou_set_v(parameters, vmax)
    res=ccall((:unur_vnrou_set_v, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, vmax)
    res
end

export unur_vnrou_chg_v
function unur_vnrou_chg_v(generator, vmax)
    res=ccall((:unur_vnrou_chg_v, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, vmax)
    res
end

export unur_vnrou_set_r
function unur_vnrou_set_r(parameters, r)
    res=ccall((:unur_vnrou_set_r, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, r)
    res
end

export unur_vnrou_set_verify
function unur_vnrou_set_verify(parameters, verify)
    res=ccall((:unur_vnrou_set_verify, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, verify)
    res
end

export unur_vnrou_chg_verify
function unur_vnrou_chg_verify(generator, verify)
    res=ccall((:unur_vnrou_chg_verify, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, verify)
    res
end

export unur_vnrou_get_volumehat
function unur_vnrou_get_volumehat(generator)
    res=ccall((:unur_vnrou_get_volumehat, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_gibbs_new
function unur_gibbs_new(distribution)
    res=ccall((:unur_gibbs_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_gibbs_set_variant_coordinate
function unur_gibbs_set_variant_coordinate(parameters)
    res=ccall((:unur_gibbs_set_variant_coordinate, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_gibbs_set_variant_random_direction
function unur_gibbs_set_variant_random_direction(parameters)
    res=ccall((:unur_gibbs_set_variant_random_direction, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_gibbs_set_c
function unur_gibbs_set_c(parameters, c)
    res=ccall((:unur_gibbs_set_c, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, c)
    res
end

export unur_gibbs_set_startingpoint
function unur_gibbs_set_startingpoint(parameters, x0)
    res=ccall((:unur_gibbs_set_startingpoint, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{Cdouble}, ), parameters, x0)
    res
end

export unur_gibbs_set_thinning
function unur_gibbs_set_thinning(parameters, thinning)
    res=ccall((:unur_gibbs_set_thinning, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, thinning)
    res
end

export unur_gibbs_set_burnin
function unur_gibbs_set_burnin(parameters, burnin)
    res=ccall((:unur_gibbs_set_burnin, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, burnin)
    res
end

export unur_gibbs_get_state
function unur_gibbs_get_state()
    res=ccall((:unur_gibbs_get_state, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_gibbs_chg_state
function unur_gibbs_chg_state(generator, state)
    res=ccall((:unur_gibbs_chg_state, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, ), generator, state)
    res
end

export unur_gibbs_reset_state
function unur_gibbs_reset_state(generator)
    res=ccall((:unur_gibbs_reset_state, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_hitro_new
function unur_hitro_new(distribution)
    res=ccall((:unur_hitro_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_hitro_set_variant_coordinate
function unur_hitro_set_variant_coordinate(parameters)
    res=ccall((:unur_hitro_set_variant_coordinate, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_hitro_set_variant_random_direction
function unur_hitro_set_variant_random_direction(parameters)
    res=ccall((:unur_hitro_set_variant_random_direction, "libunuran"), Cint, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_hitro_set_use_adaptiveline
function unur_hitro_set_use_adaptiveline(parameters, adaptive)
    res=ccall((:unur_hitro_set_use_adaptiveline, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, adaptive)
    res
end

export unur_hitro_set_use_boundingrectangle
function unur_hitro_set_use_boundingrectangle(parameters, rectangle)
    res=ccall((:unur_hitro_set_use_boundingrectangle, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, rectangle)
    res
end

export unur_hitro_set_use_adaptiverectangle
function unur_hitro_set_use_adaptiverectangle(parameters, adaptive)
    res=ccall((:unur_hitro_set_use_adaptiverectangle, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, adaptive)
    res
end

export unur_hitro_set_r
function unur_hitro_set_r(parameters, r)
    res=ccall((:unur_hitro_set_r, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, r)
    res
end

export unur_hitro_set_v
function unur_hitro_set_v(parameters, vmax)
    res=ccall((:unur_hitro_set_v, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, vmax)
    res
end

export unur_hitro_set_u
function unur_hitro_set_u(parameters, umin, umax)
    res=ccall((:unur_hitro_set_u, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{Cdouble}, Ptr{Cdouble}, ), parameters, umin, umax)
    res
end

export unur_hitro_set_adaptive_multiplier
function unur_hitro_set_adaptive_multiplier(parameters, factor)
    res=ccall((:unur_hitro_set_adaptive_multiplier, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cdouble, ), parameters, factor)
    res
end

export unur_hitro_set_startingpoint
function unur_hitro_set_startingpoint(parameters, x0)
    res=ccall((:unur_hitro_set_startingpoint, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{Cdouble}, ), parameters, x0)
    res
end

export unur_hitro_set_thinning
function unur_hitro_set_thinning(parameters, thinning)
    res=ccall((:unur_hitro_set_thinning, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, thinning)
    res
end

export unur_hitro_set_burnin
function unur_hitro_set_burnin(parameters, burnin)
    res=ccall((:unur_hitro_set_burnin, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, burnin)
    res
end

export unur_hitro_get_state
function unur_hitro_get_state()
    res=ccall((:unur_hitro_get_state, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_hitro_chg_state
function unur_hitro_chg_state(generator, state)
    res=ccall((:unur_hitro_chg_state, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, ), generator, state)
    res
end

export unur_hitro_reset_state
function unur_hitro_reset_state(generator)
    res=ccall((:unur_hitro_reset_state, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_cstd_new
function unur_cstd_new(distribution)
    res=ccall((:unur_cstd_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_cstd_set_variant
function unur_cstd_set_variant(parameters, variant)
    res=ccall((:unur_cstd_set_variant, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cuint, ), parameters, variant)
    res
end

export unur_cstd_chg_truncated
function unur_cstd_chg_truncated(generator, left, right)
    res=ccall((:unur_cstd_chg_truncated, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), generator, left, right)
    res
end

export unur_cstd_eval_invcdf
function unur_cstd_eval_invcdf(generator, u)
    res=ccall((:unur_cstd_eval_invcdf, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, ), generator, u)
    res
end

export unur_dstd_new
function unur_dstd_new(distribution)
    res=ccall((:unur_dstd_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_dstd_set_variant
function unur_dstd_set_variant(parameters, variant)
    res=ccall((:unur_dstd_set_variant, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cuint, ), parameters, variant)
    res
end

export unur_dstd_chg_truncated
function unur_dstd_chg_truncated(generator, left, right)
    res=ccall((:unur_dstd_chg_truncated, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, Cint, ), generator, left, right)
    res
end

export unur_dstd_eval_invcdf
function unur_dstd_eval_invcdf(generator, u)
    res=ccall((:unur_dstd_eval_invcdf, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, u)
    res
end

export unur_mvstd_new
function unur_mvstd_new(distribution)
    res=ccall((:unur_mvstd_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_mixt_new
function unur_mixt_new(n, prob, comp)
    res=ccall((:unur_mixt_new, "libunuran"), Ptr{UNUR_PAR}, (Cint, Ptr{Cdouble}, Ptr{UNUR_GEN}, ), n, prob, comp)
    res
end

export unur_mixt_set_useinversion
function unur_mixt_set_useinversion(parameters, useinv)
    res=ccall((:unur_mixt_set_useinversion, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, useinv)
    res
end

export unur_mixt_eval_invcdf
function unur_mixt_eval_invcdf(generator, u)
    res=ccall((:unur_mixt_eval_invcdf, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, ), generator, u)
    res
end

export unur_cext_new
function unur_cext_new(distribution)
    res=ccall((:unur_cext_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_cext_set_init
function unur_cext_set_init(parameters, init)
    res=ccall((:unur_cext_set_init, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{UNUR_GEN}, ), parameters, init)
    res
end

export unur_cext_set_sample
function unur_cext_set_sample(parameters, sample)
    res=ccall((:unur_cext_set_sample, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{UNUR_GEN}, ), parameters, sample)
    res
end

export unur_cext_get_params
function unur_cext_get_params(size)
    res=ccall((:unur_cext_get_params, "libunuran"), Ptr{Ptr{Typedef}}, (Csize_t, ), size)
    res
end

export unur_cext_get_distrparams
function unur_cext_get_distrparams()
    res=ccall((:unur_cext_get_distrparams, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_cext_get_ndistrparams
function unur_cext_get_ndistrparams(generator)
    res=ccall((:unur_cext_get_ndistrparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_dext_new
function unur_dext_new(distribution)
    res=ccall((:unur_dext_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_dext_set_init
function unur_dext_set_init(parameters, init)
    res=ccall((:unur_dext_set_init, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{UNUR_GEN}, ), parameters, init)
    res
end

export unur_dext_set_sample
function unur_dext_set_sample(parameters, sample)
    res=ccall((:unur_dext_set_sample, "libunuran"), Cint, (Ptr{UNUR_PAR}, Ptr{UNUR_GEN}, ), parameters, sample)
    res
end

export unur_dext_get_params
function unur_dext_get_params(size)
    res=ccall((:unur_dext_get_params, "libunuran"), Ptr{Ptr{Typedef}}, (Csize_t, ), size)
    res
end

export unur_dext_get_distrparams
function unur_dext_get_distrparams()
    res=ccall((:unur_dext_get_distrparams, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_dext_get_ndistrparams
function unur_dext_get_ndistrparams(generator)
    res=ccall((:unur_dext_get_ndistrparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_unif_new
function unur_unif_new(dummy)
    res=ccall((:unur_unif_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), dummy)
    res
end

export unur_distr_cvec_set_stdmarginals
function unur_distr_cvec_set_stdmarginals(distribution, marginal)
    res=ccall((:unur_distr_cvec_set_stdmarginals, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{UNUR_DISTR}, ), distribution, marginal)
    res
end

export unur_distr_cvec_set_stdmarginal_array
function unur_distr_cvec_set_stdmarginal_array(distribution, marginals)
    res=ccall((:unur_distr_cvec_set_stdmarginal_array, "libunuran"), Cint, (Ptr{UNUR_DISTR}, Ptr{UNUR_DISTR}, ), distribution, marginals)
    res
end

export unur_distr_cvec_set_stdmarginal_list
function unur_distr_cvec_set_stdmarginal_list(distribution)
    res=ccall((:unur_distr_cvec_set_stdmarginal_list, "libunuran"), Cint, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_distr_cvec_get_stdmarginal
function unur_distr_cvec_get_stdmarginal(distribution, n)
    res=ccall((:unur_distr_cvec_get_stdmarginal, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_DISTR}, Cint, ), distribution, n)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cvec_get_stdmarginal"))
    end
    res
end

export unur_cstd_chg_pdfparams
function unur_cstd_chg_pdfparams(generator, params, n_params)
    res=ccall((:unur_cstd_chg_pdfparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Cint, ), generator, params, n_params)
    res
end

export unur_dari_reinit
function unur_dari_reinit(generator)
    res=ccall((:unur_dari_reinit, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_dari_chg_pmfparams
function unur_dari_chg_pmfparams(generator, params, n_params)
    res=ccall((:unur_dari_chg_pmfparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Cint, ), generator, params, n_params)
    res
end

export unur_dari_chg_domain
function unur_dari_chg_domain(generator, left, right)
    res=ccall((:unur_dari_chg_domain, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, Cint, ), generator, left, right)
    res
end

export unur_dari_chg_mode
function unur_dari_chg_mode(generator, mode)
    res=ccall((:unur_dari_chg_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, mode)
    res
end

export unur_dari_upd_mode
function unur_dari_upd_mode(generator)
    res=ccall((:unur_dari_upd_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_dari_chg_pmfsum
function unur_dari_chg_pmfsum(generator, sum)
    res=ccall((:unur_dari_chg_pmfsum, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, sum)
    res
end

export unur_dari_upd_pmfsum
function unur_dari_upd_pmfsum(generator)
    res=ccall((:unur_dari_upd_pmfsum, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_dsrou_reinit
function unur_dsrou_reinit(generator)
    res=ccall((:unur_dsrou_reinit, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_dsrou_chg_pmfparams
function unur_dsrou_chg_pmfparams(generator, params, n_params)
    res=ccall((:unur_dsrou_chg_pmfparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Cint, ), generator, params, n_params)
    res
end

export unur_dsrou_chg_domain
function unur_dsrou_chg_domain(generator, left, right)
    res=ccall((:unur_dsrou_chg_domain, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, Cint, ), generator, left, right)
    res
end

export unur_dsrou_chg_mode
function unur_dsrou_chg_mode(generator, mode)
    res=ccall((:unur_dsrou_chg_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cint, ), generator, mode)
    res
end

export unur_dsrou_upd_mode
function unur_dsrou_upd_mode(generator)
    res=ccall((:unur_dsrou_upd_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_dsrou_chg_pmfsum
function unur_dsrou_chg_pmfsum(generator, sum)
    res=ccall((:unur_dsrou_chg_pmfsum, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, sum)
    res
end

export unur_dsrou_upd_pmfsum
function unur_dsrou_upd_pmfsum(generator)
    res=ccall((:unur_dsrou_upd_pmfsum, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_dstd_chg_pmfparams
function unur_dstd_chg_pmfparams(gen, params, n_params)
    res=ccall((:unur_dstd_chg_pmfparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Cint, ), gen, params, n_params)
    res
end

export unur_ninv_chg_pdfparams
function unur_ninv_chg_pdfparams(generator, params, n_params)
    res=ccall((:unur_ninv_chg_pdfparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Cint, ), generator, params, n_params)
    res
end

export unur_srou_reinit
function unur_srou_reinit(generator)
    res=ccall((:unur_srou_reinit, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_srou_chg_pdfparams
function unur_srou_chg_pdfparams(generator, params, n_params)
    res=ccall((:unur_srou_chg_pdfparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Cint, ), generator, params, n_params)
    res
end

export unur_srou_chg_domain
function unur_srou_chg_domain(generator, left, right)
    res=ccall((:unur_srou_chg_domain, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), generator, left, right)
    res
end

export unur_srou_chg_mode
function unur_srou_chg_mode(generator, mode)
    res=ccall((:unur_srou_chg_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, mode)
    res
end

export unur_srou_upd_mode
function unur_srou_upd_mode(generator)
    res=ccall((:unur_srou_upd_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_srou_chg_pdfarea
function unur_srou_chg_pdfarea(generator, area)
    res=ccall((:unur_srou_chg_pdfarea, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, area)
    res
end

export unur_srou_upd_pdfarea
function unur_srou_upd_pdfarea(generator)
    res=ccall((:unur_srou_upd_pdfarea, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_ssr_reinit
function unur_ssr_reinit(generator)
    res=ccall((:unur_ssr_reinit, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_ssr_chg_pdfparams
function unur_ssr_chg_pdfparams(generator, params, n_params)
    res=ccall((:unur_ssr_chg_pdfparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Cint, ), generator, params, n_params)
    res
end

export unur_ssr_chg_domain
function unur_ssr_chg_domain(generator, left, right)
    res=ccall((:unur_ssr_chg_domain, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), generator, left, right)
    res
end

export unur_ssr_chg_mode
function unur_ssr_chg_mode(generator, mode)
    res=ccall((:unur_ssr_chg_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, mode)
    res
end

export unur_ssr_upd_mode
function unur_ssr_upd_mode(generator)
    res=ccall((:unur_ssr_upd_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_ssr_chg_pdfarea
function unur_ssr_chg_pdfarea(generator, area)
    res=ccall((:unur_ssr_chg_pdfarea, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, area)
    res
end

export unur_ssr_upd_pdfarea
function unur_ssr_upd_pdfarea(generator)
    res=ccall((:unur_ssr_upd_pdfarea, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tdr_reinit
function unur_tdr_reinit(generator)
    res=ccall((:unur_tdr_reinit, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_tdrgw_reinit
function unur_tdrgw_reinit(generator)
    res=ccall((:unur_tdrgw_reinit, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_utdr_reinit
function unur_utdr_reinit(generator)
    res=ccall((:unur_utdr_reinit, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_utdr_chg_pdfparams
function unur_utdr_chg_pdfparams(generator, params, n_params)
    res=ccall((:unur_utdr_chg_pdfparams, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, Cint, ), generator, params, n_params)
    res
end

export unur_utdr_chg_domain
function unur_utdr_chg_domain(generator, left, right)
    res=ccall((:unur_utdr_chg_domain, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, Cdouble, ), generator, left, right)
    res
end

export unur_utdr_chg_mode
function unur_utdr_chg_mode(generator, mode)
    res=ccall((:unur_utdr_chg_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, mode)
    res
end

export unur_utdr_upd_mode
function unur_utdr_upd_mode(generator)
    res=ccall((:unur_utdr_upd_mode, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_utdr_chg_pdfarea
function unur_utdr_chg_pdfarea(generator, area)
    res=ccall((:unur_utdr_chg_pdfarea, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cdouble, ), generator, area)
    res
end

export unur_utdr_upd_pdfarea
function unur_utdr_upd_pdfarea(generator)
    res=ccall((:unur_utdr_upd_pdfarea, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_vmt_new
function unur_vmt_new(distribution)
    res=ccall((:unur_vmt_new, "libunuran"), Ptr{UNUR_PAR}, (Ptr{UNUR_DISTR}, ), distribution)
    res
end

export unur_str2gen
function unur_str2gen(string)
    res=ccall((:unur_str2gen, "libunuran"), Ptr{UNUR_GEN}, (Cstring, ), string)
    res
end

export unur_str2distr
function unur_str2distr(string)
    res=ccall((:unur_str2distr, "libunuran"), Ptr{UNUR_DISTR}, (Cstring, ), string)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_str2distr"))
    end
    res
end

export unur_makegen_ssu
function unur_makegen_ssu(distrstr, methodstr, urng)
    res=ccall((:unur_makegen_ssu, "libunuran"), Ptr{UNUR_GEN}, (Cstring, Cstring, Ptr{UNUR_URNG}, ), distrstr, methodstr, urng)
    res
end

export unur_makegen_dsu
function unur_makegen_dsu(distribution, methodstr, urng)
    res=ccall((:unur_makegen_dsu, "libunuran"), Ptr{UNUR_GEN}, (Ptr{UNUR_DISTR}, Cstring, Ptr{UNUR_URNG}, ), distribution, methodstr, urng)
    res
end

export unur_init
function unur_init(parameters)
    res=ccall((:unur_init, "libunuran"), Ptr{UNUR_GEN}, (Ptr{UNUR_PAR}, ), parameters)
    res
end

export unur_reinit
function unur_reinit(generator)
    res=ccall((:unur_reinit, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_sample_discr
function unur_sample_discr(generator)
    res=ccall((:unur_sample_discr, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_sample_cont
function unur_sample_cont(generator)
    res=ccall((:unur_sample_cont, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_sample_vec
function unur_sample_vec(generator, vector)
    res=ccall((:unur_sample_vec, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, ), generator, vector)
    res
end

export unur_sample_matr
function unur_sample_matr(generator, matrix)
    res=ccall((:unur_sample_matr, "libunuran"), Cint, (Ptr{UNUR_GEN}, Ptr{Cdouble}, ), generator, matrix)
    res
end

export unur_quantile
function unur_quantile(generator, U)
    res=ccall((:unur_quantile, "libunuran"), Cdouble, (Ptr{UNUR_GEN}, Cdouble, ), generator, U)
    res
end

export unur_free
function unur_free(generator)
    res=ccall((:unur_free, "libunuran"), Void, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_gen_info
function unur_gen_info(help)
    res=ccall((:unur_gen_info, "libunuran"), Ptr{Ptr{Typedef}}, (Cint, ), help)
    res
end

export unur_get_dimension
function unur_get_dimension(generator)
    res=ccall((:unur_get_dimension, "libunuran"), Cint, (Ptr{UNUR_GEN}, ), generator)
    res
end

export unur_get_genid
function unur_get_genid()
    res=ccall((:unur_get_genid, "libunuran"), Ptr{Ptr{Typedef}}, () )
    res
end

export unur_get_distr
function unur_get_distr(generator)
    res=ccall((:unur_get_distr, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{UNUR_GEN}, ), generator)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_get_distr"))
    end
    res
end

export unur_set_use_distr_privatecopy
function unur_set_use_distr_privatecopy(parameters, use_privatecopy)
    res=ccall((:unur_set_use_distr_privatecopy, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cint, ), parameters, use_privatecopy)
    res
end

export unur_gen_clone
function unur_gen_clone(gen)
    res=ccall((:unur_gen_clone, "libunuran"), Ptr{UNUR_GEN}, (Ptr{UNUR_GEN}, ), gen)
    res
end

export unur_par_free
function unur_par_free(par)
    res=ccall((:unur_par_free, "libunuran"), Void, (Ptr{UNUR_PAR}, ), par)
    res
end

export unur_distr_beta
function unur_distr_beta(params, n_params)
    res=ccall((:unur_distr_beta, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_beta"))
    end
    res
end

export unur_distr_burr
function unur_distr_burr(params, n_params)
    res=ccall((:unur_distr_burr, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_burr"))
    end
    res
end

export unur_distr_cauchy
function unur_distr_cauchy(params, n_params)
    res=ccall((:unur_distr_cauchy, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_cauchy"))
    end
    res
end

export unur_distr_chi
function unur_distr_chi(params, n_params)
    res=ccall((:unur_distr_chi, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_chi"))
    end
    res
end

export unur_distr_chisquare
function unur_distr_chisquare(params, n_params)
    res=ccall((:unur_distr_chisquare, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_chisquare"))
    end
    res
end

export unur_distr_exponential
function unur_distr_exponential(params, n_params)
    res=ccall((:unur_distr_exponential, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_exponential"))
    end
    res
end

export unur_distr_extremeI
function unur_distr_extremeI(params, n_params)
    res=ccall((:unur_distr_extremeI, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_extremeI"))
    end
    res
end

export unur_distr_extremeII
function unur_distr_extremeII(params, n_params)
    res=ccall((:unur_distr_extremeII, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_extremeII"))
    end
    res
end

export unur_distr_F
function unur_distr_F(params, n_params)
    res=ccall((:unur_distr_F, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_F"))
    end
    res
end

export unur_distr_gamma
function unur_distr_gamma(params, n_params)
    res=ccall((:unur_distr_gamma, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_gamma"))
    end
    res
end

export unur_distr_ghyp
function unur_distr_ghyp(params, n_params)
    res=ccall((:unur_distr_ghyp, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_ghyp"))
    end
    res
end

export unur_distr_gig
function unur_distr_gig(params, n_params)
    res=ccall((:unur_distr_gig, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_gig"))
    end
    res
end

export unur_distr_gig2
function unur_distr_gig2(params, n_params)
    res=ccall((:unur_distr_gig2, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_gig2"))
    end
    res
end

export unur_distr_hyperbolic
function unur_distr_hyperbolic(params, n_params)
    res=ccall((:unur_distr_hyperbolic, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_hyperbolic"))
    end
    res
end

export unur_distr_ig
function unur_distr_ig(params, n_params)
    res=ccall((:unur_distr_ig, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_ig"))
    end
    res
end

export unur_distr_laplace
function unur_distr_laplace(params, n_params)
    res=ccall((:unur_distr_laplace, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_laplace"))
    end
    res
end

export unur_distr_logistic
function unur_distr_logistic(params, n_params)
    res=ccall((:unur_distr_logistic, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_logistic"))
    end
    res
end

export unur_distr_lognormal
function unur_distr_lognormal(params, n_params)
    res=ccall((:unur_distr_lognormal, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_lognormal"))
    end
    res
end

export unur_distr_lomax
function unur_distr_lomax(params, n_params)
    res=ccall((:unur_distr_lomax, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_lomax"))
    end
    res
end

export unur_distr_normal
function unur_distr_normal(params, n_params)
    res=ccall((:unur_distr_normal, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_normal"))
    end
    res
end

export unur_distr_pareto
function unur_distr_pareto(params, n_params)
    res=ccall((:unur_distr_pareto, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_pareto"))
    end
    res
end

export unur_distr_powerexponential
function unur_distr_powerexponential(params, n_params)
    res=ccall((:unur_distr_powerexponential, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_powerexponential"))
    end
    res
end

export unur_distr_rayleigh
function unur_distr_rayleigh(params, n_params)
    res=ccall((:unur_distr_rayleigh, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_rayleigh"))
    end
    res
end

export unur_distr_slash
function unur_distr_slash(params, n_params)
    res=ccall((:unur_distr_slash, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_slash"))
    end
    res
end

export unur_distr_student
function unur_distr_student(params, n_params)
    res=ccall((:unur_distr_student, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_student"))
    end
    res
end

export unur_distr_triangular
function unur_distr_triangular(params, n_params)
    res=ccall((:unur_distr_triangular, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_triangular"))
    end
    res
end

export unur_distr_uniform
function unur_distr_uniform(params, n_params)
    res=ccall((:unur_distr_uniform, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_uniform"))
    end
    res
end

export unur_distr_weibull
function unur_distr_weibull(params, n_params)
    res=ccall((:unur_distr_weibull, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_weibull"))
    end
    res
end

export unur_distr_multinormal
function unur_distr_multinormal(dim, mean, covar)
    res=ccall((:unur_distr_multinormal, "libunuran"), Ptr{UNUR_DISTR}, (Cint, Ptr{Cdouble}, Ptr{Cdouble}, ), dim, mean, covar)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_multinormal"))
    end
    res
end

export unur_distr_multicauchy
function unur_distr_multicauchy(dim, mean, covar)
    res=ccall((:unur_distr_multicauchy, "libunuran"), Ptr{UNUR_DISTR}, (Cint, Ptr{Cdouble}, Ptr{Cdouble}, ), dim, mean, covar)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_multicauchy"))
    end
    res
end

export unur_distr_multistudent
function unur_distr_multistudent(dim, nu, mean, covar)
    res=ccall((:unur_distr_multistudent, "libunuran"), Ptr{UNUR_DISTR}, (Cint, Cdouble, Ptr{Cdouble}, Ptr{Cdouble}, ), dim, nu, mean, covar)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_multistudent"))
    end
    res
end

export unur_distr_multiexponential
function unur_distr_multiexponential(dim, sigma, theta)
    res=ccall((:unur_distr_multiexponential, "libunuran"), Ptr{UNUR_DISTR}, (Cint, Ptr{Cdouble}, Ptr{Cdouble}, ), dim, sigma, theta)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_multiexponential"))
    end
    res
end

export unur_distr_copula
function unur_distr_copula(dim, rankcorr)
    res=ccall((:unur_distr_copula, "libunuran"), Ptr{UNUR_DISTR}, (Cint, Ptr{Cdouble}, ), dim, rankcorr)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_copula"))
    end
    res
end

export unur_distr_correlation
function unur_distr_correlation(n)
    res=ccall((:unur_distr_correlation, "libunuran"), Ptr{UNUR_DISTR}, (Cint, ), n)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_correlation"))
    end
    res
end

export unur_distr_binomial
function unur_distr_binomial(params, n_params)
    res=ccall((:unur_distr_binomial, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_binomial"))
    end
    res
end

export unur_distr_geometric
function unur_distr_geometric(params, n_params)
    res=ccall((:unur_distr_geometric, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_geometric"))
    end
    res
end

export unur_distr_hypergeometric
function unur_distr_hypergeometric(params, n_params)
    res=ccall((:unur_distr_hypergeometric, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_hypergeometric"))
    end
    res
end

export unur_distr_logarithmic
function unur_distr_logarithmic(params, n_params)
    res=ccall((:unur_distr_logarithmic, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_logarithmic"))
    end
    res
end

export unur_distr_negativebinomial
function unur_distr_negativebinomial(params, n_params)
    res=ccall((:unur_distr_negativebinomial, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_negativebinomial"))
    end
    res
end

export unur_distr_poisson
function unur_distr_poisson(params, n_params)
    res=ccall((:unur_distr_poisson, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_poisson"))
    end
    res
end

export unur_distr_zipf
function unur_distr_zipf(params, n_params)
    res=ccall((:unur_distr_zipf, "libunuran"), Ptr{UNUR_DISTR}, (Ptr{Cdouble}, Cint, ), params, n_params)
    if res==C_NULL
        throw(SystemError("Null distribution returned by calling unur_distr_zipf"))
    end
    res
end

export unur_set_stream
function unur_set_stream(new_stream)
    res=ccall((:unur_set_stream, "libunuran"), Ptr{FILE}, (Ptr{Typedef}, ), new_stream)
    res
end

export unur_get_stream
function unur_get_stream()
    res=ccall((:unur_get_stream, "libunuran"), Ptr{FILE}, () )
    res
end

export unur_set_debug
function unur_set_debug(parameters, debug)
    res=ccall((:unur_set_debug, "libunuran"), Cint, (Ptr{UNUR_PAR}, Cuint, ), parameters, debug)
    res
end

export unur_chg_debug
function unur_chg_debug(generator, debug)
    res=ccall((:unur_chg_debug, "libunuran"), Cint, (Ptr{UNUR_GEN}, Cuint, ), generator, debug)
    res
end

export unur_set_default_debug
function unur_set_default_debug(debug)
    res=ccall((:unur_set_default_debug, "libunuran"), Cint, (Cuint, ), debug)
    res
end

export unur_get_errno
function unur_get_errno()
    res=ccall((:unur_get_errno, "libunuran"), Cint, () )
    res
end

export unur_reset_errno
function unur_reset_errno()
    res=ccall((:unur_reset_errno, "libunuran"), Void, () )
    res
end

export unur_get_strerror
function unur_get_strerror()
    res=ccall((:unur_get_strerror, "libunuran"), Ptr{Int}, () )
    res
end

export unur_set_error_handler
function unur_set_error_handler(new_handler)
    res=ccall((:unur_set_error_handler, "libunuran"), Ptr{UNUR_ERROR_HANDLER}, (Ptr{Void}, ), new_handler)
    res
end

export unur_set_error_handler_off
function unur_set_error_handler_off()
    res=ccall((:unur_set_error_handler_off, "libunuran"), Ptr{UNUR_ERROR_HANDLER}, () )
    res
end

