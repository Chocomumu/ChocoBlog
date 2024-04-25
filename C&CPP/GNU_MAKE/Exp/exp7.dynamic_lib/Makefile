LIB_SRCS  := $(filter-out %main.c,$(shell find src -name *.c))
LIB_OBJS  := $(patsubst src/%.c,obj/%.o,$(LIB_SRCS))

EXEC_SRCS := $(filter %main.c,$(shell find src -name *.c))
EXEC_OBJS := $(patsubst src/%.c,obj/%.o,$(EXEC_SRCS))

HEADER_OPTIONS := -I./include

DLIB_FILE := ./lib/libcal.so

LIB_PATH  := $(sort $(dir $(DLIB_FILE)))

LIB_OPTIONS := $(foreach item,$(DLIB_FILE),-l$(subst lib,,$(basename $(notdir $(item))))) -Wl,-rpath $(LIB_PATH) -L$(LIB_PATH)

COMPILE_OPTIONS := -O3

EXEC_FILE := ./bin/main

obj/%.o : src/%.c
	@mkdir -p $(sort $(dir $@))
	@gcc -c $^ -o $@ $(HEADER_OPTIONS)

# 编译链接动态库
$(DLIB_FILE) : $(LIB_OBJS)
	@mkdir -p $(sort $(dir $@))
	@gcc -shared $^ -o $@

dynamic_lib : $(DLIB_FILE)

.PHONY : dynamic_lib


$(EXEC_FILE) : dynamic_lib $(EXEC_OBJS)
	@mkdir -p $(dir $@)
	@gcc $(EXEC_OBJS) -o $@ $(HEADER_OPTIONS) $(LIB_OPTIONS) $(COMPILE_OPTIONS)

release : $(EXEC_FILE)

run : release
	@$(EXEC_FILE)

clean :
	@rm -rf bin obj lib

.PHONY : release run clean

show_files :
	@echo $(LIB_SRCS)
	@echo $(LIB_OBJS)
	@echo $(EXEC_SRCS)
	@echo $(EXEC_OBJS)
	@echo $(EXEC_FILE)
	@echo $(LIB_OPTIONS)
	@echo $(COMPILE_OPTIONS)
