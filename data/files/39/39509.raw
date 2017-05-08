module ROS

export @pyimport, @rosmsg, @temp, pyimport

using PyCall
@pyimport rospy

#Copy rospy's namespace to ROS
for i = names(rospy)
  if isdefined(rospy,i)
    @eval const $i = rospy.$i
  end
end

#In progress message import
macro rosmsg(pack, msg_type)
  return quote
    if !isdefined($(esc(Expr(:quote,pack))))
      @pyimport($(esc(pack)))
    end
    #global $msg_type = $pack.msg[string($msg_type)]
  end
end

is_shutdown() = rospy.is_shutdown()

end
