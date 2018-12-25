CXX := g++
CC  := gcc
CXX_FLAGS := -O2
CFLAGS := -O2
LDFLAGS := -lcurses

BIN_DIR := bin
BIN_FILE := snake-game

PREFIX := /
INST_DIR := ${PREFIX}usr/bin/${BIN_FILE}

SRCS := $(wildcard *.cpp)
OBJ_FILES := $(patsubst %.cpp,%.o,${SRCS})

all: directories ${BIN_FILE}

.PHONY: clean
clean:
	rm -rf "${BIN_DIR}"

${BIN_FILE}: ${OBJ_FILES}
	${CXX} ${LDFLAGS} $(addprefix ${BIN_DIR}/,${OBJ_FILES}) -o ${BIN_DIR}/${BIN_FILE}

${OBJ_FILES}: %.o : %.cpp
	echo ${BIN_DIR}
	${CXX} -c ${CXX_FLAGS} -o "${BIN_DIR}/$@" $<

# Directories needed for build
directories: ${BIN_DIR}
${BIN_DIR}:
	mkdir -p ${BIN_DIR}

rpm:
	echo rpm building
