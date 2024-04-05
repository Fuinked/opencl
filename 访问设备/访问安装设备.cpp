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
			for (unsigned int j = 0; j < num_devices; j++)
			{
				size_t size;
				char* devices_name;
				clGetDeviceInfo(devices[j], CL_DEVICE_NAME, 0, NULL, &size);
				devices_name = new char[ size];
				clGetDeviceInfo(devices[j], CL_DEVICE_NAME, size, devices_name, NULL);
				fout << "设备名称：" << devices_name << endl;
				delete[] devices_name;

				clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, 0, NULL, &size);
				devices_name = new char[size];
				clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR, size, devices_name, NULL);
				fout << "设备厂商：" << devices_name << endl;
				delete[] devices_name;

				clGetDeviceInfo(devices[j], CL_DEVICE_EXTENSIONS, 0, NULL, &size);
				devices_name = new char[ size];
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

				cl_device_type device_type;
				clGetDeviceInfo(devices[j], CL_DEVICE_TYPE, sizeof(cl_device_type), &device_type, NULL);
				if(device_type== CL_DEVICE_TYPE_CPU)
					fout << "设备类型：" << "CL_DEVICE_TYPE_CPU" << endl;
				if(device_type== CL_DEVICE_TYPE_GPU)
					fout << "设备类型：" << "CL_DEVICE_TYPE_GPU" << endl;
				if (device_type == CL_DEVICE_TYPE_ACCELERATOR)
					fout << "设备类型：" << "CL_DEVICE_TYPE_ACCELERATOR " << endl;
				if (device_type == CL_DEVICE_TYPE_CUSTOM)
					fout << "设备类型：" << "CL_DEVICE_TYPE_CUSTOM " << endl;
				if (device_type == CL_DEVICE_TYPE_DEFAULT)
					fout << "设备类型：" << "CL_DEVICE_TYPE_DEFAULT " << endl;



				cl_uint device_id;
				
				clGetDeviceInfo(devices[j], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(cl_uint), &device_id, NULL);
				fout << "设备最大工作频率：" << device_id << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_VENDOR_ID, sizeof(cl_uint), &device_id, NULL);
				fout << "设备编号：" << device_id << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(cl_uint), &device_id, NULL);
				fout << "设备最大计算单元数：" << device_id << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(cl_uint), &device_id, NULL);
				fout << "设备最大工作空间维数：" << device_id << endl;

				
				
				size_t* item_size;
				clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, 0, NULL, &size);
				item_size = new size_t[size];
				clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_ITEM_SIZES, size, item_size, NULL);
				fout << "设备工作组各维度最大大小：" ;
				for (int j = 0; j < size/sizeof(size_t); j++)
				{
					fout << item_size[j] << "		";
				}
				fout << endl;
				delete[] item_size;

				size_t group_size;
				clGetDeviceInfo(devices[j], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(size_t), &group_size, NULL);
				fout << "设备单个计算单元单个工作组最大工作项数：" << group_size << endl;

				cl_uint width_;
				clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_CHAR, sizeof(cl_uint), &width_, NULL);
				fout << "设备单向量偏好的存储的char数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_SHORT, sizeof(cl_uint), &width_, NULL);
				fout << "设备单向量偏好的存储的short数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, sizeof(cl_uint), &width_, NULL);
				fout << "设备单向量偏好的存储的int数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_LONG, sizeof(cl_uint), &width_, NULL);
				fout << "设备单向量偏好的存储的long数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_FLOAT, sizeof(cl_uint), &width_, NULL);
				fout << "设备单向量偏好的存储的float数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint), &width_, NULL);
				fout << "设备单向量偏好的存储的double数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_PREFERRED_VECTOR_WIDTH_HALF, sizeof(cl_uint), &width_, NULL);
				fout << "设备单向量偏好的存储的half数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_NATIVE_VECTOR_WIDTH_CHAR, sizeof(cl_uint), &width_, NULL);
				fout << "设备默认单向量存储的char数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_NATIVE_VECTOR_WIDTH_SHORT, sizeof(cl_uint), &width_, NULL);
				fout << "设备默认单向量存储的short数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, sizeof(cl_uint), &width_, NULL);
				fout << "设备默认单向量存储的int数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_NATIVE_VECTOR_WIDTH_LONG, sizeof(cl_uint), &width_, NULL);
				fout << "设备默认单向量存储的long数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_NATIVE_VECTOR_WIDTH_FLOAT, sizeof(cl_uint), &width_, NULL);
				fout << "设备默认单向量存储的float数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_NATIVE_VECTOR_WIDTH_DOUBLE, sizeof(cl_uint), &width_, NULL);
				fout << "设备默认单向量存储的double数：" << width_ << endl;

				clGetDeviceInfo(devices[j], CL_DEVICE_NATIVE_VECTOR_WIDTH_HALF, sizeof(cl_uint), &width_, NULL);
				fout << "设备默认单向量存储的half数：" << width_ << endl;


			}
			fout << endl;


		}
	}
	return 0;
}