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
	${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o \
	${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o \
	${OBJECTDIR}/cxmlconfig.o \
	${OBJECTDIR}/extra/tinyxml/tinyxml.o \
	${OBJECTDIR}/cmysql.o \
	${OBJECTDIR}/extra/tinyxml/tinystr.o \
	${OBJECTDIR}/main.o \
	${OBJECTDIR}/co3cwserver.o

# C Compiler Flags
CFLAGS=-pthread -D_REENTRANT

# CC Compiler Flags
CCFLAGS=-pthread -D_REENTRANT -Wall
CXXFLAGS=-pthread -D_REENTRANT -Wall

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=-lpthread ../o3cw-core/dist/Debug/GNU-Linux-x86/o3cwcore.a -lcrypto `mysql_config --libs_r`  

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/GNU-Linux-x86/o3cw-server

dist/Debug/GNU-Linux-x86/o3cw-server: ${BUILD_SUBPROJECTS}

dist/Debug/GNU-Linux-x86/o3cw-server: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${LINK.cc} -o dist/Debug/GNU-Linux-x86/o3cw-server ${OBJECTFILES} ${LDLIBSOPTIONS} 

${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o: extra/tinyxml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o extra/tinyxml/tinyxmlerror.cpp

${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o: extra/tinyxml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o extra/tinyxml/tinyxmlparser.cpp

${OBJECTDIR}/cxmlconfig.o: cxmlconfig.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cxmlconfig.o cxmlconfig.cc

${OBJECTDIR}/extra/tinyxml/tinyxml.o: extra/tinyxml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/tinyxml/tinyxml.o extra/tinyxml/tinyxml.cpp

${OBJECTDIR}/cmysql.o: cmysql.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cmysql.o cmysql.cc

${OBJECTDIR}/extra/tinyxml/tinystr.o: extra/tinyxml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/tinyxml/tinystr.o extra/tinyxml/tinystr.cpp

${OBJECTDIR}/main.o: main.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/main.o main.cc

${OBJECTDIR}/co3cwserver.o: co3cwserver.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/co3cwserver.o co3cwserver.cc

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
