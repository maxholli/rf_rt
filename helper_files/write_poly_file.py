from triangulate_roofs import find_first_concave

## bab is bad acting building (aka building with holes)
def write_poly_file(bab, file_name, path):
    f = open(path+file_name, 'w')
    walls_count = 0
    doubles = []
    for i in range(len(bab)):
        for j in range(i+1,len(bab)):
            if (bab[i] == bab[j]).all():
                walls_count += 1
                doubles.append(j)
    # print("number of holes {}".format(walls_count-1))
    # print("doubles is {}".format(doubles))
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
        a = find_first_concave(rev_sendoff)
        if a == len(rev_sendoff) - 1:
            f.write("{} {} {}\n".format(i, (rev_sendoff[0][0] + rev_sendoff[a-1][0])/2, (rev_sendoff[0][1] + rev_sendoff[a-1][1])/2))
        else:
            f.write("{} {} {}\n".format(i, (rev_sendoff[a+1][0] + rev_sendoff[a-1][0])/2, (rev_sendoff[a+1][1] + rev_sendoff[a-1][1])/2))
    f.close()