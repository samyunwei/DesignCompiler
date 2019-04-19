## what is this
this is notes for learing compiler.
It just can build in linux or mac enviroment.
- HOW TO BUILD

| Dependencies |
|---|
|CMake|
|BISON|
|FLEX|
|LEX_LIB|

BUILD STEPS

```
	mkdir build
	cd build
	cmake ../
	make -j4
```

- HOW TO TEST crowbar

```
   ./crowbar/mycrowbar_cpp ../test/crowbar/test.crb
```