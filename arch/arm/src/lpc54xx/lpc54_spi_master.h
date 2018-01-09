/************************************************************************************
 * arch/arm/src/lpc54xx/lpc54_spi_master.h
 *
 *   Copyright (C) 2017 Gregory Nutt. All rights reserved.
 *   Author: Gregory Nutt <gnutt@nuttx.org>
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

#ifndef __ARCH_ARM_SRC_LPC54XX_SPI_MASTER_H
#define __ARCH_ARM_SRC_LPC54XX_SPI_MASTER_H

/************************************************************************************
 * Included Files
 ************************************************************************************/

#include <nuttx/config.h>
#include <nuttx/spi/spi.h>

#ifdef HAVE_SPI_MASTER_DEVICE

/************************************************************************************
 * Pre-processor Definitions
 ************************************************************************************/
/* This header file defines interfaces to common SPI logic.  To use this common SPI
 * logic on your board:
 *
 * 1. Provide logic in lpc54_boardinitialize() to configure SPI chip select pins.
 * 2. Provide the lpc54_spiselect() and lpc54_spistatus() functions in your
 *    board-specific logic.  These functions will perform chip selection
 *    and status operations using GPIOs in the way your board is configured.
 * 3. If CONFIG_SPI_CMDDATA is defined in the NuttX configuration, provide
 *    lpc54_spicmddata() functions in your board-specific logic.  This
 *    function will perform cmd/data selection operations using GPIOs in the
 *    way your board is configured.
 * 4. Your low level board initialization logic should call lpc54_spibus_initialize.
 * 5. The handle returned by lpc54_spibus_initialize() may then be used to bind the
 *    SPI driver to higher level logic (e.g., calling  mmcsd_spislotinitialize(),
 *    for example, will bind the SPI driver to the SPI MMC/SD driver).
 */

/************************************************************************************
 * Public Types
 ************************************************************************************/

/************************************************************************************
 * Public Data
 ************************************************************************************/

#ifndef __ASSEMBLY__

#undef EXTERN
#if defined(__cplusplus)
#define EXTERN extern "C"
extern "C"
{
#else
#define EXTERN extern
#endif

/************************************************************************************
 * Public Functions
 ************************************************************************************/

/****************************************************************************
 * Name: lpc54_spibus_initialize
 *
 * Description:
 *   Initialize the selected SPI port
 *   0 - SPI0
 *   1 - SPI1
 *   ...
 *   9 - SPI9
 *
 * Input Parameter:
 *   port - SPI peripheral number, 0.. 9.
 *
 * Returned Value:
 *   Valid SPI device structure reference on success; a NULL on failure
 *
 ****************************************************************************/

FAR struct spi_dev_s *lpc54_spibus_initialize(int port);

/************************************************************************************
 * Name:  lpc54_spiselect, lpc54_spistatus, and lpc54_spicmddata
 *
 * Description:
 *   These functions must be provided in your board-specific logic.  The
 *   lpc54_spiselect function will perform chip selection and the lpc54_spistatus
 *   will perform status operations using GPIOs in the way your board is configured.
 *
 *   If CONFIG_SPI_CMDDATA is defined in the NuttX configuration, then
 *   lpc54_spicmddata must also be provided.  This functions performs cmd/data
 *   selection operations using GPIOs in the way your board is configured.
 *
 ************************************************************************************/

void  lpc54_spiselect(FAR struct spi_dev_s *dev, uint32_t devid, bool selected);
uint8_t lpc54_spistatus(FAR struct spi_dev_s *dev, uint32_t devid);

#ifdef CONFIG_SPI_CMDDATA
int lpc54_spicmddata(FAR struct spi_dev_s *dev, uint32_t devid, bool cmd);
#endif

/************************************************************************************
 * Name: spi_flush
 *
 * Description:
 *   Flush and discard any words left in the RX fifo.  This can be called from
 *   spiselect after a device is deselected (if you worry about such things).
 *
 * Input Parameters:
 *   dev - Device-specific state data
 *
 * Returned Value:
 *   None
 *
 ************************************************************************************/

void spi_flush(FAR struct spi_dev_s *dev);

/************************************************************************************
 * Name: lpc54_spi/spiregister
 *
 * Description:
 *   If the board supports a card detect callback to inform the SPI-based MMC/SD
 *   driver when an SD card is inserted or removed, then CONFIG_SPI_CALLBACK should
 *   be defined and the following function(s) must must be implemented.  These
 *   functions implements the registercallback method of the SPI interface (see
 *   include/nuttx/spi/spi.h for details)
 *
 * Input Parameters:
 *   dev -      Device-specific state data
 *   callback - The function to call on the media change
 *   arg -      A caller provided value to return with the callback
 *
 * Returned Value:
 *   0 on success; negated errno on failure.
 *
 ************************************************************************************/

#ifdef CONFIG_SPI_CALLBACK
int lpc54_spiregister(FAR struct spi_dev_s *dev, spi_mediachange_t callback, void *arg);
#endif

#undef EXTERN
#if defined(__cplusplus)
}
#endif

#endif /* __ASSEMBLY__ */
#endif /* HAVE_SPI_MASTER_DEVICE */
#endif /* __ARCH_ARM_SRC_LPC54XX_SPI_MASTER_H */
