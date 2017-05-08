export meshgrid, save_data, time_stamp, convert_image

using HDF5
using Images

function convert_image(file_name)
  img = load(file_name)
  image = reinterpret(UInt8, img.data)
  test = zeros(size(image)[3], size(image)[2], size(image)[1])

  test[:, :, 1] = squeeze(image[1, :, :], 1).'
  test[:, :, 2] = squeeze(image[2, :, :], 1).'
  test[:, :, 3] = squeeze(image[3, :, :], 1).'
  return test
end

function time_stamp()
  file_name = string(DateTime(now()))[1:end-3]
  file_name = replace(file_name, ":", "")
  file_name = split(file_name, "T")
  temp1 = convert(String, file_name[1])
  temp2 = convert(String, file_name[2][1:end-3])
  [temp1, temp2]

end


function meshgrid(vx, vy)
    m, n = length(vy), length(vx)
    vx = reshape(vx, 1, n)
    vy = reshape(vy, m, 1)
    (repmat(vx, m, 1), repmat(vy, 1, n))
end

function meshgrid(vx, vy,
                     vz)
    m, n, o = length(vy), length(vx), length(vz)
    vx = reshape(vx, 1, n, 1)
    vy = reshape(vy, m, 1, 1)
    vz = reshape(vz, 1, 1, o)
    om = ones(Int, m)
    on = ones(Int, n)
    oo = ones(Int, o)
    (vx[om, :, oo], vy[:, on, oo], vz[om, on, :])
end


function save_data(file_name, group_name, settings, dset...)

  if isfile(file_name)

    file = h5open(file_name, "r+")

      if  ! (group_name in names(file))
        g = g_create(file, group_name)
      else
        g = file[group_name]
      end

        for i in 1:length(dset)
          g[dset[i][1]] = dset[i][2]
        end

      close(file)
      h5writeattr(file_name, group_name, settings)

    elseif ! isfile(file_name)

      file = h5open(file_name, "w")
          g = g_create(file, group_name)

          for i in 1:length(dset)
            g[dset[i][1]] = dset[i][2]
          end

        close(file)
        h5writeattr(file_name, group_name, settings)

      end
end
