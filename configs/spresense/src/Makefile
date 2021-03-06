############################################################################
# configs/spresense/src/Makefile
#
#   Copyright 2018 Sony Semiconductor Solutions Corporation
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

DEPPATH = --dep-path .

ASRCS =
CSRCS =

CSRCS += cxd56_main.c
CSRCS += cxd56_boot.c
CSRCS += cxd56_clock.c
CSRCS += cxd56_bringup.c

ifeq ($(CONFIG_LIB_BOARDCTL),y)
CSRCS += cxd56_appinit.c
CSRCS += cxd56_power.c
endif

ifeq ($(CONFIG_BOARDCTL_IOCTL),y)
CSRCS += cxd56_ioctl.c
endif

ifeq ($(CONFIG_BOARDCTL_UNIQUEID),y)
CSRCS += cxd56_uid.c
endif

ifeq ($(CONFIG_ARCH_FPU),y)
CSRCS += cxd56_ostest.c
endif

ifeq ($(CONFIG_ARCH_LEDS),y)
CSRCS += cxd56_leds.c
else
ifeq ($(CONFIG_USERLED),y)
CSRCS += cxd56_userleds.c
endif
endif

ifeq ($(CONFIG_ARCH_BUTTONS),y)
CSRCS += cxd56_buttons.c
endif

ifeq ($(CONFIG_CXD56_GPIO_IRQ),y)
CSRCS += cxd56_gpioif.c
endif

ifeq ($(CONFIG_CXD56_PWM),y)
CSRCS += cxd56_pwm.c
endif

ifeq ($(CONFIG_CXD56_SFC),y)
CSRCS += cxd56_flash.c
endif

ifeq ($(CONFIG_SPI),y)
CSRCS += cxd56_spi.c
endif

ifeq ($(CONFIG_CXD56_SDIO),y)
CSRCS += cxd56_sdcard.c
endif

ifeq ($(CONFIG_CXD56_GAUGE),y)
CSRCS += cxd56_gauge.c
endif

ifeq ($(CONFIG_CXD56_CHARGER),y)
CSRCS += cxd56_charger.c
endif

ifeq ($(CONFIG_USBMSC),y)
CSRCS += cxd56_usbmsc.c
endif

ifeq ($(CONFIG_USBDEV_COMPOSITE),y)
CSRCS += cxd56_composite.c
endif

ifeq ($(CONFIG_NETDEVICES),y)
CSRCS += cxd56_netinit.c
endif

ifeq ($(CONFIG_WL_GS2200M),y)
CSRCS += cxd56_gs2200m.c
endif

ifeq ($(CONFIG_SENSORS_BMI160_I2C),y)
CSRCS += cxd56_bmi160_i2c.c
endif

ifeq ($(CONFIG_CXD56_I2C_DRIVER),y)
CSRCS += cxd56_i2cdev.c
endif

ifeq ($(CONFIG_LCD_LPM013M091A),y)
CSRCS += cxd56_lpm013m091a.c
endif

ifeq ($(CONFIG_LCD_ILI9340),y)
CSRCS += cxd56_ili9340.c
endif

include $(TOPDIR)/configs/Board.mk
