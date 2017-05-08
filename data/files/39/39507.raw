using ROS
@pyimport std_msgs

pub = ROS.Publisher("chatter", std_msgs.msg["String"])
ROS.init_node("talker")
r = ROS.Rate(10)

while !ROS.is_shutdown()
  str = "hello world $(ROS.get_time())"
  ROS.loginfo(str)
  pub[:publish](str)
  r[:sleep]()
end
