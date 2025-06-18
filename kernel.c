// kernel.c - Main C entry point for echOS

void kernel_main(){
	char *video_memory = (char *) 0xb8000;

	const char *message = " echOS v1.0.0 ready ";
	for (int i = 0; message[i] != '\0'; i++) {
		video_memory[i * 2] = message[i];	//char
		video_memory[i * 2 + 1] = 0x7;		//attribute: light grey on black
	}
        while (1);
}
