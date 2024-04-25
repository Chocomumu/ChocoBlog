# := 即时赋值
HOST_ARCH   := amd64
TARGET_ARCH := $(HOST_ARCH)
HOST_ARCH   := linux

show_arch :
	@echo $(HOST_ARCH)
	@echo $(TARGET_ARCH)

.PHONY : show_arch

# = 延时赋值
HOST_NAME   = make.com
TARGET_NAME = $(HOST_NAME)
HOST_NAME   = makefile.com

show_name :
	@echo $(HOST_NAME)
	@echo $(TARGET_NAME)

.PHONY : show_name

# ?= 不存在赋值
MK_KEY1 ?= value1
MK_KEY1  = value2
MK_KEY1 ?= value3

MK_KEY2 ?= value3

show_mk_keys :
	@echo $(MK_KEY1)
	@echo $(MK_KEY2)

.PHONY : show_mk_keys
