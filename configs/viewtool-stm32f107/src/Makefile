############################################################################
# configs/viewtool-stm32f107/src/Makefile
#
#   Copyright (C) 2013, 2017-2018 Gregory Nutt. All rights reserved.
#   Author: Gregory Nutt <gnutt@nuttx.org>
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
# 3. Neither the name NuttX nor the names of its contributors may be
#    used to endorse or promote products derived from this software
#    without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
# OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
# AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
############################################################################

-include $(TOPDIR)/Make.defs

ASRCS =
CSRCS = stm32_boot.c stm32_bringup.c stm32_leds.c stm32_spi.c

ifeq ($(CONFIG_CAN),y)
CSRCS += stm32_can.c
endif

ifeq ($(CONFIG_MMCSD),y)
CSRCS += stm32_mmcsd.c
endif

ifeq ($(CONFIG_STM32_OTGFS),y) # F107
CSRCS += stm32_usbdev.c
else
ifeq ($(CONFIG_STM32_USB),y) # F103
CSRCS += stm32_usbdev.c
endif
endif

ifeq ($(CONFIG_SENSORS_MPL115A),y)
CSRCS += stm32_mpl115a.c
endif

ifeq ($(CONFIG_INPUT_ADS7843E),y) # F103
CSRCS += stm32_ads7843e.c
endif

ifeq ($(CONFIG_LCD_SSD1289),y) # F103
CSRCS += stm32_ssd1289.c
endif

ifeq ($(CONFIG_LIB_BOARDCTL),y)
CSRCS += stm32_appinit.c
endif

ifeq ($(CONFIG_USBMSC),y)
CSRCS += stm32_usbmsc.c
endif

ifeq ($(CONFIG_ARCH_BUTTONS),y)
CSRCS += stm32_buttons.c
endif

ifeq ($(CONFIG_VIEWTOOL_HIGHPRI),y)
CSRCS += stm32_highpri.c
endif

ifeq ($(CONFIG_VIEWTOOL_FT80X_SPI1),y)
CSRCS += stm32_ft80x.c
else ifeq ($(CONFIG_VIEWTOOL_FT80X_SPI2),y)
CSRCS += stm32_ft80x.c
endif

ifeq ($(CONFIG_VIEWTOOL_MAX3421E_SPI1),y)
CSRCS += stm32_max3421e.c
else ifeq ($(CONFIG_VIEWTOOL_MAX3421E_SPI2),y)
CSRCS += stm32_max3421e.c
endif

include $(TOPDIR)/configs/Board.mk
