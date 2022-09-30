import rasterio

## band1[0][0] is the north east corner of the image


dataset = rasterio.open('/home/jovyan/shared/max/rf_rt/helper_files/boulder_campus/terrain/hellems_arap_10m.tin.tif')
band1 = dataset.read(1)
bb = dataset.bounds
## build visual world

res_x = dataset.transform[0] * -1
res_z = dataset.transform[4]

# world.add(make_shared<triangle>(point3(290.835,0.000,162.782), point3(290.801,0.000,169.502), point3(290.801,4.267,169.50), material_s1));
hei = dataset.height * abs(res_x)
wid = dataset.width * abs(res_z)
hei_i = dataset.height
wid_i = dataset.width

## relative 0,0 for hellems_arap = 
## bottom 4428577.785411156, left 476641.151340244
x0 = 4428577.7854
z0 = 476641.1513
for x in range(hei_i-1):
    for z in range(wid_i-1):
        a = (-1*(x0-(bb[1]+hei+((x+1)*res_x))),     band1[x,z],      -1*(z0-(bb[0]+wid+((z+1)*res_z))))
        b = (-1*(x0-(bb[1]+hei+((x+1)*res_x))),     band1[x,z+1],    -1*(z0-(bb[0]+wid+((z+2)*res_z))))
        c = (-1*(x0-(bb[1]+hei+((x+2)*res_x))),     band1[x+1,z],    -1*(z0-(bb[0]+wid+((z+1)*res_z))))
        d = (-1*(x0-(bb[1]+hei+((x+2)*res_x))),     band1[x+1,z+1],  -1*(z0-(bb[0]+wid+((z+2)*res_z))))
        if a[1] != -9999 and b[1] != -9999 and c[1] != -9999:
            p_str = "world.add(make_shared<triangle>(point3({:.3f},{:.2f},{:.3f}), point3({:.3f},{:.2f},{:.3f}), point3({:.3f},{:.2f},{:.3f}), material_s2));".format(
                a[0], a[1], a[2], b[0], b[1], b[2], c[0], c[1], c[2])
            print(p_str)
        if b[1] != -9999 and d[1] != -9999 and c[1] != -9999:
            p_str = "world.add(make_shared<triangle>(point3({:.3f},{:.2f},{:.3f}), point3({:.3f},{:.2f},{:.3f}), point3({:.3f},{:.2f},{:.3f}), material_s2));".format(
                b[0], b[1], b[2], d[0], d[1], d[2], c[0], c[1], c[2])
            print(p_str)