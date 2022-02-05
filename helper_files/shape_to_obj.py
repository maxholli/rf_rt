import shapefile
import argparse
import numpy as np
import matplotlib.pyplot as plt
from triangulate_roofs import find_first_concave
from write_poly_file import write_poly_file
from copy import copy

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
# BUILDING_I
# BLDG_HEIGH
# GROUND_ELE
# among other things
# sf.fields to see record types

lat_deg = 110950
long_deg = 85000

building_low = 0
building_high = 15

add_ground = True
add_roofs = True
add_sun = True

## path the the holey building directory
path = "/home/cc/Workspace/holey_Bs/"

# select_buildings = [322683]#, 322093, 322403]
# select_buildings = [156852]
# select_buildings = [319954] # problem building
# select_buildings = [284485] # two holes
# select_buildings = [231654] # four holes
# select_buildings = [319202] # weird
# holy buildings
select_buildings = [156852, 299306, 319304, 319954,316380,239426,255906,123053,158249,
                    149342,180685,123132,320550,313201,319202,296022,280282,152240,266762,
                    291977,284485,301222,313196,128674,281599,319202,309683,291103,298691,
                    263865,324028,249842,231654,238817,275465,276909,255315]

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
    # rec1c = rec[0]['BLDG_HEIGH']
    # print(rec1a, rec1b, rec1c)
   
    ## filter for BUILDING_I and change from tuple to array data-structure
    tmp_vertex_degrees = []
    a_building_height = []
    a_building_id = []
    a_holey_building = []
    for i in range(len(shapes)):
        if rec[i]['BUILDING_I'] in select_buildings:
        # if True:
            # print("Building is {}".format(rec[i]['BUILDING_I']))
            # print(shapes[i].points)
            # print("-----------------------")
            # print(shapes[i].parts)
            tmp = []
            for vert in shapes[i].points:
                tmp.append(np.array([copy(vert[0]),copy(vert[1])]))
            if len(shapes[i].parts) > 1: ## marks building with holes
                a_holey_building.append(shapes[i].points)
            else:
                a_holey_building.append(False)
            tmp_vertex_degrees.append(tmp)
            a_building_height.append(rec[i]['BLDG_HEIGH'])
            a_building_id.append(rec[i]['BUILDING_I'])
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

    # vertex_count and building_count 
    vc = 0
    bc = 0

    xx = []
    yy = []
    ## outfile
    f = open(args.output, 'w')
    f.write("mtllib denver.mtl\ng denver\n")

    
    for i in range(len(a_vertex_degrees)):
        xx = []
        yy = []
        building_high = a_building_height[i] * 0.3048 ## convert from feet to meters
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
                if a_holey_building[i]:
                    meter_v.append((a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg]))
            else:
                meter_v.append((a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg]))
                vertex = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_low, vertex[0]))
                v_list.append("v {:.4f} {:.4f} {:.4f}".format(vertex[1], building_high, vertex[0]))
                vc += 2
                building_vc += 2
                f_list.append("f {} {} {}".format(vc-3, vc-1, vc))
                f_list.append("f {} {} {}".format(vc-3, vc, vc-2))
        # print(a_building_id[i])
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
                new_file_name = "b{}i{}.poly".format(a_building_id[i], i)
                write_poly_file(meter_v, new_file_name, path)
            else:
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


    f.close
    print("{} written out.\n".format(args.output))




if __name__ == "__main__":
    main()