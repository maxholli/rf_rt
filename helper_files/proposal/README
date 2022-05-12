### How to generate ray tracing 3D environment from Shapefile buildings

Start by downloading the shape file for Boulder buildings. This will give you 6 files. Building_Footprints.cpg .dbf .prj .shp .shx .xml. 

Download triangle.zip from https://www.cs.cmu.edu/~quake/triangle.html

'''
mkdir holey_Bs
mv triangle.zip holey_Bs
unzip triangle.zip
make
mkdir Buildings
mv Building_* Buildings/
'''

Start with bldr_shape_to_obj.py and put the building DRCOGID in the select_buildings list. And make sure the full path is correct to holey_Bs.

'''
pip3 install pyshp
python3 bldr_shape_to_obj.py Buildings/Building_Footprints.shp --output output_file.obj
'''

The .obj is enought for the GPU ray tracer. If you're using the CPU ray tracer you need to keep going.

Change the filename variable in obj_to_CPUraytracer.py to match the output_file.obj you just created.

'''
python3 obj_to_CPUraytracer.py > output_file.txt
'''

Then copy this into a file in the worlds/ directory of your ray tracer. Check out rf_rt/proposal/worlds/proposal.h for an example. This file need to be #include'd in your main.cpp ray tracing file and then read in as the world.