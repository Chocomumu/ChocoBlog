CPP_SRCS   = ./src/main.c
CPP_I_FILE = ./src/main.i
CPP_S_FILE = ./src/main.s
CPP_O_FILE = ./src/main.o
CPP_EXEC_F = ./main

# 预处理
$(CPP_I_FILE) : $(CPP_SRCS)
	@gcc -E $^ -o $@

preprocess : $(CPP_I_FILE)
.PHONY : preprocess

# 汇编
$(CPP_S_FILE) : $(CPP_I_FILE)
	@gcc -S $^ -o $@

assemble : $(CPP_S_FILE)
.PHONY : assemble

# 编译成字节码
$(CPP_O_FILE) : $(CPP_S_FILE)
	@gcc -c $^ -o $@

compile : $(CPP_O_FILE)
.PHONY : compile

# 链接成可执行文件
$(CPP_EXEC_F) : $(CPP_O_FILE)
	@gcc $^ -o $@

link : $(CPP_EXEC_F)
.PHONY : link

# 执行
run : link
	@$(CPP_EXEC_F)
.PHONY : run

# 清理编译结果
clean :
	@rm -f $(CPP_EXEC_F) $(CPP_O_FILE) $(CPP_S_FILE) $(CPP_I_FILE)