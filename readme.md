the test assignment project was compiled with microsoft visual studio 2019

Structure of the folders:

AndreiKeinoTest: - VS solution folder
	|
	AndreiKeinoTest.sln - VS solution file
	|
	CADEX C++ assignment v4 for probationers.pdf - assignment description file
	|
	readme.txt - this file
	|
	remove_compilation_dirs.py - python code to remove auxiliary folders
	|
	AndreiKeinoTest: - project folder
		|
		AndreiKeinoTest.cpp - assignment implementation
		| 
		AndreiKeinoTest.vcxproj - VS project file
		|
		AndreiKeinoTest.vcxproj.filters - axiliary VS file
		| 
		AndreiKeinoTest.vcxproj.user - axiliary VS file
		|
		include - header file folder
			|
			constants.h - some constants declaration
			|
			curves.h - curve classes implementation
			|
			types.h - some typedefs
			| 
			vec3d.h - vector and point classes implementation
	