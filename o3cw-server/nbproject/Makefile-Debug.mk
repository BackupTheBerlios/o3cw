#
# Gererated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
CCADMIN=CCadmin
RANLIB=ranlib
CC=gcc
CCC=g++
CXX=g++
FC=gfortran

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=build/Debug/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/co3cwserver.o

# C Compiler Flags
CFLAGS=-pthread -D_REENTRANT

# CC Compiler Flags
CCFLAGS=-pthread -D_REENTRANT
CXXFLAGS=-pthread -D_REENTRANT

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread ../o3cw-core/dist/Debug/GNU-Linux-x86/o3cwcore.a -lcrypto

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/GNU-Linux-x86/o3cw-server

dist/Debug/GNU-Linux-x86/o3cw-server: ${BUILD_SUBPROJECTS}

dist/Debug/GNU-Linux-x86/o3cw-server: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o dist/Debug/GNU-Linux-x86/o3cw-server ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/main.o: main.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/main.o main.cc

${OBJECTDIR}/co3cwserver.o: co3cwserver.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/co3cwserver.o co3cwserver.cc

# Subprojects
.build-subprojects:
	cd ../o3cw-core && ${MAKE}  -f Makefile CONF=Debug

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/o3cw-server

# Subprojects
.clean-subprojects:
	cd ../o3cw-core && ${MAKE}  -f Makefile CONF=Debug clean
