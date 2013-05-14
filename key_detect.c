#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// this prints the character out
void show_char(char* thing_to_echo){
	printf("the character is %s\n",thing_to_echo);
}

// this shows what command it's going to send and then does it
void send_event(int first, int second){
	char one[16], two[16];
	char device[] = "/dev/input/event0";
	char command[256];
	sprintf(one, "%d", first);
	sprintf(two, "%d", second);
	snprintf(command, sizeof command, "input tap %s %s",one,two);
	printf("%s\n",command);

	system(command);
}

int main(int argc, char **argv){
	int fd;
	if (argc !=2){
		printf("Usage: %s <device>\n",argv[0]);
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	struct input_event ev;

	while(1){
		read(fd, &ev, sizeof(struct input_event));
		printf("%d %d\n",ev.value,ev.code);
		if(ev.type==1){
			// do_something is here because we ignore key releases
			// 1 corresponds to the key being pressed, 2 for held
			//int do_something = (ev.value==1 || ev.value==2);
			if(ev.value == 1 || ev.value== 0){
				switch(ev.code){
					case 17:
						// show_char("w");
						if(ev.value == 1){
							system("sendevent /dev/input/event0 3 57 22; sendevent /dev/input/event0 3 48 5; sendevent /dev/input/event0 3 58 11; sendevent /dev/input/event0 3 53 1246; sendevent /dev/input/event0 3 54 55");
						}
						else{
							system("sendevent /dev/input/event0 3 58 45; sendevent /dev/input/event0 3 53 1247; sendevent /dev/input/event0 3 54 60; sendevent /dev/input/event0 3 57 4294967295");
						}
						//send_event(1180,700);
						break;
					case 30:
						// show_char("a");
						//send_event(52,700);
						if(ev.value == 1){
							system("sendevent /dev/input/event0 3 57 21; sendevent /dev/input/event0 3 48 2; sendevent /dev/input/event0 3 58 2; sendevent /dev/input/event0 3 53 1268; sendevent /dev/input/event0 3 54 2085");
						}
						else{
							system("sendevent /dev/input/event0 3 58 23; sendevent /dev/input/event0 3 53 1263; sendevent /dev/input/event0 3 54 2087; sendevent /dev/input/event0 3 57 4294967295");
						}
						break;
					case 31:
						// show_char("s");
						//send_event(52,700);
						break;
					case 32:
						// show_char("d");
						//send_event(52,700);
						break;
					case 33:
						//show_char("f");
						//send_event(52,700);
						break;
					case 34:
						show_char("g");
						//send_event(52,700);
						break;
					case 35:
						show_char("h");
						//send_event(52,700);
						break;
					case 36:
						show_char("j");
						//send_event(52,700);
						break;
				}
			}
		}
	}

	return 1;
}
