import rasterio

## band1[0][0] is the north east corner of the image


dataset = rasterio.open('/home/jovyan/shared/max/rf_rt/helper_files/boulder_campus/terrain/new_hellems_arap_25m.tin.tif')
band1 = dataset.read(1)
bb = dataset.bounds
## build visual world

res_x = dataset.transform[0] * -1
res_z = dataset.transform[4] * -1

# world.add(make_shared<triangle>(point3(290.835,0.000,162.782), point3(290.801,0.000,169.502), point3(290.801,4.267,169.50), material_s1));
hei = dataset.height * abs(res_x)
wid = dataset.width * abs(res_z)
hei_i = dataset.height
wid_i = dataset.width


## relative 0,0 for full summer
## 39.9834,-105.2850
## bottom 4425953.671688922, left 475666.5780654502
x0 = 4425953.6717
z0 = 475666.5781


## relative 0,0 for new_hellems_arap
## 40.00596,-105.27487
## bottom 4428454.898455279, left 476539.20360535086
# x0 = 4428454.8985
# z0 = 476539.2036
## relative 0,0 for boulder creek 5m
## 40.0062,-105.3359
## left 471330.24144328374, bottom 4428499.385063045
# x0 = 4428499.3850
# z0 = 471330.2414

for x in range(hei_i-1):
    for z in range(wid_i-1):
        a = (-1*(x0-(bb[1]+hei+((x+1)*res_x))),     band1[x,z],      -1*(z0-(bb[0]+(z*res_z))))
        b = (-1*(x0-(bb[1]+hei+((x+1)*res_x))),     band1[x,z+1],    -1*(z0-(bb[0]+((z+1)*res_z))))
        c = (-1*(x0-(bb[1]+hei+((x+2)*res_x))),     band1[x+1,z],    -1*(z0-(bb[0]+(z*res_z))))
        d = (-1*(x0-(bb[1]+hei+((x+2)*res_x))),     band1[x+1,z+1],  -1*(z0-(bb[0]+((z+1)*res_z))))
        if a[1] != -9999 and b[1] != -9999 and c[1] != -9999:
            p_str = "world.add(make_shared<triangle>(point3({:.3f},{:.2f},{:.3f}), point3({:.3f},{:.2f},{:.3f}), point3({:.3f},{:.2f},{:.3f}), material_s2));".format(
                a[0], a[1], a[2], b[0], b[1], b[2], c[0], c[1], c[2])
            print(p_str)
        if b[1] != -9999 and d[1] != -9999 and c[1] != -9999:
            p_str = "world.add(make_shared<triangle>(point3({:.3f},{:.2f},{:.3f}), point3({:.3f},{:.2f},{:.3f}), point3({:.3f},{:.2f},{:.3f}), material_s2));".format(
                b[0], b[1], b[2], d[0], d[1], d[2], c[0], c[1], c[2])
            print(p_str)