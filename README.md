# uStack-STM32 - A portable and minimalistic IP stack, ported to the STM32

Ported from https://github.com/sjohann81/ustack.

uStack is a quick-and-dirty implementation of most common network protocols of IPv4, suitable for experiments, porting and integration of a IP network stack on embedded devices with limited resources. Currently, uStack supports a low level abstraction of a network card (using Linux TUN/TAP), Serial IP interface, Ethernet, ARP, BOOTP, IP, ICMP and UDP protocols.

## Configuration (TUN/TAP interface)

Just type *make* to build the firmware. To run it on a STM32 BlackPill, connect the board via USB, enter in programming mode (more details below) and type *make flash*. After the programming process, hit reset then connect to the board using the virtual serial port created by the USB CDC driver with the TUN/TAP tunnel using *sudo make eth_up* then try the demo.

Before reprogramming the board, be sure to bring the TUN/TAP tunnel down using Ctrl+c on the terminal running it. This process is needed because the same serial port is used for both programming and communicating with the host. If you have a different board, or arranged a different configuration on a breadboard, you may not need this (such as using a different serial port).

## Configuration (SLIP interface)

Change the rule *all* in the Makefile to build the slip stack (ustack_eth -> ustack_slip) then type *make* to build the firmware. To run it on a STM32 BlackPill, connect the board via USB and type *make flash*. After the programming process, hit reset and connect to the board using the serial port created by the USB CDC driver with *sudo make slip_up* then try the demo.

Before reprogramming the board, be sure to bring the SLIP interface down with *sudo make slip_down*. This process is needed because the same serial port is used for both programming and communicating with the host. If you have a different board, or arranged a different configuration on a breadboard, you may not need this.

## Programming the STM32 BlackPill via DFU protocol

There is a problem with entering DFU programming mode in the BlackPill, which is caused by a floating RX1 pin (PA10) which is close to BOOT and RST buttons (this is a board issue). To overcome this, place a pull-down resistor (4k7 or 10k) between PA10 and GND, then proceed with normal DFU mode: hold BOOT0, hit RESET then release BOOT0.

Another issue is the USB port. To enable USB enumeration, put a 1k5 resistor between USB D+ (PA12) and 3.3v - this makes the USB CDC serial driver work. Another option is to put a 1k5 resistor between PA12 and PA15. In this case, PA15 is used as a software pull-up for the USB bus. This enables DFU programming / reset / USB uart debugging without unpluging the device.

On Debian, sometimes *modemmanager* clashes with the virtual usb port, so removing it solves the issue:

*sudo apt-get --purge remove modemmanager*

## Demo

The demo application (main.c) uses a static IP address / network mask is configured in the makefile. The application consists of a UDP callback routine and a loop which checks for received packets. On reception, the packet is injected into the network stack. To reach the application try this:

    $ ping -c 3 172.31.69.20

    PING 172.31.69.20 (172.31.69.20) 56(84) bytes of data.
    64 bytes from 172.31.69.20: icmp_seq=1 ttl=64 time=33.0 ms
    64 bytes from 172.31.69.20: icmp_seq=2 ttl=64 time=31.3 ms
    64 bytes from 172.31.69.20: icmp_seq=3 ttl=64 time=33.2 ms

    --- 172.31.69.20 ping statistics ---
    3 packets transmitted, 3 received, 0% packet loss, time 2002ms
    rtt min/avg/max/mdev = 31.307/32.524/33.262/0.892 ms


Then, test the *echo protocol* using UDP on port 7 or the demo application on port 30168:

    $ echo "hi there" | nc -u -w1 172.31.69.20 7
    hi there

    $ nc -u 172.31.69.20 30168
    hey
    Hello world!
