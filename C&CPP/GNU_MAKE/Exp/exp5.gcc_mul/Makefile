LIB_SRCS  := $(filter-out %main.c,$(shell find src -name *.c))
LIB_OBJS  := $(patsubst src/%.c,obj/%.o,$(LIB_SRCS))

EXEC_SRCS := $(filter %main.c,$(shell find src -name *.c))
EXEC_OBJS := $(patsubst src/%.c,obj/%.o,$(EXEC_SRCS))

HEADER_OPTIONS := -I./include

EXEC_FILE := ./bin/main

obj/%.o : src/%.c
	@mkdir -p $(dir $@)
	@gcc -c $^ -o $@ $(HEADER_OPTIONS)

$(EXEC_FILE) : $(LIB_OBJS) $(EXEC_OBJS)
	@mkdir -p $(dir $@)
	@gcc $^ -o $@ $(HEADER_OPTIONS)

release : $(EXEC_FILE)

run : release
	@$(EXEC_FILE)

clean :
	@rm -rf bin obj

.PHONY : release run clean

show_files :
	@echo $(LIB_SRCS)
	@echo $(LIB_OBJS)
	@echo $(EXEC_SRCS)
	@echo $(EXEC_OBJS)
	@echo $(EXEC_FILE)
