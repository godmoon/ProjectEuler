#����Ŀ��ر���
ROOT_DIR = ../..

#������
CXX = g++

#Ŀ���ļ�
TARGET = ProjectEuler

#ͷ�ļ�����Ŀ¼��һ��һ��
INC_DIR += -I.
INC_DIR += -I./src
INC_DIR += -I./src/frame
INC_DIR += -I./src/problem
INC_DIR += -I${ROOT_DIR}
INC_DIR += -I${ROOT_DIR}/ext/include
INC_DIR += -I${ROOT_DIR}/ext/include/CppUtil

#��̬���ļ�·��
STATIC_LIBS_DIR = ${ROOT_DIR}/ext/libs
#STATIC_LIBS = $(foreach n,$(STATIC_LIBS_DIR), $(wildcard $(n)/*.a)) 

#�������ļ���һ��һ��
STATIC_LIBS += ${STATIC_LIBS_DIR}/libCppUtil.a

#��̬���ļ�·��
DYNAMIC_LIBS_DIR = ${ROOT_DIR}/ext/libs

#����ѡ��
LDFLAGS += -lrt
LDFLAGS += -fPIC -export-dynamic
#LDFLAGS += -lrtmp
LDFLAGS += ${STATIC_LIBS}

LDFLAGS += -lz
LDFLAGS += -ldl
LDFLAGS += -lpthread

#����ѡ��
CXXFLAGS += -g 
CXXFLAGS += -MMD
CXXFLAGS += -O2
CXXFLAGS += -Wall
CXXFLAGS += -Wextra
CXXFLAGS += -fPIC
CXXFLAGS += -std=c++11 
CXXFLAGS += -Wno-deprecated
CXXFLAGS += -Wunused-parameter
CXXFLAGS += -DUSE_CPP_LOG_MACRO
CXXFLAGS += $(INC_DIR)

#�Զ���Ѱ����ǰ��Ŀ��Ŀ���ļ�
#SUBDIR����ָ�����Ŀ¼��ָ����Ŀ¼�µ�����cpp�ļ��������룬���� SUBDIR = . src
SUBDIR = ./src/frame
SUBDIR += ./src/problem
CXX_SOURCES =$(foreach n,$(SUBDIR), $(wildcard $(n)/*.cpp)) 

#�����ⲿ����cpp�ļ��ڴ˴�����
CXX_SOURCES +=

#���ɶ�Ӧ��.o�ļ�
CXX_OBJECTS = $(patsubst %.cpp, %.o, $(CXX_SOURCES))

#����Զ���.o����Щ.o����cleanɾ����û����������д
EXT_OBJECTS +=

#����������ϵ
DEP_FILES = $(patsubst %.o, %.d, ${CXX_OBJECTS})

.PHONY:all 
all: ${TARGET}

$(TARGET): ${CXX_OBJECTS} ${EXT_OBJECTS} ${STATIC_LIBS}
	$(CXX) -o $@ $^ $(LDFLAGS)

#cpp����ļ������˴����Զ�ƥ�䵽cc��c�ļ�����������
%.o: %.cpp
	${CXX} -c $(CXXFLAGS) -o $@ $<

%.d: %.cpp
	@set -e;${CXX} -MM $< $(CXXFLAGS) -MF $(patsubst %.cpp, %.d, $<)

-include ${DEP_FILES}

test:
	@echo "CXX_OBJECTS:"${CXX_OBJECTS}
	@echo "STATIC_LIBS:"${STATIC_LIBS}
	@echo "DEP_FILES:"${DEP_FILES}

.PHONY:clean 
clean:
	rm -rf ${TARGET} ${CXX_OBJECTS} ${DEP_FILES}

run:
	make
	./$(TARGET) $(pro_no)
