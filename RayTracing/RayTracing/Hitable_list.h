#pragma once

#include "Hitable.h"
namespace YQS
{
	class Hitable_list : public Hitable
	{
	public:
		Hitable_list(Hitable ** list, int size)
			:list(list), list_size(size)
		{
			
		}

		bool hit(const Ray& ray, float t_min, float t_max, Hit_record& rec) const override
		{
			Hit_record temp_rec;
			bool hit_anything = false;
			float closest_so_far = t_max;
			for(int i = 0;i < list_size;i++)
			{
				if(list[i]->hit(ray, t_min, closest_so_far, temp_rec))
				{
					hit_anything = true;
					closest_so_far = temp_rec.t;
					rec = temp_rec;
				}
			}
			return hit_anything;
		}
		Hitable** list;
		int list_size;
	};
}