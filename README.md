# HoltekLib

**HoltekLib** is a comprehensive collection of lightweight and practical libraries for Holtek 8-bit microcontrollers. These libraries are written in C and utilize assembly registers as specified in the Holtek datasheets, specifically designed for embedded applications. The goal of this collection is to provide low-volume, high-efficiency libraries.

## Features

- **RCC Management**: Control of Reset and Clock functions for power management and watchdog timer functionality.
- **GPIO Support**: Control of general-purpose input and output.
- **ADC Functionality**: Read analog signals through Analog-to-Digital Conversion.
- **USART**: Serial communication with support for Hardware UART for data transmission and reception.
- **EEPROM Support**: Access and manage EEPROM for non-volatile storage.
- **Timers**: 
  - **Base Timers (BTM)**: Configuration and use of Base Timers 0 & 1, along with functions for basic timer operations.
  - **Standard Type Timer (STM)**: Support for Standard Type Timer operations.
  - **Periodic Timer (PTM)**: Functionality for periodic timer tasks.
- **NTC Support**: Integration with NTC thermistors for temperature sensing.
- **Display Control**: Manage 7-segment displays for numerical output.
- **Lightweight and Efficient**: Designed for low-volume, resource-constrained applications.
- **Compatibility with Holtek 8-bit Microcontrollers**: Optimized for the specific architecture of these microcontrollers.

## Installation and Usage

To use the HoltekLib libraries, simply include the relevant files in your project and use the provided functions. All libraries are designed to be usable with minimal initial setup.

## Contribution

We welcome your contributions to the development and improvement of these libraries. To contribute, you can fork the repository, make your changes, and submit a pull request. You can also report issues and suggestions through the Issues section.

## License

This project is licensed under the [Apache 2.0]. For more information, see the LICENSE file.
