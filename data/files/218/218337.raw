
# create the input signal
T = 5000;
t = linspace(0, 2*pi, T);

x1 = sin(t)+cos(11*t).^2;
x2 = cos(11*t);
x = vcat(x1, x2);

# plot the original signal 
using Winston
plot(x1, x2, "b")


# get slow signals
using SFA
y = linsfa(x);
