#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>

#define BUF_LEN 80


int main()
{
    int file_desc, ret_val, i, time_temp;
    float velocity, time;
    char tmp[BUF_LEN];
    char tm1[BUF_LEN];
    
    double r;
    printf("Uneti poluprecnik u cm: ");
    scanf("%lf", &r);
    
    while(1){
        file_desc = open("/dev/gpio_driver", O_RDWR);

        if(file_desc < 0){
            int err = errno;
            printf("Error, 'dummy' not opened: %d %d\n",file_desc, err);
            return -1;
        }
        
        memset(tmp, 0, BUF_LEN);
        
        ret_val = read(file_desc, tmp, BUF_LEN);
        if(ret_val != -1){
            for(i = 0; i<BUF_LEN; i++){
                if(tmp[i] == '\n')
                    break;
                tm1[i] = tmp[i];
            }
            
            time_temp = atoi(tm1);//vreme u us
            time = time_temp / 1000000.0;//vreme u s
            
            velocity = (2*3.14*(r/100))/time;
            
            printf("Vreme je: %f\n", time);
            
            printf("Brzina: %f\n", velocity);
        
        }else{
            printf("Error: 'gpio_driver' read problem\n");
            return -1;
        }
    
        /* Close dummy file. */
    
        close(file_desc);
    }
    
    
    return 0;
}
