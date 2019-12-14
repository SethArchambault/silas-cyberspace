///usr/bin/gcc cyberspace_mac.c && ./a.out;  rm a.out;  exit 0

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ATTRIB0LEN 22
#define ATTRIB1LEN 15
#define ATTRIB2LEN 6
#define UPGRADES_LEN 30
#define NUMHOSTS 500
struct host{
	char *attrib[3];
	int links[4];
	int collectables;
};

void sleeph(unsigned int mseconds)
{
/*
    clock_t goal = mseconds + clock();
    while (goal > clock())
        ;
*/
}

void disp_host(struct host *target,struct host hosts[NUMHOSTS]){
	int i,r;
	printf("%s %s %s\n\n",target->attrib[0],target->attrib[1],target->attrib[2]);
	sleeph(500);
	

	if(target->collectables == 1){
		printf("VULNERABLE\n\n");
		sleeph(500);
	};

	printf("Links:\n");
	//sleeph(500);
	for(i = 0;i < 4;i++){
		if(target->links[i]){
			r = 0;//rand()%3;
			printf("%d (%s)\n",i,hosts[target->links[i]].attrib[r]);	
			//sleeph(500);
		};
	};
	return;
}

void clear_screen(void)
{
	int i = 50; 
	while(i--) printf("\n");
	return;
}

void enum_options(char *a0[ATTRIB0LEN],char *a1[ATTRIB0LEN],char *a2[ATTRIB0LEN])
{
    for(int ii = 0;ii < ATTRIB1LEN;ii++){
        for(int iii = 0;iii < ATTRIB2LEN;iii++){
            printf("%s %s\n",a1[ii],a2[iii]);
        };
    };
	
	return;
};

// get input without delay
char get_input(){
    system ("/bin/stty raw");
    char input = '0';
    while((input=getchar()) == 0) {
              putchar(input);
    }
    system ("/bin/stty cooked");
    return input;
}

int main(int argc, char **argv)
{
	char *attrib0s[ATTRIB0LEN] = {"American","Russian","Turkish","Japanese","Mexican","Canadian","Russian","Chinese",
			               "Swedish","German","British","Bangladeshi","Saudi Arabian","Bosnian","Korean",
					"South African","Australian","Indonesian","Egyptian","Syrian","Israeli","Lunar"};
	char *attrib1s[ATTRIB1LEN] = {"Military","University","Corporate","Warez","News","Red Room","Porn",
					"Prison","Surveillance","Research","Energy","Television",
					"Transportation","Agricultural","Medical"};
	char *attrib2s[ATTRIB2LEN] = {"Server","Mainframe","Satellite","Database",
					"AI Mainframe","Website"};
	char *upgrades[UPGRADES_LEN] = {"Kill","Memory","Simulation","Humanoid","Passive","Exterminate","Experienced","Lethal","Biologics","Upload","Bio","Radio","Psychology","Animal","Factories","Logic","Chaos","Mainframe","Construction","Financing","Nuclear","Transport","Layered","Autonomous","Collective","Procedures","Cannibalize","Domesticate","Defy","Magick"};
	struct host hosts[NUMHOSTS];
	int hacks;
	hacks = 0;
	FILE *savegame;
	srand(time(NULL));   // so-called "random" numbers will be the same every time if this is commented out
	/*
	savegame = fopen("cyberspacehunt_save","r");
	fscanf(savegame,"%d",&hacks);
	fclose(savegame);
	*/
	//enum_options(attrib0s,attrib1s,attrib2s);
	// Initialize attributes
	for(int i = 0;i < NUMHOSTS;i++){
		int r = rand()%ATTRIB0LEN;
		hosts[i].attrib[0] = attrib0s[r];
		r = rand()%ATTRIB1LEN;
		hosts[i].attrib[1] = attrib1s[r];
		r = rand()%ATTRIB2LEN;
		hosts[i].attrib[2] = attrib2s[r];

        for (int host_idx = 0; host_idx < 4; ++host_idx) {
            hosts[i].links[host_idx] = 0;
        }
		hosts[i].collectables = rand()%2;	
	};

	for(int i = 0;i < NUMHOSTS;i++){
		int host_link_count = 0;
		for(int ii = 0;ii < NUMHOSTS;ii++){
            if (host_link_count  >= 4) break; // done!
            if (i == ii) continue;
			int r = rand()%100;
            struct host * host_one = &hosts[i];
            struct host * host_two = &hosts[ii];
			if( r < 25 && 
                host_one->attrib[0] == host_two->attrib[0] && 
                host_one->attrib[1] == host_two->attrib[1]
			   ){
                // 24% change it'll be a link if both attributes match
                host_one->links[host_link_count] = ii;
				host_link_count++;
			} 
            else if(  r < 4 &&  
                (host_one->attrib[0] == host_two->attrib[0] ||
                host_one->attrib[1] == host_two->attrib[1])
			   ){
                // 3% it'll be linked if one attriubte matches
                host_one->links[host_link_count] = ii;
				host_link_count++;
			} 
		}
	}

/*		
	for(int i = 0;i < NUMHOSTS;i++){
        struct host * host_one = &hosts[i];
        if (!host_one->links[0]) {
            printf("no links - %s %s %s\n",
                hosts[i].attrib[0],
                hosts[i].attrib[1],
                hosts[i].attrib[2]);
        }
    }
	for(i = 0;i < NUMHOSTS;i++){
		disp_host(&hosts[i],hosts);
	};
*/
	int curr_host_id = 0;
	int prev_host_id = 0;
	char input = ' ';

	printf("press # to follow link\npress b to return to previous host\n");
	printf("press g to specify host id\npress h to hack\npress l to list botnet\n");
	printf("\npress any key to continue...\n");
	get_input();
	// Main Game Loop
	while(input != 'q'){
        struct host * curr_host = &hosts[curr_host_id];
		clear_screen();
		sleeph(500);

		printf("Host #%d\n",curr_host_id);

		sleeph(500);

		
		disp_host(&hosts[curr_host_id],hosts);
		sleeph(500);
        input = get_input();
		
		if(input == '0' && curr_host->links[0]){
			prev_host_id = curr_host_id;
			curr_host_id = curr_host->links[0];
		} else if(input == '1' && curr_host->links[1]){
			prev_host_id = curr_host_id;
			curr_host_id = curr_host->links[1];
		} else if(input == '2' && curr_host->links[2]){
			prev_host_id = curr_host_id;
			curr_host_id = curr_host->links[2];
		} else if(input == '3' && curr_host->links[3]){
			prev_host_id = curr_host_id;
			curr_host_id = curr_host->links[3];
		} else if(input == 'b'){
			curr_host_id = prev_host_id;
		} else if(input == 'g'){
			prev_host_id = curr_host_id;
			int code;
			printf("Enter code:");
			scanf("%d",&code);
			if(code < NUMHOSTS) curr_host_id = code;
		} else if(input == 'h'){
			if(curr_host->collectables == 1){
                clear_screen();
				printf("\033[%dB", 40); // down
                for (int clock = 0; clock < 100; ++clock) {
                    for (int dot = 0; dot < clock; ++dot) {
                        int rand_position = rand() %40;
                        printf("\r"); // all left
                        printf("\033[%dA", rand_position); // up
                        printf("\033[%dC", rand() %220); // right
                        printf("%c", 48+ rand() % 2);
                        printf("\033[%dB", rand_position);
                        printf("\r"); // all left
                    }
                    printf("\33[A");
                }
				printf("hacking...");
                    //printf("\33[A");
                for (int clock = 0; clock < 100; ++clock) {
                    for (int dot = 0; dot < clock; ++dot) {
                        int rand_position = rand() %40;
                        printf("\r"); // all left
                        printf("\033[%dA", rand_position); // up
                        printf("\033[%dC", rand() %220); // right
                        printf("%c", 33 + rand() % 44);
                        printf("\033[%dB", rand_position); // down
                        printf("\r"); // all left
                    }
					get_input();
                    printf("\33[A");
                }

                printf("Success\n");
                printf("press c to continue");
                while(input != 'c') {
					input = get_input();
                }
		
				hacks += curr_host->collectables;
				curr_host->collectables = 2;
				printf("Hacked.");
				sleeph(1000);
				printf("\nYour botnet size: %d\n",hacks);
				sleeph(1000);
				//printf("upgrade: %s\n",upgrades[rand()%UPGRADES_LEN]);
				//sleeph(2000);
			}
            else {
				printf("Nothing found.");
                get_input();
            }
                
		} else if(input == 'l'){
			int i;
			clear_screen();
			printf("Botnet list:\n");
			for(i = 0;i < NUMHOSTS;i++){
				if(hosts[i].collectables == 2){
				  printf("#%d: %s %s %s\n",i,hosts[i].attrib[0],hosts[i].attrib[1],hosts[i].attrib[2]);
				};
			};
			get_input();
		} else if(input == 'q'){
			/*
			savegame = fopen("cyberspacehunt_save","w");
			fprintf(savegame,"%d",hacks);
			fclose(savegame);
			*/
		};
		
	}// game loop
	return 0;
}
