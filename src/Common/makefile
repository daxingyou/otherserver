#==============================================================
# makefile for common library 
#==============================================================
MODULE = CommFunc   Template  lua5.1 ToLua++  MiniApr uuid 
INCMODULE=CommFunc   Template  lua5.1 ToLua++  uuid 
         

include ../ServerEngine/makefile_lib

all: 
	rm -rf $(LIB_FILE)

	@for dir in $(MODULE);do\
   ( $(MAKE) -C $$dir all ); done
    
	@echo -en "\033[1;36m"
	ranlib  $(LIB_FILE)
	ar -t $(LIB_FILE)
	@echo -en "\033[0m"
	@echo
	@echo -e "\033[1;36m======= Packing Library $(LIB_FILE) Done ============ \033[0m"
	cp $(LIB_FILE) $(PATH_LIB)

clean: 
	rm -rf $(LIB_FILE)
	rm -rf *.h
	for dir in $(MODULE); do\
   ( $(MAKE) -C $$dir clean ); done
	@echo
	@echo -e "\033[1;38m====== Cleaning Target Done ==================== \033[0m"
	rm -rf $(PATH_LIB)
	mkdir $(PATH_LIB)

release: all
	rm -rf $(PATH_INCLUDE)
	mkdir $(PATH_INCLUDE)
	for dir in $(INCMODULE); do\
    ( cp $$dir/*.h*  $(PATH_INCLUDE) ); done
	rm -rf $(PATH_INCLUDE)/MiniApr/
	mkdir $(PATH_INCLUDE)/MiniApr/
	cp MiniApr/Include/* -rf $(PATH_INCLUDE)/MiniApr/
	rm -rf $(PATH_LIB)
	mkdir $(PATH_LIB)
	cp $(LIB_FILE) $(PATH_LIB)
	# cp ../ServreEngine/CommLib.mk $(PATH_ROOT)
	# cp ../ServreEngine/CommInclude.mk $(PATH_ROOT)
	@echo "release COMM done..."
    

rebuild: clean all release

