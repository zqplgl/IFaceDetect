INCLUDE_DIRS = -I./include
INCLUDE_DIRS += -I/home/zqp/github/caffe/include
INCLUDE_DIRS += -I/usr/local/cuda/include

LIBRARY_DIRS = -L/home/zqp/github/caffe/build/lib
LIBRARY_DIRS += -L./lib

SRC = ./src/mtcnn.cpp

all: libmtcnn testmtcnn

libmtcnn: ${SRC}
	mkdir -p ./lib
	g++ -std=c++11 -o lib/libmtcnn.so ${SRC} -shared -fPIC `pkg-config --libs opencv` -lcaffe ${INCLUDE_DIRS} ${LIBRARY_DIRS} -lglog -lboost_system


testmtcnn: ./testmtcnn.cpp
	g++ -std=c++11 -o testmtcnn ./testmtcnn.cpp `pkg-config --libs opencv` -lmtcnn ${INCLUDE_DIRS} ${LIBRARY_DIRS}
