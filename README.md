# bluefish password manager

This is the c++ linux command line interface to the bluefish password manager.
The hardware specs and firmware can be found
[here](https://github.com/aghoward/bluefish-firmware).


## What is bluefish?

bluefish is a hardware based password manager that is about the size of a usb
flash drive. It's meant to be portable and secure. All data on the device is
encrypted, so even if someone made a copy of your device, they wouldn't be able
to get any information from it. All decryption is done inside the client, so the
device itself acts as a dumb data store. This also means that if anyone were
spying on the traffic on your USB bus, they still wouldn't be able to glean any
information.


## How does it work?

First you'll have to build the hardware so that the client has something to talk
to. The hardware is little more than an arduino nano with an attached EEPROM for
storage. The details of the slim-lined version can be found in the hardware
repository linked in the first section of this README. If you just want
something that works, you can easily hook up a nano and a EEPROM (24LC512 or
24LC64). The readme in the firmware repository explains how you can flash the
firmware after it's built.

Then you'll need to compile this repository. This should be as simple as:

```
$ git clone git@github.com:aghoward/bluefish-client.git
$ cd bluefish-client
$ git submodule update --init --recursive
$ make
```


## Usage

```
Usage: bluefish [-d|--device <device>] [-b|--baud <baud>] [-l|--list] [-a|--add <add_file>] [-u|--username <username>] [--remove|--rm <remove>] [-r|--read <read>] [-f|--format] [-p|--print-usage]
```


### Universal Options

`-d|--device <device>` - This option points to the serial device. It defaults to
/dev/ttyUSB0 as the official hardware uses the CH330N USB serial UART; which on
linux creates the /dev/ttyUSBXX devices. You can change this to point to
whatever your system identifies the device as

`-b|--baud <baud>` - This is the baud rate of the device. It defaults to 115200.
This is mostly useful for debugging. It will need to match whatever the device
firmware thinks the baud rate is (hint it also defaults to 115200).


### Formatting and First Usage

When you first flash the firmware it won't be able to make sense of a blank or
unformatted EEPROM. There is a small amount of record keeping the device needs
to write on the EEPROM before anything will work, and this can take some time to
write. To setup, or to clear a previously used EERPM you'll need to format the
device:

`-f|--format` - This formats the EEPROM! Don't worry it will ask you to enter
the word "format" before it will actually do anything, so you shouldn't be able
to accidentally format a working storage device.

Formatting will ask you for a master password, this will be the password used to
encrypt everything on the bluefish device. If you lose this password, you will
not be able to read any data from the device! You have been warned. This
password won't be stored on the device in anyway, but it will be used to encrypt
a challenge (random bytes) which can be used later to verify you entered the
correct password when doing certain things on the device (adding, removing,
listing, and reading files).


### Listing files

`-l|--list` - This list the names of all files on the device. We use the term
"file" here to denote passwords because they can be thought of as files, where
they have a name (the filename), a username and password (the contents). This
command just lists the names of all files on the device. It won't actually list
any of the contents (usernames or password).

*Note*: This command will ask you for the master password and won't be able to
list anything unless you provide the correct password. Why is this? Remember how
we said everything on the device is encrypted? Yup, that includes the filenames
as well as their contents.


### Adding a file

`-a|--add <filename>` - Specifies the filename for the file to add. This needs
to be used with the `-u|--username` flag.

`-u|--username <useranme>` - Specifies the username portion of the credentials
to associate with this file.

After specifying these two flags and values, you'll be asked for the password
(don't worry it won't display what you type while you are typing the password).
Then it will ask for your master password.

*Note*: Why does it ask for the master password _and_ the password? Remember
that the master password is used to encrypt everything on the device, and it
isn't stored anywhere on the device.


### Reading a file

`-r|--read <filename>` - Specifies a file to read. This will display all the
contents of the file as well as the filename, in plaintext on the command line.

This will prompt for your master password, which will not be echoed to the
command line, before the file is decrypted and read.


### Removing a file


`--rm <filename>` - Removes a file from the device by filename.

*Note*: While this client will ask for the master password and verify it before
removing the file from the device; there really isn't anyway to ensure another
client won't just allow anyone to delete files (though they wouldn't know what
the filenames were).


### How much storage is left?

`-p|--print-usage` - This just prints some usage statistics about the device.
Specifically it will list the number of free inodes, the number of files written
to the device and the initialization vector.
