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
	${OBJECTDIR}/src/frameListener.o \
	${OBJECTDIR}/src/joyListener.o \
	${OBJECTDIR}/src/keyListener.o \
	${OBJECTDIR}/src/main.o \
	${OBJECTDIR}/src/mouseListener.o \
	${OBJECTDIR}/src/ogreApplication.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-L/usr/lib/OGRE -Wl,-rpath,/usr/lib/OGRE -Wl,-rpath,../lib -lCEGUIBase -lOgreMain -lOIS -Wl,-rpath,../GameCommon/../lib -L../GameCommon/../lib -lGameCommon_Debug -lCEGUIOgreRenderer

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../bin/graphicsclient_${CND_CONF}

../bin/graphicsclient_${CND_CONF}: ../GameCommon/../lib/libGameCommon_Debug.so

../bin/graphicsclient_${CND_CONF}: ${OBJECTFILES}
	${MKDIR} -p ../bin
	${LINK.cc} -o ../bin/graphicsclient_${CND_CONF} ${OBJECTFILES} ${LDLIBSOPTIONS}

${OBJECTDIR}/src/frameListener.o: src/frameListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../GameCommon/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -I/usr/include/CEGUI/RendererModules/Ogre -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/frameListener.o src/frameListener.cpp

${OBJECTDIR}/src/joyListener.o: src/joyListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../GameCommon/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -I/usr/include/CEGUI/RendererModules/Ogre -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/joyListener.o src/joyListener.cpp

${OBJECTDIR}/src/keyListener.o: src/keyListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../GameCommon/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -I/usr/include/CEGUI/RendererModules/Ogre -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/keyListener.o src/keyListener.cpp

${OBJECTDIR}/src/main.o: src/main.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../GameCommon/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -I/usr/include/CEGUI/RendererModules/Ogre -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/main.o src/main.cpp

${OBJECTDIR}/src/mouseListener.o: src/mouseListener.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../GameCommon/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -I/usr/include/CEGUI/RendererModules/Ogre -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/mouseListener.o src/mouseListener.cpp

${OBJECTDIR}/src/ogreApplication.o: src/ogreApplication.cpp 
	${MKDIR} -p ${OBJECTDIR}/src
	${RM} $@.d
	$(COMPILE.cc) -O2 -Iinclude -I../GameCommon/include -I/usr/include/OGRE -I/usr/include/OIS -I/usr/include/CEGUI -I/usr/include/CEGUI/RendererModules/Ogre -MMD -MP -MF $@.d -o ${OBJECTDIR}/src/ogreApplication.o src/ogreApplication.cpp

# Subprojects
.build-subprojects:
	cd ../GameCommon && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} ../bin/graphicsclient_${CND_CONF}

# Subprojects
.clean-subprojects:
	cd ../GameCommon && ${MAKE}  -f Makefile CONF=Debug clean

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
