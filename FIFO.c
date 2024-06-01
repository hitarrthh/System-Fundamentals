
 #include <stdio.h>  
    void main()  
    {  
        int incomingStream[] = {1 , 3 , 0 , 3 , 5, 6};  
        int pf = 0, ph = 0;  
        int frames = 3;  
        int m, n, s, pages;   
        pages = sizeof(incomingStream)/sizeof(incomingStream[0]);   
        
        int temp[ frames ];  
        for(m = 0; m < frames; m++)  
        {  
            temp[m] = -1;  
        }  
        for(m = 0; m < pages; m++)  
        {  
            s = 0;   
            for(n = 0; n < frames; n++)  
            {  
                if(incomingStream[m] == temp[n])  
                {  
                    s++;  
                    pf--;  
                }  
            }  
            pf++;  
            if((pf <= frames) && (s == 0))  
            {  
                temp[m] = incomingStream[m];  
            }  
            else if(s == 0)  
            {  
                temp[(pf - 1) % frames] = incomingStream[m];  
            }  
            
            
        }  
        printf("\nTOTAL PAGE FAULTS:\t%d\n", pf);
        printf("\nHIT RATIO:\t%d/6\n", (6-pf));

    }  
