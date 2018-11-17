#pragma once

#include "Hitable.h"
namespace YQS
{
	//存储场景中的所有光线碰撞体
	class Hitable_list : public Hitable
	{
	public:
		Hitable_list(Hitable ** list, int size)
			:list(list), list_size(size)
		{
			
		}
		//ray:光线 t_min:光线最短碰撞距离 t_max光线最远碰撞距离 rec光线碰撞到的第一个物体 
		bool hit(const Ray& ray, float t_min, float t_max, Hit_record& rec) const override
		{
			Hit_record temp_rec;
			bool hit_anything = false;
			float closest_so_far = t_max;		//这条光线碰撞到的最近的物体
			for(int i = 0;i < list_size;i++)	//遍历场景中的所有物体
			{
				if(list[i]->hit(ray, t_min, closest_so_far, temp_rec))	//如果这个物体在这条ray的路径上（ray的长度为t_min~closest_so_far）
				{
					hit_anything = true;			//发生碰撞
					closest_so_far = temp_rec.t;	//更新ray的最远碰撞距离
					rec = temp_rec;					//更新rec为光线碰撞到的第一个物体
				}
			}
			return hit_anything;	
		}
		Hitable** list;
		int list_size;
	};
}