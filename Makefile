aiffcreate: aiffcreate.c
	gcc -o $@ $< -framework AudioToolbox -framework CoreFoundation -framework CoreAudio -lm

clean:
	rm hello.aiff aiffcreate || true
