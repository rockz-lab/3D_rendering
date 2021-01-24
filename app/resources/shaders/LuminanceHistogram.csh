#version 430

#define GROUP_SIZE 1024
#define THREADS_X 32
#define THREADS_Y 32

#define RGB_TO_LUM vec3(0.2126, 0.7152, 0.0722)
#define EPSILON 0.005

#define threadID gl_LocalInvocationIndex

layout (local_size_x = THREADS_X, local_size_y = THREADS_Y) in;

layout (binding = 0, rgba16f) uniform readonly image2D LDR_frame;

layout(std430, binding = 1) coherent restrict buffer histBuffer
{
    uint histogram[GROUP_SIZE];
};

uniform float minLum;
uniform float inverseLoglumRange;   // inverted so it can be multiplied?

shared uint histShared[GROUP_SIZE];


uint colorToBin(vec3 hdrColor, float minLogLum, float inverseLogLumRange) {
  // Convert our RGB value to Luminance, see note for RGB_TO_LUM macro above
  float lum = dot(hdrColor, RGB_TO_LUM);    // Transform Luminance as dot product

  // Avoid taking the log of zero
  if (lum < EPSILON) {
    return 0;
  }

  // Calculate the log_2 luminance and express it as a value in [0.0, 1.0]
  // where 0.0 represents the minimum luminance, and 1.0 represents the max.
  float logLum = clamp((log2(lum) - minLogLum) * inverseLogLumRange, 0.0, 1.0);

  //float logLum = ( (lum - minLogLum) * inverseLogLumRange * 1022.0 + 1.0 );
  // Map [0, 1] to [1, 255]. The zeroth bin is handled by the epsilon check above.
  return uint(logLum * (float(GROUP_SIZE)-2.0) + 1.0);
  //return uint(1024 - 2);
}


void main()
{
    // Initialize the bin for this thread to 0
    
    //histogram[gl_WorkGroupID] = 0
    histShared[threadID] = 0;

    ivec2 dim = imageSize(LDR_frame);
    //groupMemoryBarrier();
    //memoryBarrierShared();
    //barrier();

    memoryBarrier();
    barrier();

    if ( gl_GlobalInvocationID.x < dim.x && gl_GlobalInvocationID.y < dim.y )       // to make sure, we are in the image bounds
    {
        vec3 hdrColor = imageLoad(LDR_frame, ivec2(gl_GlobalInvocationID.xy) ).xyz;
        uint binIndex = colorToBin(hdrColor, minLum, inverseLoglumRange);
        //uint binIndex = 10;
        atomicAdd(histShared[binIndex], 1);
        //atomicAdd(histShared[0], uint( dot(hdrColor, RGB_TO_LUM)) );
        //histShared[0] = 1000000;

    }

    memoryBarrier();
    barrier();


    //histogram[1022] = 100;
    //uint a = histShared[gl_LocalInvocationIndex];
    atomicAdd(histogram[threadID], histShared[threadID]);

    memoryBarrier();
    barrier();
    //histogram[gl_LocalInvocationIndex] = histShared[gl_LocalInvocationIndex];
}
