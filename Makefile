CLIENT_TARGET			:= client
SERVER_TARGET			:= server
NAME					:= $(CLIENT_TARGET) $(SERVER_TARGET) 

CLIENT_DIR				:= mini_client
SERVER_DIR				:= mini_server
DEPEND_DIR 				:= $(PARENT_DIR)/Dependencies

DEPEND_DIR				:= ./Dependencies
INT_DIR					:= ./obj

LIBFT_DIR				:= $(DEPEND_DIR)/libft
LIBFT_LIB				:= $(LIBFT_DIR)/libft.a

UTILS_DIR				:= ./mini_utils
UTILS_LIB				:= $(UTILS_DIR)/mini_utils.a

ifndef config
	config := release
endif

ifeq ($(config),debug)
	client_config = debug
	server_config = debug
	utils_config = debug
	libft_config = debug
else ifeq ($(config),release)
	client_config = release
	server_config = release
	utils_config = release
	libft_config = release
else ifeq ($(config),distr)
	client_config = distr
	server_config = distr
	utils_config = distr
	libft_config = distr
else
	$(error "invalid config $(config)")
endif

.PHONY: all clean fclean re $(CLIENT_TARGET) $(SERVER_TARGET)

all: $(NAME)

$(CLIENT_TARGET): $(LIBFT_LIB) $(UTILS_LIB)
	@echo "=== Building $(CLIENT_TARGET) ($(client_config)) ==="
	@${MAKE} -C $(CLIENT_DIR) -f Makefile config=$(client_config) 
	@mv $(CLIENT_DIR)/$(CLIENT_TARGET) .

$(SERVER_TARGET): $(LIBFT_LIB) $(UTILS_LIB)
	@echo "=== Building $(SERVER_TARGET) ($(server_config)) ==="
	@${MAKE} -C $(SERVER_DIR) -f Makefile config=$(server_config) 
	@mv $(SERVER_DIR)/$(SERVER_TARGET) .

$(LIBFT_LIB):
	@echo "=== Building $(LIBFT_LIB) ($(libft_config)) ==="
	@${MAKE} -C $(LIBFT_DIR) -f Makefile config=$(LIBFT_LIB) 

$(UTILS_LIB):
	@echo "=== Building $(UTILS_LIB) ($(client_config)) ==="
	@${MAKE} -C $(UTILS_DIR) -f Makefile config=$(utils_config) 

clean:
	@${MAKE} -C $(CLIENT_DIR) clean
	@${MAKE} -C $(SERVER_DIR) clean
	@${MAKE} -C $(UTILS_DIR) clean
	@${MAKE} -C $(LIBFT_DIR) clean

fclean:
	@${MAKE} -C $(CLIENT_DIR) fclean
	@${MAKE} -C $(SERVER_DIR) fclean
	@${MAKE} -C $(UTILS_DIR) fclean
	@${MAKE} -C $(LIBFT_DIR) fclean

re: fclean all
