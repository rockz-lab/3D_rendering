#version 430

//#extension GL_ARB_compute_shader : enable
//#extension GL_ARB_shader_storage_buffer_object : enable

#define GROUP_SIZE 1024
#define THREADS_X 32
#define THREADS_Y 32




layout (local_size_x = THREADS_X, local_size_y = THREADS_Y) in;

layout (binding = 0, r32f) uniform readonly image2D reducedFrame_in;
layout (binding = 1, r32f) uniform image2D average_out;

shared float localPixels[GROUP_SIZE];



void main()
{
    ivec2 dim = imageSize(reducedFrame_in);

    // simply add up the reduced values

    if ( gl_GlobalInvocationID.x < dim.x && gl_GlobalInvocationID.y < dim.y )       // to make sure, we are in the image bounds
    {
        float luminance = imageLoad(reducedFrame_in, ivec2(gl_GlobalInvocationID.xy)).x;
        localPixels[gl_LocalInvocationIndex] = luminance;
    }
    memoryBarrierShared();
    barrier();

    for (uint i = GROUP_SIZE >> 1; i > 0; i >>= 1)  // (<< uses bit shifting to divide by 2)
    {
        if (uint(gl_LocalInvocationIndex) < i)
        {
            localPixels[gl_LocalInvocationIndex] += localPixels[gl_LocalInvocationIndex + i];
        }
        memoryBarrierShared();
        barrier();
    }
}
