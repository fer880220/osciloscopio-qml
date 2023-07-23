# QML Oscilloscope

![Oscilloscope](oscilloscopePC.JPG)

This project is aimed at developing a homebrew single-channel oscilloscope capable of measuring signals with frequencies up to 100 KHz within a range of 0 to 3.3V.

## Frameworks

- Qt 5.8: Provides the graphical user interface for PC.
- Thonny: Facilitates signal capture and transmission from the Raspberry Pi Pico to the PC.

## Compatibility

The current version of the oscilloscope is compatible only with the Windows operating system.

## Features

- Single-channel oscilloscope for measuring electronic signals.
- User-friendly graphical interface developed using Qt.
- Captures signals from the Raspberry Pi Pico.
- Supports frequencies of up to 100 KHz.
- Measurement range from 0 to 3.3V.

## Installation

To install and run the oscilloscope on your Windows PC, follow these steps:

1. Clone this repository to your local machine.

   ```bash
   git clone https://github.com/fer880220/osciloscopio-qml.git
   
2. Ensure you have Qt 5.8 installed on your system.
3. Download and install Thonny from their website: [Thonny Download](https://thonny.org/).
3. Connect the Raspberry Pi Pico to your PC via USB.
4. Open Thonny and install MicroPython on the Pico.
5. Open the `.py` files located in the "MicroPy ADC proj" folder of this project in Thonny. Save a copy of each `.py` file to the Pico using Thonny, then close Thonny and disconnect the USB cable from the Pico.


## How to Use
1. Connect the Raspberry Pi Pico to your PC.
2. Open `qmloscilloscope.pro` located in the "QT C++" folder of the project using Qt-Creator.
3. Execute `qmloscilloscope` in Qt-Creator to run the oscilloscope.
4. Start capturing and visualizing signals on the oscilloscope.

## Contributing
We welcome contributions to enhance the functionality and compatibility of the oscilloscope. If you would like to contribute, please fork this repository, create a new branch, make your changes, and submit a pull request.

## License
This project is licensed under the MIT License.

## Contact
If you have any questions or suggestions regarding this project, please feel free to contact the development team at https://t.me/+EbFdxe7a9z5mNjJh .