#include <iostream>

#define REVERB_FADE_THRESH 10   
#define DELAY_BUFSIZ ( 50L * ST_MAXRATE )   
#define MAXREVERBS 8   

class reverb {   
    private:
        int counter;               
        int numdelays;   
        float   *buffer;   
        float   in_gain, out_gain, time;   
        float   delay[MAXREVERBS], decay[MAXREVERBS];   
        long    samples[MAXREVERBS], maxsamples;   
        st_sample_t pl, ppl, pppl; 

    public:
        reverb(eff_t effp, int n, char **argv) {   
            int i;   
    
            this.numdelays = 0;   
            this.maxsamples = 0;   
    
            if ( (n < 3) || (n - 2 > MAXREVERBS) )   
            {  
                std::cerr << "Please choose delay number between 3 and 6"; 
                return;   
            }   
        
            i = 0;   
            sscanf(argv[i++], "%f", &reverb->out_gain);   
            sscanf(argv[i++], "%f", &reverb->time);   
            while (i < n) {   
                /* Linux bug and it's cleaner. */   
                sscanf(argv[i++], "%f", &reverb->delay[reverb->numdelays]);   
                reverb->numdelays++;   
            }   
            return (ST_SUCCESS);   
        }   
   
/*  
 * Prepare for processing.  
 */   
int st_reverb_start(eff_t effp)   
{   
    reverb_t reverb = (reverb_t) effp->priv;   
    int i;   
   
    reverb->in_gain = 1.0;   
   
    if ( reverb->out_gain < 0.0 )   
    {   
        st_fail("reverb: gain-out must be positive");   
        return (ST_EOF);   
    }   
    if ( reverb->out_gain > 1.0 )   
        st_warn("reverb: warnig >>> gain-out can cause saturation of output <<<");   
    if ( reverb->time < 0.0 )   
    {   
        st_fail("reverb: reverb-time must be positive");   
        return (ST_EOF);   
    }   
    for(i = 0; i < reverb->numdelays; i++) {   
        reverb->samples[i] = reverb->delay[i] * effp->ininfo.rate / 1000.0;   
        if ( reverb->samples[i] < 1 )   
        {   
            st_fail("reverb: delay must be positive!\n");   
            return (ST_EOF);   
        }   
        if ( reverb->samples[i] > DELAY_BUFSIZ )   
        {   
            st_fail("reverb: delay must be less than %g seconds!\n",   
                DELAY_BUFSIZ / (float) effp->ininfo.rate );   
            return(ST_EOF);   
        }   
        /* Compute a realistic decay */   
        reverb->decay[i] = (float) pow(10.0,(-3.0 * reverb->delay[i] / reverb->time));   
        if ( reverb->samples[i] > reverb->maxsamples )   
            reverb->maxsamples = reverb->samples[i];   
    }   
    if (! (reverb->reverbbuf = (float *) malloc(sizeof (float) * reverb->maxsamples)))   
    {   
        st_fail("reverb: Cannot malloc %d bytes!\n",    
            sizeof(float) * reverb->maxsamples);   
        return(ST_EOF);   
    }   
    for ( i = 0; i < reverb->maxsamples; ++i )   
        reverb->reverbbuf[i] = 0.0;   
    reverb->pppl = reverb->ppl = reverb->pl = 0x7fffff;        /* fade-outs */   
    reverb->counter = 0;   
    /* Compute the input volume carefully */   
    for ( i = 0; i < reverb->numdelays; i++ )   
        reverb->in_gain *=    
            ( 1.0 - ( reverb->decay[i] * reverb->decay[i] ));   
    return (ST_SUCCESS);   
}   
   
/*  
 * Processed signed long samples from ibuf to obuf.  
 * Return number of samples processed.  
 */   
int st_reverb_flow(eff_t effp, st_sample_t *ibuf, st_sample_t *obuf,    
                   st_size_t *isamp, st_size_t *osamp)   
{   
    reverb_t reverb = (reverb_t) effp->priv;   
    int len, done;   
    int i, j;   
       
    float d_in, d_out;   
    st_sample_t out;   
   
    i = reverb->counter;   
    len = ((*isamp > *osamp) ? *osamp : *isamp);   
    for(done = 0; done < len; done++) {   
        /* Store delays as 24-bit signed longs */   
        d_in = (float) *ibuf++ / 256;   
        d_in = d_in * reverb->in_gain;   
        /* Mix decay of delay and input as output */   
        for ( j = 0; j < reverb->numdelays; j++ )   
            d_in +=   
reverb->reverbbuf[(i + reverb->maxsamples - reverb->samples[j]) % reverb->maxsamples] * reverb->decay[j];   
        d_out = d_in * reverb->out_gain;   
        out = st_clip24((st_sample_t) d_out);   
        *obuf++ = out * 256;   
        reverb->reverbbuf[i] = d_in;   
        i++;        /* XXX need a % maxsamples here ? */   
        i %= reverb->maxsamples;   
    }   
    reverb->counter = i;   
    /* processed all samples */   
    return (ST_SUCCESS);   
}   
   
/*  
 * Drain out reverb lines.   
 */   
int st_reverb_drain(eff_t effp, st_sample_t *obuf, st_size_t *osamp)   
{   
    reverb_t reverb = (reverb_t) effp->priv;   
    float d_in, d_out;   
    st_sample_t out, l;   
    int i, j, done;   
   
    i = reverb->counter;   
    done = 0;   
    /* drain out delay samples */   
    do {   
        d_in = 0;   
        d_out = 0;   
        for ( j = 0; j < reverb->numdelays; ++j )   
            d_in +=    
reverb->reverbbuf[(i + reverb->maxsamples - reverb->samples[j]) % reverb->maxsamples] * reverb->decay[j];   
        d_out = d_in * reverb->out_gain;   
        out = st_clip24((st_sample_t) d_out);   
        obuf[done++] = out * 256;   
        reverb->reverbbuf[i] = d_in;   
        l = st_clip24((st_sample_t) d_in);   
        reverb->pppl = reverb->ppl;   
        reverb->ppl = reverb->pl;   
        reverb->pl = l;   
        i++;        /* need a % maxsamples here ? */   
        i %= reverb->maxsamples;   
    } while((done < *osamp) &&    
        ((abs(reverb->pl) + abs(reverb->ppl) + abs(reverb->pppl)) > REVERB_FADE_THRESH));   
    reverb->counter = i;   
    *osamp = done;   
    return (ST_SUCCESS);   
}   
   
/*  
 * Clean up reverb effect.  
 */   
int st_reverb_stop(eff_t effp)   
{   
    reverb_t reverb = (reverb_t) effp->priv;   
   
    free((char *) reverb->reverbbuf);   
    reverb->reverbbuf = (float *) -1;   /* guaranteed core dump */   
    return (ST_SUCCESS);   
}   
  
};

