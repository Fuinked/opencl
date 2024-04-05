#include<iostream>
#include<fstream>

#ifdef MAC
#include<OpenCL/cl.h>
#else
#include<CL/cl.h>
#endif
using namespace  std;
int main(void)
{
	cl_platform_id* platform=0;
	cl_uint num_platform;
	cl_uint i;
	cl_int err;
	struct platinfo {
		char* name;
		char* vendor;
		char* version;
		char* extensions;
		char* profile;
	};
	size_t size;
	ofstream fout;
	fout.open("out.txt");
	err = clGetPlatformIDs(10, NULL, &num_platform);
	if (err < 0)
	{
		cout << "无法获取platformids";
		exit(-1);
	}
	
	try 
	{
		platform = new cl_platform_id[sizeof(cl_platform_id) * num_platform];
		//根据平台数分配内存
	}
	catch (std::bad_alloc)
	{
		cout << "分配platform内存失败";
		exit(-1);
	}
	clGetPlatformIDs(num_platform, platform, NULL);
	//获取平台ID
	struct platinfo info = { 0 };
	for (i = 0; i < num_platform; i++)
	{
		clGetPlatformInfo(platform[i], CL_PLATFORM_NAME, 0, NULL, &size);
		//获取平台名称的长度
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
		//获取平台名称

		clGetPlatformInfo(platform[i], CL_PLATFORM_VENDOR, 0, NULL, &size);
		//获取平台厂商名称的长度
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
		//获取平台厂商名称

		clGetPlatformInfo(platform[i], CL_PLATFORM_VERSION, 0, NULL, &size);
		//获取平台支持的最高OPenCL版本的字长
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
		//获取平台支持的最高OPenCL版本

		clGetPlatformInfo(platform[i], CL_PLATFORM_PROFILE, 0, NULL, &size);
		//
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

		clGetPlatformInfo(platform[i], CL_PLATFORM_EXTENSIONS, 0, NULL, &size);
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