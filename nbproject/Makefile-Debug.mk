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
CND_PLATFORM=GNU-Linux
CND_DLIB_EXT=so
CND_CONF=Debug
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/RFIDReader.o \
	${OBJECTDIR}/charPointers.o \
	${OBJECTDIR}/lib_rfid/src/rfid.o \
	${OBJECTDIR}/lib_rfid/src/rfidPrivate.o \
	${OBJECTDIR}/newmain.o \
	${OBJECTDIR}/rfidReader.o \
	${OBJECTDIR}/rfidVisual.o


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
LDLIBSOPTIONS=-Wl,-rpath,build

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk build/rfidVisual

build/rfidVisual: ${OBJECTFILES}
	${MKDIR} -p build
	${LINK.c} -o build/rfidVisual ${OBJECTFILES} ${LDLIBSOPTIONS} $$(pkg-config --cflags --libs gtk+-3.0 )

${OBJECTDIR}/RFIDReader.o: RFIDReader.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/RFIDReader.o RFIDReader.c

${OBJECTDIR}/charPointers.o: charPointers.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/charPointers.o charPointers.c

${OBJECTDIR}/lib_rfid/src/rfid.o: lib_rfid/src/rfid.c 
	${MKDIR} -p ${OBJECTDIR}/lib_rfid/src
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib_rfid/src/rfid.o lib_rfid/src/rfid.c

${OBJECTDIR}/lib_rfid/src/rfidPrivate.o: lib_rfid/src/rfidPrivate.c 
	${MKDIR} -p ${OBJECTDIR}/lib_rfid/src
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/lib_rfid/src/rfidPrivate.o lib_rfid/src/rfidPrivate.c

${OBJECTDIR}/newmain.o: newmain.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/newmain.o newmain.c

${OBJECTDIR}/rfidReader.o: rfidReader.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rfidReader.o rfidReader.c

${OBJECTDIR}/rfidVisual.o: rfidVisual.c 
	${MKDIR} -p ${OBJECTDIR}
	${RM} "$@.d"
	$(COMPILE.c) -g -std=c11 -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/rfidVisual.o rfidVisual.c

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}
	${RM} build/rfidVisual

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
