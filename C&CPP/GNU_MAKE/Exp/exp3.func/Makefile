# shell 函数
CPP_SRCS    := $(shell find src -name *.c)
CPP_HEADERS := $(shell find include -name *.h)

# dir 获取文件所属目录
show_dir :
	@echo $(dir $(CPP_SRCS))

.PHONY : show_dir
	

# patsubst 正则替换函数
OBJ_TARGETS := $(patsubst src/%.c,obj/%.o,$(CPP_SRCS))

# notdir 去除文件夹
USR_LIBS    := $(notdir $(shell find /usr/lib))
# basename 获取文件名(无后缀，.符号前), subst 字符串替换函数， filter筛选符合要求的
USR_P_LIBS  := $(subst lib,,$(basename $(filter %.dylib,$(USR_LIBS))))

LIST_STR = cal\
           fix \
		   fine\

LIST_NEW  = $(foreach item,$(LIST_STR),-l$(item))
LIST_NEW2 = $(LIST_STR:%=-s%)

show_files :
	@echo $(CPP_SRCS)
	@echo $(CPP_HEADERS)
	@echo $(OBJ_TARGETS)

.PHONY : show_files

show_libs :
	@echo $(USR_LIBS)
	@echo $(USR_P_LIBS)

.PHONY : show_libs

show_list :
	@echo $(LIST_STR)
	@echo $(LIST_NEW)
	@echo $(LIST_NEW2)

.PHONY : show_list