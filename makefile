#本项目相关变量
ROOT_DIR = ../..

#编译器
CXX = g++

#目标文件
TARGET = ProjectEuler

#头文件包含目录，一行一个
INC_DIR += -I.
INC_DIR += -I./src
INC_DIR += -I./src/frame
INC_DIR += -I./src/problem
INC_DIR += -I${ROOT_DIR}
INC_DIR += -I${ROOT_DIR}/ext/include
INC_DIR += -I${ROOT_DIR}/ext/include/CppUtil

#静态库文件路径
STATIC_LIBS_DIR = ${ROOT_DIR}/ext/libs
#STATIC_LIBS = $(foreach n,$(STATIC_LIBS_DIR), $(wildcard $(n)/*.a)) 

#其他库文件，一行一个
STATIC_LIBS += ${STATIC_LIBS_DIR}/libCppUtil.a

#动态库文件路径
DYNAMIC_LIBS_DIR = ${ROOT_DIR}/ext/libs

#链接选项
LDFLAGS += -lrt
LDFLAGS += -fPIC -export-dynamic
#LDFLAGS += -lrtmp
LDFLAGS += ${STATIC_LIBS}

LDFLAGS += -lz
LDFLAGS += -ldl
LDFLAGS += -lpthread

#编译选项
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

#自动搜寻，当前项目的目标文件
#SUBDIR可以指定多个目录，指定的目录下的所有cpp文件会加入编译，比如 SUBDIR = . src
SUBDIR = ./src/frame
SUBDIR += ./src/problem
CXX_SOURCES =$(foreach n,$(SUBDIR), $(wildcard $(n)/*.cpp)) 

#其他外部依赖cpp文件在此处加上
CXX_SOURCES +=

#生成对应的.o文件
CXX_OBJECTS = $(patsubst %.cpp, %.o, $(CXX_SOURCES))

#添加自定义.o，这些.o不由clean删除，没有则无需填写
EXT_OBJECTS +=

#生成依赖关系
DEP_FILES = $(patsubst %.o, %.d, ${CXX_OBJECTS})

.PHONY:all 
all: ${TARGET}

$(TARGET): ${CXX_OBJECTS} ${EXT_OBJECTS} ${STATIC_LIBS}
	$(CXX) -o $@ $^ $(LDFLAGS)

#cpp相关文件处理，此处会自动匹配到cc，c文件，隐含规则
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
