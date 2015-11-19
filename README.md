                                                                                |
When encoding the encoder.c and encoder files, using gzip and our own encoder,
the following results are obtained:

file		| No encoding	| gzip			| ratio
------------+---------------+---------------+---------------
encoder		| 13180			| 2512			| 0.1905918058
------------+---------------+---------------+---------------
encoder.c	| 5684			| 1653			| 0.2908163265


file		| No encoding	| encoder		| ratio
------------+---------------+---------------+---------------
encoder		| 13180			| 14504			| 1.1004552352
------------+---------------+---------------+---------------
encoder.c	| 5684			| 3376			| 0.593947924


While using encoder on either file didn't match even close with the results of
gzip, encoder had a much larger improvment on encoder.c over encoder. I believe
the reason for this is with the use of 15 frequent characters. When encoding
the english letters of code, many characters repeat and finding these characters
in the input is easy. With the encoder object file however, the character values
are more or less "random". While not truely random of course, the values are
much more spread out, reducing the number of repeated values. Because non
repeated characters, which are 8 bits, require an encoding into 9 bits, the file
size actually increases.

This leads to the conclusion that while this program is great for encoding
text files, its usefullness is less appearent with other types of files.
