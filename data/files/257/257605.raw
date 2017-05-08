using MsgPack

module client

type Method
  args::String
  ret_type::String
  args_type::String

  function Method(args, ret_type, args_type)
    this = new()
    this.args = args
    this.ret_type = ret_type
    this.args_type = args_type
    this
  end

end

type Error
end

function error_handler(e::Error)
end

type Client
  name::String

  function Client(name::String)
    this = new()
    this.name = name
    this
  end

  function init(self::Client)
    # self.client = client
    # self.name = name
  end

  function call(self::Client, m::Method)
    # ToDo: Implement some msgpack features.
    if length(m.args) != length(m.args_type)
    end

    target = Dict()
    for i = 1:length(m.args)
      merge!(target, Dict(m.args[i] => m.args_type[i]))
    end
    values = [self.name]
    for (v, t) in target
      # append(values, to_msgpack(t,v))
    end

    # future = self.client.call_async(m, values)
    # future.attach_error_handler(error_handler)
    # ret = future.get()

    # if m.ret_type != nothing
    #   return m.ret_type.from_msgpack(ret)
    # end
  end

end

type Host
  id::Int
  ip::String
  port::Int
  name::String
  timeout::Int

  function Host(id, ip, port, name, timeout)
    this = new()
    this.id = id
    this.ip = ip
    this.port = port
    this.name = name
    this.timeout = timeout
    this
  end

end

type ClientBase
  client::Client

  function ClientBase(client)
    this = new()
    this.client = client
    this
  end

  function init(self::ClientBase, host::Host)
    # address = msgpackrpc.Address(host.ip, host.port)
    # self.client = msgpackrpc.Client(address, host.timeout)
    # self.jubatus_client = Client(self.client, self.client.name)
  end

  function get_client(self::ClientBase)
    return self.client
  end

  function get_name(self::ClientBase)
    return self.client.name
  end

  function set_name(self::ClientBase, name::String)
    self.client.name = name
  end

  function save(self::ClientBase, id::Int)
    #return self.client.call("save", [id], TBool(), [TString()])
  end

  function load(self::ClientBase, id::Int)
    #return self.client.call("load", [id], TBool(), [TString()])
  end

  function do_mix(self::ClientBase)
    #return self.client.call("do_mix", [], TBool(), [])
  end

  function get_config(self::ClientBase)
    #return self.client.call("get_config", [], TString(), [])
  end

  function get_status(self::ClientBase)
    #return self.client.call("get_status", [], TMap(TString(), TMap(TString(), TString())), [])
  end

  function get_proxy_status(self::ClientBase)
    #return self.client.call("get_proxy_status", [], TMap(TString(), TMap(TString(), TString())), [])
  end

end

end #module
