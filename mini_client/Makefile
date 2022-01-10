TARGET				:= client

LIBFT_DIR			:= $(DEPEND_DIR)/Libft
LIBFT_LIB			:= $(LIBFT_DIR)/libft.a

SRC_DIR				:= ./src

SRC_FILES			:= 
OBJ_FILES			:= $(addprefix $(INT_DIR)/,$(SRC_FILES:%.c=%.o))

VPATH				:= $(SRC_DIR)

DEFINES				:=
INCLUDE_DIRS		:= -I $(LIBFT_DIR)/include
LIBRARIES			:= $(LIBFT_LIB)

CC					:= cc
LINK_CMD			:= cc

ALL_CFLAGS			:= -std=c89 -Wall -Wextra -Werror -pedantic $(INCLUDE_DIRS)
ALL_LINKFLAGS		:=

DEBUG_CFLAGS		:= -g -O0 -fsanitize=address
DEBUG_LINKFLAGS		:= -fsanitize=address -fsanitize=undefined
DEBUG_DEFINES		:= -DMINI_SERVER_DEBUG

RELEASE_CFLAGS		:= -g -O2 -fsanitize=address
RELEASE_LINKFLAGS	:= -fsanitize=address -fsanitize=undefined
RELEASE_DEFINES		:= -DMINI_SERVER_RELEASE

DISTR_CFLAGS		:= -Ofast -g0
DISTR_LINKFLAGS		:=
DISTR_DEFINES		:= -DMINI_SERVER_DISTRIBUTION

SILENT		:= @
ifdef verbose
	SILENT	:=
endif

ifndef config
	config := release
endif

ifeq ($(config), debug)
	ALL_CFLAGS += $(DEBUG_CFLAGS)
	ALL_LINKFLAGS += $(DEBUG_LINKFLAGS)
	DEFINES += $(DEBUG_DEFINES)
else ifeq ($(config), release)
	ALL_CFLAGS += $(RELEASE_CFLAGS)
	ALL_LINKFLAGS += $(RELEASE_LINKFLAGS)
	DEFINES += $(RELEASE_DEFINES)
else ifeq ($(config), distribution)
	ALL_CFLAGS += $(DISTR_CFLAGS)
	ALL_CFLAGS += $(DISTR_DEFINES)
	ALL_LINKFLAGS += $(DISTR_LINKFLAGS)
endif

all: $(TARGET)

$(TARGET): $(OBJ_FILES) $(LIBRARIES)
	$(SILENT)echo Linking $@
	$(SILENT)$(LINK_CMD) $(ALL_LINKFLAGS) $(OBJ_FILES) $(LIBRARIES) -o $@

$(INT_DIR)/%.o: %.c
	$(SILENT)echo $(notdir $<)
	$(SILENT)mkdir -p $(INT_DIR)
	$(SILENT)$(CC) $(ALL_CFLAGS) -c $< -o $@

$(LIBFT_LIB):
	$(SILENT) make -C $(LIBFT_DIR)

clean:
	$(SILENT)echo Cleaning object files
	$(SILENT)rm -f $(OBJ_FILES)

fclean: clean
	$(SILENT)echo Cleaning $(TARGET)
	$(SILENT)rm -f $(TARGET)

re: fclean all