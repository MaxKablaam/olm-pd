/**
 * Copyright (c) 2023 Enzien Audio, Ltd.
 * 
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions, and the following disclaimer.
 * 
 * 2. Redistributions in binary form must reproduce the phrase "powered by heavy",
 *    the heavy logo, and a hyperlink to https://enzienaudio.com, all in a visible
 *    form.
 * 
 *   2.1 If the Application is distributed in a store system (for example,
 *       the Apple "App Store" or "Google Play"), the phrase "powered by heavy"
 *       shall be included in the app description or the copyright text as well as
 *       the in the app itself. The heavy logo will shall be visible in the app
 *       itself as well.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */

#ifndef _HEAVY_OLM_MAIN__H_
#define _HEAVY_OLM_MAIN__H_

#include "HvHeavy.h"

#ifdef __cplusplus
extern "C" {
#endif

#if HV_APPLE
#pragma mark - Heavy Context
#endif

typedef enum {
  HV_OLM_MAIN__PARAM_IN_BAT = 0x9DFAFEDD, // bat
  HV_OLM_MAIN__PARAM_IN_HEADPHONESWITCH_PRESS = 0xA86B827B, // headphoneswitch_press
  HV_OLM_MAIN__PARAM_IN_KNOB1 = 0x3A6EC41A, // knob1
  HV_OLM_MAIN__PARAM_IN_KNOB2 = 0x17356E1C, // knob2
  HV_OLM_MAIN__PARAM_IN_KNOB3 = 0xA28F86ED, // knob3
  HV_OLM_MAIN__PARAM_IN_KNOB4 = 0x569E2BA8, // knob4
  HV_OLM_MAIN__PARAM_IN_STEREOSWITCH_PRESS = 0x7771A90D, // stereoswitch_press
  HV_OLM_MAIN__PARAM_IN_SW1 = 0xC360BB65, // sw1
  HV_OLM_MAIN__PARAM_IN_SW2 = 0xBF5DA8B6, // sw2
} Hv_olm_main__ParameterIn;

typedef enum {
  HV_OLM_MAIN__PARAM_OUT_HEADPHONEGATE = 0xCB2E0352, // headphonegate
  HV_OLM_MAIN__PARAM_OUT_LED_GREEN = 0x7BCDAA14, // led_green
  HV_OLM_MAIN__PARAM_OUT_LED_RED = 0x284C40D6, // led_red
} Hv_olm_main__ParameterOut;


/**
 * Creates a new patch instance.
 * Sample rate should be positive and in Hertz, e.g. 44100.0.
 */
HeavyContextInterface *hv_olm_main__new(double sampleRate);

/**
 * Creates a new patch instance.
 * @param sampleRate  Sample rate should be positive (> 0) and in Hertz, e.g. 48000.0.
 * @param poolKb  Pool size is in kilobytes, and determines the maximum amount of memory
 *   allocated to messages at any time. By default this is 10 KB.
 * @param inQueueKb  The size of the input message queue in kilobytes. It determines the
 *   amount of memory dedicated to holding scheduled messages between calls to
 *   process(). Default is 2 KB.
 * @param outQueueKb  The size of the output message queue in kilobytes. It determines the
 *   amount of memory dedicated to holding scheduled messages to the default sendHook.
 *   See getNextSentMessage() for info on accessing these messages. Default is 0 KB.
 */
HeavyContextInterface *hv_olm_main__new_with_options(double sampleRate, int poolKb, int inQueueKb, int outQueueKb);

/**
 * Free the patch instance.
 */
void hv_olm_main__free(HeavyContextInterface *instance);


#ifdef __cplusplus
} // extern "C"
#endif

#endif // _HEAVY_OLM_MAIN__H_
