# Runge-Kutta-Simulation
Runge Kutta 4(5) order simulation suite for Apple II in Aztec C

*  This work is based on 1999-2000 Thesis work of Greco Riccardo coded in ANSI C for x86 and DSP processor.
It implement an Runge Kutta 4(5)^ order integration numerical method of differential equations set
by use of double precision floating point operation in Aztec C65 language.
It allow to simulate different mathematical models such as:
* Resistance Capacitor electrical circuit,
* Direct Current electric motor,
* Alternating Current three phase induction motor.


# Snapshots

![alt tag](https://cloud.githubusercontent.com/assets/10941944/6314894/71717efe-b9f0-11e4-8552-a8fe283bb92a.png)

![alt tag](https://cloud.githubusercontent.com/assets/10941944/6314896/7623330c-b9f0-11e4-9702-c7f39740751e.png)

![alt tag](https://cloud.githubusercontent.com/assets/10941944/6314897/7a2587f2-b9f0-11e4-85cf-aa073b315c51.png)

![alt tag](https://cloud.githubusercontent.com/assets/10941944/6314898/7d1d67f4-b9f0-11e4-9f37-fb7fba42e4cb.png)

## Build Instructions

### For Building from Source

**Prerequisites:**
- Windows with DOSBox support (or Windows XP/7)
- Apple II emulator (AppleWin recommended)
- ProDOS disk utility (CiderPress recommended)

**Quick Build:**
1. Copy `AppleX/` folder to `C:\AppleX\`
2. Double-click `Aztec Apple C6502 DOSBox Prompt.lnk` (for modern Windows) 
3. Navigate to project directory: `cd [project-path]`
4. Build: `make` (creates RCRK.SYS and *.OVR files)
5. Use CiderPress or similar tool to copy files to ProDOS disk image
6. Test: Load `RKSIM.po` in Apple II emulator

**For complete setup details, read:**
- `AppleX/ReadMe.txt` - Installation and environment setup
- `AppleX/ReadFirst.txt` - AppleX features and documentation
- `AppleX/XBox.txt` - DOSBox configuration

### For Immediate Use
Simply load `RKSIM.po` in an Apple II emulator - no build required.

---

**Thanks to Bill Buckels for his invaluable support:**
* Aztec C compilers http://www.aztecmuseum.ca/compilers.htm
