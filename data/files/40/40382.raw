using TR55
using Base.Test

# Test cases from the TR-55 manual example worksheets
# http://www.nrcs.usda.gov/Internet/FSE_DOCUMENTS/stelprdb1044171.pdf

# Figure 2-5
figure_25_s = round(TR55.s(70), 2)
figure_25_q = round(TR55.q(figure_25_s, 6), 2)
@test figure_25_s == 4.29
@test figure_25_q == 2.8

# Figure 2-6
figure_26_s = round(TR55.s(75), 2)
figure_26_q = round(TR55.q(figure_26_s, 6), 2)
@test figure_26_s == 3.33
@test figure_26_q == 3.28

# Figure 2-7
figure_27_s = round(TR55.s(77), 2)
figure_27_q = round(TR55.q(figure_27_s, 6), 2)
@test figure_27_s == 2.99
@test figure_27_q == 3.48

# Figure 2-8
figure_28_s = round(TR55.s(74), 2)
figure_28_q = round(TR55.q(figure_28_s, 6), 2)
@test figure_28_s == 3.51
@test figure_28_q == 3.19
