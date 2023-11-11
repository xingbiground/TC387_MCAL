################################################################################
# Tresos.mk
################################################################################
TRESOS_BIN_PATH?=$(TRESOS_ROOT)/bin
TRESOS_CMD=$(TRESOS_BIN_PATH)/tresos_cmd.bat
SUITE_CFG_DIR?=$(SUITE_ROOT)/$(SUITE_NAME)/Cfg
TRESOS_OUT_DIR?=$(SUITE_ROOT)/CfgMcal
TRESOS_XDM_FILES=$(TRESOS_WORKSPACE)/$(TRESOS_PROJECT_NAME)/config/*.xdm
TRESOS_EPC_FILES=$(SUITE_CFG_DIR)/$(SUITE_CFG)

ifeq ($(BUILDENV),DEMOAPP)
BUILD_BASE_PATH=.
DEMOAPP_CONFIG_PATH=1_ToolEnv/2_Tresos/AS422/DemoApp/config
TRESOS_ROOT?=C:/sofit/aurix2g_sw_mcal/tresos/26.2.0/tresos/tresos
TRESOS_PROJECT_NAME?=DemoApp
TRESOS_BIN_PATH?=$(TRESOS_ROOT)/bin

TRESOS_GEN_BAT=$(TRESOS_BIN_PATH)/tresos_cmd.bat
TRESOS_WORKSPACE=1_ToolEnv/2_Tresos/AS422
TRESOS_OUT_DIR=0_Src/AppSw/Tricore/CfgMcal

TRESOS_GEN_COMMAND=$(TRESOS_GEN_BAT) -data $(TRESOS_WORKSPACE) generate -o $(TRESOS_OUT_DIR) $(TRESOS_PROJECT_NAME)
endif

EPC_QUALIFIED_NAME?=$(SUITE_CFG)

TRESOS_ARG_XDM=-data $(TRESOS_WORKSPACE) generate -o $(TRESOS_OUT_DIR) $(TRESOS_PROJECT_NAME)
TRESOS_ARG_EPC=-Dtarget=$(DEVICE) -Dderivate=$(DERIVATE) legacy generate $(EPC_QUALIFIED_NAME) -c $(SUITE_CFG_DIR) -o $(TRESOS_OUT_DIR)

#TRESOS_OUT_DIR:=$(subst \,/,$(realpath $(TRESOS_OUT_DIR)))
#TRESOS_OUT_DIR:=$(subst /c/,c:/,$(TRESOS_OUT_DIR))

.phony: demoapp_build appcfg rename clean out_clean build_fr_node
demoapp_build: clean out_clean
	@$(TRESOS_GEN_COMMAND)


appcfg: $(TRESOS_OUT_DIR)/status.txt

.ONESHELL:
# Generate source files by Tresos configuration

TRESOS_PLUGIN_LINK=$(subst \,/,$(TRESOS_ROOT)/links)

$(TRESOS_OUT_DIR)/status.txt:
	@echo $(SRC_FOLDERS)
	@echo Generating Tresos Configurations ...
	@if [[ ! -d "$(@D)" ]]; then	 					\
		echo Creating $(@D);							\
		mkdir -p $(@D);									\
	fi	
	@-rm -rf $(@D)/*.*
	
	@if [[ ! -d "$(TRESOS_PLUGIN_LINK)" ]]; then	 	\
		echo Creating $(TRESOS_PLUGIN_LINK);			\
		mkdir $(TRESOS_PLUGIN_LINK);					\
	fi	
	@-rm -f $(TRESOS_PLUGIN_LINK)/*.link
	
	@python $(ASE_LIB)/TresosLib.py  "$(SRC_FOLDERS)"  "$(TRESOS_ROOT)" "PluginsTresos"
	
ifeq ($(TRESOS_CFG_MODE),XDM)
	@$(TRESOS_CMD) $(subst /,//,$(TRESOS_ARG_XDM))
else
	@echo ... from EPC.
	@$(TRESOS_CMD) $(subst /,//,$(TRESOS_ARG_EPC))
endif
	@echo Tresos Generated the Configurations! > $(TRESOS_OUT_DIR)/status.txt

# Remove Geenrated Folders 2_Out and 9_Make
out_clean:
	@-rm -rf 2_Out/Tricore_$(COMPILER)/*
	@-rm -rf 2_Out/Tricore_$(COMPILER)
	@-rm -rf 1_ToolEnv/0_Build/9_Make/*
	@-rm -rf 1_ToolEnv/0_Build/9_Make
# Remove generated files by Tresos and all plugin links
clean:
	@-rm -f $(TRESOS_PLUGIN_LINK)/*.link
	@-rm -f $(TRESOS_PLUGIN_LINK)
	@-rm -rf 0_Src/AppSw/Tricore/CfgMcal
	@-rm -rf 0_Src/AppSw/Tricore/CfgMcal_FR
   
build_fr_node:
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*.elf $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp_Node0.elf
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*.hex $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp_Node0.hex
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*.map $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp_Node0.map
ifeq ($(COMPILER),Tasking)
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*.mdf $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp_Node0.mdf
endif
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Fr.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Fr_Node0.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Fr_Node1.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Fr.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/FrIf.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/FrIf_Node0.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/FrIf_Node1.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/FrIf.xdm	
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Hssl.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Hssl_Master.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Hssl_Slave.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Hssl.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Dma.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Dma_Master.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Dma_Slave.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Dma.xdm
	
	@echo Copying file for FR2
	@cp ../../../Tools/Compiler_Configs_AS422_225MR/TC38A_FR2_Config_$(COMPILER).xml 1_ToolEnv/0_Build/1_Config/Config.xml
	@$(eval TRESOS_OUT_DIR=0_Src/AppSw/Tricore/CfgMcal_FR)
ifeq ($(TRESOS_BUILD),YES)	
	@$(TRESOS_GEN_COMMAND)
endif	
	@$(MAKE) -B DECLARED_DEMOAPP_MACROS=-DDEMO_APP_NODE_1 DECLARED_DEMOAPP_MACROS+=-DAURIX2G_MCAL_DEMOAPP=1 build 
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Fr.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Fr_Node1.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Fr_Node0.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Fr.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/FrIf.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/FrIf_Node1.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/FrIf_Node0.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/FrIf.xdm	
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Hssl.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Hssl_Slave.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Hssl_Master.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Hssl.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Dma.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Dma_Slave.xdm
	-mv $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Dma_Master.xdm $(BUILD_BASE_PATH)/$(DEMOAPP_CONFIG_PATH)/Dma.xdm	
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*_tc.elf $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp_Node1.elf
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*_tc.hex $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp_Node1.hex
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*_tc.map $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp_Node1.map
ifeq ($(COMPILER),Tasking)
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*_tc.mdf $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp_Node1.mdf
endif

rename:
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*.elf $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp.elf
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*.hex $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp.hex
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*.map $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp.map
ifeq ($(COMPILER),Tasking)
	-mv $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/*.mdf $(BUILD_BASE_PATH)/2_Out/Tricore_$(COMPILER)/DemoApp.mdf
endif
