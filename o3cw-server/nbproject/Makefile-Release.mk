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
	${OBJECTDIR}/cpermission.o \
	${OBJECTDIR}/extra/libbonbon/cjobmanager.o \
	${OBJECTDIR}/extra/libbonbon/cjob.o \
	${OBJECTDIR}/extra/libbonbon/ctparam.o \
	${OBJECTDIR}/extra/libbonbon/cmutex.o \
	${OBJECTDIR}/extra/libbonbon/cmodule.o \
	${OBJECTDIR}/cidsobject.o \
	${OBJECTDIR}/extra/libbonbon/bonbon.o \
	${OBJECTDIR}/cuser.o \
	${OBJECTDIR}/extra/libbonbon/csemaphore.o \
	${OBJECTDIR}/cclient.o \
	${OBJECTDIR}/csharedobject.o \
	${OBJECTDIR}/extra/libbonbon/clock.o \
	${OBJECTDIR}/extra/libbonbon/cthread.o \
	${OBJECTDIR}/cdiff.o \
	${OBJECTDIR}/extra/libbonbon/cbreak.o \
	${OBJECTDIR}/cdoc.o \
	${OBJECTDIR}/cdocpart.o \
	${OBJECTDIR}/cintimeobject.o \
	${OBJECTDIR}/cacessmode.o \
	${OBJECTDIR}/extra/libbonbon/cthreadjobs.o \
	${OBJECTDIR}/main.o

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

${OBJECTDIR}/cpermission.o: cpermission.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cpermission.o cpermission.cc

${OBJECTDIR}/extra/libbonbon/cjobmanager.o: extra/libbonbon/cjobmanager.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/cjobmanager.o extra/libbonbon/cjobmanager.cc

${OBJECTDIR}/extra/libbonbon/cjob.o: extra/libbonbon/cjob.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/cjob.o extra/libbonbon/cjob.cc

${OBJECTDIR}/extra/libbonbon/ctparam.o: extra/libbonbon/ctparam.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/ctparam.o extra/libbonbon/ctparam.cc

${OBJECTDIR}/extra/libbonbon/cmutex.o: extra/libbonbon/cmutex.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/cmutex.o extra/libbonbon/cmutex.cc

${OBJECTDIR}/extra/libbonbon/cmodule.o: extra/libbonbon/cmodule.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/cmodule.o extra/libbonbon/cmodule.cc

${OBJECTDIR}/cidsobject.o: cidsobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cidsobject.o cidsobject.cc

${OBJECTDIR}/extra/libbonbon/bonbon.o: extra/libbonbon/bonbon.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/bonbon.o extra/libbonbon/bonbon.cc

${OBJECTDIR}/cuser.o: cuser.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cuser.o cuser.cc

${OBJECTDIR}/extra/libbonbon/csemaphore.o: extra/libbonbon/csemaphore.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/csemaphore.o extra/libbonbon/csemaphore.cc

${OBJECTDIR}/cclient.o: cclient.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cclient.o cclient.cc

${OBJECTDIR}/csharedobject.o: csharedobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/csharedobject.o csharedobject.cc

${OBJECTDIR}/extra/libbonbon/clock.o: extra/libbonbon/clock.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/clock.o extra/libbonbon/clock.cc

${OBJECTDIR}/extra/libbonbon/cthread.o: extra/libbonbon/cthread.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/cthread.o extra/libbonbon/cthread.cc

${OBJECTDIR}/cdiff.o: cdiff.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cdiff.o cdiff.cc

${OBJECTDIR}/extra/libbonbon/cbreak.o: extra/libbonbon/cbreak.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/cbreak.o extra/libbonbon/cbreak.cc

${OBJECTDIR}/cdoc.o: cdoc.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cdoc.o cdoc.cc

${OBJECTDIR}/cdocpart.o: cdocpart.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cdocpart.o cdocpart.cc

${OBJECTDIR}/cintimeobject.o: cintimeobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cintimeobject.o cintimeobject.cc

${OBJECTDIR}/cacessmode.o: cacessmode.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/cacessmode.o cacessmode.cc

${OBJECTDIR}/extra/libbonbon/cthreadjobs.o: extra/libbonbon/cthreadjobs.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/extra/libbonbon/cthreadjobs.o extra/libbonbon/cthreadjobs.cc

${OBJECTDIR}/main.o: main.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -O2 -o ${OBJECTDIR}/main.o main.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Release
	${RM} dist/Release/GNU-Linux-x86/o3cw-server

# Subprojects
.clean-subprojects:
