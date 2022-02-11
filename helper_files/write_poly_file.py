from triangulate_roofs import find_first_concave


# doubles is [43, 48, 53]
# 54
# p_doubles is [0, 44, 49]

# doubles is [41, 46, 51, 56, 61]
# 62
# p_doubles is [0, 42, 47, 52, 57]

# doubles is [168, 4, 173]
# 174
# p_doubles is [0, 169]

## bab is bad acting building (aka building with holes)
def write_poly_file(bab, p_doubles, file_name, path):
    f = open(path+file_name+".poly", 'w')
    # walls_count = len(p_doubles) - 1
    walls_count = 0
    doubles = []
    # print("bab is {}".format(bab))
    for i in range(len(bab)):
        # print(bab[i])
        for j in range(i+1,len(bab)):
            if (bab[i] == bab[j]).all():
                walls_count += 1
                doubles.append(j)
    # # for i in range(1,len(p_doubles)):
    # #     doubles.append(p_doubles[i]-1)
    # # doubles.append(len(bab)-1)
    # print("number of holes {}".format(walls_count-1))
    # print("doubles is {}".format(doubles))
    # print(len(bab))
    # print("p_doubles is {}".format(p_doubles))
    f.write("{} {} {} {}\n".format(len(bab)-walls_count, 2, 0, 0))
    vi = 1
    for ii, vert in enumerate(bab):
        if ii not in doubles:
            f.write("{} {} {}\n".format(vi, vert[0], vert[1]))
            vi += 1
    f.write("{} {}\n".format(len(bab)-walls_count, 0))
    vi = 1
    throw_back = 1
    skip = False
    myiter = iter(range(len(bab)))
    for ii in myiter:
        if ii+1 not in doubles:
            f.write("{} {} {}\n".format(vi, vi, vi+1))
        else:
            f.write("{} {} {}\n".format(vi, vi, throw_back))
            throw_back = vi + 1
            next(myiter, None)
        vi += 1
    f.write("{}\n".format(walls_count-1))
    for i in range(1, len(doubles)):
        sendoff = []
        for v in range(doubles[i-1]+1,doubles[i]):
            sendoff.append(bab[v])
        rev_sendoff = []
        for j in range(1,len(sendoff)+1):
            rev_sendoff.append(sendoff[len(sendoff)-j])
        # print("rev_sendoff is {}".format(rev_sendoff))
        a = find_first_concave(rev_sendoff)
        if a is None:
            return 0
        if a == len(rev_sendoff) - 1:
            f.write("{} {} {}\n".format(i, (rev_sendoff[0][0] + rev_sendoff[a-1][0])/2, (rev_sendoff[0][1] + rev_sendoff[a-1][1])/2))
        else:
            f.write("{} {} {}\n".format(i, (rev_sendoff[a+1][0] + rev_sendoff[a-1][0])/2, (rev_sendoff[a+1][1] + rev_sendoff[a-1][1])/2))
    f.close()
    return 1

## vc is vertex count
def read_ele_node(vc, building_high, file_name, path):
    return_ar = [[],[],[]] # will hold [[verts],[faces],[vc]]

    filename = path+file_name+".1.node"
    f = open(filename, 'r')
    line_num = 0
    points_num = 0
    while True:
        line = f.readline()
        if line == '':
            break
        else:
            if line_num == 0:
                points_num = int(line.split()[0])
                return_ar[2].append(points_num+vc)
            else:
                verts = line.split()
    #             print(verts)
                if verts[0] != '#':
                    out_str = "v {} {} {}".format( verts[2], building_high, verts[1])
                    return_ar[0].append(out_str)
            line_num += 1        
    f.close()
    filename = path+file_name+".1.ele"
    f = open(filename, 'r')
    line_num = 0
    faces_num = 0
    while True:
        line = f.readline()
        if line == '':
            break
        else:
            if line_num == 0:
                faces_num = int(line.split()[0])
            else:
                tri = line.split()
    #             print(verts)
                if tri[0] != '#':
                    out_str = "f {} {} {}".format(vc+int(tri[1]), vc+int(tri[2]), vc+int(tri[3]))
                    return_ar[1].append(out_str)
            line_num += 1        
    f.close()
    return return_ar

