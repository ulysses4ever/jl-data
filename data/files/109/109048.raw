nr = 5000
ret = randn(nr)/100
dum = rand(0:1, nr)
dum_f = float(dum)
freq = 252
niter = 5000

function vec_dum_stats(ret, dum; freq = 252)
	n_f = float(size(ret)[1])
	freq_f = float(freq)
	dum_f = float(dum)
	dum_b = bool(dum)
	sqrt_freq = sqrt(freq)

	n_pos = sum(dum)
	pos_ret = .*(ret, dum_f)
	cumsum_ret = cumsum(pos_ret)
	tot_ret = last(cumsum_ret)
	mean_ret = tot_ret/n_f
    mean_ann_ret = mean_ret * freq_f
    sd_ret = std(pos_ret)
    sd_ann_ret = sd_ret * sqrt_freq
    info_ratio = mean_ann_ret/sd_ann_ret
    cummax_ret = cummax(cumsum_ret)
    drawdown = cummax_ret - cumsum_ret
    maxdrawdown = max(drawdown)
    calmar_ratio = tot_ret/maxdrawdown
    mean_ret_trd = tot_ret/n_pos
    mean_ann_ret_trd = mean_ret_trd * freq
    ret_trd = pos_ret[dum_b]

    if (n_pos > 1)
        sd_ret_trd = std(ret_trd)
        sd_ann_ret_trd = sd_ret_trd * sqrt_freq
        info_ratio_trd = mean_ann_ret_trd/sd_ann_ret_trd
    else
        sd_ret_trd = sd_ann_ret_trd = info_ratio_trd = NaN
    end

	{
        "TotalReturn",  tot_ret,
        "MeanReturn",  mean_ret,
        "MeanAnnualReturn",  mean_ann_ret,
        "StDevReturn",  sd_ret,
        "StDevAnnualReturn",  sd_ann_ret,
        "InfoRatio",  info_ratio,
        "MeanReturnTraded",  mean_ret_trd,
        "MeanAnnualReturnTraded",  mean_ann_ret_trd,
        "StDevReturnTraded",  sd_ret_trd,
        "StDevAnnualReturnTraded",  sd_ann_ret_trd,
        "InfoRatioTraded",  info_ratio_trd,
        "MaxDrawdown",  maxdrawdown,
        "CalmarRatio",  calmar_ratio,
        "NPos",  n_pos,
        "TradedReturns",  ret_trd
    }
end

vds = vec_dum_stats(ret, dum);
foo(n) = [vec_dum_stats(ret, dum) for i in 1:n]
z = {1, 2, 3, 4}
@parallel for i = 1:4
	z[i] = foo(2)
	end

bar(i::Int) = (min(i, 1000) * min(i, 1000)) + 1

tic()
vdsp = [vec_dum_stats(ret, dum) for i = 1:10000];
toc()

println("Finished\n")	