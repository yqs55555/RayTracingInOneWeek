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

YQS::Vector3 color(const YQS::Ray &ray, YQS::Hitable* world, int depth)
{
	YQS::Hit_record rec;
	if (world->hit(ray, 0.5f, FLT_MAX, rec))
	{
		YQS::Ray scattered;
		YQS::Vector3 attenuation;
		if (depth < 100 && rec.mat_ptr->scatter(ray, rec, attenuation, scattered))
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

int main()
{
	int nx = 800;
	int ny = 400;
	int ns = 100;

	YQS::Hitable *list[5];
	list[0] = new YQS::Sphere(YQS::Vector3(0, 0, -1), 0.5f, new YQS::Lambertian(YQS::Vector3(0.8f, 0.3f, 0.3f)));
	list[1] = new YQS::Sphere(YQS::Vector3(0, -100.5f, -1), 100, new YQS::Lambertian(YQS::Vector3(0.8f, 0.8f, 0.0f)));
	list[2] = new YQS::Sphere(YQS::Vector3(1.0f, 0, -1.0f), 0.5f, new YQS::Metal(YQS::Vector3(0.8f, 0.6f, 0.2f), 0.3f));
	list[3] = new YQS::Sphere(YQS::Vector3(-1.0f, 0, -1.0f), 0.5f, new YQS::Dielectric(1.5f));
	list[4] = new YQS::Sphere(YQS::Vector3(-1.0f, 0, -1.0f), -0.45f, new YQS::Dielectric(1.5f));
	YQS::Hitable* world = new YQS::Hitable_list(list, 4);
	YQS::Camera camera;

	std::ofstream outFile;
	YQS::srand48(static_cast<unsigned int>(time(nullptr)));
	clock_t start = clock();
	outFile.open("world_6.ppm");
	outFile << "P3\n" << nx << " " << ny << "\n255\n";
	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			YQS::Vector3 col(0, 0, 0);
			for (int s = 0; s < ns; s++)
			{
				float u = (i + static_cast<float>(YQS::drand48())) / nx;
				float v = (j + static_cast<float>(YQS::drand48())) / ny;
				YQS::Ray ray = camera.get_ray(u, v);
				col += color(ray, world, 0);
			}
			col /= static_cast<float>(ns);
			col = YQS::Vector3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			outFile << static_cast<int>(255.9f * col.r()) << " " << static_cast<int>(255.9f * col.g()) << " " << static_cast<int>(255.9f * col.b()) << " ";
		}
		outFile << "\n";
	}
	outFile.close();
	clock_t end = clock();
	std::cout << end - start / CLOCKS_PER_SEC << "ms" << std::endl;

	return 0;
}
