# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build

# Include any dependencies generated for this target.
include CMakeFiles/socserver.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/socserver.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/socserver.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/socserver.dir/flags.make

CMakeFiles/socserver.dir/main.cpp.o: CMakeFiles/socserver.dir/flags.make
CMakeFiles/socserver.dir/main.cpp.o: /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/main.cpp
CMakeFiles/socserver.dir/main.cpp.o: CMakeFiles/socserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/socserver.dir/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/socserver.dir/main.cpp.o -MF CMakeFiles/socserver.dir/main.cpp.o.d -o CMakeFiles/socserver.dir/main.cpp.o -c /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/main.cpp

CMakeFiles/socserver.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socserver.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/main.cpp > CMakeFiles/socserver.dir/main.cpp.i

CMakeFiles/socserver.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socserver.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/main.cpp -o CMakeFiles/socserver.dir/main.cpp.s

CMakeFiles/socserver.dir/server/SServer.cpp.o: CMakeFiles/socserver.dir/flags.make
CMakeFiles/socserver.dir/server/SServer.cpp.o: /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/SServer.cpp
CMakeFiles/socserver.dir/server/SServer.cpp.o: CMakeFiles/socserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/socserver.dir/server/SServer.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/socserver.dir/server/SServer.cpp.o -MF CMakeFiles/socserver.dir/server/SServer.cpp.o.d -o CMakeFiles/socserver.dir/server/SServer.cpp.o -c /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/SServer.cpp

CMakeFiles/socserver.dir/server/SServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socserver.dir/server/SServer.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/SServer.cpp > CMakeFiles/socserver.dir/server/SServer.cpp.i

CMakeFiles/socserver.dir/server/SServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socserver.dir/server/SServer.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/SServer.cpp -o CMakeFiles/socserver.dir/server/SServer.cpp.s

CMakeFiles/socserver.dir/server/mongo.cpp.o: CMakeFiles/socserver.dir/flags.make
CMakeFiles/socserver.dir/server/mongo.cpp.o: /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/mongo.cpp
CMakeFiles/socserver.dir/server/mongo.cpp.o: CMakeFiles/socserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/socserver.dir/server/mongo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/socserver.dir/server/mongo.cpp.o -MF CMakeFiles/socserver.dir/server/mongo.cpp.o.d -o CMakeFiles/socserver.dir/server/mongo.cpp.o -c /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/mongo.cpp

CMakeFiles/socserver.dir/server/mongo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socserver.dir/server/mongo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/mongo.cpp > CMakeFiles/socserver.dir/server/mongo.cpp.i

CMakeFiles/socserver.dir/server/mongo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socserver.dir/server/mongo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/mongo.cpp -o CMakeFiles/socserver.dir/server/mongo.cpp.s

CMakeFiles/socserver.dir/server/MongoInstance.cpp.o: CMakeFiles/socserver.dir/flags.make
CMakeFiles/socserver.dir/server/MongoInstance.cpp.o: /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/MongoInstance.cpp
CMakeFiles/socserver.dir/server/MongoInstance.cpp.o: CMakeFiles/socserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/socserver.dir/server/MongoInstance.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/socserver.dir/server/MongoInstance.cpp.o -MF CMakeFiles/socserver.dir/server/MongoInstance.cpp.o.d -o CMakeFiles/socserver.dir/server/MongoInstance.cpp.o -c /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/MongoInstance.cpp

CMakeFiles/socserver.dir/server/MongoInstance.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socserver.dir/server/MongoInstance.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/MongoInstance.cpp > CMakeFiles/socserver.dir/server/MongoInstance.cpp.i

CMakeFiles/socserver.dir/server/MongoInstance.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socserver.dir/server/MongoInstance.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/server/MongoInstance.cpp -o CMakeFiles/socserver.dir/server/MongoInstance.cpp.s

CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o: CMakeFiles/socserver.dir/flags.make
CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o: /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/model/ObjectInfo.cpp
CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o: CMakeFiles/socserver.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o -MF CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o.d -o CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o -c /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/model/ObjectInfo.cpp

CMakeFiles/socserver.dir/model/ObjectInfo.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/socserver.dir/model/ObjectInfo.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/model/ObjectInfo.cpp > CMakeFiles/socserver.dir/model/ObjectInfo.cpp.i

CMakeFiles/socserver.dir/model/ObjectInfo.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/socserver.dir/model/ObjectInfo.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/model/ObjectInfo.cpp -o CMakeFiles/socserver.dir/model/ObjectInfo.cpp.s

# Object files for target socserver
socserver_OBJECTS = \
"CMakeFiles/socserver.dir/main.cpp.o" \
"CMakeFiles/socserver.dir/server/SServer.cpp.o" \
"CMakeFiles/socserver.dir/server/mongo.cpp.o" \
"CMakeFiles/socserver.dir/server/MongoInstance.cpp.o" \
"CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o"

# External object files for target socserver
socserver_EXTERNAL_OBJECTS =

socserver: CMakeFiles/socserver.dir/main.cpp.o
socserver: CMakeFiles/socserver.dir/server/SServer.cpp.o
socserver: CMakeFiles/socserver.dir/server/mongo.cpp.o
socserver: CMakeFiles/socserver.dir/server/MongoInstance.cpp.o
socserver: CMakeFiles/socserver.dir/model/ObjectInfo.cpp.o
socserver: CMakeFiles/socserver.dir/build.make
socserver: /usr/local/lib/libmongocxx.so.r3.9.0
socserver: /usr/local/lib/libbsoncxx.so.r3.9.0
socserver: CMakeFiles/socserver.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable socserver"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/socserver.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/socserver.dir/build: socserver
.PHONY : CMakeFiles/socserver.dir/build

CMakeFiles/socserver.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/socserver.dir/cmake_clean.cmake
.PHONY : CMakeFiles/socserver.dir/clean

CMakeFiles/socserver.dir/depend:
	cd /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build /home/afz/workzone/socket/mongo-eclipse-ws/vts-cocket/tr-06-cpp-server/build/CMakeFiles/socserver.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/socserver.dir/depend

