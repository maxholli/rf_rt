filename = "new_hellems_arap.obj"
file = open(filename, "r")
faces = []
vert_strings = []
vert_floats = ["dummy"]
buildings = []
current_face_count = 0
for line in file:
    if line[0] == 'f':
        faces.append(line)
        current_face_count += 1
    elif line[0] == 'v':
        vert_strings.append(line)
    elif line[0] == 'g':
        if line[2] == 'b':
            buildings.append([current_face_count, line[2:]])
# print(faces)
# print(verticies)

for vert in vert_strings:
    val = vert[2:-1].split(' ')
    a = float(val[0])
    b = float(val[1])
    c = float(val[2])
    vert_floats.append([a,b,c])
# print(vert_floats)

f_count = 0
for face in faces:
    indices = face[2:-1].split(' ')
    a = int(indices[0])
    b = int(indices[1])
    c = int(indices[2])
    # world.add(make_shared<triangle>(point3(108.48,0.00,-333.12), point3(108.48,0.00,-337.70), point3(108.48,20.00,-333.12), material_s1));
    for building in buildings:
        if building[0] == f_count:
            print("\n// {}".format(building[1][:-1]))
    out_string = "world.add(make_shared<triangle>(point3({:.3f},{:.3f},{:.3f}), point3({:.3f},{:.3f},{:.3f}), point3({:.3f},{:.3f},{:.2f}), material_s1));".format(
                    vert_floats[a][0], vert_floats[a][1], vert_floats[a][2],
                    vert_floats[b][0], vert_floats[b][1], vert_floats[b][2],
                    vert_floats[c][0], vert_floats[c][1], vert_floats[c][2])
    print(out_string)
    f_count += 1

    
# world.add(make_shared<triangle>(point3(108.48,0.00,-333.12), point3(108.48,0.00,-337.70), point3(108.48,20.00,-333.12), material_s1));
# exm = "f 123 13 4\n"
# 'v 5.9461 0.0000 6.0684\n'
# print(exm[2:-1].split(' '))