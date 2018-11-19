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

//�������һ������
YQS::Hitable *random_scene()
{
	int n = 500;
	YQS::Hitable **list = new YQS::Hitable*[n + 1];		//����501����
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
	if (world->hit(ray, 0.0001f, FLT_MAX, rec))		//��������볡���е����巢������ײ��rec�д洢�Ź�����ײ���ĵ�һ������
	{
		YQS::Ray scattered;						//�����˴�ɢ�����¹���
		YQS::Vector3 attenuation(1, 1, 1);		//ÿ��ɢ����ǿ˥��ϵ��
		if (depth < 200 && rec.mat_ptr->scatter(ray, rec, attenuation, scattered))	//�������ɢ��200��
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

int const nx = 800;	//����ͼƬ����
int const ny = 600;	//����ͼƬ���
int ns = 100;		//ÿ��������Ҫ���й���׷�ٵĴ���
YQS::Vector3 image[nx][ny];
YQS::Camera* camera;

//�����i+1�е�j+1�����ص���ɫ
void cal_pixel_thread(int i, int j, YQS::Hitable* world)
{
	YQS::Vector3 col(0, 0, 0);
	for (int s = 0; s < ns; s++)
	{
		float u = (i + static_cast<float>(YQS::drand48())) / nx;
		float v = (j + static_cast<float>(YQS::drand48())) / ny;
		YQS::Ray ray = camera->get_ray(u, v);		//��ȡһ�������꣨u,v�����������
		col += color(ray, world, 0);
	}
	col /= static_cast<float>(ns);
	col = YQS::Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));	//ת����gammaɫ�ʿռ���
	image[i][ny - j - 1] = col;
}

int main()
{
	/*
		YQS::Hitable *list[5];	//�����������������
		list[0] = new YQS::Sphere(YQS::Vector3(0, 0, -1), 0.5f, new YQS::Lambertian(YQS::Vector3(0.1f, 0.2f, 0.5f)));
		list[1] = new YQS::Sphere(YQS::Vector3(0, -100.5f, -1), 100, new YQS::Lambertian(YQS::Vector3(0.8f, 0.8f, 0.0f)));
		list[2] = new YQS::Sphere(YQS::Vector3(1.0f, 0, -1.0f), 0.5f, new YQS::Metal(YQS::Vector3(0.8f, 0.6f, 0.2f), 0.2f));
		list[3] = new YQS::Sphere(YQS::Vector3(-1.0f, 0, -1.0f), 0.5f, new YQS::Dielectric(1.5f));
		list[4] = new YQS::Sphere(YQS::Vector3(-1.0f, 0, -1.0f), -0.5f, new YQS::Dielectric(1.5f));
	*/
	YQS::Vector3 lookfrom(13, 2, 3);	//���������
	YQS::Vector3 lookat(0, 0, 0);		//���������
	float dist_to_focus = 10.0f;		//����
	float aperture = 0.1f;				//�������Ȧ���׾���
	YQS::Hitable* world = random_scene();	//�������һ������
	camera = new YQS::Camera(lookfrom, lookat, YQS::Vector3(0, 1, 0), 20, static_cast<float>(nx) / ny, aperture, dist_to_focus);

	std::ofstream outFile;
	YQS::srand48(static_cast<unsigned int>(time(nullptr)));
	clock_t start = clock();	//��ʼ��ʱ
	outFile.open("Chapter12_05_800X600.ppm");
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	std::vector<std::thread*> threads;	//�洢���е����ؼ�������߳�
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
	std::cout << "Total use time��" << end - start / CLOCKS_PER_SEC << "ms" << std::endl;

	delete camera;
	delete world;

	return 0;
}
