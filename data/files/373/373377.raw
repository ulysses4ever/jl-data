# Run one simulation.

# -------------------------------------------------------------------------
function simulation( mp::Array, bp::Array, param::Parameters, dist::Dist,
                    data::Data )

  # set up simulation
  sim = set_up_sim( mp, bp, param )

  # ---------------------- Run simulation ---------------------------------
  for d = 1 : param.D

    u = sim.u_0

    for t = 1 : param.T

      # store values
      sim.s[d, t] = u
      sim.b[d, t, :, 3] = u

      for i = 1 : param.I

        # debugging
        #@printf "d=%d, t=%d, i=%d\n" d t i

        # retrieve information
        w = sim.w[d, t, i]

        # simplified: determine variable values
        b1 = 'A'
        b2 = 100

        # store values
        sim.b[d, t, i, 1] = b1
        sim.b[d, t, i, 2] = b2

        # update w
        w = update_w( d, t, i, sim, param, dist, data )

        # store updated w
        sim.w[d, t+1, i] = w

      end # i

      # aggregate some data
      D_A = sum(sim.b[d, t, :, 1] .== 65)
      D_B = sum(sim.b[d, t, :, 1] .== 66)

      # omitted: do stuff with aggregated data

    end # t

  end # d


  # return output
  return sim

end
