/************************************************************************************
 * configs/olimexino-stm32/src/stm32_boot.c
 *
 *   Copyright (C) 2015 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
 *           David Sidrane <david_s5@nscdg.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name NuttX nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ************************************************************************************/

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <debug.h>
#include <arch/board/board.h>

#include <nuttx/board.h>
#include "olimexino-stm32.h"

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/

/************************************************************************************
 * Private Functions
 ************************************************************************************/

/************************************************************************************
 * Name: vbus_handler
 ************************************************************************************/

#if defined(CONFIG_USBDEV)
static int vbus_handler(int irq, FAR void *context, FAR void *arg)
{
  return OK;
}
#endif

/************************************************************************************
 * Public Functions
 ************************************************************************************/

/************************************************************************************
 * Name: stm32_boardinitialize
 *
 * Description:
 *   All STM32 architectures must provide the following entry point.  This entry point
 *   is called early in the initialization -- after all memory has been configured
 *   and mapped but before any devices have been initialized.
 *
 ************************************************************************************/

void stm32_boardinitialize(void)
{
#ifdef CONFIG_ARCH_LEDS
  /* Configure on-board LEDs if LED support has been selected. */

  stm32_led_initialize();
#endif

#ifdef CONFIG_ARCH_BUTTONS
  /* Configure on-board buttons. */

  board_button_initialize();
#endif

#if defined(CONFIG_STM32_SPI1) || defined(CONFIG_STM32_SPI2) || \
    defined(CONFIG_STM32_SPI3)
  /* Configure SPI chip selects if 1) SP2 is not disabled, and 2) the weak function
   * stm32_spidev_initialize() has been brought into the link.
   */

  if (stm32_spidev_initialize)
    {
      stm32_spidev_initialize();
    }
#endif

#if defined(CONFIG_USBDEV) && defined(CONFIG_STM32_USB)
  /* Initialize USB is 1) USBDEV is selected, 2) the USB controller is not
   * disabled, and 3) the weak function stm32_usbinitialize() has been brought
   * into the build.
   */

  stm32_usbinitialize();
#endif
}

/****************************************************************************
 * Name: board_late_initialize
 *
 * Description:
 *   If CONFIG_BOARD_LATE_INITIALIZE is selected, then an additional
 *   initialization call will be performed in the boot-up sequence to a
 *   function called board_late_initialize().  board_late_initialize() will be
 *   called immediately after up_initialize() is called and just before the
 *   initial application is started.  This additional initialization phase
 *   may be used, for example, to initialize board-specific device drivers.
 *
 ****************************************************************************/

#ifdef CONFIG_BOARD_LATE_INITIALIZE
void board_late_initialize(void)
{
#if defined(CONFIG_NSH_LIBRARY) && !defined(CONFIG_LIB_BOARDCTL)
  /* Perform NSH initialization here instead of from the NSH.  This
   * alternative NSH initialization is necessary when NSH is ran in user-
   * space but the initialization function must run in kernel space.
   */

  board_app_initialize(0);
#endif

#if defined(CONFIG_USBDEV)
  stm32_usb_set_pwr_callback(vbus_handler);
#endif
}
#endif
