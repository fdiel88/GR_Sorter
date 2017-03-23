QT_GUI_CFLAGS := $(shell pkg-config QtGui --cflags)
QT_GUI_LIBS := $(shell pkg-config QtGui --libs)

ROOT_CFLAGS := $(shell root-config --cflags)
ROOT_LIBS := $(shell root-config --glibs)

#CFLAGS = -Wall - Werror - g - O2 $(QT_GUI_CFLAGS)
CXXFLAGS = -Wall -Werror -g -O2 -std=c++11 $(ROOT_CFLAGS) 
LDLIBS = $(ROOT_LIBS)

.PHONY : all clean

all : gr_sorter

clean : 
	rm -rf *.o gr_sorter
gr_sorter : gr_sorter.cc sorter_config.cc sorter_user.cc sorter_root.cc sorter_init.cc sorter_util.cc sorter_read.cc sorter_treedata.cc
