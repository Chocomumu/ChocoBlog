LIB_SRCS  := $(filter-out %main.c,$(shell find src -name *.c))
LIB_OBJS  := $(patsubst src/%.c,obj/%.o,$(LIB_SRCS))

EXEC_SRCS := $(filter %main.c,$(shell find src -name *.c))
EXEC_OBJS := $(patsubst src/%.c,obj/%.o,$(EXEC_SRCS))

HEADER_OPTIONS := -I./include

SLIB_FILE := ./lib/libcal.a

LIB_PATH  := $(sort $(dir $(SLIB_FILE)))

LIB_OPTIONS := $(foreach item,$(SLIB_FILE),-l$(subst lib,,$(basename $(notdir $(item))))) -L$(LIB_PATH)

EXEC_FILE := ./bin/main

obj/%.o : src/%.c
	@mkdir -p $(sort $(dir $@))
	@gcc -c $^ -o $@ $(HEADER_OPTIONS)

# 编译链接静态库
$(SLIB_FILE) : $(LIB_OBJS)
	@mkdir -p $(sort $(dir $@))
	@ar -r $@ $^

static_lib : $(SLIB_FILE)

.PHONY : static_lib


$(EXEC_FILE) : static_lib $(EXEC_OBJS)
	@mkdir -p $(dir $@)
	@gcc $(EXEC_OBJS) -o $@ $(HEADER_OPTIONS) $(LIB_OPTIONS)

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
