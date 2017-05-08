using TR55
using Base.Test

# Test cases from the TR-55 manual example worksheets
# http://www.nrcs.usda.gov/Internet/FSE_DOCUMENTS/stelprdb1044171.pdf

# Figure 2-5
figure_25_regions = [{"area" => 30, "cn" => 61}, {"area" => 70, "cn" => 74}]
figure_25_cn = TR55.weighted_cn(figure_25_regions, true)
figure_25_s = TR55.max_retention(figure_25_cn)
figure_25_q = TR55.runoff(figure_25_s, 6)

@test figure_25_cn == 70
@test figure_25_s == 4.29
@test figure_25_q == 2.8

# Figure 2-6
figure_26_regions = [{"area" => 75, "cn" => 70}, {"area" => 100, "cn" => 80}, {"area" => 75, "cn" => 74}]
figure_26_cn = TR55.weighted_cn(figure_26_regions, false)
figure_26_s = TR55.max_retention(figure_26_cn)
figure_26_q = TR55.runoff(figure_26_s, 6)

@test figure_26_cn == 75
@test figure_26_s == 3.33
@test figure_26_q == 3.28

# Figure 2-7
figure_27_regions = [{"area" => 75, "cn" => 74}, {"area" => 100, "cn" => 82}, {"area" => 75, "cn" => 74}]
figure_27_cn = TR55.weighted_cn(figure_27_regions, false)
figure_27_s = TR55.max_retention(77)
figure_27_q = TR55.runoff(figure_27_s, 6)

@test figure_27_cn == 77
@test figure_27_s == 2.99
@test figure_27_q == 3.48

# Figure 2-8
figure_28_s = TR55.max_retention(74)
figure_28_q = TR55.runoff(figure_28_s, 6)
figure_28_regions = [{"area" => 75, "cn" => 70}, {"area" => 100, "cn" => 78}, {"area" => 75, "cn" => 74}]
figure_28_cn = TR55.weighted_cn(figure_28_regions, false)

@test figure_28_cn == 74
@test figure_28_s == 3.51
@test figure_28_q == 3.19

# Test that weighted CN requires areas to sum to 100 when using percents
test_regions = [{"area" => 20, "cn" => 61}, {"area" => 90, "cn" => 74}]
@test_throws ErrorException TR55.weighted_cn(test_regions, true)
