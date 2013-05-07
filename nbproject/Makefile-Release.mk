#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=GNU-Linux-x86
CND_DLIB_EXT=so
CND_CONF=Release
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/src/ClientSocket.o \
	${OBJECTDIR}/src/ServerSocket.o \
	${OBJECTDIR}/src/Socket.o \
	${OBJECTDIR}/src/cNet.o \
	${OBJECTDIR}/src/cObject.o \
	${OBJECTDIR}/src/cUnits.o \
	${OBJECTDIR}/src/threads.o


# C Compiler Flags
CFLAGS=-m64

# CC Compiler Flags
CCFLAGS=-m64
CXXFLAGS=-m64

# Fortran Compiler Flags
FFLAGS=-m64

# Assembler Flags
ASFLAGS=--64

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../lib/libGameCommon_${CND_CONF}.${CND_DLIB_EXT}

../lib/libGameCommon_${CND_CONF}.${CND_DLIB_EXT}: ${OBJECTFILES}
	${MKDIR} -p ../lib
	${LINK.cc} -o ../lib/libGameCommon_${CND_CONF}.${CND_DLIB_EXT} ${OBJECTFILES} ${LDLIBSOPTIONS} -shared -fPIC

${OBJECTDIR}/src/ClientSocket.o: src/ClientSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -Isrc -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ClientSocket.o src/ClientSocket.cpp

${OBJECTDIR}/src/ServerSocket.o: src/ServerSocket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -Isrc -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ServerSocket.o src/ServerSocket.cpp

${OBJECTDIR}/src/Socket.o: src/Socket.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -Isrc -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/Socket.o src/Socket.cpp

${OBJECTDIR}/src/cNet.o: src/cNet.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -Isrc -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/cNet.o src/cNet.cpp

${OBJECTDIR}/src/cObject.o: src/cObject.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -Isrc -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/cObject.o src/cObject.cpp

${OBJECTDIR}/src/cUnits.o: src/cUnits.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -Isrc -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/cUnits.o src/cUnits.cpp

${OBJECTDIR}/src/threads.o: src/threads.c 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.c) -O2 -Iinclude -fPIC  -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/threads.o src/threads.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../lib/libGameCommon_${CND_CONF}.${CND_DLIB_EXT}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
