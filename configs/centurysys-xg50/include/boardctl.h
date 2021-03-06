/************************************************************************************
 * configs/centurysys-xg50/include/boardctl.h
 *
 *   Copyright (C) 2018 Century Systems. All rights reserved.
 *   Author: kikuchi@centurysys.co.jp
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

#ifndef __CONFIGS_CENTURYSYS_XG50_INCLUDE_BOARDCTL_H
#define __CONFIGS_CENTURYSYS_XG50_INCLUDE_BOARDCTL_H

/****************************************************************************
 * Included Files
 ****************************************************************************/

#include <sys/boardctl.h>

/****************************************************************************
 * Pre-processor Definitions
 ****************************************************************************/

#define BIOC_CONFIG_GPIO  (BOARDIOC_USER + 1)
#  ifndef CONFIG_CENTURYSYS_XG50_ADDON_NONE
#define BIOC_ENABLE_B2B   (BOARDIOC_USER + 2)
#define BIOC_DISABLE_B2B  (BOARDIOC_USER + 3)
#define BIOC_RESET_B2B    (BOARDIOC_USER + 4)
#  endif
#define BIOC_GET_LEDSW    (BOARDIOC_USER + 5)
#define BIOC_GET_INITSW   (BOARDIOC_USER + 6)
#define BIOC_SET_LED      (BOARDIOC_USER + 7)

#endif  /* __CONFIGS_CENTURYSYS_XG50_INCLUDE_BOARDCTL_H */
