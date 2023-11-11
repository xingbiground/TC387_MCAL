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

ifeq ($(COMPILER),Ghs2018)

B_GHS_TRICORE_PATH?= $(GREEN_HILLS_HOME)\comp_201815

B_GHS_TRICORE_CC_OPTIONS= -cpu=tc1v162 --diag_error 39,549,940,1056,1780,1999 \
        --diag_warning 193,1705,1706,1709,1710,1718,1729,1735,1777,1826,1835,2017 -dual_debug -ffunctions \
        -fno_NaN_cmp_unordered -fsingle -g -gnu99 --gnu_asm -half_precision_type -lnk=-no_append -map -minlib \
        -Mn -Mx -nostartfiles -nostdlib --no_commons -no_float_associativity -no_fused_madd -no_precise_signed_zero \
        --no_short_enum --no_vla -Ogeneral -Oinline_constant_math -Onoexplodejumps -Onoprintfuncs -Onotailrecursion \
        -Onounroll -roxda -sda=none -srec -tricore_ppccompat_abi --unsigned_chars --xref=full

B_GHS_TRICORE_ASM_OPTIONS=

B_GHS_TRICORE_LIB_INC= -L"$(B_GHS_TRICORE_PATH)/lib/tri162_compat"

B_GHS_TRICORE_LIBS= -lansi -lstartup -lind_sd -larch -lsys -lmath_sd -lwc_s32

B_GHS_TRICORE_LD_OPTIONS= $(B_GHS_TRICORE_CC_OPTIONS)

endif
