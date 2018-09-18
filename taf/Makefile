
TOPDIR	:= .

Project_PATH := $(realpath names ${TOPDIR}/..)

include ${TOPDIR}/make.rules



# PLATFORM := $(shell uname -m)

# ifeq ($(PLATFORM),x86_64)
# 	lib = lib64 lib32
# else
# 	lib = lib32
# endif
lib = lib64

DIRS            = src $(lib) 
DIRS_CLEAN      = src bin test $(lib) script
DIRS_INSTALL    = conf bin include doc $(lib)

default:
	@echo "make libonly: only make libs, libutil.a libtaf.a libhessian.a libparse.a"
	@echo "make all: make all the libs and taf exe, such as tafregistry, tafnode, tafpatch,..."
	@echo "make clean: clean the temp files"
	@echo "make cleanall: clean all the temp files and .d .log files"
	@echo "make install: install to the "${INSTALL_PATH}
	@echo "make uninstall: uninstall taf"

libonly:
	@for dir in $(DIRS); do make -C $$dir libonly; echo; done

all:
	@for dir in $(DIRS); do make -C $$dir; echo; done

clean:
	@for dir in $(DIRS_CLEAN); do make -C $$dir clean; echo; done

cleanall:
	@for dir in $(DIRS_CLEAN); do make -C $$dir cleanall; echo; done

install:
	if [ ! -d ${INSTALL_PATH} ]; then mkdir -p ${INSTALL_PATH}; fi
	if [ ! -d ${INSTALL_PATH}/include ]; then mkdir -p ${INSTALL_PATH}/include/util; fi
	if [ ! -d ${INSTALL_PATH}/bin ]; then mkdir -p ${INSTALL_PATH}/bin; fi
	if [ ! -d ${INSTALL_PATH}/conf ]; then mkdir -p ${INSTALL_PATH}/conf; fi
	if [ ! -d ${INSTALL_PATH}/doc ]; then mkdir -p ${INSTALL_PATH}/doc; fi
	# if [ ! -d ${INSTALL_PATH}/lib32 ]; then ln -sfT ${TOPDIR}/lib32 ${INSTALL_PATH}/lib32; fi
	# if [ ! -d ${INSTALL_PATH}/lib64 ]; then ln -sfT ${TOPDIR}/lib64 ${INSTALL_PATH}/lib64; fi
	if [ -d ${INSTALL_PATH}/lib32 ]; then rm -r ${INSTALL_PATH}/lib32; fi
	ln -sfT ${Project_PATH}/taf/lib32 ${INSTALL_PATH}/lib32
	if [ -d ${INSTALL_PATH}/lib64 ]; then rm -r ${INSTALL_PATH}/lib64; fi
	ln -sfT ${Project_PATH}/taf/lib64 ${INSTALL_PATH}/lib64
	# if [ ! -d ${INSTALL_PATH}/lib32 ]; then mkdir -p ${INSTALL_PATH}/lib32; fi
	# if [ ! -d ${INSTALL_PATH}/lib64 ] && [ "$(PLATFORM)" == "x86_64"  ]; then mkdir -p ${INSTALL_PATH}/lib64; fi; 
	# if [ "$(PLATFORM)" == "x86_64" ]; then ln -sfT ${INSTALL_PATH}/lib64 ${INSTALL_PATH}/lib; fi
	# if [ "$(PLATFORM)" != "x86_64" ]; then ln -sfT ${INSTALL_PATH}/lib32 ${INSTALL_PATH}/lib; fi
	@for dir in $(DIRS_INSTALL); do make -C $$dir install; echo; done
	@echo 'TAF_PATH    :=$(realpath names ${CURDIR}/..)/tool/taf/taf'-$(TAF_VERSION) > makefile.taf.tmp
	@echo 'Project_PATH    :=${Project_PATH}' >> makefile.taf.tmp
	@cat makefile.taf >> makefile.taf.tmp
	cp -rf makefile.taf.tmp ${INSTALL_PATH}/makefile.taf
	cp -rf make.rules.lp64 ${INSTALL_PATH}/
	@echo 'Project_PATH    :=${Project_PATH}' > taf.mk.tmp
	@cat taf.mk >> taf.mk.tmp
	cp -rf taf.mk.tmp ${INSTALL_PATH}/taf.mk
	cp -rf script/create_taf_server.sh ${INSTALL_PATH}/
	cp -rf script/demo ${INSTALL_PATH}/
	# if [ ! -d ${INSTALL_PATH}/taf_server_java ]; then mkdir -p ${INSTALL_PATH}/taf_server_java; fi
	@for dir in $(DIRS_INSTALL); do make -C $$dir install; echo; done
	# cp -rf java/tafservercreate/* ${INSTALL_PATH}/taf_server_java/
	ln -sfT  ${INSTALL_PATH} ${LINK_PATH}
	if [  -d ${Project_PATH}/src ]; then cp -rf script/release ${Project_PATH}/src; fi
	if [  -d ${Project_PATH}/src/release ]; then ${Project_PATH}/src/release/clean_obj.sh; fi
	if [  -d ${Project_PATH}/src/release ]; then ${Project_PATH}/src/release/release_all.sh; fi

uninstall:
	rm -rf ${INSTALL_PATH}
	@for dir in $(DIRS_INSTALL); do make -C $$dir uninstall; echo; done


