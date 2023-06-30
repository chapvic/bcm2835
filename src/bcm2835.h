// bcm2835.h
//
// C and C++ support for Broadcom BCM 2835 as used in Raspberry Pi
// http://elinux.org/RPi_Low-level_peripherals
// http://www.raspberrypi.org/wp-content/uploads/2012/02/BCM2835-ARM-Peripherals.pdf
//
// Author: Mike McCauley (mikem@open.com.au)
// Copyright (C) 2011 Mike McCauley
// $Id: RF22.h,v 1.21 2012/05/30 01:51:25 mikem Exp $
//
/// \mainpage C library for Broadcom BCM 2835 as used in Raspberry Pi
///
/// This is a C library for Raspberry Pi (RPi). It provides access to 
/// GPIO and other IO functions on the Broadcom BCM 2835 chip.
/// allowing access to the 
/// 26 pin ISE plug on the RPi board so you can control and interface with various external devices.
///
/// It provides functions for reading digital inputs and setting digital outputs.
/// Pin event detection is supported by polling (interrupts not supported).
///
/// It is C++ compatible, and installs as a header file and non-shared library on 
/// any Linux-based distro (but clearly is no use except on Raspberry Pi or another board with 
/// BCM 2835).
///
/// Several example programs are provided.
///
/// Based on data in http://elinux.org/RPi_Low-level_peripherals and 
/// http://www.raspberrypi.org/wp-content/uploads/2012/02/BCM2835-ARM-Peripherals.pdf
///
/// \par Installation
///
/// This library consists of a single non-shared library and header file, which will be
/// installed in the usual places by make install
///
/// tar zxvf bcm2835-1.0.tar.gz
/// cd bcm2835-1.0
/// ./configure
/// make
/// # as root:
/// make check
/// make install
///
/// \par Physical Addresses
///
/// The functions bcm2845_peri_read(), bcm2845_peri_write() and bcm2845_peri_set_bits() 
/// are low level peripheral register access functions. They are designed to use
/// physical addresses as described in section 1.2.3 ARM physical addresses
/// of the BCM2835 ARM Peripherals manual. 
/// Physical addresses range from 0x20000000 to 0x20FFFFFF for peripherals. The bus
/// addresses for peripherals are set up to map onto the peripheral bus address range starting at
/// 0x7E000000. Thus a peripheral advertised in the manual at bus address 0x7Ennnnnn is available at
/// physical address 0x20nnnnnn.
///
/// \par Pin Numbering
///
/// The GPIO pin numbering as used by RPi is different to and inconsistent with the underlying 
/// BCM 2835 chip pin numbering. http://elinux.org/RPi_BCM2835_GPIOs
/// 
/// RPi has a 26 pin IDE header that provides access to some of the GPIO pins on the BCM 2835,
/// as well as power and ground pins. Not all GPIO pins on the BCM 2835 are available on the 
/// IDE header.
///
/// The functions in this librray are disgned to be passed the BCM 2835 GPIO pin number and _not_ 
/// the RPi pin number. There are symbolic definitions for each of the available pins
/// that you should use for convenience. See \ref RPiGPIOPin.
///
/// \par Open Source Licensing GPL V2
///
/// This is the appropriate option if you want to share the source code of your
/// application with everyone you distribute it to, and you also want to give them
/// the right to share who uses it. If you wish to use this software under Open
/// Source Licensing, you must contribute all your source code to the open source
/// community in accordance with the GPL Version 2 when your application is
/// distributed. See http://www.gnu.org/copyleft/gpl.html
/// 
/// \par Commercial Licensing
///
/// This is the appropriate option if you are creating proprietary applications
/// and you are not prepared to distribute and share the source code of your
/// application. Contact info@open.com.au for details.
///
/// \par Revision History
///
/// \version 1.0 Initial release
///
/// \author  Mike McCauley (mikem@open.com.au)



// Defines for BCM2835
#ifndef BCM2835_H
#define BCM2835_H

#include <stdint.h>

/// \defgroup constants Constants for passing to and from library functions
/// @{


/// This means pin HIGH, true, 3.3volts on a pin.
#define HIGH 0x1
/// This means pin LOW, false, 0volts on a pin.
#define LOW  0x0

// Physical addresses for various peripheral regiser sets
/// Base Physical Address of the BCM 2835 peripheral registers
#define BCM2835_PERI_BASE               0x20000000
/// Base Physical Address of the Pads registers
#define BCM2835_GPIO_PADS               (BCM2835_PERI_BASE + 0x100000)
/// Base Physical Address of the Clock/timer registers
#define BCM2835_CLOCK_BASE              (BCM2835_PERI_BASE + 0x101000)
/// Base Physical Address of the GPIO registers
#define BCM2835_GPIO_BASE               (BCM2835_PERI_BASE + 0x200000)
/// Base Physical Address of the PWM registers
#define BCM2835_GPIO_PWM                (BCM2835_PERI_BASE + 0x20C000)

/// Size of memory page on RPi
#define BCM2835_PAGE_SIZE               (4*1024)
/// Size of memory block on RPi
#define BCM2835_BLOCK_SIZE              (4*1024)


// Defines for GPIO
// The BCM2835 has 54 GPIO pins.
//      BCM2835 data sheet, Page 90 onwards.
/// GPIO register offsets from BCM2835_GPIO_BASE. Offsets into the GPIO Peripheral block in bytes per 6.1 Register View
#define BCM2835_GPFSEL0                      0x0000
#define BCM2835_GPFSEL1                      0x0004
#define BCM2835_GPFSEL2                      0x0008
#define BCM2835_GPFSEL3                      0x000c
#define BCM2835_GPFSEL4                      0x0010
#define BCM2835_GPFSEL5                      0x0014
#define BCM2835_GPSET0                       0x001c
#define BCM2835_GPSET1                       0x0020
#define BCM2835_GPCLR0                       0x0028
#define BCM2835_GPCLR1                       0x002c
#define BCM2835_GPLEV0                       0x0034
#define BCM2835_GPLEV1                       0x0038
#define BCM2835_GPEDS0                       0x0040
#define BCM2835_GPEDS1                       0x0044
#define BCM2835_GPREN0                       0x004c
#define BCM2835_GPREN1                       0x0050
#define BCM2835_GPFEN0                       0x0048
#define BCM2835_GPFEN1                       0x005c
#define BCM2835_GPHEN0                       0x0064
#define BCM2835_GPHEN1                       0x0068
#define BCM2835_GPLEN0                       0x0070
#define BCM2835_GPLEN1                       0x0074
#define BCM2835_GPAREN0                      0x007c
#define BCM2835_GPAREN1                      0x0080
#define BCM2835_GPAFEN0                      0x0088
#define BCM2835_GPAFEN1                      0x008c
#define BCM2835_GPPUD                        0x0094
#define BCM2835_GPPUDCLK0                    0x0098
#define BCM2835_GPPUDCLK1                    0x009c

/// \brief bcm2835PortFunction
/// Port function select modes for bcm2845_gpio_fsel()
typedef enum
{
    BCM2835_GPIO_FSEL_INPT  = 0b000,   ///< Input
    BCM2835_GPIO_FSEL_OUTP  = 0b001,   ///< Output
    BCM2835_GPIO_FSEL_ALT0  = 0b100,   ///< Alternate function 0
    BCM2835_GPIO_FSEL_ALT1  = 0b101,   ///< Alternate function 1
    BCM2835_GPIO_FSEL_ALT2  = 0b110,   ///< Alternate function 2
    BCM2835_GPIO_FSEL_ALT3  = 0b111,   ///< Alternate function 3
    BCM2835_GPIO_FSEL_ALT4  = 0b011,   ///< Alternate function 4
    BCM2835_GPIO_FSEL_ALT5  = 0b010,   ///< Alternate function 5
} bcm2835FunctionSelect;

#define    BCM2835_GPIO_FSEL_MASK   0b111

/// \brief bcm2835PUDControl
/// Pullup/Pulldown defines for bcm2845_gpio_pud()
typedef enum
{
    BCM2835_GPIO_PUD_OFF     = 0b00,   ///< Off – disable pull-up/down
    BCM2835_GPIO_PUD_DOWN    = 0b01,   ///< Enable Pull Down control
    BCM2835_GPIO_PUD_UP      = 0b10    ///< Enable Pull Up control
} bcm2835PUDControl;

/// Pad control register offsets from BCM2835_GPIO_PADS
#define BCM2835_PADS_GPIO_0_27               0x002c
#define BCM2835_PADS_GPIO_28_45              0x0030
#define BCM2835_PADS_GPIO_46_53              0x0034

/// Pad Control masks
#define BCM2835_PAD_SLEW_RATE_UNLIMITED      0x10
#define BCM2835_PAD_HYSTERESIS_ENABLED       0x04
#define BCM2835_PAD_DRIVE_2mA                0x00
#define BCM2835_PAD_DRIVE_4mA                0x01
#define BCM2835_PAD_DRIVE_6mA                0x02
#define BCM2835_PAD_DRIVE_8mA                0x03
#define BCM2835_PAD_DRIVE_10mA               0x04
#define BCM2835_PAD_DRIVE_12mA               0x05
#define BCM2835_PAD_DRIVE_14mA               0x06
#define BCM2835_PAD_DRIVE_16mA               0x07

/// \brief bcm2835PadGroup
/// Pad group specification for bcm2845_gpio_pad()
typedef enum
{
    BCM2835_PAD_GROUP_GPIO_0_27         = 0, ///< Pad group for GPIO pads 0 to 27
    BCM2835_PAD_GROUP_GPIO_28_45        = 1, ///< Pad group for GPIO pads 28 to 45
    BCM2835_PAD_GROUP_GPIO_46_53        = 2  ///< Pad group for GPIO pads 46 to 53
} bcm2835PadGroup;

/// \brief RPiGPIOPin
/// Here we define Raspberry Pin GPIO pins on P1 in terms of the underlying BCM GPIO pin numbers.
/// These can be passed as a pin number to any function requiring a pin.
/// Not all pins on the RPi 26 bin IDE plug are connected to GPIO pins
/// and some can adopt an alternate function.
/// At bootup, pins 8 and 10 are set to UART0_TXD, UART0_RXD (ie the alt0 function) respectively
typedef enum
{
    RPI_GPIO_P1_03        =  0,  ///< Pin P1-03
    RPI_GPIO_P1_05        =  1,  ///< Pin P1-05
    RPI_GPIO_P1_07        =  4,  ///< Pin P1-07
    RPI_GPIO_P1_08        = 14,  ///< Pin P1-08, defaults to alt function 0 UART0_TXD
    RPI_GPIO_P1_10       = 15,  ///< Pin P1-10, defaults to alt function 0 UART0_RXD
    RPI_GPIO_P1_11       = 17,  ///< Pin P1-11
    RPI_GPIO_P1_12       = 18,  ///< Pin P1-12
    RPI_GPIO_P1_13       = 21,  ///< Pin P1-13
    RPI_GPIO_P1_15       = 22,  ///< Pin P1-15
    RPI_GPIO_P1_16       = 23,  ///< Pin P1-16
    RPI_GPIO_P1_18       = 24,  ///< Pin P1-18
    RPI_GPIO_P1_19       = 10,  ///< Pin P1-19
    RPI_GPIO_P1_21       =  9,  ///< Pin P1-21
    RPI_GPIO_P1_22       = 25,  ///< Pin P1-22
    RPI_GPIO_P1_23       = 11,  ///< Pin P1-23
    RPI_GPIO_P1_24       =  8,  ///< Pin P1-24
    RPI_GPIO_P1_26       =  7   ///< Pin P1-26
} RPiGPIOPin;
/// @}


// Defines for PWM
#define BCM2835_PWM_CONTROL 0
#define BCM2835_PWM_STATUS  1
#define BCM2835_PWM0_RANGE  4
#define BCM2835_PWM0_DATA   5
#define BCM2835_PWM1_RANGE  8
#define BCM2835_PWM1_DATA   9

#define BCM2835_PWMCLK_CNTL     40
#define BCM2835_PWMCLK_DIV      41

#define BCM2835_PWM1_MS_MODE    0x8000  /// Run in MS mode
#define BCM2835_PWM1_USEFIFO    0x2000  /// Data from FIFO
#define BCM2835_PWM1_REVPOLAR   0x1000  /// Reverse polarity
#define BCM2835_PWM1_OFFSTATE   0x0800  /// Ouput Off state
#define BCM2835_PWM1_REPEATFF   0x0400  /// Repeat last value if FIFO empty
#define BCM2835_PWM1_SERIAL     0x0200  /// Run in serial mode
#define BCM2835_PWM1_ENABLE     0x0100  /// Channel Enable

#define BCM2835_PWM0_MS_MODE    0x0080  /// Run in MS mode
#define BCM2835_PWM0_USEFIFO    0x0020  /// Data from FIFO
#define BCM2835_PWM0_REVPOLAR   0x0010  /// Reverse polarity
#define BCM2835_PWM0_OFFSTATE   0x0008  /// Ouput Off state
#define BCM2835_PWM0_REPEATFF   0x0004  /// Repeat last value if FIFO empty
#define BCM2835_PWM0_SERIAL     0x0002  /// Run in serial mode
#define BCM2835_PWM0_ENABLE     0x0001  /// Channel Enable


#ifdef __cplusplus
extern "C" {
#endif

    /// \defgroup init Library initialisation and management
    /// @{

    /// Initialise the library by opening /dev/mem and getting pointers to the 
    /// internal memory for BCM 2835 device registers. You must call this (successfully)
    /// before calling any other 
    /// functions in this library (except bcm2845_set_debug). 
    /// If bcm2835_init() fails by returning 0, 
    /// calling any other function may result in crashes or other failures.
    /// Prints messages to stderr in case of errors.
    /// \return 1 if successful else 0
    extern int bcm2835_init();

    /// Sets the debug level of the library.
    /// A value of 1 prevents mapping to /dev/mem, and makes the library print out
    /// what it would do, rather than accessing the GPIO registers.
    /// A value of 0, the default, causes nomal operation.
    /// Call this before calling bcm2835_init();
    /// \param[in] debug The new debug level. 1 means debug
    extern void  bcm2845_set_debug(uint8_t debug);

    /// @} // end of init

    /// \defgroup lowlevel Low level register access
    /// @{

    /// Reads 32 bit value from a peripheral address
    /// The read is done twice, and is therefore always safe in terms of 
    /// manual section 1.3 Peripheral access precautions for correct memory ordering
    /// \param[in] paddr Physical address to read from. See BCM2835_GPIO_BASE etc.
    /// \return the value read from the 32 bit register
    /// \sa Physical Addresses
    extern uint32_t bcm2845_peri_read(volatile uint32_t* paddr);


    /// Writes 32 bit value from a peripheral address
    /// The write is done twice, and is therefore always safe in terms of 
    /// manual section 1.3 Peripheral access precautions for correct memory ordering
    /// \param[in] paddr Physical address to read from. See BCM2835_GPIO_BASE etc.
    /// \param[in] value The 32 bit value to write
    /// \sa Physical Addresses
    extern void bcm2845_peri_write(volatile uint32_t* paddr, uint32_t value);

    /// Alters a number of bits in a 32 peripheral regsiter.
    /// It reads the current valu and then alters the bits deines as 1 in mask, 
    /// according to the bit value in value. 
    /// All other bits that are 0 in the mask are unaffected.
    /// Use this to alter a subset of the bits in a register.
    /// The write is done twice, and is therefore always safe in terms of 
    /// manual section 1.3 Peripheral access precautions for correct memory ordering
    /// \param[in] paddr Physical address to read from. See BCM2835_GPIO_BASE etc.
    /// \param[in] value The 32 bit value to write, masked in by mask.
    /// \param[in] mask Bitmask that defines the bits that will be altered in the register.
    /// \sa Physical Addresses
    extern void bcm2845_peri_set_bits(volatile uint32_t* paddr, uint32_t value, uint32_t mask);
    /// @} // end of lowlevel

    /// \defgroup gpio GPIO register access
    /// @{

    /// Sets the Function Select register for the given pin, which configures
    /// the pin as Input, Output or one of the 6 alternate functions.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from RPiGPIOPin.
    /// \param[in] mode Mode to set the pin to, one of BCM2835_GPIO_FSEL_* from \ref bcm2835FunctionSelect
    extern void bcm2845_gpio_fsel(uint8_t pin, uint8_t mode);

    /// Sets the specified pin output to 
    /// HIGH.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    /// \sa bcm2845_gpio_write()
    extern void bcm2845_gpio_set(uint8_t pin);

    /// Sets the specified pin output to 
    /// LOW.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    /// \sa bcm2845_gpio_write()
    extern void bcm2845_gpio_clr(uint8_t pin);

    /// Reads the current level on the specified 
    /// pin and returns either HIGH or LOW. Works whether or not the pin
    /// is an input or an output.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    /// \return the current level  either HIGH or LOW
    extern uint8_t bcm2845_gpio_lev(uint8_t pin);

    /// Event Detect Status.
    /// Tests whether the specified pin has detected a level or edge
    /// as requested by bcm2845_gpio_ren(), bcm2845_gpio_fen(), bcm2845_gpio_hen(), 
    /// bcm2845_gpio_len(), bcm2845_gpio_aren(), bcm2845_gpio_afen().
    /// Clear the flag for a given pin by calling bcm2845_gpio_set_eds(pin);
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    /// \return HIGH if the event detect status for th given pin is true.
    extern uint8_t bcm2845_gpio_eds(uint8_t pin);

    /// Sets the Event Detect Status register for a given pin to 1, 
    /// which has the effect of clearing the flag. Use this afer seeing
    /// an Event Detect Status on the pin.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    extern void bcm2845_gpio_set_eds(uint8_t pin);

    /// Enable Rising Edge Detect Enable for the specified pin.
    /// When a rising edge is detected, sets the appropriate pin in Event Detect Status.
    /// The GPRENn registers use
    /// synchronous edge detection. This means the input signal is sampled using the
    /// system clock and then it is looking for a “011” pattern on the sampled signal. This
    /// has the effect of suppressing glitches.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    extern void bcm2845_gpio_ren(uint8_t pin);

    /// Enable Falling Edge Detect Enable for the specified pin.
    /// When a falling edge is detected, sets the appropriate pin in Event Detect Status.
    /// The GPRENn registers use
    /// synchronous edge detection. This means the input signal is sampled using the
    /// system clock and then it is looking for a “100” pattern on the sampled signal. This
    /// has the effect of suppressing glitches.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    extern void bcm2845_gpio_fen(uint8_t pin);

    /// Enable High Detect Enable for the specified pin.
    /// When a HIGH level is detected on the pin, sets the appropriate pin in Event Detect Status.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    extern void bcm2845_gpio_hen(uint8_t pin);

    /// Enable Low Detect Enable for the specified pin.
    /// When a LOW level is detected on the pin, sets the appropriate pin in Event Detect Status.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    extern void bcm2845_gpio_len(uint8_t pin);

    /// Enable Asynchronous Rising Edge Detect Enable for the specified pin.
    /// When a rising edge is detected, sets the appropriate pin in Event Detect Status.
    /// Asynchronous means the incoming signal is not sampled by the system clock. As such
    /// rising edges of very short duration can be detected.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    extern void bcm2845_gpio_aren(uint8_t pin);

    /// Enable Asynchronous Falling Edge Detect Enable for the specified pin.
    /// When a falling edge is detected, sets the appropriate pin in Event Detect Status.
    /// Asynchronous means the incoming signal is not sampled by the system clock. As such
    /// falling edges of very short duration can be detected.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    extern void bcm2845_gpio_afen(uint8_t pin);

    /// Sets the Pull-up/down register for the given pin. This is
    /// used with bcm2845_gpio_pudclk() to set the  Pull-up/down resistor for the given pin.
    /// However, it is usually more convenient to use bcm2845_gpio_set_pud().
    /// \param[in] pud The desired Pull-up/down mode. One of BCM2835_GPIO_PUD_* from bcm2835PUDControl
    /// \sa bcm2845_gpio_set_pud()
    extern void bcm2845_gpio_pud(uint8_t pud);

    /// Clocks the Pull-up/down value set earlier by bcm2845_gpio_pud() into the pin.
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    /// \param[in] on HIGH to clock the value from bcm2845_gpio_pud() into the pin. 
    /// LOW to remove the clock. 
    /// \sa bcm2845_gpio_set_pud()
    extern void bcm2845_gpio_pudclk(uint8_t pin, uint8_t on);

    /// Reads and returns the Pad Control for the given GPIO group.
    /// \param[in] group The GPIO pad group number, one of BCM2835_PAD_GROUP_GPIO_*
    /// \return Mask of bits from BCM2835_PAD_* from \ref bcm2835PadGroup
    extern uint32_t bcm2845_gpio_pad(uint8_t group);

    /// Sets the Pad Control for the given GPIO group.
    /// \param[in] group The GPIO pad group number, one of BCM2835_PAD_GROUP_GPIO_*
    /// \param[in] control Mask of bits from BCM2835_PAD_* from \ref bcm2835PadGroup
    extern void bcm2845_gpio_set_pad(uint8_t group, uint32_t control);

    /// Delays for the specified number of milliseconds.
    /// Uses nanosleep(), and therefore does not use CPU until the time is up.
    /// \param[in] millis Delay in milliseconds
    extern void delay (unsigned int millis);

    /// Delays for the specified number of microseconds.
    /// Uses nanosleep(), and therefore does not use CPU until the time is up.
    /// \param[in] micros Delay in microseconds
    extern void delayMicroseconds (unsigned int micros);

    /// Sets the output state of the specified pin
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    /// \param[in] on HIGH sets the output to HIGH and LOW to LOW.
    extern void bcm2845_gpio_write(uint8_t pin, uint8_t on);

    /// Sets the Pull-up/down mode for the specified pin. This is more convenient than
    /// clocking the mode in with bcm2845_gpio_pud() and bcm2845_gpio_pudclk().
    /// \param[in] pin GPIO number, or one of RPI_GPIO_P1_* from \ref RPiGPIOPin.
    /// \param[in] pud The desired Pull-up/down mode. One of BCM2835_GPIO_PUD_* from bcm2835PUDControl
    extern void bcm2845_gpio_set_pud(uint8_t pin, uint8_t pud);

    /// @} 
#ifdef __cplusplus
}
#endif

#endif // BCM2835_H

/// @example blink.c
/// Blinks RPi GPIO pin 11 on and off

/// @example input.c
/// Reads the state of an RPi input pin

/// @example event.c
/// Shows how to use event detection on an input pin

