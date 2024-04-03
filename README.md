# Network Sniffer

Network Sniffer is a simple packet capture tool that allows you to monitor network traffic on your system. It captures packets from a specified network interface and logs them to a file.

## Features

- Packet capture from a specified network interface.
- Logging of captured packets to a file.
- Simple GUI interface for starting and stopping packet capture.

## Requirements

- GNU Compiler Collection (GCC)
- GTK+ 3.0
- libpcap

## Installation

To compile the program, run the following command in your terminal:

```
gcc -o program main.c gui.c pkg-config --cflags --libs gtk+-3.0 -I. -lpcap
```

## Usage

After compiling the program, you can run it with the following command:

```
sudo ./program
```

This will start the packet capture process. You can stop it by closing the application window.

## License

This project is licensed under the [MIT License](LICENSE).

## Credits

This project was developed by [TwistyJead](https://github.com/moonlxight).
