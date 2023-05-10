all:
	make clean-old-compile
	emcc -lembind -o find_words.js c_bin/test.cpp --preload-file romanian_dict.txt --preload-file english_dict.txt --preload-file oxford_dict.txt

clean-old-compile:
	-rm find_words.wasm
	-rm find_words.js
	-rm find_words.data
