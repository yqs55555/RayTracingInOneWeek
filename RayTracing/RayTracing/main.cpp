#include <fstream>
#include "Vector3.h"
#include "Ray.h"
#include <ctime>
#include <iostream>
#include "Hitable.h"
#include "Sphere.h"
#include "Hitable_list.h"
#include "Camera.h"
#include "Random.h"
#include "Material.h"
#include "Lambertian.h"
#include "Metal.h"
#include "Dielectric.h"
#include <thread>
#include <vector>

//随机生成一个场景
YQS::Hitable *random_scene()
{
	int n = 500;
	YQS::Hitable **list = new YQS::Hitable*[n + 1];		//生成501个球
	list[0] = new YQS::Sphere(YQS::Vector3(0, -1000, 0), 1000, new YQS::Lambertian(YQS::Vector3(0.5f, 0.5f, 0.5f)));
	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			float choose_mat = YQS::drand48();
			YQS::Vector3 center(a + 0.9f * YQS::drand48(), 0.2f, b + 0.9f * YQS::drand48());
			if ((center - YQS::Vector3(4, 0.2f, 0)).length() > 0.9f)
			{
				if (choose_mat < 0.8f)
				{
					list[i++] = new YQS::Sphere(center, 0.2f, new YQS::Lambertian(YQS::Vector3(YQS::drand48() * YQS::drand48(), YQS::drand48() * YQS::drand48(), YQS::drand48() * YQS::drand48())));
				}
				else if (choose_mat < 0.95)
				{
					list[i++] = new YQS::Sphere(center, 0.2f, new YQS::Metal(YQS::Vector3(0.5f*(1 + YQS::drand48()), 0.5f * (1 + YQS::drand48()), 0.5f *(1 + YQS::drand48())), 0.5f * YQS::drand48()));
				}
				else
				{
					list[i++] = new YQS::Sphere(center, 0.2f, new YQS::Dielectric(1.5f));
				}
			}
		}
	}
	list[i++] = new YQS::Sphere(YQS::Vector3(0, 1, 0), 1.0f, new YQS::Dielectric(1.5f));
	list[i++] = new YQS::Sphere(YQS::Vector3(-4, 1, 0), 1.0f, new YQS::Lambertian(YQS::Vector3(0.4f, 0.2f, 0.1f)));
	list[i++] = new YQS::Sphere(YQS::Vector3(4, 1, 0), 1.0f, new YQS::Metal(YQS::Vector3(0.7f, 0.6f, 0.5f), 0.0f));
	return new YQS::Hitable_list(list, i);
}

YQS::Vector3 color(const YQS::Ray &ray, YQS::Hitable* world, int depth)
{
	YQS::Hit_record rec;
	if (world->hit(ray, 0.0001f, FLT_MAX, rec))		//如果光线与场景中的物体发生了碰撞，rec中存储着光线碰撞到的第一个物体
	{
		YQS::Ray scattered;						//经过此次散射后的新光线
		YQS::Vector3 attenuation(1, 1, 1);		//每次散射后光强衰减系数
		if (depth < 200 && rec.mat_ptr->scatter(ray, rec, attenuation, scattered))	//光线最多散射200次
		{
			return attenuation * color(scattered, world, depth + 1);
		}
		else
		{
			return YQS::Vector3(0, 0, 0);
		}
	}
	else
	{
		YQS::Vector3 unit_direction = YQS::Vector3::unit_vector(ray.direction());
		float t = 0.5f * (unit_direction.y() + 1.0f);
		return (1.0f - t) * YQS::Vector3(1.0f, 1.0f, 1.0f) + t * YQS::Vector3(0.5f, 0.7f, 1.0f);
	}
}

int const nx = 800;	//生成图片长度
int const ny = 600;	//生成图片宽度
int ns = 100;		//每个像素需要进行光线追踪的次数
YQS::Vector3 image[nx][ny];
YQS::Camera* camera;

//计算第i+1行第j+1列像素的颜色
void cal_pixel_thread(int i, int j, YQS::Hitable* world)
{
	YQS::Vector3 col(0, 0, 0);
	for (int s = 0; s < ns; s++)
	{
		float u = (i + static_cast<float>(YQS::drand48())) / nx;
		float v = (j + static_cast<float>(YQS::drand48())) / ny;
		YQS::Ray ray = camera->get_ray(u, v);		//获取一条从坐标（u,v）射出的射线
		col += color(ray, world, 0);
	}
	col /= static_cast<float>(ns);
	col = YQS::Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));	//转换到gamma色彩空间下
	image[i][ny - j - 1] = col;
}

int main()
{
	/*
		YQS::Hitable *list[5];	//场景中生成五个物体
		list[0] = new YQS::Sphere(YQS::Vector3(0, 0, -1), 0.5f, new YQS::Lambertian(YQS::Vector3(0.1f, 0.2f, 0.5f)));
		list[1] = new YQS::Sphere(YQS::Vector3(0, -100.5f, -1), 100, new YQS::Lambertian(YQS::Vector3(0.8f, 0.8f, 0.0f)));
		list[2] = new YQS::Sphere(YQS::Vector3(1.0f, 0, -1.0f), 0.5f, new YQS::Metal(YQS::Vector3(0.8f, 0.6f, 0.2f), 0.2f));
		list[3] = new YQS::Sphere(YQS::Vector3(-1.0f, 0, -1.0f), 0.5f, new YQS::Dielectric(1.5f));
		list[4] = new YQS::Sphere(YQS::Vector3(-1.0f, 0, -1.0f), -0.5f, new YQS::Dielectric(1.5f));
	*/
	YQS::Vector3 lookfrom(13, 2, 3);	//摄像机坐标
	YQS::Vector3 lookat(0, 0, 0);		//摄像机朝向
	float dist_to_focus = 10.0f;		//焦距
	float aperture = 0.1f;				//摄像机光圈（孔径）
	YQS::Hitable* world = random_scene();	//随机生成一个场景
	camera = new YQS::Camera(lookfrom, lookat, YQS::Vector3(0, 1, 0), 20, static_cast<float>(nx) / ny, aperture, dist_to_focus);

	std::ofstream outFile;
	YQS::srand48(static_cast<unsigned int>(time(nullptr)));
	clock_t start = clock();	//开始计时
	outFile.open("Chapter12_05_800X600.ppm");
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	std::vector<std::thread*> threads;	//存储所有的像素计算的子线程
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			std::thread* t = new std::thread(cal_pixel_thread, i, j, world);
			threads.push_back(t);
		}
	}
	for (auto it = threads.begin(); it < threads.end(); ++it)
	{
		if((**it).joinable())
		{
			(**it).join();
		}
		else
		{
			--it;
		}
	}
	for (int j = 0; j < ny; j++)
	{
		for (int i = 0; i < nx; i++)
		{
			outFile << static_cast<int>(255.9f * image[i][j].r()) << " " << static_cast<int>(255.9f * image[i][j].g()) << " " << static_cast<int>(255.9f * image[i][j].b()) << " ";
			delete threads.back();
			threads.pop_back();
		}
		outFile << "\n";
	}
	outFile.close();
	clock_t end = clock();
	std::cout << "Total use time：" << end - start / CLOCKS_PER_SEC << "ms" << std::endl;

	delete camera;
	delete world;

	return 0;
}
