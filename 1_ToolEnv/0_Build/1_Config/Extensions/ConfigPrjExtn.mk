###############################################################################
#                                                                             #
#        Copyright © 2016 Infineon Technologies AG. All rights reserved.      #
#                                                                             #
#                                                                             #
#                              IMPORTANT NOTICE                               #
#                                                                             #
#                                                                             #
# Infineon Technologies AG (Infineon) is supplying this file for use          #
# exclusively with Infineon’s microcontroller products. This file can be      #
# freely distributed within development tools that are supporting such        #
# microcontroller products.                                                   #
#                                                                             #
# THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED #
# OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF          #
# MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.#
# INFINEON SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,#
# OR CONSEQUENTIAL DAMAGES, FOR	ANY REASON WHATSOEVER.                        #
#                                                                             #
###############################################################################
TRESOS_BUILD?=YES

ifeq ($(BUILDENV),DEMOAPP)
PRE_BUILD_TARGET+=check
ifeq ($(WITHOUT_TRESOS_WITHOUT_FR),0)
ifeq ($(TRESOS_BUILD),YES)
PRE_BUILD_TARGET+=demoapp_link
endif
endif
endif
ifeq ($(BUILDENV),VAL)
PRE_BUILD_TARGET+=val_link
endif
ifeq ($(TRESOS_BUILD),YES)
ifeq ($(WITHOUT_TRESOS_WITHOUT_FR),0)
CLEAN_TARGETS+=tresosClean
endif
endif

ifeq ($(BUILDENV),DEMOAPP)
ifeq ($(WITHOUT_TRESOS_WITHOUT_FR),0)
POST_BUILD_TARGET+=post_build_fr_step
endif
endif

.phony: val_link demoapp_link tresosClean post_build_fr_step
val_link::
	@$(MAKE) -f 1_ToolEnv/0_Build/1_Config/Extensions/Tresos.mk appcfg

demoapp_link:
	@$(MAKE) -f 1_ToolEnv/0_Build/1_Config/Extensions/Tresos.mk demoapp_build

tresosClean::
	@$(MAKE) -f 1_ToolEnv/0_Build/1_Config/Extensions/Tresos.mk clean
post_build_fr_step:
	@$(MAKE) -f 1_ToolEnv/0_Build/1_Config/Extensions/Tresos.mk rename
	@$(MAKE) -f 1_ToolEnv/0_Build/1_Config/Extensions/Tresos.mk build_fr_node

check::
ifneq ($(wildcard 2_Out/Tricore_$(COMPILER)/*.elf),)
	@echo $(COMPILER) is already compiled, if needed will do the incremental build!
else 
	@echo Compiling with Compiler $(COMPILER)!
	@$(MAKE) -f 1_ToolEnv/0_Build/1_Config/Extensions/Tresos.mk out_clean
endif
