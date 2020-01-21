# Scop
42 school project: 3D modeler of .obj files

![](new_maya_demo.gif)


## Setup
Launch the Makefile command in the root repository : `make`

When **scop** binary is created, you can use it like :
```
./scop obj_file
./scop res/obj_files/newmaya.obj
```

## What it does ?
It reprensent graphically a .obj file, like your favorite model. There are lot of features:
- .OBJ parser
- .TGA parser
- Object movement
- Several types of display
- Light handling (when normal vectors are in .obj)
	- Light movement
	- Real time update of light

Input commands:
- `W A S D` : Camera movement
- `[ ]` :	Increase / Decrease camera speed
- `M` :		Enable / Disable mouse mode
- `Y U` :	Object movement over X axis
- `H J` :	Object movement over Y axis
- `B N` :	Object movement over Z axis
- `P` :		Change polygon mode (Fill, Line, Point)
- `T` :		Add / Remove texture
- `C` :		Change color mode (Grey, Normal if available, position)
- `R` : 	Enable / Disable object rotation
- `L` : 	Enable / Disable light if available
- `O` : 	Change object selection (Object / Light if available)
