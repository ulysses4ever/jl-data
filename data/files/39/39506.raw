tic()

using ROS
@pyimport std_msgs

ROS.init_node("listener")

pub = ROS.Publisher("outgoing", std_msgs.msg["String"])

global count = 0
global init
num_messages = 100

function callback(data)
  global count += 1
  if count < num_messages
    pub[:publish](data)
  else
    run = time() - init
    println("Time to send $(num_messages) Strings: $(run)")
    println("Latency: $(run/(2*num_messages))")
  end
end

ROS.Subscriber("incoming", std_msgs.msg["String"], callback)

println("Startup: $(toc())")
tic()

r = ROS.Rate(50)

sleep(1)
init = time()
sent = 0
while !ROS.is_shutdown()
  if count >= 100
    break
  end
  r[:sleep]()
  if sent < 2
    pub[:publish]("Hello World: $sent")
    sent += 1
  end
end
