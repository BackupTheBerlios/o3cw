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
	${OBJECTDIR}/extra/libbonbon/cjobmanager.o \
	${OBJECTDIR}/cmysql.o \
	${OBJECTDIR}/cnetwork.o \
	${OBJECTDIR}/cidsobject.o \
	${OBJECTDIR}/cconnectionhandler.o \
	${OBJECTDIR}/extra/libbonbon/bonbon.o \
	${OBJECTDIR}/cuser.o \
	${OBJECTDIR}/extra/libbonbon/csemaphore.o \
	${OBJECTDIR}/csharedobject.o \
	${OBJECTDIR}/extra/libbonbon/clock.o \
	${OBJECTDIR}/extra/tinyxml/tinyxml.o \
	${OBJECTDIR}/extra/libbonbon/cbreak.o \
	${OBJECTDIR}/cdoc.o \
	${OBJECTDIR}/cdocpart.o \
	${OBJECTDIR}/cintimeobject.o \
	${OBJECTDIR}/cpermission.o \
	${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o \
	${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o \
	${OBJECTDIR}/cstorage.o \
	${OBJECTDIR}/extra/libbonbon/cmutex.o \
	${OBJECTDIR}/csql.o \
	${OBJECTDIR}/cclient.o \
	${OBJECTDIR}/ccmdexec.o \
	${OBJECTDIR}/csocket.o \
	${OBJECTDIR}/cconfig.o \
	${OBJECTDIR}/ccommand.o \
	${OBJECTDIR}/extra/libbonbon/cvthread.o \
	${OBJECTDIR}/extra/libbonbon/cthread.o \
	${OBJECTDIR}/cdiff.o \
	${OBJECTDIR}/co3cwbase.o \
	${OBJECTDIR}/extra/tinyxml/tinystr.o \
	${OBJECTDIR}/cacessmode.o \
	${OBJECTDIR}/cthreadsafeobject.o \
	${OBJECTDIR}/ccrypto.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pthread -D_REENTRANT `mysql_config --cflags` 
CXXFLAGS=-pthread -D_REENTRANT `mysql_config --cflags` 

# Fortran Compiler Flags
FFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS} dist/Debug/GNU-Linux-x86/o3cwcore.a

dist/Debug/GNU-Linux-x86/o3cwcore.a: ${OBJECTFILES}
	${MKDIR} -p dist/Debug/GNU-Linux-x86
	${RM} dist/Debug/GNU-Linux-x86/o3cwcore.a
	${AR} rv dist/Debug/GNU-Linux-x86/o3cwcore.a ${OBJECTFILES} 
	$(RANLIB) dist/Debug/GNU-Linux-x86/o3cwcore.a

${OBJECTDIR}/extra/libbonbon/cjobmanager.o: extra/libbonbon/cjobmanager.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/libbonbon/cjobmanager.o extra/libbonbon/cjobmanager.cc

${OBJECTDIR}/cmysql.o: cmysql.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cmysql.o cmysql.cc

${OBJECTDIR}/cnetwork.o: cnetwork.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cnetwork.o cnetwork.cc

${OBJECTDIR}/cidsobject.o: cidsobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cidsobject.o cidsobject.cc

${OBJECTDIR}/cconnectionhandler.o: cconnectionhandler.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cconnectionhandler.o cconnectionhandler.cc

${OBJECTDIR}/extra/libbonbon/bonbon.o: extra/libbonbon/bonbon.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/libbonbon/bonbon.o extra/libbonbon/bonbon.cc

${OBJECTDIR}/cuser.o: cuser.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cuser.o cuser.cc

${OBJECTDIR}/extra/libbonbon/csemaphore.o: extra/libbonbon/csemaphore.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/libbonbon/csemaphore.o extra/libbonbon/csemaphore.cc

${OBJECTDIR}/csharedobject.o: csharedobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/csharedobject.o csharedobject.cc

${OBJECTDIR}/extra/libbonbon/clock.o: extra/libbonbon/clock.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/libbonbon/clock.o extra/libbonbon/clock.cc

${OBJECTDIR}/extra/tinyxml/tinyxml.o: extra/tinyxml/tinyxml.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/tinyxml/tinyxml.o extra/tinyxml/tinyxml.cpp

${OBJECTDIR}/extra/libbonbon/cbreak.o: extra/libbonbon/cbreak.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/libbonbon/cbreak.o extra/libbonbon/cbreak.cc

${OBJECTDIR}/cdoc.o: cdoc.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cdoc.o cdoc.cc

${OBJECTDIR}/cdocpart.o: cdocpart.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cdocpart.o cdocpart.cc

${OBJECTDIR}/cintimeobject.o: cintimeobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cintimeobject.o cintimeobject.cc

${OBJECTDIR}/cpermission.o: cpermission.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cpermission.o cpermission.cc

${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o: extra/tinyxml/tinyxmlparser.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/tinyxml/tinyxmlparser.o extra/tinyxml/tinyxmlparser.cpp

${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o: extra/tinyxml/tinyxmlerror.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/tinyxml/tinyxmlerror.o extra/tinyxml/tinyxmlerror.cpp

${OBJECTDIR}/cstorage.o: cstorage.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cstorage.o cstorage.cc

${OBJECTDIR}/extra/libbonbon/cmutex.o: extra/libbonbon/cmutex.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/libbonbon/cmutex.o extra/libbonbon/cmutex.cc

${OBJECTDIR}/csql.o: csql.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/csql.o csql.cc

${OBJECTDIR}/cclient.o: cclient.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cclient.o cclient.cc

${OBJECTDIR}/ccmdexec.o: ccmdexec.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/ccmdexec.o ccmdexec.cc

${OBJECTDIR}/csocket.o: csocket.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/csocket.o csocket.cc

${OBJECTDIR}/cconfig.o: cconfig.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cconfig.o cconfig.cc

${OBJECTDIR}/ccommand.o: ccommand.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/ccommand.o ccommand.cc

${OBJECTDIR}/extra/libbonbon/cvthread.o: extra/libbonbon/cvthread.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/libbonbon/cvthread.o extra/libbonbon/cvthread.cc

${OBJECTDIR}/extra/libbonbon/cthread.o: extra/libbonbon/cthread.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/libbonbon/cthread.o extra/libbonbon/cthread.cc

${OBJECTDIR}/cdiff.o: cdiff.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cdiff.o cdiff.cc

${OBJECTDIR}/co3cwbase.o: co3cwbase.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/co3cwbase.o co3cwbase.cc

${OBJECTDIR}/extra/tinyxml/tinystr.o: extra/tinyxml/tinystr.cpp 
	${MKDIR} -p ${OBJECTDIR}/extra/tinyxml
	$(COMPILE.cc) -g -o ${OBJECTDIR}/extra/tinyxml/tinystr.o extra/tinyxml/tinystr.cpp

${OBJECTDIR}/cacessmode.o: cacessmode.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cacessmode.o cacessmode.cc

${OBJECTDIR}/cthreadsafeobject.o: cthreadsafeobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/cthreadsafeobject.o cthreadsafeobject.cc

${OBJECTDIR}/ccrypto.o: ccrypto.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -o ${OBJECTDIR}/ccrypto.o ccrypto.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/o3cwcore.a

# Subprojects
.clean-subprojects:
