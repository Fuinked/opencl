#include<iostream>
#include<fstream>

#ifdef MAC
#include<OpenCL/cl.h>
#else
#include<CL/cl.h>
#endif
using namespace std;
int main(void)
{
	cl_platform_id* platform = 0;
	cl_uint num_platform,num_devices;
	cl_uint i;
	cl_int err;

	cl_device_id* devices;


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
	}
	catch (std::bad_alloc)
	{
		cout << "分配platform内存失败";
		exit(-1);
	}
	clGetPlatformIDs(num_platform, platform, NULL);



	for (i = 0; i < num_platform; i++)
	{
		err = clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_ALL, 1, NULL, &num_devices);
		if (err < 0)
		{
			cout << "无法获取第" << i+1 << "个平台的设备信息。";
			exit(-1);
		}
		else
		{
			try
			{
				devices = new cl_device_id[sizeof(cl_device_id) * num_devices];
			}
			catch (std::bad_alloc)
			{
				cout << "分配devices内存失败";
				exit(-1);
			}
			clGetDeviceIDs(platform[i], CL_DEVICE_TYPE_ALL, num_devices, devices, NULL);
			fout << "平台编号：" << i << endl;
			for (int j = 0; j < num_devices; j++)
			{
				size_t size;
				char* devices_name;
				clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &size);
				devices_name = new char[sizeof(char) * size];
				clGetDeviceInfo(devices[j], CL_DEVICE_NAME, size, devices_name, NULL);
				fout << "设备名称：" << devices_name << endl;
				delete[] devices_name;

				clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, 0, NULL, &size);
				devices_name = new char[sizeof(char) * size];
				clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, size, devices_name, NULL);
				fout << "设备厂商：" << devices_name << endl;
				delete[] devices_name;

				clGetDeviceInfo(devices[j], CL_DEVICE_EXTENSIONS, 0, NULL, &size);
				devices_name = new char[sizeof(char) * size];
				clGetDeviceInfo(devices[j], CL_DEVICE_EXTENSIONS, size, devices_name, NULL);
				fout << "设备拓展：" << devices_name << endl;
				delete[] devices_name;

				cl_ulong mem_size;
				clGetDeviceInfo(devices[j], CL_DEVICE_GLOBAL_MEM_SIZE, sizeof(mem_size), &mem_size, NULL);
				fout << "设备全局内存大小：" << mem_size << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_ADDRESS_BITS, sizeof(mem_size), &mem_size, NULL);
				fout << "设备地址空间大小：" << mem_size << endl;

				cl_bool x;
				clGetDeviceInfo(devices[j], CL_DEVICE_AVAILABLE, sizeof(x), &x, NULL);
				fout << "设备可用性：" << x << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_COMPILER_AVAILABLE, sizeof(x), &x, NULL);
				fout << "设备是否提供编译器：" << x << endl;
			}
			fout << endl;
		}
	}
	return 0;
}