tic()

using ROS
@pyimport std_msgs

ROS.init_node("echo")
pub = ROS.Publisher("incoming", std_msgs.msg["String"])

callback(data) = pub[:publish](data)
ROS.Subscriber("outgoing", std_msgs.msg["String"], callback)

println("Startup: $(toc())")

ROS.spin()
