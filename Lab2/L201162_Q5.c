#include<stdio.h>
// Faraz Majid 20L-1162
int main(){

    while (1)
    {
        FILE *ptr = fopen("/proc/stat","r");
        char str[1024];
        int i = 0; //float U = 0; float S = 0; float I = 0; float IO = 0; float N = 0; float IR = 0; float SIR = 0; 
        float total = 0; 
        float useful = 0;

        while (fgets(str,1024,ptr) != 0)
        {
            int user,system,idle,iowait,nice,irq,softirq;


            if (sscanf(str,"cpu %d %d %d %d %d %d %d",&user,&nice,&system,&idle,&iowait,&irq,&softirq) == 7 )
            {
                printf("user: %d nice: %d system: %d idle: %d iowait: %d irq: %d softirq: %d \n",
                        user,nice,system,idle,iowait,irq,softirq
                );
                
                i++;

                if (i == 1)
                {
                    total = system + user + nice + idle + iowait + irq + softirq;
                    double percent;
                    useful = system + user + nice;
                    percent = (useful / total) *100;
                    printf("CPU %f\n",percent);
                }
            }
            
        }
        
    }
    

}