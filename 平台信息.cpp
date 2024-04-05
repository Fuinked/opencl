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
	ofstream fout;
	fout.open("out.txt");
	struct platinfo {
		char* name;
		char* vendor;
		char* version;
		char* profile;
		char* extensions;
	};
	size_t size;
	err = clGetPlatformIDs(10, NULL, &num_platform);
	if (err < 0)
	{
		cout << "无法获取platformids";
		exit(-1);
	}
	
	try 
	{
		platform = new cl_platform_id[sizeof(cl_platform_id) * num_platform];
	}
	catch (std::bad_alloc)
	{
		cout << "分配platform内存失败";
		exit(-1);
	}
	clGetPlatformIDs(num_platform, platform, NULL);
	struct platinfo info = { 0 };
	for (i = 0; i < num_platform; i++)
	{
		clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, NULL, NULL, &size);
		try 
		{
			info.name = new char[sizeof(char) * size];
		}
		catch (std::bad_alloc)
		{
			cout << "info.name内存分配失败";
			exit(-1);
		}
		clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, size, info.name, NULL);

		clGetPlatformInfo(platform[i], CL_PLATFORM_VENDOR, NULL, NULL, &size);
		try
		{
			info.vendor = new char[sizeof(char) * size];
		}
		catch (std::bad_alloc)
		{
			cout << "info.vendor内存分配失败";
			exit(-1);
		}
		clGetPlatformInfo(platform[i], CL_PLATFORM_VENDOR, size, info.vendor, NULL);

		clGetPlatformInfo(platform[i], CL_PLATFORM_VERSION, NULL, NULL, &size);
		try
		{
			info.version = new char[sizeof(char) * size];
		}
		catch (std::bad_alloc)
		{
			cout << "info.version内存分配失败";
			exit(-1);
		}
		clGetPlatformInfo(platform[i], CL_PLATFORM_VERSION, size, info.version, NULL);

		clGetPlatformInfo(platform[i], CL_PLATFORM_PROFILE, NULL, NULL, &size);
		try
		{
			info.profile = new char[sizeof(char) * size];
		}
		catch (std::bad_alloc)
		{
			cout << "info.profile内存分配失败";
			exit(-1);
		}
		clGetPlatformInfo(platform[i], CL_PLATFORM_PROFILE, size, info.profile, NULL);

		clGetPlatformInfo(platform[i], CL_PLATFORM_EXTENSIONS, NULL, NULL, &size);
		try
		{
			info.extensions = new char[sizeof(char) * size];
		}
		catch (std::bad_alloc)
		{
			cout << "info.extensions内存分配失败";
			exit(-1);
		}
		clGetPlatformInfo(platform[i], CL_PLATFORM_EXTENSIONS, size, info.extensions, NULL);

		fout << "平台名称：" << info.name<<endl;
		fout << "平台厂商：" << info.vendor << endl;
		fout << "最高OPenCL版本：" << info.version << endl;
		fout << "支持的完整性：" << info.profile << endl;
		fout << "支持的拓展名列表：" << info.extensions << endl << endl;


	}

	return 0;
}