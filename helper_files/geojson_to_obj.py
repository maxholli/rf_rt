import json
import argparse
import numpy as np
import matplotlib.pyplot as plt
from triangulate_roofs import find_first_concave

# norlin_quad = [1096917, 396338, 1177401, 1337077, 1437282, 1397169, 1776796, 255849, 1656928,
#                 1876842, 1357122, 2076723, 35870, 1437281, 1137135, 856256, 1497069, 856255,
#                 1157312, 1316999, 1256757, 135927, 155908, 1377146, 1916620, 1796724, 1876841,
#                 1137138, 1497070, 896646, 456368, 996694, 1776795, 1357120, 536067, 155909,
#                 215847, 236028, 1096927, 876578, 16084, 35871, 436310, 336137, 916590, 1096918,
#                 715690]
# norlin_quad = [1776795, 536067]
# norlin_quad = [1796724]
norlin_quad = [15883]
# 1 degree to meters. This is approx, and only works for things at 40 degree Lat (i.e., long_deg changes with the latitude)
lat_deg = 110950
long_deg = 85000

building_low = 0
building_high = 15

add_ground = True
add_roofs = True
add_sun = True

def main():
    parser = argparse.ArgumentParser(description="geojson dataset please")
    parser.add_argument("geojson_f", nargs="?")
    parser.add_argument("--output", nargs="?", default="new.obj")
    args = parser.parse_args()
    
    geojson_f = args.geojson_f
    # print(args.output)
    print("reading {} geojson file".format(geojson_f))

    # # Opening JSON file
    f = open(geojson_f)
    
    # # returns JSON object as
    # # a dictionary
    data = json.load(f)
    
    FIDs = []
    vertex_degrees = []
    # # Iterating through the json
    # # list
    for i in data['features']:
        # if i["properties"]["FID"] in norlin_quad:
        if True:
            # print(i["properties"]["FID"])
            FIDs.append(i["properties"]["FID"])
            # print(i["geometry"]["coordinates"][0][0])
            vertex_degrees.append(i["geometry"]["coordinates"][0][0])
    # check for duplicates in the vertex list 
    for i in range(len(vertex_degrees)):
        num_vs = len(vertex_degrees[i])
        for j in range(num_vs-1):
            if (vertex_degrees[i][j] == vertex_degrees[i][j+1]):
                vertex_degrees[i].pop(j)
                break

    # # Closing file
    f.close()
    # # clear data from memory
    del data

    a_FIDs = np.array(FIDs)
    a_vertex_degrees = np.array(vertex_degrees, dtype=object)
    lower_left = np.array([a_vertex_degrees[0][0][0], a_vertex_degrees[0][0][1]])
    upper_right = np.array([a_vertex_degrees[0][0][0], a_vertex_degrees[0][0][1]])
    # # find geographic center
    for i in range(len(a_vertex_degrees)):
        for j in range(len(a_vertex_degrees[i])):
            if a_vertex_degrees[i][j][0] < lower_left[0]:
                lower_left[0] = a_vertex_degrees[i][j][0]
            if a_vertex_degrees[i][j][0] > upper_right[0]:
                upper_right[0] = a_vertex_degrees[i][j][0]
            if a_vertex_degrees[i][j][1] < lower_left[1]:
                lower_left[1] = a_vertex_degrees[i][j][1]
            if a_vertex_degrees[i][j][1] > upper_right[1]:
                upper_right[1] = a_vertex_degrees[i][j][1]    
    print("lower left is {}".format(lower_left))
    print("upper right is {}".format(upper_right))

    print("num buildings to write: {}".format(len(a_vertex_degrees)))
    print("total number of objects: {}".format(a_vertex_degrees.size))
    geo_center = np.zeros(2)
    geo_center[0] = (lower_left[0] + upper_right[0]) / 2.0
    geo_center[1] = (lower_left[1] + upper_right[1]) / 2.0
    ## geo_center is still in long,lat
    # meter_geo_center = (geo_center - lower_left) * np.array([long_deg, lat_deg])

    # vertex_count 
    vc = 0
    bc = 0
    # v_list = []
    # f_list = []

    xx = []
    yy = []
    ## outfile
    f = open(args.output, 'w')
    f.write("mtllib norlin.mtl\ng norlin_quad\n")
    for i in range(len(a_vertex_degrees)):
        xx = []
        yy = []
        v_list = []
        f_list = []
        building_vc = 0
        meter_v = []
        for j in range(0, len(a_vertex_degrees[i])):
            xx.append((a_vertex_degrees[i][j][0] - lower_left[0]) * long_deg)
            yy.append((a_vertex_degrees[i][j][1] - lower_left[1]) * lat_deg)
            if j == 0:
                meter_v.append((a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg]))
                vertex = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_low, vertex[0]))
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_high, vertex[0]))
                vc += 2
                building_vc += 2
            elif j == len(a_vertex_degrees[i])-1:
                f_list.append("f {} {} {}".format(vc-1, vc-building_vc+1, vc-building_vc+2))
                f_list.append("f {} {} {}".format(vc-1, vc-building_vc+2, vc)) 
            else:
                meter_v.append((a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg]))
                vertex = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_low, vertex[0]))
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_high, vertex[0]))
                vc += 2
                building_vc += 2
                f_list.append("f {} {} {}".format(vc-3, vc-1, vc))
                f_list.append("f {} {} {}".format(vc-3, vc, vc-2))
        
        
        
        
        if add_roofs:
            xx = xx[:-1]
            yy = yy[:-1]
            roof_indi = []
            for ri in range(vc-building_vc+2, vc+2, 2):
                roof_indi.append(ri)
            while len(meter_v) > 3:
                cave_i = find_first_concave(meter_v)
                # print("ci ", cave_i)
                if cave_i == len(roof_indi) - 1:
                    try:
                        f_list.append("f {} {} {}".format(roof_indi[cave_i], roof_indi[0], roof_indi[cave_i-1]))
                    except TypeError:
                        plt.plot(xx,yy)
                        plt.show()
                else:
                    try:
                        f_list.append("f {} {} {}".format(roof_indi[cave_i], roof_indi[cave_i+1], roof_indi[cave_i-1]))
                    except TypeError:
                        print("FID is ", FIDs[i])
                        plt.plot(xx,yy)
                        plt.show()
                # plt.plot(xx,yy)
                # plt.scatter(xx[cave_i],yy[cave_i])
                # plt.show()
                
                meter_v.pop(cave_i)
                # xx.pop(cave_i)
                # yy.pop(cave_i)
                roof_indi.pop(cave_i)
            f_list.append("f {} {} {}".format(roof_indi[0], roof_indi[1], roof_indi[2]))
            # for item in n_f_list:
            #     print(item)
            # print(roof_indi)

            # print(meter_v[cave_i])
            # f_list.append("f {} {} {}".format(vc-3, vc-1, vc))

        for item in v_list:
            f.write(item)
            f.write('\n')
        f.write("g building{:04d}\n".format(bc))
        f.write("usemtl buildings\n")
        for item in f_list:
            f.write(item)
            f.write('\n')
        bc += 1
        if bc % 1000 == 0:
            print("{} buildings written\r".format(bc), end='')

    # # +y is coming out of the screen towards you
    #                        x 
    #                        |       y
    #                        |     //
    #                        |    //
    #                        |   //
    #                        |  //
    #                        | //
    #                        |//
    # # FYI ------------------------------------ z
    #                        |
    #                        |
    #                        |
    #                        |
    #                        |
    #                        |
    #                        |
    #                        |
    # plt.plot(xx,yy)
    # plt.ylabel("x axis")
    # plt.xlabel("z axis")
    # plt.show()


    if add_ground:
        meter_upper_right = (upper_right-lower_left) * np.array([long_deg, lat_deg])
        f.write("v 0.0 0.0 0.0\n")
        f.write("v 0.0 0.0 {:.4f}\n".format(meter_upper_right[0]))
        f.write("v {:.4f} 0.0 0.0\n".format(meter_upper_right[1]))
        f.write("v {:.4f} 0.0 {:.4f}\n".format(meter_upper_right[1], meter_upper_right[0]))
        vc += 4
        f.write("g ground\n")
        f.write("usemtl ground\n")
        f.write("f {} {} {}\n".format(vc-3, vc, vc-2))
        f.write("f {} {} {}\n".format(vc-3, vc-1, vc))
    if add_sun:
        meter_upper_right = (upper_right-lower_left) * np.array([long_deg, lat_deg])
        f.write("v {:.4f} 2000.0 0.0\n".format(meter_upper_right[1]/2.8 - 1200))
        f.write("v {:.4f} 2000.0 0.0\n".format(meter_upper_right[1]/2.8))
        f.write("v {:.4f} 3200.0 0.0\n".format(meter_upper_right[1]/2.8 - 1200))
        f.write("v {:.4f} 3200.0 0.0\n".format(meter_upper_right[1]/2.8))
        vc += 4
        f.write("g ground\n")
        f.write("usemtl sun\n")
        f.write("f {} {} {}\n".format(vc-3, vc-1, vc-2))
        f.write("f {} {} {}\n".format(vc-2, vc-1, vc))
    f.close

    print("{} written out.\n{} is the geographic center.".format(args.output, (geo_center - lower_left) * np.array([long_deg, lat_deg])))


    


if __name__ == "__main__":
    main()

# # example geojson file. # #

# {"type":"FeatureCollection",
#  "features":[
#         {
#                 "type":"Feature",
#                 "id":"boulder_county_buildings.1",
#                 "geometry":
#                 {
#                     "type":"MultiPolygon",
#                     "coordinates":[[[
#                         [-105.537135,40.235571],
#                         [-105.537108,40.235455],
#                         [-105.537222,40.235439],
#                         [-105.537249,40.235556],
#                         [-105.537135,40.235571]]]]
#                 },
#                 "geometry_name":"the_geom",
#                 "properties":
#                 {
#                     "FID":1007,
#                     "County":"Boulder County"
#                 }
#         },{
#                 "type":"Feature",
#                 "id":"boulder_county_buildings.2",
#                 "geometry":
#                 {
#                     "type":"MultiPolygon",
#                     "coordinates":[[[
#                         [-105.513635,40.18401],
#                         [-105.513706,40.183983],
#                         [-105.513754,40.184057],
#                         [-105.513683,40.184084],
#                         [-105.513635,40.18401]]]]
#                 },
#                 "geometry_name":"the_geom",
#                 "properties":
#                 {
#                     "FID":1008,
#                     "County":"Boulder County"
#                 }
#         },{
#                 "type":"Feature","id":"boulder_county_b






# # output

# #
# # object sponza_05
# #

# v  914.8004 413.9111 -310.1346
# v  914.8004 494.0525 -310.1346
# v  914.8008 494.0525 238.6791
# v  914.8008 413.9111 238.6791
# v  -1045.7410 413.9111 -310.1346
# v  -1045.7410 494.0525 -310.1345
# v  -1045.7410 413.9111 238.6795
# v  -1045.7410 494.0525 238.6795
# # 8 vertices

# vn 1.0000 0.0000 -0.0000
# vn -0.0000 0.0000 -1.0000
# vn 0.0000 0.0000 -1.0000
# vn -1.0000 0.0000 -0.0000
# vn 0.0000 0.0000 1.0000
# # 5 vertex normals

# vt 16.4555 0.3608 0.0000
# vt 16.4555 0.6819 0.0000
# vt 18.6031 0.6819 0.0000
# vt 18.6031 0.3608 0.0000
# vt 8.6439 0.3609 0.0000
# vt 8.6439 0.6819 0.0000
# vt 6.4963 0.3609 0.0000
# vt 6.4963 0.6819 0.0000
# vt -1.3153 0.3609 0.0000
# vt -1.3153 0.6819 0.0000
# # 10 texture coords

# g sponza_05
# usemtl bricks
# s 16
# f 13681/6892/14472 13682/6893/14472 13683/6894/14472 13684/6895/14472 
# s 32
# f 13685/6896/14473 13686/6897/14473 13682/6893/14474 13681/6892/14474 
# s off
# f 13685/6896/14475 13687/6898/14475 13688/6899/14475 13686/6897/14475 
# f 13687/6898/14476 13684/6900/14476 13683/6901/14476 13688/6899/14476 
# # 4 polygons