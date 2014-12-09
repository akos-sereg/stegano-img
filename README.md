stegano-img
===========

This command line application allows you to encode text file into PNG images, with - relatively - minimal loss of quality. For each pixel, least significant bits of colour channels (red, green, blue, alpha) are used to store hidden data. Using this algorithm, we can store 4 bits of data in every pixel.

Pre-requisite:
```
# apt-get install libgd-dev
```

Compile with make:
```
$ make
make[1]: Entering directory `/media/samsung/share/dev/c/stegano-img/src'
gcc    -c -o herbivore.o herbivore.c
gcc    -c -o help.o help.c
gcc    -c -o std_encode.o std_encode.c
gcc    -c -o string.o string.c
gcc    -c -o key.o key.c
gcc    -c -o user.o user.c
gcc    -c -o hcore.o hcore.c
gcc    -c -o std_decode.o std_decode.c
gcc    -c -o math.o math.c
gcc    -c -o io.o io.c
gcc   herbivore.o help.o std_encode.o string.o key.o user.o hcore.o std_decode.o math.o io.o /usr/lib/i386-linux-gnu/libgd.so /usr/lib/i386-linux-gnu/libm.so   -o herbivore
make[1]: Leaving directory `/media/samsung/share/dev/c/stegano-img/src'
akoss@sauron:/media/samsung/share/dev/c/stegano-img$
```

Usage:
```
# Encode the content of textfile.txt into image.png image, cipher-image.png will hold the hidden text
$ ./herbivore -e image.png -t textfile.txt -o cipher-image.png

# Decode text from cipher-image.png - the result (content of the original file, textfile.txt) will be printed to stdout
$ ./herbivore -d cipher-image.png
```
