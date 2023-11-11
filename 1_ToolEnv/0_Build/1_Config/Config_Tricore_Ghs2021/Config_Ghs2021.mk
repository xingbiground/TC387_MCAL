###############################################################################
#                                                                             #
#       Copyright (C) 2023 Infineon Technologies AG. All rights reserved.     #
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

ifeq ($(COMPILER),Ghs2021)

B_GHS_TRICORE_PATH?= $(GREEN_HILLS_2021_1_5_HOME)\comp_202115

B_GHS_TRICORE_CC_OPTIONS= -c99 -cpu=tc1v162 -frigor=accurate -globalcheck=normal -globalcheck_qualifiers \
        --gnu_asm -lnk=-no_append -Mn -Mx -nostartfiles -nostdlib --no_short_enum -Ogeneral -Omax

B_GHS_TRICORE_LD_OPTIONS= $(B_GHS_TRICORE_CC_OPTIONS)

#Include path for library directories. Add each path with following format as shown below.
#Each path prefixed with -L and separated by a space.
#B_GHS_TRICORE_LIB_INC=-L<path>[ -L<path>][..]
B_GHS_TRICORE_LIB_INC= -L"$(B_GHS_TRICORE_PATH)/lib/tri162"

#Libraries to include shall be listed with option -l, with following format.
#B_GHS_TRICORE_LIBS=-l<lib name>[ -l<lib name>][..]
B_GHS_TRICORE_LIBS= -lansi -lstartup -lind_sd -larch -lsys -lwc_s32

endif
