import json
import argparse
import numpy as np
import matplotlib.pyplot as plt
import random
from datetime import datetime
random.seed(datetime.now())

## assumptions:
## all points are listed in clockwise order.


# norlin_quad = [1096917, 396338, 1177401, 1337077, 1437282, 1397169, 1776796, 255849, 1656928,
#                 1876842, 1357122, 2076723, 35870, 1437281, 1137135, 856256, 1497069, 856255,
#                 1157312, 1316999, 1256757, 135927, 155908, 1377146, 1916620, 1796724, 1876841,
#                 1137138, 1497070, 896646, 456368, 996694, 1776795, 1357120, 536067, 155909,
#                 215847, 236028, 1096927, 876578, 16084, 35871, 436310, 336137, 916590, 1096918,
#                 715690]
# norlin_quad = [1776795, 536067]
# norlin_quad = [1617093]
norlin_quad = [1796724]

# 1 degree to meters. This is approx, and only works for things at 40 degree Lat (i.e., long_deg changes with the latitude)
lat_deg = 110950
long_deg = 85000

building_low = 0
building_high = 15

add_ground = True


def find_concave_convex(meter_v_array):
    cave_x = []
    vex_x = []
    cave_y = []
    vex_y = []

    num_v = len(meter_v_array)
    for j in range(num_v):
        A = meter_v_array[j]
        B = np.zeros(2)
        C = np.zeros(2)
        if j == 0:
            B = meter_v_array[j+1]
            C = meter_v_array[num_v-1]
        elif j == num_v - 1:
            B = meter_v_array[0]
            C = meter_v_array[j-1]
        else:
            B = meter_v_array[j+1]
            C = meter_v_array[j-1]

        opp = C[1] - A[1]
        adj = C[0] - A[0]
        hype = np.sqrt(opp*opp + adj*adj)
        c_cah = np.arccos(adj/hype)
        c_ans = c_cah
        if C[1] < A[1]:
            c_ans = np.pi + (np.pi-c_cah)
        opp = B[1] - A[1]
        adj = B[0] - A[0]
        hype = np.sqrt(opp*opp + adj*adj)
        b_cah = np.arccos(adj/hype)
        b_ans = b_cah
        if B[1] < A[1]:
            b_ans = np.pi + (np.pi-b_cah)

        ans = b_ans + (2*np.pi) - c_ans
        if ans > np.pi *2:
            ans = ans - np.pi*2
        if (ans > np.pi):
            vex_x.append(A[0])
            vex_y.append(A[1])
        else:
            cave_x.append(A[0])
            cave_y.append(A[1])
# need to add is there a point within the triangle test.
def cross2d(u, v):
    return u[1] * v[0] - u[0] * v[1]

def find_first_concave(meter_v_array):
    A = np.zeros(2)
    B = np.zeros(2)
    C = np.zeros(2)
    num_v = len(meter_v_array)
    # print("number of verticies is ", num_v)
    for j in range(num_v):
        A = meter_v_array[j]
        if j == 0:
            B = meter_v_array[j+1]
            C = meter_v_array[num_v-1]
        elif j == num_v - 1:
            B = meter_v_array[0]
            C = meter_v_array[j-1]
        else:
            B = meter_v_array[j+1]
            C = meter_v_array[j-1]

        # is A concave or convex
        opp = C[1] - A[1]
        adj = C[0] - A[0]
        hype = np.sqrt(opp*opp + adj*adj)
        # print("c_cah call {} {} {}".format(opp, adj, hype))
        # print("A {}, B {}, C {}".format(A, B, C))
        c_cah = np.arccos(adj/hype)
        c_ans = c_cah
        if C[1] < A[1]:
            c_ans = np.pi + (np.pi-c_cah)
        opp = B[1] - A[1]
        adj = B[0] - A[0]
        hype = np.sqrt(opp*opp + adj*adj)
        # print("b_cah call {} {} {}".format(opp, adj, hype))
        b_cah = np.arccos(adj/hype)
        b_ans = b_cah
        if B[1] < A[1]:
            b_ans = np.pi + (np.pi-b_cah)
        ans = b_ans + (2*np.pi) - c_ans
        if ans > np.pi*2: 
            ans = ans - np.pi*2
        if ans <= np.pi: ## if angle <= 180 degress, then it's concave
            ## A is concave
            # but, need to check if another point lays within the ABC triangle
            
            v_inside = False
            for k in range(num_v):
                if j == 0:
                    if k == j or k == j+1 or k == num_v-1:
                        continue
                elif j == num_v - 1:
                    if k == j or k == 0 or k == j-1:
                        continue
                else:
                    if k == j or k == j+1 or k == j-1:
                        continue
                # print(j,k)

                p_hit = meter_v_array[k]
                tester1 = cross2d(B - A, p_hit - A) # WARNING: ABC need to be clockwise
                tester2 = cross2d(C - B, p_hit - B)
                tester3 = cross2d(A - C, p_hit - C)
                if (tester1 >= 0 and tester2 >= 0) and tester3 >= 0:
                    v_inside = True
                    break
            
            # return (np.array([A,B,C])) # returns the point and neighbors

            if v_inside == False:
                return j # returns the index of A








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
        # if True:
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
    print("lower left is {}".format(lower_left))
    print("upper right is {}".format(upper_right))

    geo_center = np.zeros(2)
    geo_center[0] = (lower_left[0] + upper_right[0]) / 2.0
    geo_center[1] = (lower_left[1] + upper_right[1]) / 2.0
    ## geo_center is still in long,lat
    # meter_geo_center = (geo_center - lower_left) * np.array([long_deg, lat_deg])

    bb_meters = np.zeros((2,2))
    bb_meters[1] = (upper_right - lower_left) *  np.array([long_deg, lat_deg])
    print(bb_meters)

    # vertex_count 
    vc = 0
    bc = 0
    # v_list = []
    # f_list = []

    # xx = []
    # yy = []
    ## outfile
    # f = open(args.output, 'w')
    # f.write("mtllib norlin.mtl\ng norlin_quad\n")
    for i in range(len(a_vertex_degrees)):
        xx = []
        yy = []
        sx_0 = 0.0
        sy_0 = 0.0
        sx_1 = 0.0
        sy_1 = 0.0
        meter_v_array = np.zeros((len(a_vertex_degrees[i])-1, 2))
        for j in range(0, len(a_vertex_degrees[i])):
            xx.append((a_vertex_degrees[i][j][0] - lower_left[0]) * long_deg)
            yy.append((a_vertex_degrees[i][j][1] - lower_left[1]) * lat_deg)
            if j == 0:
                sx_0 = (a_vertex_degrees[i][j][0] - lower_left[0]) * long_deg
                sy_0 = (a_vertex_degrees[i][j][1] - lower_left[1]) * lat_deg
            if j == 1:
                sx_1 = (a_vertex_degrees[i][j][0] - lower_left[0]) * long_deg
                sy_1 = (a_vertex_degrees[i][j][1] - lower_left[1]) * lat_deg
            if j != len(a_vertex_degrees[i])-1:
                meter_v_array[j] = (a_vertex_degrees[i][j] - lower_left) * np.array([long_deg, lat_deg])

        # plt.plot(xx,yy)
        # plt.scatter(sx_0,sy_0,color='r',s=45)
        # plt.scatter(sx_1,sy_1,color='b',s=45)
        # plt.show()    
        # print(meter_v_array)


        # find first concave
        v_list = []
        f_list = []
        ret = find_first_concave(meter_v_array)
        print(ret)
        f_list.append("f {} {} {}".format(vc-1, vc-building_vc+1, vc-building_vc+2))
        ## write triangle A,B,C out to file and remove A


    print("{} written out.\n{} is the geographic center.".format(args.output, (geo_center - lower_left) * np.array([long_deg, lat_deg])))










if __name__ == "__main__":
    main()

