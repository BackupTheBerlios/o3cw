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
	${OBJECTDIR}/cnetwork.o \
	${OBJECTDIR}/cidsobject.o \
	${OBJECTDIR}/cconnectionhandler.o \
	${OBJECTDIR}/extra/libbonbon/bonbon.o \
	${OBJECTDIR}/ckey.o \
	${OBJECTDIR}/cuser.o \
	${OBJECTDIR}/extra/libbonbon/csemaphore.o \
	${OBJECTDIR}/cprivatekey.o \
	${OBJECTDIR}/csharedobject.o \
	${OBJECTDIR}/extra/libbonbon/clock.o \
	${OBJECTDIR}/extra/libbonbon/cbreak.o \
	${OBJECTDIR}/cdoc.o \
	${OBJECTDIR}/cdocpart.o \
	${OBJECTDIR}/cstoreobjwrapper.o \
	${OBJECTDIR}/cintimeobject.o \
	${OBJECTDIR}/cpermission.o \
	${OBJECTDIR}/cstorage.o \
	${OBJECTDIR}/extra/libbonbon/cmutex.o \
	${OBJECTDIR}/csql.o \
	${OBJECTDIR}/cclient.o \
	${OBJECTDIR}/ccmdexec.o \
	${OBJECTDIR}/csocket.o \
	${OBJECTDIR}/cconfig.o \
	${OBJECTDIR}/ccommand.o \
	${OBJECTDIR}/cdifferenced.o \
	${OBJECTDIR}/extra/libbonbon/cvthread.o \
	${OBJECTDIR}/extra/libbonbon/cthread.o \
	${OBJECTDIR}/cdiff.o \
	${OBJECTDIR}/cpublickey.o \
	${OBJECTDIR}/co3cwbase.o \
	${OBJECTDIR}/cacessmode.o \
	${OBJECTDIR}/cthreadsafeobject.o \
	${OBJECTDIR}/ccrypto.o

# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=-pthread -D_REENTRANT `mysql_config --cflags` -Wall 
CXXFLAGS=-pthread -D_REENTRANT `mysql_config --cflags` -Wall 

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
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/libbonbon/cjobmanager.o extra/libbonbon/cjobmanager.cc

${OBJECTDIR}/cnetwork.o: cnetwork.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cnetwork.o cnetwork.cc

${OBJECTDIR}/cidsobject.o: cidsobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cidsobject.o cidsobject.cc

${OBJECTDIR}/cconnectionhandler.o: cconnectionhandler.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cconnectionhandler.o cconnectionhandler.cc

${OBJECTDIR}/extra/libbonbon/bonbon.o: extra/libbonbon/bonbon.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/libbonbon/bonbon.o extra/libbonbon/bonbon.cc

${OBJECTDIR}/ckey.o: ckey.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/ckey.o ckey.cc

${OBJECTDIR}/cuser.o: cuser.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cuser.o cuser.cc

${OBJECTDIR}/extra/libbonbon/csemaphore.o: extra/libbonbon/csemaphore.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/libbonbon/csemaphore.o extra/libbonbon/csemaphore.cc

${OBJECTDIR}/cprivatekey.o: cprivatekey.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cprivatekey.o cprivatekey.cc

${OBJECTDIR}/csharedobject.o: csharedobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/csharedobject.o csharedobject.cc

${OBJECTDIR}/extra/libbonbon/clock.o: extra/libbonbon/clock.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/libbonbon/clock.o extra/libbonbon/clock.cc

${OBJECTDIR}/extra/libbonbon/cbreak.o: extra/libbonbon/cbreak.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/libbonbon/cbreak.o extra/libbonbon/cbreak.cc

${OBJECTDIR}/cdoc.o: cdoc.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cdoc.o cdoc.cc

${OBJECTDIR}/cdocpart.o: cdocpart.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cdocpart.o cdocpart.cc

${OBJECTDIR}/cstoreobjwrapper.o: cstoreobjwrapper.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cstoreobjwrapper.o cstoreobjwrapper.cc

${OBJECTDIR}/cintimeobject.o: cintimeobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cintimeobject.o cintimeobject.cc

${OBJECTDIR}/cpermission.o: cpermission.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cpermission.o cpermission.cc

${OBJECTDIR}/cstorage.o: cstorage.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cstorage.o cstorage.cc

${OBJECTDIR}/extra/libbonbon/cmutex.o: extra/libbonbon/cmutex.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/libbonbon/cmutex.o extra/libbonbon/cmutex.cc

${OBJECTDIR}/csql.o: csql.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/csql.o csql.cc

${OBJECTDIR}/cclient.o: cclient.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cclient.o cclient.cc

${OBJECTDIR}/ccmdexec.o: ccmdexec.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/ccmdexec.o ccmdexec.cc

${OBJECTDIR}/csocket.o: csocket.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/csocket.o csocket.cc

${OBJECTDIR}/cconfig.o: cconfig.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cconfig.o cconfig.cc

${OBJECTDIR}/ccommand.o: ccommand.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/ccommand.o ccommand.cc

${OBJECTDIR}/cdifferenced.o: cdifferenced.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cdifferenced.o cdifferenced.cc

${OBJECTDIR}/extra/libbonbon/cvthread.o: extra/libbonbon/cvthread.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/libbonbon/cvthread.o extra/libbonbon/cvthread.cc

${OBJECTDIR}/extra/libbonbon/cthread.o: extra/libbonbon/cthread.cc 
	${MKDIR} -p ${OBJECTDIR}/extra/libbonbon
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/extra/libbonbon/cthread.o extra/libbonbon/cthread.cc

${OBJECTDIR}/cdiff.o: cdiff.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cdiff.o cdiff.cc

${OBJECTDIR}/cpublickey.o: cpublickey.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cpublickey.o cpublickey.cc

${OBJECTDIR}/co3cwbase.o: co3cwbase.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/co3cwbase.o co3cwbase.cc

${OBJECTDIR}/cacessmode.o: cacessmode.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cacessmode.o cacessmode.cc

${OBJECTDIR}/cthreadsafeobject.o: cthreadsafeobject.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/cthreadsafeobject.o cthreadsafeobject.cc

${OBJECTDIR}/ccrypto.o: ccrypto.cc 
	${MKDIR} -p ${OBJECTDIR}
	$(COMPILE.cc) -g -Werror -o ${OBJECTDIR}/ccrypto.o ccrypto.cc

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf:
	${RM} -r build/Debug
	${RM} dist/Debug/GNU-Linux-x86/o3cwcore.a

# Subprojects
.clean-subprojects:
