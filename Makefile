# Compiler Options
CXX := g++
CC  := gcc
CXX_FLAGS := -O2 -std=c++11
CFLAGS := -O2
LDFLAGS := -lcurses

# Release Configuration
RELNAME := snake-game
RELVER := 0.0.1
RELDIR  := ${RELNAME}-${RELVER}
RELFILE := ${RELNAME}-${RELVER}.tar.gz

# Output Configuration
BIN_DIR := bin
BIN_FILE := snake-game

# Install Configuration
PREFIX := /tmp/
INST_DEST := ${PREFIX}usr/bin/${BIN_FILE}

# RPM Packaging settings
SPEC_FILE := snake-game.spec
TOPDIR := ${PWD}/.rpmbuild

SRCS := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,${SRCS})

all: directories ${BIN_FILE}

.PHONY: clean
clean:
	rm -rf "${BIN_DIR}"
	rm -f ${RELDIR}
	rm -rf ${RELFILE}

.PHONY: install
install: all
	mkdir -p $(dir ${INST_DEST})
	install --mode=755 ${BIN_DIR}/${BIN_FILE} ${INST_DEST}
rpm: release rpmtree
	cp ${RELFILE} ${TOPDIR}/SOURCES
	rpmbuild -ba --define '_topdir ${TOPDIR}' ${SPEC_FILE}
rpmtree:
	if [ ! -d ${TOPDIR} ]; then \
		rpmdev-setuptree; \
		cp -r ~/rpmbuild ${TOPDIR}; \
		rpmdev-wipetree; \
	fi
.PHONY: release
release: clean
	ln -s . ${RELDIR}
	tar cvzf ${RELFILE} ${RELDIR}

${BIN_FILE}: ${OBJ_FILES}
	${CXX} ${LDFLAGS} $(addprefix ${BIN_DIR}/,${OBJ_FILES}) -o ${BIN_DIR}/${BIN_FILE}

${OBJ_FILES}: %.o : %.cpp
	${CXX} -c ${CXX_FLAGS} -o "${BIN_DIR}/$@" $<

# Directories needed for build
directories: ${BIN_DIR}
${BIN_DIR}:
	mkdir -p ${BIN_DIR}

