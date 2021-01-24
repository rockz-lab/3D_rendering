#version 430

//#extension GL_ARB_compute_shader : enable
//#extension GL_ARB_shader_storage_buffer_object : enable

#define GROUP_SIZE 1024
#define THREADS_X 32
#define THREADS_Y 32




layout (local_size_x = THREADS_X, local_size_y = THREADS_Y) in;

layout (binding = 0, rgba32f) uniform readonly image2D LDR_frame;
layout (binding = 1, r32f) uniform image2D reducedFrame;

shared float localPixels[GROUP_SIZE];


float Luminance(vec3 c)
{
    return 0.2126 * c.x + 0.7152 * c.y + 0.0722 * c.z;
}

void main()
{
    ivec2 dim = imageSize(LDR_frame);

    // Load the image Data into shared memory
    // calculate the log luminance
    if ( gl_GlobalInvocationID.x < dim.x && gl_GlobalInvocationID.y < dim.y )       // to make sure, we are in the image bounds
    {
        ivec2 index = ivec2(gl_WorkGroupID.xy)*ivec2(THREADS_X*2, THREADS_Y) + ivec2(gl_LocalInvocationID.xy);
        vec3 hdrColor_1 = imageLoad(LDR_frame, index).xyz;
        vec3 hdrColor_2 = imageLoad(LDR_frame, index + ivec2(THREADS_X, THREADS_Y)).xyz;
        localPixels[gl_LocalInvocationIndex] = log2(Luminance(hdrColor_1)) + log2(Luminance(hdrColor_2));
    }
    memoryBarrierShared();
    barrier();


    // now, add the Values in shared memory using sequential Adressing:
    // [----,----]  i = 4
    // [--,--]      i = 2
    // [-,-]        i = 1

    for (uint i = GROUP_SIZE >> 1; i > 0; i >>= 1)  // (<< uses bit shifting to divide by 2)
    {
        if (uint(gl_LocalInvocationIndex) < i)
        {
            localPixels[gl_LocalInvocationIndex] += localPixels[gl_LocalInvocationIndex + i];
        }
        memoryBarrierShared();
        barrier();
    }

    //avgResult += localPixels[0];

    //memoryBarrierShared();
    //barrier();

    if (gl_LocalInvocationID.x == 0)
    {
        imageStore(reducedFrame, ivec2(gl_WorkGroupID.xy), vec4(localPixels[0], 0, 0, 0));
    }


    //groupMemoryBarrier();
    //ivec2 storePos = ivec2(gl_GlobalInvocationID.xy);
    //float localCoef = length(vec2(ivec2(gl_LocalInvocationID.xy)-8)/8.0);
    //float globalCoef = sin(float(gl_WorkGroupID.x+gl_WorkGroupID.y)*0.1 + roll)*0.5;
    //imageStore(destTex, storePos, vec4(1.0-globalCoef*localCoef, 0.0, 0.0, 0.0));
}
