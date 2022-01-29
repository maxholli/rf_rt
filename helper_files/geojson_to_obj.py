import json
import argparse
import numpy as np
import matplotlib.pyplot as plt

norlin_quad = [1096917, 396338, 1177401, 1337077, 1437282, 1397169, 1776796, 255849, 1656928,
                1876842, 1357122, 2076723, 35870, 1437281, 1137135, 856256, 1497069, 856255,
                1157312, 1316999, 1256757, 135927, 155908, 1377146, 1916620, 1796724, 1876841,
                1137138, 1497070, 896646, 456368, 996694, 1776795, 1357120, 536067, 155909,
                215847, 236028, 1096927, 876578, 16084, 35871, 436310, 336137, 916590, 1096918,
                715690]
# norlin_quad = [1776795, 536067]
# norlin_quad = [1617093]

# 1 degree to meters. This is approx, and only works for things at 40 degree Lat (i.e., long_deg changes with the latitude)
lat_deg = 110950
long_deg = 85000

building_low = 0
building_high = 12

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
        if i["properties"]["FID"] in norlin_quad:
            # print(i["properties"]["FID"])
            FIDs.append(i["properties"]["FID"])
            # print(i["geometry"]["coordinates"][0][0])
            vertex_degrees.append(i["geometry"]["coordinates"][0][0])
    
    # # Closing file
    f.close()
    # # clear data from memory
    del data

    a_FIDs = np.array(FIDs)
    a_vertex_degrees = np.array(vertex_degrees, dtype=object)
    # print(a_vertex_degrees[0][0])
    lower_left = np.array([a_vertex_degrees[0][0][0], a_vertex_degrees[0][0][1]])
    upper_right = np.array([a_vertex_degrees[0][0][0], a_vertex_degrees[0][0][1]])
    points_to_average = 0
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
    print(lower_left)
    print(upper_right)
            # lat_sum += a_vertex_degrees[i][j][1]
            # long_sum += a_vertex_degrees[i][j][0]
            # points_to_average += 1
    geo_center = np.zeros(2)
    geo_center[0] = (lower_left[0] + upper_right[0]) / 2.0
    geo_center[1] = (lower_left[1] + upper_right[1]) / 2.0
    
    # shift lower left a little lower and left-er
    # lower_left += np.array([-1.0, -1.0])

    # vertex_count 
    vc = 0
    v_list = []
    f_list = []

    xx = []
    yy = []
    for i in range(len(a_vertex_degrees)):
        building_vc = 0
        for j in range(0, len(a_vertex_degrees[i])):
            xx.append((a_vertex_degrees[i][j][0] - lower_left[0]) * long_deg)
            yy.append((a_vertex_degrees[i][j][1] - lower_left[1]) * lat_deg)
            if j == 0:
                vertex = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_low, vertex[0]))
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_high, vertex[0]))
                vc += 2
                building_vc += 2
            elif j == len(a_vertex_degrees[i])-1:
                 # vertex_count is 8 
                 # building_vc is 8
                f_list.append("f {} {} {}".format(vc-1, vc-building_vc+1, vc-building_vc+2))
                f_list.append("f {} {} {}".format(vc-1, vc-building_vc+2, vc)) 
            else:
                vertex = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_low, vertex[0]))
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_high, vertex[0]))
                vc += 2
                building_vc += 2
                # vertex_count is 4 
                f_list.append("f {} {} {}".format(vc-3, vc-1, vc))
                f_list.append("f {} {} {}".format(vc-3, vc, vc-2))
    
    # plt.plot(xx,yy)
    # plt.show()


    f = open(args.output, 'w')
    f.write("mtllib cube.mtl\ng building\n")
    for item in v_list:
        f.write(item)
        f.write('\n')
        # print(item)
    for item in f_list:
        f.write(item)
        f.write('\n')
        # print(item)
    f.close

    print("{} written out.\n{} is the geographic center.".format(args.output, (geo_center - lower_left) * np.array([lat_deg, long_deg])))


    


if __name__ == "__main__":
    main()


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