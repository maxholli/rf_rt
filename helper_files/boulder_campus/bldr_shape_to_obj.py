import shapefile
import argparse
import numpy as np
import matplotlib.pyplot as plt
from triangulate_roofs import find_first_concave
from write_poly_file import write_poly_file
from write_poly_file import read_ele_node
from copy import copy
import os

# # # shape files have two parts. Geometry and Records
# Geometry is as the following:
# bbox              bounding box for the shape
# oid               original index position in the shapefile
# parts             group of collections of points into shapes, if the record has multiple parts this attribute
#                       contains the index of the first point in each part. 
# points            list of tuples containing and (x,y) coordinate for each point in the shape
# shapeType         integer representing the type of the shape
# shapeTypeName     string representing the type of the shape
# # # called:
# >>> shapes[0].bbox

# Records are as the following:
# DRCOGID
# BLDGHEIGHT
# GROUND_ELE
# among other things
# sf.fields to see record types

lat_deg = 110950
long_deg = 85000

building_low = 0
building_high = 15

add_ground = False
add_roofs = True
add_sun = True

## path the the holey building directory
path = "/home/jovyan/shared/max/rf_rt/helper_files/boulder_campus/holey_Bs/boulder_bs/"

# select_buildings = [322683]#, 322093, 322403]
# select_buildings = [156852]
# select_buildings = [319954] # problem building
# select_buildings = [284485] # two holes
# select_buildings = [231654] # four holes
# select_buildings = [319202] # rose medical complex
# select_buildings = [840098] # problem building
# select_buildings = [38392] # height issue
# select_buildings = [16353] # height issue
# select_buildings = [15933] # height issue
# select_buildings = [18501] # height issue
# select_buildings = [18501, 15933, 16353] # height issue
# holey buildings
# select_buildings = [156852, 299306, 319304, 316380, 239426, 255906, 123053, 158249, 149342, 180685, 
#                     123132, 320550, 313201, 319202, 296022, 280282, 152240, 266762, 291977, 284485, 
#                     301222, 313196, 281599, 319202, 309683, 298691, 263865, 324028, 249842, 231654, 
#                     238817, 275465, 276909, 255315, 195919, 149516, 239263, 267643, 126810, 135919, 
#                     133662, 145379, 239274, 199126, 163575, 232168, 253697, 231993, 145387, 120313, 
#                     188216, 145391, 255439, 157104, 132472, 157176, 132239, 249271, 245886, 218524, 
#                     199997, 249470, 249274, 151507, 157708, 276910, 263118, 254775, 208885, 207153, 
#                     180965, 208861, 163981, 169291, 147777, 139224, 152849, 210860, 203991, 160963, 
#                     232001, 162720, 208105, 202712, 139016, 208983, 163150, 145868, 840217, 914551, 
#                     124634, 158927, 209001, 157965, 190467, 151025] 
# 
# bad_buildings = [840098, 892619, 905571, 836735, 910001, 906652, 892542, 539926, 639960, 545763, 
                    # 381063, 731359, 654489, 413861, 640234, 670255, 413597, 640784, 417886, 417472, 
                    # 395456, 373791, 376169, 384094, 387427, 278432, 155453, 202061, 157530, 315982, 
                    # 159052]

# building 202061
# Denver Academy
# 4400 E Iliff Ave, Denver, CO 80222
# select_buildings = [202061] # part index 4 (of 9) has 3 erronious vertexes that make an inner hole (breaks triangle) fix by removing points 2, 3, 4

# building 278432
# residential building on Alameda 
# 255 S Cherokee St, Denver, CO 80223
# select_buildings = [278432] # part index 1 (of 2) has 3 erronious vertexes that make an inner hole (breaks triangle) in the hole

# boulder specific
select_buildings = [971604, 971606, 974534] #hellems
# select_buildings = [971724] # engineering center
bad_buildings = []


def main():
    parser = argparse.ArgumentParser(description="shapefile dataset please")
    parser.add_argument("shapefile_f", nargs="?")
    parser.add_argument("--output", nargs="?", default="new.obj")
    args = parser.parse_args()
    
    shapefile_f = args.shapefile_f
    print("reading {} shapefile".format(shapefile_f))


    sf = shapefile.Reader(shapefile_f)
    shapes = sf.shapes()
    rec = sf.records()
    # ls1 = shapes[0].points
    # print(ls1)
    # print(len(ls1))
    # print(ls1[0])
    # print(ls1[0][0])
    # print(type(ls1[0][0]))
    # rec1a = rec[0]['BUILDING_I']
    # rec1b = rec[0]['GROUND_ELE']
    # rec1c = rec[0]['BLDGHEIGHT']
    # print(rec1a, rec1b, rec1c)
   
    ## filter for BUILDING_I and change from tuple to array data-structure
    tmp_vertex_degrees = []
    a_building_height = []
    a_building_low = []
    a_building_id = []
    a_holey_building = []
    for i in range(len(shapes)):
        # if rec[i]['DRCOGID'] not in bad_buildings:
        if rec[i]['DRCOGID'] not in bad_buildings and rec[i]['DRCOGID'] in select_buildings:
        # if True:
            # print("Building is {}".format(rec[i]['DRCOGID']))
            # print(shapes[i].points)
            # print("-----------------------")
            # print(shapes[i].parts)
            tmp = []
            for vert in shapes[i].points:
                tmp.append(np.array([copy(vert[0]),copy(vert[1])]))
            if len(shapes[i].parts) > 1: ## marks building with holes
                a_holey_building.append(shapes[i].parts)
            else:
                a_holey_building.append(False)
            tmp_vertex_degrees.append(tmp)
            a_building_height.append(rec[i]['BLDGHEIGHT']+rec[i]['GROUNDELEV'])
            a_building_low.append(rec[i]['GROUNDELEV'])
            a_building_id.append(rec[i]['DRCOGID'])
            # if (len(a_building_id)> 10500):
            #     break
    del sf
    del shapes
    del rec

    a_vertex_degrees = np.array(tmp_vertex_degrees, dtype=object)

    # print("printing array")
    # print(len(a_vertex_degrees[0]))
    # print(a_vertex_degrees)
    

    del tmp_vertex_degrees

    print("num buildings to write: {}".format(len(a_vertex_degrees)))
    print("total number of objects: {}".format(a_vertex_degrees.size))
    # for obj in a_vertex_degrees:
    #     for vert in obj:
    #         print("{:.15f} {:.15f}".format(vert[0],vert[1]))

    ## finding lower left and finding the upper right
    building_lower_left = np.array([a_vertex_degrees[0][0][0], a_vertex_degrees[0][0][1]])
    building_upper_right = np.array([a_vertex_degrees[0][0][0], a_vertex_degrees[0][0][1]])
    for i in range(len(a_vertex_degrees)):
        for j in range(len(a_vertex_degrees[i])):
            if a_vertex_degrees[i][j][0] < building_lower_left[0]:
                building_lower_left[0] = a_vertex_degrees[i][j][0]
            if a_vertex_degrees[i][j][0] > building_upper_right[0]:
                building_upper_right[0] = a_vertex_degrees[i][j][0]
            if a_vertex_degrees[i][j][1] < building_lower_left[1]:
                building_lower_left[1] = a_vertex_degrees[i][j][1]
            if a_vertex_degrees[i][j][1] > building_upper_right[1]:
                building_upper_right[1] = a_vertex_degrees[i][j][1]    
    print("building lower left is {}".format(building_lower_left))
    print("building upper right is {}".format(building_upper_right))

    ## chosen lower left base my 0m, 0m orientation on 
    lower_left = np.array([-105.27368, 40.00707])
    ## in format CRS.from_epsg(32613)
    ## bottom 4428577.785411156, left 476641.151340244

    # vertex_count and building_count 
    vc = 0
    bc = 0

    xx = []
    yy = []
    ## outfile
    f = open(args.output, 'w')
    f.write("mtllib denver.mtl\ng denver\n")

    ## loop thru each building
    for i in range(len(a_vertex_degrees)):
        xx = []
        yy = []
        print("building height is ", a_building_height[i])
        building_high = a_building_height[i] * 0.3048 ## convert from feet to meters
        building_low = a_building_low[i] * 0.3048 ## convert from feet to meters
        v_list = []
        f_list = []
        building_vc = 0
        meter_v = []
        ## do the walls
        if not a_holey_building[i]:
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
                    # if a_holey_building[i]:
                    #     meter_v.append((a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg]))
                else:
                    meter_v.append((a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg]))
                    vertex = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])
                    v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_low, vertex[0]))
                    v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_high, vertex[0]))
                    vc += 2
                    building_vc += 2
                    f_list.append("f {} {} {}".format(vc-3, vc-1, vc))
                    f_list.append("f {} {} {}".format(vc-3, vc, vc-2))
        else:
            # print("doubles at :", a_holey_building[i])
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
                # elif j == len(a_vertex_degrees[i])-1:
                #     f_list.append("f {} {} {}".format(vc-1, vc-building_vc+1, vc-building_vc+2))
                #     f_list.append("f {} {} {}".format(vc-1, vc-building_vc+2, vc))
                #     meter_v.append((a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg]))
                else:
                    meter_v.append((a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg]))
                    vertex = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])
                    v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_low, vertex[0]))
                    v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_high, vertex[0]))
                    vc += 2
                    building_vc += 2
                    if j in a_holey_building[i]:
                        continue
                    else:
                        f_list.append("f {} {} {}".format(vc-3, vc-1, vc))
                        f_list.append("f {} {} {}".format(vc-3, vc, vc-2))

        # print(a_building_id[i], i)
        # print(a_vertex_degrees[i])
        print("{}, {}".format(a_vertex_degrees[i][0][0], a_vertex_degrees[i][0][1], '.60g'))
        # print(a_holey_building[i])
        # annots= []
        # for li in range(len(xx)):
        #     annots.append("{}".format(li))
        # plt.plot(xx,yy)
        # plt.ylabel("x axis")
        # plt.xlabel("z axis")
        # for ii, label in enumerate(annots):
        #     plt.annotate(label, xx[ii], yy[ii])
        # plt.show()


        # print("printing meter version")
        # print(len(meter_v))
        # print(meter_v)
        

        if add_roofs:
            if a_holey_building[i]:
                ## the "else" code only works on polygon roofs that don't have holes
                ## for holey roofs we'll use Jon Shewchuk's Triangle code. https://www.cs.cmu.edu/~quake/triangle.html
                ## step 1, generate .poly file as input for triangle software
                new_file_name = "b{}i{}".format(a_building_id[i], i)
                out = write_poly_file(meter_v, a_holey_building[i], new_file_name, path)
                if out == 1:
                    ## step 2, run triangle software on .poly file ---> returns .node (verticies) and .ele (faces) files 
                    os.system("{}triangle -pq {} 1>/dev/null".format(path, path+new_file_name))
                    ## read .node and .ele files and prepare .obj output
                    vs_and_faces = read_ele_node(vc, building_high, new_file_name, path)
                    for ver_i in range(len(vs_and_faces[0])):
                        v_list.append(vs_and_faces[0][ver_i])
                    vc = vs_and_faces[2][0]
                    for fac_i in range(len(vs_and_faces[1])):
                        f_list.append(vs_and_faces[1][fac_i])
                else:
                    print("{}, {}, ".format(a_building_id[i], i), end='')
                    print(" ")
                    print(" ")
            else: ## only does polygons with no holes, used the ear clipping method.
                xx = xx[:-1]
                yy = yy[:-1]
                roof_indi = []
                for ri in range(vc-building_vc+2, vc+2, 2):
                    roof_indi.append(ri)
                while len(meter_v) > 3:
                    cave_i = find_first_concave(meter_v)
                    # print(cave_i)
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
                            print("FID is ", a_building_id[i])
                            plt.plot(xx,yy)
                            plt.show()
                            # break
                    # plt.plot(xx,yy)
                    # try:
                    #     plt.scatter(xx[cave_i],yy[cave_i])
                    # except TypeError:
                    #     print("problems")
                    #     print(meter_v)
                    # plt.show()
            
                    meter_v.pop(cave_i)
                    # xx.pop(cave_i)
                    # yy.pop(cave_i)
                    roof_indi.pop(cave_i)
                f_list.append("f {} {} {}".format(roof_indi[0], roof_indi[1], roof_indi[2]))
        
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

    if add_ground:
        meter_upper_right = (building_upper_right-building_lower_left) * np.array([long_deg, lat_deg])
        f.write("v 0.0 0.0 0.0\n")
        f.write("v 0.0 0.0 {:.4f}\n".format(meter_upper_right[0]))
        f.write("v {:.4f} 0.0 0.0\n".format(meter_upper_right[1]))
        f.write("v {:.4f} 0.0 {:.4f}\n".format(meter_upper_right[1], meter_upper_right[0]))
        vc += 4
        f.write("g ground\n")
        f.write("usemtl ground\n")
        f.write("f {} {} {}\n".format(vc-3, vc, vc-2))
        f.write("f {} {} {}\n".format(vc-3, vc-1, vc))


    f.close
    print("{} written out.\n".format(args.output))




if __name__ == "__main__":
    main()