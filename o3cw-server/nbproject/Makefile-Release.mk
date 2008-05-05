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
OBJECTDIR=build/Release/GNU-Linux-x86

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o \
	${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o \
	${OBJECTDIR}/cxmlconfig.o \
	${OBJECTDIR}/extra/tinyxml/tinyxml.o \
	${OBJECTDIR}/cmysql.o \
	${OBJECTDIR}/extra/tinyxml/tinystr.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/co3cwserver.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Release/GNU-Linux-x86/o3cw-server

dist/Release/GNU-Linux-x86/o3cw-server: ${OBJECTFILES}
	${MKDIR} -p dist/Release/GNU-Linux-x86
	${LINK.cc} -o dist/Release/GNU-Linux-x86/o3cw-server ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o: extra/tinyxml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o extra/tinyxml/tinyxmlerror.cpp

${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o: extra/tinyxml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o extra/tinyxml/tinyxmlparser.cpp

${OBJECTDIR}/cxmlconfig.o: cxmlconfig.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cxmlconfig.o cxmlconfig.cc

${OBJECTDIR}/extra/tinyxml/tinyxml.o: extra/tinyxml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/tinyxml/tinyxml.o extra/tinyxml/tinyxml.cpp

${OBJECTDIR}/cmysql.o: cmysql.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cmysql.o cmysql.cc

${OBJECTDIR}/extra/tinyxml/tinystr.o: extra/tinyxml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/tinyxml/tinystr.o extra/tinyxml/tinystr.cpp

${OBJECTDIR}/main.o: main.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/main.o main.cc

${OBJECTDIR}/co3cwserver.o: co3cwserver.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/co3cwserver.o co3cwserver.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/o3cw-server

# Subprojects
.clean-subprojects:
