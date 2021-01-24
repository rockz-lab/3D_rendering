#version 430


#define THREADS_X 1024

#define localIndex gl_LocalInvocationIndex


layout(std430, binding = 1) buffer histBuffer
{
    uint histogram[THREADS_X];
};

layout(std430, binding = 2) buffer avgLum
{
    float L_current;
    float L_previous;
    float L_max;
};

uniform int numPixels;
uniform float minLum;
uniform float loglumRange;

shared uint histShared[THREADS_X];

layout (local_size_x = THREADS_X, local_size_y = 1) in;

void main()
{
    //groupMemoryBarrier();
    uint maxIndex = 0;

    uint histCounts = histogram[localIndex];
    histShared[localIndex] = histCounts * localIndex; // values from 0 to 1024, (0 is for dark pixels under a threshold)

    if (histCounts > 0)
    {
        maxIndex = localIndex;
    }

    memoryBarrierShared();
    barrier();

    // Reset the count stored in the buffer in anticipation of the next pass
    histogram[localIndex] = 0;

    
    //groupMemoryBarrier();
    

    memoryBarrierShared();
    barrier();

    /*if (localIndex == 1023)
    {
        histShared[localIndex] *= 500;
    }*/

    

    // add up all the values
    for (uint i = (THREADS_X >> 1); i > 0; i >>= 1)  // (<< uses bit shifting to divide by 2)
    {
        if (localIndex < i)
        {
            histShared[localIndex] += histShared[localIndex + i];
        }
       
        memoryBarrier();
        barrier();
        //groupMemoryBarrier();
    }

    //memoryBarrierShared();
    //barrier();


    memoryBarrier();
    barrier();

    if (localIndex == 0)
    {
        // calulate the Average ( divide by the number of non-black pixels)
        float avgLogLum = (histShared[0]) / max(numPixels - float(histCounts), 1.0) - 1.0; // histCounts is number of black pixels
        float avgLum = exp2( avgLogLum/ (THREADS_X-2.0) * loglumRange + minLum);
       
        float maxLum = exp2(histShared[maxIndex] / (THREADS_X - 2.0) * loglumRange + minLum);

        L_current = avgLum;
        L_max = maxLum;
    }

    
}
