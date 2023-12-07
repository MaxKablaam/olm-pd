# Olm-pd

Olm-pd is the [Puredata][pd] (Pd) component of the [_Olm_][olm] project.

- [Olm-pd](#olm-pd)
  - [General Information](#general-information)
    - [Related projects](#related-projects)
  - [Audio demo](#audio-demo)
  - [Technologies used](#technologies-used)
  - [Setup](#setup)
    - [Desktop](#desktop)
    - [Getting it on the Daisy Seed](#getting-it-on-the-daisy-seed)
  - [Usage](#usage)
  - [Project status](#project-status)
    - [Room for improvement](#room-for-improvement)
  - [Acknowledgements](#acknowledgements)
  - [Reference Material](#reference-material)
  - [Contact](#contact)
  - [License](#license)

## General Information

This repo is a collection of puredata patches than when compiled through [Plugdata][plugdata] or [pd2dsy][pd2dsy] can be flashed to the [Electro-Smith Daisy Seed][seed] for embedding in a standalone, battery-powered synthesizer/interactive-object. These patches are the basis for sound generation for the [_Olm_][olm] project.

If you don't have a Daisy Seed, the Pd patches can be enjoyed on any desktop computer as well with either Pd or Plugdata. With Plugdata you can host it in any compatible DAW.

The _Olm_ is both an interactive sculpture and a tool for randomly generating ambient soundscapes and music. It is a digital, aleatoric synthesizer housed in a hand-crafted enclosure of plywood, plaster and aluminum.

### Related projects

- [Olm][olm]
- [Olm PCB][olm-pcb]

## Audio demo

To hear how olm-pd sounds (and see the physical version), you can watch this [video](https://vimeo.com/manage/videos/896051761).

## Technologies used

- [Plugdata][plugdata]
- [Puredata][pd]
- [LibDaisy][libdaisy]
- [Electro-Smith][electrosmith] [Daisy Seed][seed]

## Setup

### Desktop

Simply open the `/olm.main-desktop.pd` file in either [Plugdata][plugdata] or [Puredata vanilla][pd]. The `.pd` files were created with a nightly build of Plugdata v0.8.1, but hopefully they will work with any future version. If you are using vanilla Pd, then you must ensure you have the [heavylib][heavylib] library of abstractions.

### Getting it on the Daisy Seed

In order to make use of the interactive controls, you must either somehow get your hands on the [Olm PCB][olm-pcb], or you can make your own interface. If you decide to make your own, it will either need to conform to the `/olm_components.json` file, or you will have to create your own configuration. Info on how to create the configuration file can be found in the [pd2dsy][pd2dsy] project.

To flash the patch to Daisy Seed, you will need to use either [Plugdata][plugdata] or [pd2dsy][pd2dsy]. I mostly relied on Plugdata. It can load the patch straight to the Daisy Seed, or if you like, it can compile your Pd patch into C/C++, which you can then load onto the Daisy Seed using [LibDaisy][libdaisy]. For more info on using these tools, please consult their respective project pages and documentation. The [Daisy][daisy-discord] and [Plugdata][plugdata-discord] Discord channels are also great for getting help. The patch to flash/compile is `/olm.main-seed.pd`. In Plugdata v0.8.1, you must direct it to compile an SRAM program, and use the `/sram_linker_sdram.lds` linker file. This was the workflow with the nightly build that I was using, so it's possible that some things have changed in a more recent version. Consult the documentation and/or the discord.

In order to get the best performance out of my patch, I opted to compile to C/C++ so that I could get some small performance gains with a few tricks:

- Adjusting the block size to 256, from the Plugdata default, which is 48. This is like setting the sample buffer on a sound card. The trade-off is latency vs. CPU usage. Higher block size = less CPU, but more latency. This adjustment is made in the `/export/daisy/source/HeavyDaisy_olm_main_.cpp` file. The file might be named something different, like `HeavyDaisy_[YourProject].cpp` if you compile it yourself from Plugdata. Add the line `hardware.SetAudioBlockSize(256)` to the `main()` function, like this:

    ```cpp
    int main(void)
    {
        hardware.Init(true); // Make sure it goes right under this line
        hardware.SetAudioBlockSize(256);

        // ...
    ```

- Using the optimizer in the makefile. I wasn't able to truly test this, but it didn't seem to hurt.  
Add the line:

    ```makefile
    OPT = -O3
    ```

- Set the message pool to 6. This alleviated some issues I was having with the `[makenote ]` node in my sequencer, causing the seed to crash.  
Do this in the `/export/daisy/source/HvMessagePool.h` file, by adjusting line 25 like this:

    ```cpp
    #define MP_NUM_MESSAGE_LISTS 6
    ```

I have provided the C/C++ files compiled from Plugdata in the `/export/daisy` directory.

## Usage

On the physical version of the _Olm_, you have three non-continuous dials and two momentary buttons at your disposal. Rather than predictably affecting specific sonic parameters, the dials only push the randomization further, negating the ability to shape the sound to your will. When you come across something you find interesting/inspiring/terrifying you may use the buttons for storing and recalling the state of the synthesizer parameters.

To try it in the pd patch, you can open the `/olm.main-desktop.pd` file, and you will have the controls available to you.

![cXDA5w9Xqf](https://github.com/MaxKablaam/olm-pd/assets/55173884/7b962fa0-17e2-4931-83f5-1cccc6082ae6)

## Project status

Project is: *in progress*

### Room for improvement

The project is nearly complete. The final things to polish are:

Room for improvement:

- Refine the randomization so that there are never any fully quiet moments.
- Fine tune the randomization constraints controlled by the "chaos" knob.

## Acknowledgements

This project owes its success to the dedication of Daisy, Plugdata, and Puredata developers and the invaluable support of their communities. Special acknowledgments go to:

- [Wasted Audio](https://wasted.audio/) for the generous help.
- [Mike Moreno](https://mikemorenodsp.github.io/learning/) for the tools and advice.
- [Daisy Seed Discord][daisy-discord]
- [Plugdata Discord][plugdata-discord]
<!-- - Takumi Ogata: That helpful dude on the daisy seed discord, for his help, and tutorials TODO -->

## Reference Material

The following materials were used to aid in the creation and design:

- [Mike Moreno DSP - Basic waverforms in pd vanilla](https://mikemorenodsp.github.io/basic-waveforms/)
- [Mike Moreno DSP - pd-mkmr](https://github.com/MikeMorenoDSP/pd-mkmr)
- [Mike Moreno DSP - LIRA-8](https://github.com/MikeMorenoDSP/LIRA-8)
- [Physical Audio Signal Processing for Virtual Musical Instruments and Audio Effects - Julius O. Smith III](https://ccrma.stanford.edu/~jos/pasp/)
- [The Theory and Technique of Electronic Music - Miller Puckette (2006)](https://msp.ucsd.edu/techniques/latest/book.pdf)
- [DIY Swarmatron (Pure Data & Arduino Tutorial) - Sound Simulator](https://www.youtube.com/watch?v=0H5wQOUrlIY)
- [Real-time Music and Sound with Pure Data - QCGInteractiveMusic](https://youtube.com/playlist?list=PLuxj2jXSuTvvqYcDLJ-poN-JxvqX0wq-m&si=WBfX3bjELYKcLhyd)

## Contact

Created by [Eric Max Kaplin][me]

## License

This project is open source and unless otherwise specified in specific files, available under the [GPL-3 License][license].

[olm]: https://ericmaxkaplin.com/content/projects/olm/
[olm-pcb]: https://github.com/MaxKablaam/olm-pcb
[pd]: https://puredata.info/
[plugdata]: https://plugdata.org/
[plugdata-discord]: https://discord.com/invite/eT2RxdF9Nq
[heavylib]: https://github.com/Wasted-Audio/heavylib
[libdaisy]: https://github.com/electro-smith/libDaisy
[electrosmith]: https://www.electro-smith.com/
[seed]: https://www.electro-smith.com/daisy/daisy
[daisy-discord]: https://discord.gg/ByHBnMtQTR
[pd2dsy]: https://github.com/electro-smith/pd2dsy
[license]: https://www.gnu.org/licenses/gpl-3.0.en.html
[me]: https://ericmaxkaplin.com/
