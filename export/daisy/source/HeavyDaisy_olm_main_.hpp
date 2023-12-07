/*
 * MIT License
 * 
 * Copyright (c) 2021 Electrosmith
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * 
 */

#ifndef __JSON2DAISY_OLM_COMPONENTS_H__
#define __JSON2DAISY_OLM_COMPONENTS_H__

#include "daisy_seed.h"
#include "dev/codec_ak4556.h"


#define ANALOG_COUNT 4

namespace json2daisy {



struct DaisyOlm_components {

  /** Initializes the board according to the JSON board description
   *  \param boost boosts the clock speed from 400 to 480 MHz
   */
  void Init(bool boost=true) 
  {
    som.Configure();
    som.Init(boost);
 

    // Switches
    sw1.Init(som.GetPin(27), som.AudioCallbackRate(), daisy::Switch::TYPE_MOMENTARY, daisy::Switch::POLARITY_INVERTED, daisy::Switch::PULL_UP);
    sw2.Init(som.GetPin(28), som.AudioCallbackRate(), daisy::Switch::TYPE_MOMENTARY, daisy::Switch::POLARITY_INVERTED, daisy::Switch::PULL_UP);
    stereoswitch.Init(som.GetPin(2), som.AudioCallbackRate(), daisy::Switch::TYPE_MOMENTARY, daisy::Switch::POLARITY_INVERTED, daisy::Switch::PULL_UP);
    headphoneswitch.Init(som.GetPin(1), som.AudioCallbackRate(), daisy::Switch::TYPE_MOMENTARY, daisy::Switch::POLARITY_INVERTED, daisy::Switch::PULL_UP); 
 

    // Gate ins
    dsy_gpio_pin bat_pin = som.GetPin(3);
    bat.Init(&bat_pin, true); 
 

    // Single channel ADC initialization
    cfg[0].InitSingle(som.GetPin(15));
    cfg[1].InitSingle(som.GetPin(16));
    cfg[2].InitSingle(som.GetPin(19));
    cfg[3].InitSingle(som.GetPin(20)); 
    som.adc.Init(cfg, ANALOG_COUNT);
 

    // AnalogControl objects
    knob1.Init(som.adc.GetPtr(0), som.AudioCallbackRate(), false, false);
    knob2.Init(som.adc.GetPtr(1), som.AudioCallbackRate(), false, false);
    knob3.Init(som.adc.GetPtr(2), som.AudioCallbackRate(), false, false);
    knob4.Init(som.adc.GetPtr(3), som.AudioCallbackRate(), false, false); 

    // RBG LEDs 
    led.Init(som.GetPin(11), som.GetPin(12), som.GetPin(13), true);
    led.Set(0.0f, 0.0f, 0.0f); 
 

    // Gate outs
    headphonegate.pin  = som.GetPin(14);
    headphonegate.mode = DSY_GPIO_MODE_OUTPUT_PP;
    headphonegate.pull = DSY_GPIO_NOPULL;
    dsy_gpio_init(&headphonegate); 

    som.adc.Start();
  }

  /** Handles all the controls processing that needs to occur at the block rate
   * 
   */
  void ProcessAllControls() 
  {
 
    knob1.Process();
    knob2.Process();
    knob3.Process();
    knob4.Process();
    sw1.Debounce();
    sw2.Debounce();
    stereoswitch.Debounce();
    headphoneswitch.Debounce(); 
  }

  /** Handles all the maintenance processing. This should be run last within the audio callback.
   * 
   */
  void PostProcess()
  {
    led.Update();
  }

  /** Handles processing that shouldn't occur in the audio block, such as blocking transfers
   * 
   */
  void LoopProcess()
  {
    
  }

  /** Sets the audio sample rate
   *  \param sample_rate the new sample rate in Hz
   */
  void SetAudioSampleRate(size_t sample_rate) 
  {
    daisy::SaiHandle::Config::SampleRate enum_rate;
    if (sample_rate >= 96000)
      enum_rate = daisy::SaiHandle::Config::SampleRate::SAI_96KHZ;
    else if (sample_rate >= 48000)
      enum_rate = daisy::SaiHandle::Config::SampleRate::SAI_48KHZ;
    else if (sample_rate >= 32000)
      enum_rate = daisy::SaiHandle::Config::SampleRate::SAI_32KHZ;
    else if (sample_rate >= 16000)
      enum_rate = daisy::SaiHandle::Config::SampleRate::SAI_16KHZ;
    else
      enum_rate = daisy::SaiHandle::Config::SampleRate::SAI_8KHZ;
    som.SetAudioSampleRate(enum_rate);
    knob1.SetSampleRate(som.AudioCallbackRate());
    knob2.SetSampleRate(som.AudioCallbackRate());
    knob3.SetSampleRate(som.AudioCallbackRate());
    knob4.SetSampleRate(som.AudioCallbackRate());
    sw1.SetUpdateRate(som.AudioCallbackRate());
    sw2.SetUpdateRate(som.AudioCallbackRate());
    stereoswitch.SetUpdateRate(som.AudioCallbackRate());
    headphoneswitch.SetUpdateRate(som.AudioCallbackRate());
  }

  /** Sets the audio block size
   *  \param block_size the new block size in words
   */
  inline void SetAudioBlockSize(size_t block_size) 
  {
    som.SetAudioBlockSize(block_size);
  }

  /** Starts up the audio callback process with the given callback
   * 
   */
  inline void StartAudio(daisy::AudioHandle::AudioCallback cb)
  {
    som.StartAudio(cb);
  }

  /** This is the board's "System On Module" */
  daisy::DaisySeed som;
  daisy::AdcChannelConfig cfg[ANALOG_COUNT];

  // I/O Components
  daisy::AnalogControl knob1;
  daisy::AnalogControl knob2;
  daisy::AnalogControl knob3;
  daisy::AnalogControl knob4;
  daisy::GateIn bat;
  dsy_gpio headphonegate;
  daisy::RgbLed led;
  daisy::Switch sw1;
  daisy::Switch sw2;
  daisy::Switch stereoswitch;
  daisy::Switch headphoneswitch;
  
  

};

} // namspace json2daisy

#endif // __JSON2DAISY_OLM_COMPONENTS_H__