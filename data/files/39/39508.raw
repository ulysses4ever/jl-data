using ROS
@pyimport std_msgs

callback(data) = ROS.loginfo("$(ROS.get_caller_id()) I heard: $(data[:data])")

ROS.init_node("listener")
ROS.Subscriber("chatter", std_msgs.msg["String"], callback)
ROS.spin()
