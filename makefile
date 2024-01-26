default:
	gcc -Wall -Wextra main.c cache.c -o caches.exe

debug:
	gcc -Wall -Wextra -g main.c cache.c -o caches.exe

clean:
	del caches.exe