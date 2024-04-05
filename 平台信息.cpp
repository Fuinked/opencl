#include<iostream>
#include<fstream>

#ifdef MAC
#include<OpenCL/cl.h>
#else
#include<CL/cl.h>
#endif
using namespace::std;
int main(void)
{
	cl_platform_id* platform=0;
	cl_uint num_platform;
	cl_uint i;
	cl_int err;
	char* ext_data;
	size_t ext_size;
	err = clGetPlatformIDs(10, NULL, &num_platform);
	if (err < 0)
	{
		exit(-1);
	}
	
	try 
	{
		platform = new cl_platform_id[sizeof(cl_platform_id) * num_platform];
	}
	catch (std::bad_alloc)
	{
		cout << "分配platform内存失败";
	}
	clGetPlatformIDs(num_platform, platform, NULL);

	return 0;
}